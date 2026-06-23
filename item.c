#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "item.h"
#include "jogador.h"
#include "common.h"

// Função auxiliar para normalizar nomes de itens para comparação
void normalizar_nome_item(char *nome) {
    // Converte para minúsculas
    for (int i = 0; nome[i]; i++) {
        nome[i] = tolower(nome[i]);
    }

    // Remove acentos (simplificado para os nomes de itens)
    char *src = nome;
    char *dst = nome;
    while (*src) {
        if (*src == 'á' || *src == 'à' || *src == 'ã' || *src == 'â') *dst = 'a';
        else if (*src == 'é' || *src == 'ê') *dst = 'e';
        else if (*src == 'í') *dst = 'i';
        else if (*src == 'ó' || *src == 'ô' || *src == 'õ') *dst = 'o';
        else if (*src == 'ú' || *src == 'ü') *dst = 'u';
        else if (*src == 'ç') *dst = 'c';
        else *dst = *src;
        src++;
        dst++;
    }
    *dst = '\0';
}

void examinar_item(Jogador *jogador, const char *nome_item) {
    bool encontrado = false;
    char nome_normalizado[50];
    strcpy(nome_normalizado, nome_item);
    normalizar_nome_item(nome_normalizado);

    for(int i=0; i<MAX_ITENS; i++) {
        if(jogador->inventario[i].coletado) {
            char nome_inventario_normalizado[50];
            strcpy(nome_inventario_normalizado, jogador->inventario[i].nome);
            normalizar_nome_item(nome_inventario_normalizado);

            if (strcmp(nome_inventario_normalizado, nome_normalizado) == 0) {
                falar(jogador->inventario[i].descricao, VOZ_SISTEMA);
                encontrado = true;
                break;
            }
        }
    }
    if (!encontrado) {
        falar("Você nao possui este item ou ele nao existe.", VOZ_SISTEMA);
    }
}
