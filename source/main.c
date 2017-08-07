#include <3ds.h>
#include <sf2d.h>
#include <sfil.h>
#include <stdio.h>

#include "player_png.h"
#include "3dbrew_png.h"
#include "map_png.h"

#include "map.h"
#include "player.h"
#include "global.h"
#include "bottomScreen.h"

void incrementPlayer(struct player *player_ptr, int x, int y);

int main()
{
	sf2d_init();
	sf2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));

    font = sfil_load_PNG_buffer(Font_png, SF2D_PLACE_RAM);

    initMap();
    initBottom();
    struct player cursor;
    initCursor(&cursor);

    struct player cra;
    initCra(&cra);
    addPlayer(&cra);

    calculShortestPath(&cra);

	while (aptMainLoop()) {

		hidScanInput();

		if (hidKeysDown() & KEY_START) {
			break;
		}

		if (hidKeysDown() & KEY_DDOWN) {
            incrementPlayer(&cursor, 0, 1);
		}

		if (hidKeysDown() & KEY_DUP) {
            incrementPlayer(&cursor, 0, -1);
		}

		if (hidKeysDown() & KEY_DRIGHT) {
            incrementPlayer(&cursor, 1, 0);
		}

		if (hidKeysDown() & KEY_DLEFT) {
            incrementPlayer(&cursor, -1, 0);
		}

		if (hidKeysHeld() & KEY_X) {
            calculSpell(&cra);
		}
        else{
            clearSpell();
            updateMovement(&cursor, &cra);
        }

		if (hidKeysDown() & KEY_A) {
            movePlayer(&cra, &cursor);
            calculShortestPath(&cra);
		}

		sf2d_start_frame(GFX_TOP, GFX_LEFT);

            drawMap(&cursor);

		sf2d_end_frame();

		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);

            drawBottom(&cra);

		sf2d_end_frame();

		sf2d_swapbuffers();
        
	}

    deletePlayer(&cra);
    deleteCursor(&cursor);
    clearMap();
    clearBottom();

	sf2d_fini();
	return 0;
}

void incrementPlayer(struct player *player_ptr, int x, int y){
    if (player_ptr->x + x < MAPSIZE && player_ptr->x + x >= 0){ 
        player_ptr->x += x;
    }
    if (player_ptr->y + y < MAPSIZE && player_ptr->y + y >= 0){ 
        player_ptr->y += y;
    }
}
