#include <Core/Timer.hpp>
#include <Core/Debug.h>

#include "Renderer.hpp"

#include "BoxelScene/BoxelScene.hpp"

#include <imgui.h>

#include <memory>

class Application {
public:
    static constexpr int DefaultWindowSizeX = 1024;
    static constexpr int DefaultWindowSizeY = 768;

    Application(){
        mWindow = std::make_unique<cc::System::Window>(DefaultWindowSizeX, DefaultWindowSizeY);
        mWindow->addAction(SDL_SCANCODE_F3, &mShowInfoWindow, false);

        Renderer::createRenderer();

        changeScene("Boxel");
        mScene->addAction(*mWindow);
    }

    Application(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) = delete;

    ~Application() {
        mScene = nullptr;
        Renderer::destroyRenderer();
    }

    void run() {
        while (mWindow->isOpen()) {
            frame();
        }
    }

private:
    static constexpr unsigned int mMaxInputSize = 32;

    std::unique_ptr<cc::System::Window> mWindow;
    std::unique_ptr<Scene> mScene;
    cc::Timer mGlobalTimer;
    float mFrameTime = 0;
    bool mShowTestWindow = false;
    bool mShowInfoWindow = false;
    std::array<char, mMaxInputSize> mCommandText = {0};
    std::string mConsoleText;

    void changeScene(std::string_view /*name*/) {
        mScene = std::make_unique<BoxelScene>();
    }

    void frame() {
        mFrameTime = mGlobalTimer.timeInSecond();
        mGlobalTimer.restart();

        mWindow->beginFrame();

        int width = 0;
        int height = 0;
        if (mWindow->getSize(&width, &height)) {
            Renderer::resize(width, height);
        }

        mWindow->clear();

        if (mShowInfoWindow) {
            constexpr int showInfoSizeX = 400;
            constexpr int showInfoSizeY = 100;
            ImGui::SetNextWindowSize(ImVec2(showInfoSizeX, showInfoSizeY), ImGuiSetCond_FirstUseEver);
            ImGui::Begin("Info", &mShowInfoWindow);
            constexpr float OneSecondInMillisecond = 1000.f;
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", // NOLINT
                        OneSecondInMillisecond / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            if (ImGui::Button("Test Window")) {
                mShowTestWindow = !mShowTestWindow;
            }

            ImGui::Text("%s", mConsoleText.c_str()); // NOLINT

            ImGui::InputText("command", mCommandText.data(), mMaxInputSize);
            if (ImGui::Button("exec")) {
                runCommand();
            }

            ImGui::End();
        }

        if (mShowTestWindow) {
            constexpr int testWindowSizeX = 650;
            constexpr int testWindowSizeY = 200;
            ImGui::SetNextWindowPos(ImVec2(testWindowSizeX, testWindowSizeY), ImGuiSetCond_FirstUseEver);
            ImGui::ShowTestWindow(&mShowTestWindow);
        }

        mScene->update(mFrameTime);
        Renderer::renderAllObject();

        ImGui::Render();

        mWindow->endFrame();
    }

    void runCommand() {
        cc::log("Main", "run command : ", mCommandText.data());

        std::string command = mCommandText.data();
        memset(mCommandText.data(), 0, mMaxInputSize);

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
        cc::log("Main", "begin main loop");
        app.run();
        cc::log("Main", "end main loop");
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "unknown error" << std::endl;
    }
    return 0;
}
