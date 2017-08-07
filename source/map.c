#include "map.h"
#include "tile_png.h"
#include "tree_png.h"
#include "movement_png.h"

#define H_OFFSET 20
#define V_OFFSET 10
#define H_SIZE 400
#define V_SIZE 240

struct tile map[MAPSIZE][MAPSIZE];
struct prede predeMap[MAPSIZE][MAPSIZE];
int spellMap[MAPSIZE][MAPSIZE];

sf2d_texture *tile;
sf2d_texture *tree;
sf2d_texture *movement;

void dijsktraSP(int x, int y, int cost, int maxCost);
int isLineOfSight(int x1, int y1, int x2, int y2, int rangeMAX, int rangeMIN);
int isWalkable(int x, int y);

void initMap(){
    for (int i=0; i<MAPSIZE; i++){
        for (int j=0; j<MAPSIZE; j++){
            map[i][j].type = 0;
            map[i][j].player = NULL;
        }
    }
    tile = sfil_load_PNG_buffer(tile_png, SF2D_PLACE_RAM);
    tree = sfil_load_PNG_buffer(tree_png, SF2D_PLACE_RAM);
    movement = sfil_load_PNG_buffer(movement_png, SF2D_PLACE_RAM);

    // Add some trees
    map[4][3].type |= TREE;
    map[2][4].type |= TREE;
    map[9][5].type |= TREE;
}

void drawMap(struct player *cursor){
    int topY;
    int firstYPixel;
    if(cursor->y < 4){
        topY = 0;
        firstYPixel = V_OFFSET;
    }
    else if(cursor->y <= 6){
        topY = cursor->y - 3;
        firstYPixel = 0;
    }
    else{
        topY = 4;
        firstYPixel = -V_OFFSET;
    }
    for(int x = 0; x < 12; x++){
        for(int y = 0;y < 8; y++){
            // Draw each visile tile
            int pixelX = x*tile->width+H_OFFSET;
            int pixelY = (y)*tile->height+firstYPixel;
            sf2d_draw_texture(tile, pixelX, pixelY);
            // Draw Tree
            if (map[x][y+topY].type & TREE){
                sf2d_draw_texture(tree, pixelX, pixelY);
            }
            // Draw Player
            if (map[x][y+topY].player != NULL){
                sf2d_draw_texture(map[x][y+topY].player ->sprite, pixelX, pixelY);
            }
            // Draw Movement
            if (map[x][y+topY].type & MOVEMENT){
                sf2d_draw_texture(movement, pixelX, pixelY);
                map[x][y+topY].type &= ~MOVEMENT;
            }
            // Draw Spell 
            if (map[x][y+topY].type & SPELL){
                sf2d_draw_texture(movement, pixelX, pixelY);
            }
            // Draw Cursor
            if (x == cursor->x && y + topY == cursor->y){
                sf2d_draw_texture(cursor->sprite, pixelX, pixelY);
            }
        }
    }
}

void clearMap(){
    sf2d_free_texture(tile);
    sf2d_free_texture(tree);
    sf2d_free_texture(movement);
}

void addPlayer(struct player *addPlayer){
    map[addPlayer->x][addPlayer->y].player = addPlayer;
}

void calculShortestPath(struct player *currentPlayer){
    for (int i=0; i<MAPSIZE; i++){
        for (int j=0; j<MAPSIZE; j++){
            predeMap[i][j].x = -1;
            predeMap[i][j].y = -1;
            predeMap[i][j].cost = 99999;
        }
    }
    dijsktraSP(currentPlayer->x, currentPlayer->y, 1, currentPlayer->currentMP);
}

void dijsktraSP(int x, int y, int cost, int maxCost){
    if(cost > maxCost) return;
    int nextX[4] = {x+1, x-1, x, x};
    int nextY[4] = {y, y, y+1, y-1};
    for (int i=0; i < 4; i++){
        if (nextX[i] < MAPSIZE && nextX[i] >= 0 && nextY[i] < MAPSIZE && nextY[i] >= 0){
            if (isWalkable(nextX[i], nextY[i]) &&
                    predeMap[nextX[i]][nextY[i]].cost > cost){
                predeMap[nextX[i]][nextY[i]].x = x;
                predeMap[nextX[i]][nextY[i]].y = y;
                predeMap[nextX[i]][nextY[i]].cost = cost;
                dijsktraSP(nextX[i], nextY[i], cost+1, maxCost);
            }
        }
    }
}

void updateMovement(struct player *cursor, struct player *currentPlayer){
    struct prede *currentTile = &predeMap[cursor->x][cursor->y];
    if (currentTile->x != -1 || currentTile->y != -1){
        while (currentTile != &predeMap[currentPlayer->x][currentPlayer->y]){
            map[currentTile->x][currentTile->y].type |= MOVEMENT;
            currentTile = &predeMap[currentTile->x][currentTile->y];
        }
        map[currentPlayer->x][currentPlayer->y].type &= ~MOVEMENT;
        map[cursor->x][cursor->y].type |= MOVEMENT;
    }
}

void calculSpell(struct player *currentPlayer){
    for (int i=0; i<MAPSIZE; i++){
        for (int j=0; j<MAPSIZE; j++){
            spellMap[i][j] = isLineOfSight(currentPlayer->x, currentPlayer->y, i, j, currentPlayer->spells[0]->rangeMAX, currentPlayer->spells[0]->rangeMIN);
            if (spellMap[i][j] != -1){
                map[i][j].type |= SPELL;
            }
        }
    }
}

void clearSpell(){
    for (int i=0; i<MAPSIZE; i++){
        for (int j=0; j<MAPSIZE; j++){
            map[i][j].type &= ~SPELL;
        }
    }
}


int isLineOfSight(int x1, int y1, int x2, int y2, int rangeMAX, int rangeMIN){
    int dx = x2-x1;
    int dy = y2-y1;
    int nx = abs(dx);
    int ny = abs(dy);
    if (nx+ny > rangeMAX || nx+ny < rangeMIN) return -1;
    if (dx > 0){
        dx = 1;
    }
    else{
        dx = -1;
    }
    if (dy > 0){
        dy = 1;
    }
    else{
        dy = -1;
    }
    int px = x1;
    int py = y1;
    for (int ix = 0, iy = 0; ix < nx || iy < ny;){
        if ((1+2*ix) * ny == (1+2*iy) * nx){
            px += dx;
            py += dy;
            ix += 1;
            iy += 1;
        }
        else if ((1+2*ix) * ny < (1+2*iy) * nx){
            px += dx;
            ix += 1;
        }
        else{
            py += dy;
            iy += 1;
        }
        if (map[px][py].type & TREE || map[px][py].player != NULL) return -1;
    }
    return (nx+ny);
}

int isWalkable(int x, int y){
    return !(map[x][y].type & TREE || map[x][y].player != NULL);
}

int movePlayer(struct player *currentPlayer, struct player *cursor){
    int cost = predeMap[cursor->x][cursor->y].cost;
    if (cost <= currentPlayer->currentMP){
        map[currentPlayer->x][currentPlayer->y].player = NULL;
        currentPlayer->currentMP -= cost;
        currentPlayer->x = cursor->x;
        currentPlayer->y = cursor->y;
        map[currentPlayer->x][currentPlayer->y].player = currentPlayer;
        calculShortestPath(currentPlayer);
        return 1;
    }
    return -1;
}

