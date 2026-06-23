#ifndef NPC_H
#define NPC_H

#include "common.h"

typedef struct NPC {
    char nome[50];
    char fala[1024];
    int item_com_ele; // ID do item que ele dá (-1 se nenhum)
    bool ja_falou;
} NPC;

#endif // NPC_H
