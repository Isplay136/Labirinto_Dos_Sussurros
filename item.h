#ifndef ITEM_H
#define ITEM_H

#include "common.h"
#include <stdbool.h>

// Forward declaration para evitar dependência circular
typedef struct Jogador Jogador;

typedef struct Item {
    char nome[50];
    char descricao[256];
    bool coletado;
} Item;

// Item related functions
void examinar_item(Jogador *jogador, const char *nome_item);
void normalizar_nome_item(char *nome);

#endif // ITEM_H
