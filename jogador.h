#ifndef JOGADOR_H
#define JOGADOR_H

#include "common.h"
#include "item.h"
#include "npc.h"

typedef struct Jogador {
    int sala_atual;
    int sanidade;
    int experiencia;
    Item inventario[MAX_ITENS];
    bool vivo;
    NPC npcs_estado[MAX_NPCS];
    char ultima_descricao_sala[1024]; // Para o comando 'repetir'
    char ultimas_opcoes_sala[MAX_OPCOES][MAX_INPUT_LENGTH]; // Para o comando 'repetir'
    int num_ultimas_opcoes;
    // Configurações de Acessibilidade
    bool audio_ativo;
    int velocidade_fala; // 80 a 260, padrão 160
} Jogador;

// Jogador related functions
void exibir_status(Jogador *jogador);
void exibir_inventario(Jogador *jogador);

#endif // JOGADOR_H
