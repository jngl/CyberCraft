//
// Created by jngl on 03/10/2020.
//

#include "System/Window.h"


#include <Core/Debug.h>
#include <iostream>
#include <glad/glad.h>
#include <imgui.h>
#include "imgui_impl_sdl_gl3.h"

#ifdef GLAD_DEBUG
void pre_gl_call(const char *name, void *funcptr, int len_args, ...) {
    printf("Calling: %s (%d arguments)\n", name, len_args);
}
#endif

constexpr int glMajorVersion = 3;
constexpr int glMinorVersion = 2;
constexpr int doubleBuffer = 1;
constexpr int depthSize = 24;

namespace cs {
    Window::Window(int width, int height) :
            mOpen(true),
            mWindow(nullptr) {
        cc::log("Window", "construct");
        //init sdl
        int error = SDL_Init(SDL_INIT_VIDEO);
        cc::check("Window", error == 0, "SDL_Init Error: ", SDL_GetError());

        // OpenGL 3.2
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, glMajorVersion);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, glMinorVersion);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        // Double Buffer
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, doubleBuffer);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, depthSize);

        //sdl window
        mWindow = SDL_CreateWindow("Cyber engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,  // NOLINT
                                   SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        cc::check("Window", mWindow != nullptr, "SDL_CreateWindow Error: ", SDL_GetError());

        // opengl contex
        mGLContext = SDL_GL_CreateContext(mWindow);
        cc::check("Window", mGLContext != nullptr, "SDL_GL_CreateContext Error: ", SDL_GetError());

        SDL_GL_MakeCurrent(mWindow, mGLContext);

        //glad
        cc::check("Window", gladLoadGL() != 0, "Something went wrong with glad");

#ifdef GLAD_DEBUG
        // before every opengl call call pre_gl_call
        // glad_set_pre_callback(pre_gl_call);
        // don't use the callback for glClear
        // (glClear could be replaced with your own function)
        glad_debug_glClear = glad_glClear;
#endif

        ImGui_ImplSdlGL3_Init(mWindow);

        cc::log("Window", "OpenGL ", GLVersion.major, ".", GLVersion.minor, ", GLSL ",
                    glGetString(GL_SHADING_LANGUAGE_VERSION));

        glViewport(0, 0, width, height);
        mResize = true;
    }

    Window::~Window() {
        cc::log("Window", "destruct");
        ImGui_ImplSdlGL3_Shutdown();
        if (mGLContext != nullptr) {
            SDL_GL_DeleteContext(mGLContext);
        }
        if (mWindow != nullptr) {
            SDL_DestroyWindow(mWindow);
        }
        SDL_Quit();
    }

    bool Window::isOpen() const {
        return mOpen;
    }

    void Window::beginFrame() {
        //Event Polling
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (!ImGui_ImplSdlGL3_ProcessEvent(&e)) {
                switch (e.type) {
                    case SDL_KEYDOWN:
                    case SDL_KEYUP:
                        if (e.key.repeat == 0) {
                            updateAction(e.key.keysym.scancode, e.key.type == SDL_KEYDOWN);
                        }
                        break;
                    case SDL_WINDOWEVENT:
                        if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
                            glViewport(0, 0, e.window.data1, e.window.data2);
                            mResize = true;
                        }
                        break;
                    default:
                        break;
                }
            }
            if (e.type == SDL_QUIT) {
                mOpen = false;
            }
        }
    }

    void Window::endFrame() {
        SDL_GL_SwapWindow(mWindow);
    }

    void Window::close() {
        mOpen = false;
    }

    bool Window::getSize(int *w, int *h) {
        SDL_GetWindowSize(mWindow, w, h);
        bool oldState = mResize;
        mResize = false;
        return oldState;
    }

    void Window::addAction(SDL_Scancode key, bool *state, bool onPress) {
        mActions[key] = {state, onPress};
    }

    void Window::updateAction(SDL_Scancode key, bool press) {
        auto it = mActions.find(key);
        if (it != mActions.end()) {
            Action &a = it->second;
            if (a.onPress) {
                *(a.state) = press;
            } else if (press) {
                *(a.state) = !*(a.state);
            }

        }
    }

    void Window::clear() {
        ImGui_ImplSdlGL3_NewFrame(mWindow);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // NOLINT
    }
}