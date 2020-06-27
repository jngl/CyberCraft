#include "Game/MyPlayer.h"
#include "Game/MyTileTypeRegistry.h"
#include "Game/MyTileMap.h"

#include "Window.h"

int main() {
    Window win;

    MyTileTypeRegistry types;
    MyPlayer player(types);

    MyTileMap map(types);
    map.set({5,5}, "long grass");
    map.set({15,5}, "rock");
    map.set({5,15}, "tree");
    map.set({15,15}, "water");
    map.set({7,12}, "dead bush");

	while (win.isOpen()) {
	    win.beginFrame();

		player.input(map, win.getSFMLWindowsRef());

		//update
		win.update([&player, &map](){
            player.update(map);
		});

		//render
		map.draw(win.getSFMLWindowsRef());
		player.draw(win.getSFMLWindowsRef());

		win.endFrame();
	}

	return 0;
}
