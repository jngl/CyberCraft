#include "Core/Update.h"

#include "Game.h"

#include <CyberCraftSFML/WindowSFML.h>
#include <GameEngine.h>

#include <string>
#include <array>

namespace bloc {
    struct BlocInfo {
        std::string_view name;
        int value;
    };

    constexpr std::array<BlocInfo, 2> blocInfoArray = {
            BlocInfo{
                    "A",
                    1
            },
            BlocInfo{
                    "B",
                    2
            }
    };

    constexpr const BlocInfo *DataFromName(std::string_view name) {
        for (const BlocInfo &data : blocInfoArray) {
            if (data.name == name) {
                return &data;
            }
        }
        return nullptr;
    }

    static_assert(DataFromName("A") == &blocInfoArray[0]);
    static_assert(DataFromName("B") == &blocInfoArray[1]);
    static_assert(DataFromName("C") == nullptr);

    struct InvalidBlocError : public Error {
        InvalidBlocError(): Error("bloc not found") {}
    };

    class Bloc {
    public:
        constexpr explicit Bloc(std::string_view name) {
            bool found = false;
            for (int i = 0; i < blocInfoArray.size(); ++i) {
                if (blocInfoArray[i].name == name) {
                    m_index = i;
                    found = true;
                }
            }
            if(!found){
                throw InvalidBlocError();
            }
        }

        [[nodiscard]] constexpr bool isValid() const {
            return m_index != -1;
        }

        [[nodiscard]] constexpr std::string_view getName() const {
            if(m_index < 0 || m_index >= blocInfoArray.size()){
                return "";
            }
            return blocInfoArray[m_index].name;
        }

        [[nodiscard]] constexpr int getValue() const {
            if(m_index < 0 || m_index >= blocInfoArray.size()){
                return 0;
            }
            return blocInfoArray[m_index].value;
        }

    private:
        std::size_t m_index = -1;
    };

    static_assert(Bloc("A").isValid());
    static_assert(Bloc("B").isValid());
    //static_assert(!Bloc("C").isValid());

    static_assert(Bloc("A").getName() == "A");
    static_assert(Bloc("B").getName() == "B");
    //static_assert(Bloc("C").getName().empty());

    static_assert(Bloc("A").getValue() == 1);
    static_assert(Bloc("B").getValue() == 2);
    //static_assert(Bloc("C").getValue() == 0);
}

int main() {
    GameEngineImpl<WindowSFML> gameEngine;

    FixStepUpdater updater(std::chrono::milliseconds{33});

    Game game(gameEngine.getWindow());

	while (gameEngine.getWindow().isOpen()) {
        gameEngine.getWindow().beginFrame();

	    game.draw();

	    updater.update([&game](){
	        game.update();
	    });

        gameEngine.getWindow().endFrame();
	}

	return 0;
}
