#include "Window.hpp"

#include "Timer.hpp"
#include "cmdline.h"
#include "debugAssert.hpp"

#include "Renderer.hpp"

#include "BasicScene.hpp"
#include "BoxelScene/BoxelScene.hpp"

#include "filesystem.hpp"

#include <imgui.h>

#include <memory>

struct Arg {
  int width;
  int height;
  std::string sceneName;
};

Arg parseArg(int argc, char *argv[]) {
 /* cmdline::parser a;
  
  a.add<int>("width", 'w', "width of the window", false, 1024,
             cmdline::range(1, 65535));
  a.add<int>("height", 'h', "height of the window", false, 768,
             cmdline::range(1, 65535));
  a.add<std::string>("scene", 's', "the scene to run", false, "Boxel",
                     cmdline::oneof<std::string>("Boxel", "Basic"));

  a.parse_check(argc, argv);
  */
  Arg arg;
 /* arg.width = a.get<int>("width");
  arg.height = a.get<int>("height");
  arg.sceneName = a.get<std::string>("scene");*/

  arg.width = 1024;
  arg.height = 768;
  arg.sceneName= "Boxel";

  return arg;
}

class Application {
public:
  Application(int argc, char *argv[])
    : mShowTestWindow(false),
      mShowInfoWindow(false),
      mCommandText("")
  {
    Arg arg = parseArg(argc, argv);

    filesystem::createFileSystem();

    mWindow.reset(new Window(arg.width, arg.height));
    mWindow->addAction(SDL_SCANCODE_F3, &mShowInfoWindow, false);

    Renderer::createRenderer();
    
    changeScene(arg.sceneName);
    mScene->addAction(*mWindow);
  }

  ~Application() {
    mScene = nullptr;
    Renderer::destroyRenderer();
    filesystem::destroyFileSystem();
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
  float mFrameTime;
  bool mShowTestWindow;
  bool mShowInfoWindow;
  char mCommandText[mMaxInputSize];
  std::string mConsoleText;

  void changeScene(std::string name) {
    if (name == "Boxel") {
      mScene.reset(new BoxelScene);
    } else {
      mScene.reset(new BasicScene);
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
	mShowTestWindow ^= 1;

      ImGui::Text("%s", mConsoleText.c_str());
      
      ImGui::InputText("command", mCommandText, mMaxInputSize);
      if (ImGui::Button("exec")){
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

  void runCommand(){
    debug::log("Main", "run command : ", mCommandText);

    std::string command = mCommandText;
    memset(mCommandText, 0, mMaxInputSize);

    if(command=="exit"){
      mWindow->close();
    }else{
      printConsole("unkown command");
    }
  }

  void printConsole(std::string msg){
    mConsoleText += ">"+msg+"\n";
  }
};

int main(int argc, char *argv[]) {
	try
	{
		Application app(argc, argv);
		debug::log("Main", "begin main loop");
		app.run();
		debug::log("Main", "end main loop");
	}
	catch (std::exception e) {
		std::cerr << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "unkonw error" << std::endl;
	}
  return 0;
}
