#ifndef SALA_H
#define SALA_H

#include "common.h"
#include "npc.h"

typedef struct Sala {
    int id;
    char descricao[1024];
    char opcoes[MAX_OPCOES][MAX_INPUT_LENGTH];
    int destinos[MAX_OPCOES];
    int num_opcoes;
    int npc_id; // -1 se nenhum
    int item_necessario; // ID do item para acessar a sala (-1 se nenhum)
    int item_coletavel;  // ID do item para coletar na sala (-1 se nenhum)
    char enigma_pergunta[256]; // Para enigmas textuais
    char enigma_resposta[50];
    bool enigma_resolvido;
} Sala;

// Sala related functions
void inicializar_mundo(Sala salas[], NPC npcs[]);

#endif // SALA_H
