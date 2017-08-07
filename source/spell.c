#include "spell.h"

void initAssault(struct spell *spell){
    spell->name = "Assault";
    spell->description = "Switch position with the targeted caracter.";
    spell->rangeMAX = 5;
    spell->rangeMIN = 2;
    spell->damage = 1;
    spell->AP = 1;
}
