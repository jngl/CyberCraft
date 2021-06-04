#include "TextureManager.h"

#include <Core/Engine.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include <algorithm>
#include <iostream>
#include <string>

constexpr int windowSizeXDefault = 1024;
constexpr int windowSizeYDefault = 768;



cc::Vector2f generateWindowViewSize(int windowX, int windowY){
    constexpr float minSize = 100;

    if(windowX > windowY){
        return {
            minSize * static_cast<float>(windowX)  / static_cast<float>(windowY),
            minSize
        };
    }

    return {
            minSize,
            minSize * static_cast<float>(windowY) / static_cast<float>(windowX)
    };
}

class BgfxFrame final : public cc::ColoredRectangleDrawer, public cc::NonCopyable {
public:
    friend class MyBgfxContext;

    ~BgfxFrame() final{
        bgfx::frame();
    }

    void drawRectangle(const cc::Vector2f& pos, const cc::Vector2f& size, const cc::Color& color) override{
        bgfx::dbgTextPrintf(0, 0, 0x0f, "rect : %.2f %.2f %.2f %.2f %i %i %i %i", pos.x, pos.y, size.x, size.y, (int)color.red, (int)color.green, (int)color.blue, (int)color.alpha);

//        cc::Vector2f size2 = size / 2.f;
//
//        glBegin(GL_QUADS);
//        glColor3ub(color.red, color.green, color.blue);
//        glVertex2f(pos.x + size2.x, pos.y + size2.y);
//        glVertex2f(pos.x + size2.x, pos.y - size2.y);
//        glVertex2f(pos.x - size2.x, pos.y - size2.y);
//        glVertex2f(pos.x - size2.x, pos.y + size2.y);
//        glEnd();
    }

private:
    BgfxFrame(){
//        glViewport(0, 0, windowX, windowY);
//        glClearColor(0.f, 0.f, 0.f, 0.f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        cc::Vector2f view = generateWindowViewSize(windowX, windowY);
//
//        glPushMatrix();
//        glOrtho(-view.x / 2.f, view.x / 2.f, -view.y/2.f, view.y/2.f, -1, 1);
    }
};

class SystemError : public std::exception
{
public:
    SystemError(std::string_view msg)
    {
        m_message = std::string("System Error : ") + std::string(msg);
    }


    [[nodiscard]] const char* what() const noexcept override{
        return m_message.c_str();
    }

private:
    std::string m_message;
};

class MySdlWindow {
public:
    MySdlWindow(){
        if(SDL_Init(0) != 0){
            throw SystemError{SDL_GetError()};
        }

        m_window = SDL_CreateWindow("OpenGL Test", 0, 0, windowSizeXDefault, windowSizeYDefault, SDL_WINDOW_RESIZABLE);
        if (m_window == nullptr) {
            throw SystemError{SDL_GetError()};
        }
    }

    ~MySdlWindow(){
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    SDL_Window* GetSdlWindow(){
        return m_window;
    }

    void swap(){
        SDL_GL_SwapWindow(m_window);
    }

    void* sdlNativeWindowHandle()
    {
        SDL_SysWMinfo wmi;
        SDL_VERSION(&wmi.version);
        if (!SDL_GetWindowWMInfo(m_window, &wmi) )
        {
            return NULL;
        }

#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#		if ENTRY_CONFIG_USE_WAYLAND
        wl_egl_window *win_impl = (wl_egl_window*)SDL_GetWindowData(_window, "wl_egl_window");
		if(!win_impl)
		{
			int width, height;
			SDL_GetWindowSize(_window, &width, &height);
			struct wl_surface* surface = wmi.info.wl.surface;
			if(!surface)
				return nullptr;
			win_impl = wl_egl_window_create(surface, width, height);
			SDL_SetWindowData(_window, "wl_egl_window", win_impl);
		}
		return (void*)(uintptr_t)win_impl;
#		else
        return (void*)wmi.info.x11.window;
#		endif
#	elif BX_PLATFORM_OSX
        return wmi.info.cocoa.window;
#	elif BX_PLATFORM_WINDOWS
		return wmi.info.win.window;
#	endif // BX_PLATFORM_
    }

    [[nodiscard]] cc::Vector2i getSize() const {
        cc::Vector2i result;
        SDL_GetWindowSize(m_window, &result.x, &result.y);
        return result;
    }

private:
    SDL_Window *m_window;
};

class MyBgfxContext{
public:
    explicit MyBgfxContext(MySdlWindow& win):
            m_window(win){
        sdlSetWindow(win);

        m_size = win.getSize();

        bgfx::renderFrame();

        bgfx::Init init;
     //   init.type = bgfx::RendererType::OpenGL;
        init.resolution.width  = m_size.x;
        init.resolution.height = m_size.y;
        bgfx::init(init);

        bgfx::setDebug(BGFX_DEBUG_TEXT);

        bgfx::setViewClear(0
                , BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
                , 0x303030ff
                , 1.0f
                , 0
        );
    }

    BgfxFrame beginFrame(){
        cc::Vector2i  newSize = m_window.getSize();

        if(newSize.x != m_size.x || newSize.y != m_size.y){
            std::cout<<"resize "<<newSize.x<<" "<<newSize.y<<std::endl;
            bgfx::reset((uint32_t)newSize.x, (uint32_t)newSize.y);
            m_size = newSize;
        }

        bgfx::setViewRect(0, 0, 0, uint16_t(m_size.x), uint16_t(m_size.y) );
        bgfx::touch(0);

        bgfx::dbgTextClear();
        bgfx::dbgTextPrintf(0, 1, 0x0f, "win : %i %i", m_size.x, m_size.y);


        return BgfxFrame();
    }

private:
    MySdlWindow& m_window;
    cc::Vector2i m_size;

    inline bool sdlSetWindow(MySdlWindow& win)
    {
        SDL_SysWMinfo wmi;
        SDL_VERSION(&wmi.version);
        if (!SDL_GetWindowWMInfo(win.GetSdlWindow(), &wmi) )
        {
            return false;
        }

        bgfx::PlatformData pd;
#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#		if ENTRY_CONFIG_USE_WAYLAND
        pd.ndt          = wmi.info.wl.display;
#		else
        pd.ndt          = wmi.info.x11.display;
#		endif
#	elif BX_PLATFORM_OSX
        pd.ndt          = NULL;
#	elif BX_PLATFORM_WINDOWS
		pd.ndt          = NULL;
#	endif // BX_PLATFORM_
        pd.nwh          = win.sdlNativeWindowHandle();

        pd.context      = NULL;
        pd.backBuffer   = NULL;
        pd.backBufferDS = NULL;
        bgfx::setPlatformData(pd);

        return true;
    }
};

class GameLoader
{
public:
    GameLoader(){
        reload();
    }

    ~GameLoader(){
        SDL_UnloadObject(m_gameCodeHandle);
    }

    void reload(){
        std::cout<<"Reload"<<std::endl;

        m_game.reset();

        using Func = cc::GameBase*(*)();

        void* handle = SDL_LoadObject("./libDemo.so");
        if(handle == nullptr){
            throw SystemError{SDL_GetError()};
        }

        Func creator = (Func)SDL_LoadFunction(handle, "createGame"); // NOLINT
        if(creator == nullptr){
            throw SystemError{SDL_GetError()};
        }

        m_game = std::unique_ptr<cc::GameBase>(creator());
    }

    cc::GameBase& getGame(){
        return *m_game;
    }

    const cc::GameBase& getGame() const{
        return *m_game;
    }

    void processEvent(){
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            switch(event.type){
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    processKey(event.key);
                    break;
                case SDL_QUIT:
                    m_game->exit();
                    break;
                default:
                    break;
            }
        }
    }

private:
    std::unique_ptr<cc::GameBase> m_game;
    void* m_gameCodeHandle;

    static cc::Key keyFromSdlKey(SDL_Keycode sdlKey){
        switch (sdlKey){
            case SDLK_ESCAPE:
                return cc::Key::ESCAPE;
            case SDLK_UP:
                return cc::Key::UP;
            case SDLK_DOWN:
                return cc::Key::DOWN;
            case SDLK_LEFT:
                return cc::Key::LEFT;
            case SDLK_RIGHT:
                return cc::Key::RIGHT;
            case SDLK_F1:
                return cc::Key::F1;
            case SDLK_F2:
                return cc::Key::F2;
            case SDLK_F3:
                return cc::Key::F3;
            case SDLK_F4:
                return cc::Key::F4;
            case SDLK_F5:
                return cc::Key::F5;
            case SDLK_F6:
                return cc::Key::F6;
            case SDLK_F7:
                return cc::Key::F7;
            case SDLK_F8:
                return cc::Key::F8;
            case SDLK_F9:
                return cc::Key::F9;
            case SDLK_F10:
                return cc::Key::F10;
            case SDLK_F11:
                return cc::Key::F11;
            case SDLK_F12:
                return cc::Key::F12;
            default:
                return cc::Key::UNKNOWN;
        }
    }

    void processKey(SDL_KeyboardEvent& keyEvent){
        cc::Key key = keyFromSdlKey(keyEvent.keysym.sym);
        if(keyEvent.type == SDL_KEYDOWN){
            if(key == cc::Key::F5){
                reload();
            }
            m_game->processKeyDown(key);
        }else if(keyEvent.type == SDL_KEYUP){
            m_game->processKeyUp(key);
        }
    }

};

class SystemState{
public:
    SystemState(): m_context(m_window) {}

    [[nodiscard]] bool isRunning() const{
        return m_gameLoader.getGame().isRunning();
    }

    void frame(){
        m_gameLoader.processEvent();
        m_gameLoader.getGame().updateMultiFrameAction();

        BgfxFrame renderer= m_context.beginFrame();
        m_gameLoader.getGame().render(renderer);
    }

private:
    MySdlWindow m_window;
    MyBgfxContext m_context;
    TextureManager m_textures;
    GameLoader m_gameLoader;
};

int main () {
    try{
        SystemState systemState;

        while(systemState.isRunning()){
            systemState.frame();
        }

        return 0;
    }catch(const std::exception& e){
        std::cout<<e.what()<<std::endl;
        return 1;
    }
}
