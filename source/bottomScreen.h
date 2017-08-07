#ifndef BOTTOM_H_ 
#define BOTTOM_H_

#include <3ds.h>
#include <sf2d.h>
#include <sfil.h>

#include "global.h"
#include "bottom_bg_png.h"
#include "spell_png.h"

void initBottom();
void drawBottom(struct player *currentPlayer);
void clearBottom();

#endif // BOTTOM_H_
