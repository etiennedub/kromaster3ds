#ifndef MAP_H_ 
#define MAP_H_

#include <3ds.h>
#include <sf2d.h>
#include <sfil.h>
#include <stdlib.h>

#include "global.h"

#define MAPSIZE 12
struct tile {
    int type;
    struct player *player;
};

void initMap();
void drawMap(struct player *cursor);
void addPlayer(struct player *addPlayer);
void clearMap();
void calculShortestPath(struct player *currentPlayer);
void updateMovement(struct player *cursor, struct player *currentPlayer);
void calculSpell(struct player *currentPlayer);
void clearSpell();
int movePlayer(struct player *currentPlayer, struct player *cursor);

#endif // MAP_H_
