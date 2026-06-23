#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>

#define MAX_SALAS 50
#define MAX_ITENS 10
#define MAX_NPCS 5
#define MAX_INPUT_LENGTH 100
#define MAX_OPCOES 6

typedef enum { VOZ_NARRADOR, VOZ_SISTEMA, VOZ_NPC, VOZ_PERIGO } TipoVoz;

// Forward declarations for structs to avoid circular dependencies
typedef struct Item Item;
typedef struct NPC NPC;
typedef struct Sala Sala;
typedef struct Jogador Jogador;

// Global pointers for easier access (can be refactored later if needed)
extern Sala *current_sala_ptr;
extern Jogador *current_jogador_ptr;

// Utility functions (from utils.h)
void verificar_audio();
void falar(const char *texto, TipoVoz tipo);
void tocar_efeito(const char *arquivo);
void normalizar_string(char *str);
bool confirmar_acao(const char *mensagem);
void pausar();

#endif // COMMON_H
