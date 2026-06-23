#include <stdio.h>
#include <string.h>
#include "jogador.h"

void exibir_status(Jogador *jogador) {
    printf("[ Sanidade: %d%% | XP: %d ]\n", jogador->sanidade, jogador->experiencia);
    falar("Sua sanidade é de " , VOZ_SISTEMA);
    char sanidade_str[10];
    sprintf(sanidade_str, "%d", jogador->sanidade);
    falar(sanidade_str, VOZ_SISTEMA);
    falar(" por cento. Sua experiência é de " , VOZ_SISTEMA);
    char xp_str[10];
    sprintf(xp_str, "%d", jogador->experiencia);
    falar(xp_str, VOZ_SISTEMA);
    falar(" pontos.", VOZ_SISTEMA);
}

void exibir_inventario(Jogador *jogador) {
    printf("[ Inventário: ");
    falar("Seu inventário contém: ", VOZ_SISTEMA);
    bool tem_item_print = false;
    for(int i=0; i<MAX_ITENS; i++) {
        if(jogador->inventario[i].coletado) {
            printf("%s ", jogador->inventario[i].nome);
            falar(jogador->inventario[i].nome, VOZ_SISTEMA);
            tem_item_print = true;
        }
    }
    if(!tem_item_print) {
        printf("Vazio");
        falar("Nada.", VOZ_SISTEMA);
    }
    printf(" ]\n");
}
