#include "player.h"

#include "cursor_png.h"
#include "cra_png.h"

void initCursor(struct player *cursor){
	sf2d_texture *sprite = sfil_load_PNG_buffer(cursor_png, SF2D_PLACE_RAM);
    cursor->x = 5;
    cursor->y = 5;
    cursor->sprite = sprite;
}

void initCra(struct player *player){
	sf2d_texture *sprite = sfil_load_PNG_buffer(cra_png, SF2D_PLACE_RAM);
    player->x = 5;
    player->y = 5;
    player->sprite = sprite;
    player->currentMP = 5;
    player->initMP = 5;
    for(int i = 0; i < SPELLSIZE; i++){
        player->spells[i] = malloc(sizeof(struct spell));
    }
    initAssault(player->spells[0]);

    player->currentSpell = player->spells[0];
}

void deletePlayer(struct player *player){
    sf2d_free_texture(player->sprite);
    for(int i = 0; i < SPELLSIZE; i++){
        free(player->spells[i]);
    }
}

void deleteCursor(struct player *cursor){
    sf2d_free_texture(cursor->sprite);
}
