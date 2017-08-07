#ifndef GLOBAL_H_ 
#define GLOBAL_H_

#include <3ds.h>
#include <sf2d.h>
#include <sfil.h>
#include <ctype.h>
#include <stdlib.h>

#define TREE 1
#define COIN 2
#define MOVEMENT 4
#define SPELL 8

#define SPELLSIZE 3

#include "Font_png.h"
sf2d_texture *font;

struct player{
    int x;
    int y;
    sf2d_texture *sprite;
    int initMP;
    int currentMP;
    struct spell *currentSpell;
    struct spell *spells[3];
};

struct prede{
    int x;
    int y;
    int cost;
};

struct spell{
    int rangeMIN;
    int rangeMAX;
    int rangeType;
    int damage;
    int AP;
    char *name;
    char *description;
};

void drawText(char * msg, u32 x, u32 y);
void drawSizedText(char * msg, u32 x, u32 y, float size);
void drawTextColor(char * msg, u32 x, u32 y, u32 color);
void drawSizedTextColor(char * msg, int x, int y, float size, u32 color);

#endif // GLOBAL 
