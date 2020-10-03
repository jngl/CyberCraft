#include "Window.hpp"

#include "Timer.hpp"
#include <Core/Debug.h>

#include "Renderer.hpp"

#include "BasicScene.hpp"
#include "BoxelScene/BoxelScene.hpp"

#include "filesystem.hpp"

#include <imgui.h>

#include <memory>

class Application {
public:
    Application(){
        mWindow = std::make_unique<Window>(1024, 768);
        mWindow->addAction(SDL_SCANCODE_F3, &mShowInfoWindow, false);

        Renderer::createRenderer();

        changeScene("Boxel");
        mScene->addAction(*mWindow);
    }

    ~Application() {
        mScene = nullptr;
        Renderer::destroyRenderer();
    }

    void run() {
        while (mWindow->isRunning()) {
            frame();
        }
    }

private:
    static constexpr unsigned int mMaxInputSize = 32;

    std::unique_ptr<Window> mWindow;
    std::unique_ptr<Scene> mScene;
    Timer mGlobalTimer;
    float mFrameTime = 0;
    bool mShowTestWindow = false;
    bool mShowInfoWindow = false;
    char mCommandText[mMaxInputSize] = "";
    std::string mConsoleText;

    void changeScene(std::string_view name) {
        if (name == "Boxel") {
            mScene = std::make_unique<BoxelScene>();
        } else {
            mScene = std::make_unique<BoxelScene>();
        }
    }

    void frame() {
        mFrameTime = mGlobalTimer.timeInSecond();
        mGlobalTimer.restart();

        mWindow->doEvent();

        int width, height;
        if (mWindow->getSize(&width, &height)) {
            Renderer::resize(width, height);
        }

        mWindow->clear();

        if (mShowInfoWindow) {
            ImGui::SetNextWindowSize(ImVec2(400, 100), ImGuiSetCond_FirstUseEver);
            ImGui::Begin("Info", &mShowInfoWindow);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                        1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            if (ImGui::Button("Test Window"))
                mShowTestWindow = !mShowTestWindow;

            ImGui::Text("%s", mConsoleText.c_str());

            ImGui::InputText("command", mCommandText, mMaxInputSize);
            if (ImGui::Button("exec")) {
                runCommand();
            }

            ImGui::End();
        }

        if (mShowTestWindow) {
            ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
            ImGui::ShowTestWindow(&mShowTestWindow);
        }

        mScene->update(mFrameTime);
        Renderer::renderAllObject();

        ImGui::Render();

        mWindow->endFrame();
    }

    void runCommand() {
        ccCore::log("Main", "run command : ", mCommandText);

        std::string command = mCommandText;
        memset(mCommandText, 0, mMaxInputSize);

        if (command == "exit") {
            mWindow->close();
        } else {
            printConsole("unknown command");
        }
    }

    void printConsole(std::string_view msg) {
        mConsoleText += ">" + std::string(msg) + "\n";
    }
};

int main() {
    try {
        Application app;
        ccCore::log("Main", "begin main loop");
        app.run();
        ccCore::log("Main", "end main loop");
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "unknown error" << std::endl;
    }
    return 0;
}
