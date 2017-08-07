#ifndef PLAYER_H_ 
#define PLAYER_H_

#include <3ds.h>
#include <sf2d.h>
#include <sfil.h>
#include <stdlib.h>

#include "global.h"
#include "spell.h"

void initCursor(struct player *cursor);
void initCra(struct player *player);
void deletePlayer(struct player *player);
void deleteCursor(struct player *cursor);

#endif // PLAYER 
