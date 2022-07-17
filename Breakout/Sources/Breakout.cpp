#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>

#include <sstream>
#include <filesystem>

#include "Level.h"
#include "Game.h"

namespace fs = std::filesystem;

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

#define ICON_PATH           "Resources/ball2.png"
#define LEVELS_PATH         "Resources/Levels/"

#define PLAYER_HIT_SOUND    "Resources/Sounds/350862__cabled-mess__blip-c-04.wav"
#define WALL_HIT_SOUND      "Resources/Sounds/350862__cabled-mess__blip-c-04.wav"

void init()
{
	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(3);
}

int main()
{
	init();

	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	ALLEGRO_BITMAP* icon = al_load_bitmap(ICON_PATH);
	al_set_window_title(display, "Breakout");
	al_set_display_icon(display, icon);

	std::vector<std::string> levelPaths;
	for (const auto& entry : fs::directory_iterator(LEVELS_PATH)) {
		levelPaths.push_back(entry.path().string());
	}

	Game* game;
	game = new Game(levelPaths, display);
	game->run();

	al_destroy_display(display);
	al_destroy_bitmap(icon);
	al_uninstall_keyboard();

	return 0;
}
