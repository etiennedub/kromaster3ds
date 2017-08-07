#include "bottomScreen.h"

#define BLACK 0xFF000000

sf2d_texture *bg;
sf2d_texture *spell;

void initBottom(){
    bg = sfil_load_PNG_buffer(bottom_bg_png, SF2D_PLACE_RAM);
    spell = sfil_load_PNG_buffer(spell_png, SF2D_PLACE_RAM);
}

void drawBottom(struct player *currentPlayer){
    sf2d_draw_texture(bg, 0, 0);
    sf2d_draw_texture(spell, 57, 5);
    sf2d_draw_texture(spell, 57, 75);
    sf2d_draw_texture(spell, 57, 145);
    drawTextColor(currentPlayer->currentSpell->name, 60,80, BLACK);
    drawSizedTextColor(currentPlayer->currentSpell->description, 57,150,0.90, BLACK);
}

void clearBottom(){
    sf2d_free_texture(bg);
    sf2d_free_texture(spell);
}
