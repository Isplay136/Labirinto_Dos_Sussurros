#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "jogador.h"
#include "sala.h"
#include "item.h"
#include "npc.h"

#define SAVE_FILE "savegame_final.txt"

Sala *current_sala_ptr = NULL;
Jogador *current_jogador_ptr = NULL;

void salvar_jogo(Jogador *j);
bool carregar_jogo(Jogador *j);
int processar_comando(char *comando_str, Jogador *jogador, Sala salas[], NPC npcs_modelo[]);

int main() {
    Jogador jogador;
    Sala salas[MAX_SALAS];
    NPC npcs_modelo[MAX_NPCS];
    
    current_jogador_ptr = &jogador; // Define o ponteiro global para o utils.c usar
    
    verificar_audio(); 
    inicializar_mundo(salas, npcs_modelo);
    current_sala_ptr = &salas[0];

    falar("Bem-vindo ao Labirinto dos Sussurros: Projeto Final.", VOZ_SISTEMA);
    falar("Deseja carregar um jogo salvo? 1 para Sim, 2 para Não.", VOZ_SISTEMA);
    
    char input_buffer[MAX_INPUT_LENGTH];
    if (fgets(input_buffer, sizeof(input_buffer), stdin)) {
        normalizar_string(input_buffer);
        int op_save = atoi(input_buffer);
        
        if (op_save == 1 && carregar_jogo(&jogador)) {
            falar("Jogo carregado com sucesso!", VOZ_SISTEMA);
            for(int i=0; i<MAX_NPCS; i++) {
                npcs_modelo[i] = jogador.npcs_estado[i];
            }
            current_sala_ptr = &salas[jogador.sala_atual];
        } else {
            jogador.sala_atual = 0;
            jogador.sanidade = 100;
            jogador.experiencia = 0;
            jogador.vivo = true;
            jogador.audio_ativo = true;
            jogador.velocidade_fala = 160;
            
            for(int i=0; i<MAX_ITENS; i++) {
                jogador.inventario[i].coletado = false;
                strcpy(jogador.inventario[i].nome, "");
                strcpy(jogador.inventario[i].descricao, "");
            }
            strcpy(jogador.inventario[0].nome, "Chave de Bronze");
            strcpy(jogador.inventario[0].descricao, "Uma chave antiga e pesada, feita de bronze.");
            strcpy(jogador.inventario[1].nome, "Amuleto Antigo");
            strcpy(jogador.inventario[1].descricao, "Um amuleto com símbolos estranhos, emana uma leve energia protetora.");
            strcpy(jogador.inventario[2].nome, "Mapa Rasgado");
            strcpy(jogador.inventario[2].descricao, "Um pedaço de mapa rasgado, parece indicar um caminho secreto.");
            strcpy(jogador.inventario[3].nome, "Martelo Pesado");
            strcpy(jogador.inventario[3].descricao, "Um martelo robusto, bom para quebrar coisas.");

            for(int i=0; i<MAX_NPCS; i++) {
                jogador.npcs_estado[i] = npcs_modelo[i];
            }
            falar("Iniciando nova jornada épica...", VOZ_SISTEMA);
        }
    }

    while (jogador.vivo && jogador.sanidade > 0) {
        current_sala_ptr = &salas[jogador.sala_atual];

        for(int i=0; i<MAX_NPCS; i++) {
            npcs_modelo[i] = jogador.npcs_estado[i];
        }

        exibir_status(&jogador);
        exibir_inventario(&jogador);
        printf("----------------------------------------\n");

        if (current_sala_ptr->item_necessario != -1 && !jogador.inventario[current_sala_ptr->item_necessario].coletado) {
            falar("Uma força invisível bloqueia seu caminho. Algo falta em sua posse.", VOZ_PERIGO);
            jogador.sanidade -= 10;
            char msg_sanidade[100];
            snprintf(msg_sanidade, sizeof(msg_sanidade), "Sua sanidade diminuiu. Agora você tem %d por cento.", jogador.sanidade);
            falar(msg_sanidade, VOZ_PERIGO);
            pausar();
            jogador.sala_atual = 0; 
            continue;
        }

        strcpy(jogador.ultima_descricao_sala, current_sala_ptr->descricao);
        for(int i=0; i<current_sala_ptr->num_opcoes; i++) {
            strcpy(jogador.ultimas_opcoes_sala[i], current_sala_ptr->opcoes[i]);
        }
        jogador.num_ultimas_opcoes = current_sala_ptr->num_opcoes;

        falar(current_sala_ptr->descricao, VOZ_NARRADOR);

        if (current_sala_ptr->npc_id != -1) {
            NPC *n = &npcs_modelo[current_sala_ptr->npc_id];
            if (!n->ja_falou) {
                falar(n->fala, VOZ_NPC);
                if (n->item_com_ele != -1) {
                    jogador.inventario[n->item_com_ele].coletado = true;
                    char msg[100];
                    snprintf(msg, sizeof(msg), "Você recebeu: %s.", jogador.inventario[n->item_com_ele].nome);
                    falar(msg, VOZ_SISTEMA);
                }
                n->ja_falou = true;
            }
        }

        if (current_sala_ptr->item_coletavel != -1 && !jogador.inventario[current_sala_ptr->item_coletavel].coletado) {
            jogador.inventario[current_sala_ptr->item_coletavel].coletado = true;
            char msg[100];
            snprintf(msg, sizeof(msg), "Você encontrou: %s.", jogador.inventario[current_sala_ptr->item_coletavel].nome);
            falar(msg, VOZ_SISTEMA);
        }

        if (strlen(current_sala_ptr->enigma_pergunta) > 0 && !current_sala_ptr->enigma_resolvido) {
            falar(current_sala_ptr->enigma_pergunta, VOZ_NARRADOR);
            falar("Por favor, digite sua resposta.", VOZ_SISTEMA);
            char resposta_usuario[MAX_INPUT_LENGTH];
            if (fgets(resposta_usuario, sizeof(resposta_usuario), stdin)) {
                normalizar_string(resposta_usuario);
                if (strcmp(resposta_usuario, current_sala_ptr->enigma_resposta) == 0) {
                    falar("Correto! O caminho se abre.", VOZ_SISTEMA);
                    current_sala_ptr->enigma_resolvido = true;
                    jogador.experiencia += 50;
                } else {
                    falar("Resposta incorreta. Tente novamente.", VOZ_PERIGO);
                    jogador.sanidade -= 5;
                    char msg_sanidade[100];
                    snprintf(msg_sanidade, sizeof(msg_sanidade), "Sua sanidade diminuiu. Agora você tem %d por cento.", jogador.sanidade);
                    falar(msg_sanidade, VOZ_PERIGO);
                    pausar();
                    continue;
                }
            }
        }

        printf("\nO que deseja fazer?\n");
        for (int i = 0; i < current_sala_ptr->num_opcoes; i++) {
            char opt[150];
            snprintf(opt, sizeof(opt), "Opção %d [ou tecla %c]: %s", i + 1, 'a' + i, current_sala_ptr->opcoes[i]);
            falar(opt, VOZ_NARRADOR);
        }
        
        falar("Você também pode digitar: ajuda, status, inventario, examinar [item], repetir, opcoes, salvar, sair, audio ligar/desligar ou velocidade [80-260].", VOZ_SISTEMA);

        char comando_str[MAX_INPUT_LENGTH];
        if (fgets(comando_str, sizeof(comando_str), stdin)) {
            normalizar_string(comando_str);
            int resultado_comando = processar_comando(comando_str, &jogador, salas, npcs_modelo);

            if (resultado_comando == -1) return 0;
            else if (resultado_comando == 0) continue;
            else if (resultado_comando > 0) {
                jogador.sala_atual = resultado_comando;
                jogador.experiencia += 20;
            }
        }
        
        if (jogador.sala_atual == 19) {
            falar("A luz do sol aquece seu rosto. Você finalmente escapou do Labirinto dos Sussurros! Parabéns!", VOZ_SISTEMA);
            jogador.vivo = false;
        } else if (jogador.sala_atual == 18) {
            falar("Você aceita o poder, mas a escuridão o consome. Seu corpo se torna um receptáculo para a antiga força, e você se torna parte do Labirinto. Este é o seu novo fim.", VOZ_SISTEMA);
            jogador.vivo = false;
        }
        
        pausar();
    }

    if (jogador.sanidade <= 0) falar("A escuridão consumiu sua alma. Você falhou.", VOZ_PERIGO);

    return 0;
}

void salvar_jogo(Jogador *j) {
    FILE *f = fopen(SAVE_FILE, "w");
    if (f) {
        fprintf(f, "sala_atual=%d\n", j->sala_atual);
        fprintf(f, "sanidade=%d\n", j->sanidade);
        fprintf(f, "experiencia=%d\n", j->experiencia);
        fprintf(f, "vivo=%d\n", j->vivo);
        fprintf(f, "audio_ativo=%d\n", j->audio_ativo);
        fprintf(f, "velocidade_fala=%d\n", j->velocidade_fala);

        fprintf(f, "[INVENTARIO]\n");
        for(int i=0; i<MAX_ITENS; i++) {
            if(j->inventario[i].coletado) {
                fprintf(f, "item_id=%d\n", i);
                fprintf(f, "item_nome=%s\n", j->inventario[i].nome);
                fprintf(f, "item_descricao=%s\n", j->inventario[i].descricao);
            }
        }

        fprintf(f, "[NPCs_ESTADO]\n");
        for(int i=0; i<MAX_NPCS; i++) {
            fprintf(f, "npc_id=%d\n", i);
            fprintf(f, "npc_ja_falou=%d\n", j->npcs_estado[i].ja_falou);
        }

        fclose(f);
        falar("Jogo salvo com sucesso!", VOZ_SISTEMA);
    } else {
        falar("Erro ao salvar o jogo.", VOZ_SISTEMA);
    }
}

bool carregar_jogo(Jogador *j) {
    FILE *f = fopen(SAVE_FILE, "r");
    if (f) {
        char linha[256];
        int parsing_section = 0;
        int current_item_idx = -1;
        int current_npc_idx = -1;

        for(int i=0; i<MAX_ITENS; i++) j->inventario[i].coletado = false;
        j->audio_ativo = true; // Padrão
        j->velocidade_fala = 160;

        while (fgets(linha, sizeof(linha), f)) {
            linha[strcspn(linha, "\n")] = 0;

            if (strcmp(linha, "[INVENTARIO]") == 0) { parsing_section = 1; continue; }
            else if (strcmp(linha, "[NPCs_ESTADO]") == 0) { parsing_section = 2; continue; }

            char *chave = strtok(linha, "=");
            char *valor_str = strtok(NULL, "\0");
            if (!chave || !valor_str) continue;

            if (parsing_section == 0) {
                if (strcmp(chave, "sala_atual") == 0) j->sala_atual = atoi(valor_str);
                else if (strcmp(chave, "sanidade") == 0) j->sanidade = atoi(valor_str);
                else if (strcmp(chave, "experiencia") == 0) j->experiencia = atoi(valor_str);
                else if (strcmp(chave, "vivo") == 0) j->vivo = (bool)atoi(valor_str);
                else if (strcmp(chave, "audio_ativo") == 0) j->audio_ativo = (bool)atoi(valor_str);
                else if (strcmp(chave, "velocidade_fala") == 0) j->velocidade_fala = atoi(valor_str);
            } else if (parsing_section == 1) {
                if (strcmp(chave, "item_id") == 0) {
                    current_item_idx = atoi(valor_str);
                    j->inventario[current_item_idx].coletado = true;
                } else if (current_item_idx != -1 && strcmp(chave, "item_nome") == 0) strcpy(j->inventario[current_item_idx].nome, valor_str);
                else if (current_item_idx != -1 && strcmp(chave, "item_descricao") == 0) strcpy(j->inventario[current_item_idx].descricao, valor_str);
            } else if (parsing_section == 2) {
                if (strcmp(chave, "npc_id") == 0) current_npc_idx = atoi(valor_str);
                else if (current_npc_idx != -1 && strcmp(chave, "npc_ja_falou") == 0) j->npcs_estado[current_npc_idx].ja_falou = (bool)atoi(valor_str);
            }
        }
        fclose(f);
        return true;
    }
    return false;
}

int processar_comando(char *comando_str, Jogador *jogador, Sala salas[], NPC npcs_modelo[]) {
    int escolha = atoi(comando_str);
    if (escolha == 0 && strlen(comando_str) == 1) {
        char c = comando_str[0];
        if (c >= 'a' && c <= 'z') escolha = c - 'a' + 1;
    }

    if (escolha >= 1 && escolha <= current_sala_ptr->num_opcoes) {
        if (current_sala_ptr->id == 17 && escolha == 1) {
            if (!confirmar_acao("Esta é uma decisão irreversível. Tem certeza?")) return 0;
        }
        return current_sala_ptr->destinos[escolha - 1];
    }

    if (strcmp(comando_str, "ajuda") == 0) {
        falar("Comandos: status, inventario, examinar [item], repetir, opcoes, salvar, sair, audio ligar/desligar, velocidade [80-260].", VOZ_SISTEMA);
        return 0;
    } else if (strcmp(comando_str, "status") == 0) {
        exibir_status(jogador);
        return 0;
    } else if (strcmp(comando_str, "inventario") == 0) {
        exibir_inventario(jogador);
        return 0;
    } else if (strncmp(comando_str, "examinar ", 9) == 0) {
        examinar_item(jogador, comando_str + 9);
        return 0;
    } else if (strcmp(comando_str, "audio ligar") == 0) {
        jogador->audio_ativo = true;
        falar("Áudio ativado.", VOZ_SISTEMA);
        return 0;
    } else if (strcmp(comando_str, "audio desligar") == 0) {
        falar("Áudio desativado.", VOZ_SISTEMA);
        jogador->audio_ativo = false;
        return 0;
    } else if (strncmp(comando_str, "velocidade ", 11) == 0) {
        int v = atoi(comando_str + 11);
        if (v >= 80 && v <= 260) {
            jogador->velocidade_fala = v;
            char msg[50];
            snprintf(msg, sizeof(msg), "Velocidade ajustada para %d.", v);
            falar(msg, VOZ_SISTEMA);
        } else {
            falar("Velocidade inválida. Use entre 80 e 260.", VOZ_SISTEMA);
        }
        return 0;
    } else if (strcmp(comando_str, "repetir") == 0 || strcmp(comando_str, "opcoes") == 0) {
        falar(jogador->ultima_descricao_sala, VOZ_NARRADOR);
        for (int i = 0; i < jogador->num_ultimas_opcoes; i++) {
            char opt[150];
            snprintf(opt, sizeof(opt), "Opção %d [ou tecla %c]: %s", i + 1, 'a' + i, jogador->ultimas_opcoes_sala[i]);
            falar(opt, VOZ_NARRADOR);
        }
        return 0;
    } else if (strcmp(comando_str, "salvar") == 0) {
        if (confirmar_acao("Salvar o jogo?")) salvar_jogo(jogador);
        return 0;
    } else if (strcmp(comando_str, "sair") == 0) {
        if (confirmar_acao("Sair do jogo?")) return -1;
        return 0;
    } else {
        falar("Opção inválida. Digite 'ajuda'.", VOZ_SISTEMA);
        return 0;
    }
}
