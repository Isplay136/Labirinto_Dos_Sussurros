#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"
#include "jogador.h"

// Detecção de Sistema Operacional
#ifdef _WIN32
    #define OS_WINDOWS
#elif __APPLE__
    #define OS_MAC
#else
    #define OS_LINUX
#endif

void verificar_audio() {
    printf("\n[ SISTEMA DE ÁUDIO DE ALTA QUALIDADE (PIPER IA) ]\n");
    
#ifdef OS_WINDOWS
    printf("Plataforma: Windows\n");
    printf("Método: PowerShell Speech (Nativo)\n");
#elif defined(OS_MAC)
    printf("Plataforma: macOS\n");
    printf("Método: Command 'say' (Nativo)\n");
#else
    printf("Plataforma: Linux (Arch Linux)\n");
    
    // Verifica se o Piper está instalado
    if (system("piper --version > /dev/null 2>&1") == 0) {
        printf("Motor detectado: Piper TTS (Voz Humana de Alta Qualidade)\n");
        printf("Status: PRONTO PARA USO OFFLINE.\n");
    } else {
        printf("Motor detectado: Espeak-ng (Voz Robótica de Backup)\n");
        printf("DICA: Para vozes humanas, instale o 'piper-tts' e baixe um modelo .onnx\n");
    }
#endif
    printf("----------------------------------------\n\n");
}

void falar(const char *texto, TipoVoz tipo) {
    char comando[4096];
    char variante[10] = "";
    int p = 50;
    int s = 160; 
    
    if (current_jogador_ptr != NULL) {
        if (!current_jogador_ptr->audio_ativo) {
            printf("%s\n", texto);
            return;
        }
        s = current_jogador_ptr->velocidade_fala;
    }

    printf("%s\n", texto);

#ifdef OS_WINDOWS
    snprintf(comando, sizeof(comando), 
        "powershell -Command \"$ErrorActionPreference = 'SilentlyContinue'; "
        "Add-Type -AssemblyName System.Speech; "
        "$speak = New-Object System.Speech.Synthesis.SpeechSynthesizer; "
        "$speak.Rate = %d; "
        "$speak.Speak('%s')\" > $null 2>&1", (s - 160) / 10, texto);
    system(comando);

#elif defined(OS_MAC)
    snprintf(comando, sizeof(comando), "say -r %d \"%s\" > /dev/null 2>&1", s, texto);
    system(comando);

#else
    /* 
       LINUX: ESTRATÉGIA PIPER (IA OFFLINE)
       O Piper usa modelos .onnx para gerar vozes humanas.
       O comando assume que você tem um modelo em ~/piper_models/pt_BR.onnx
    */
    
    // 1. Tenta usar o Piper (Qualidade de Cinema)
    // Nota: O piper gera um arquivo temporário e o aplay toca.
    snprintf(comando, sizeof(comando), 
        "echo \"%s\" | piper --model ~/piper_models/pt_BR.onnx --output_file /tmp/rpg_piper.wav > /dev/null 2>&1 && aplay /tmp/rpg_piper.wav > /dev/null 2>&1", texto);
    
    if (system(comando) != 0) {
        // 2. Backup: Espeak-ng com variantes (Se o Piper não estiver configurado)
        if (tipo == VOZ_SISTEMA) { strcpy(variante, "+m1"); p = 80; }
        else if (tipo == VOZ_NPC) { strcpy(variante, "+f1"); p = 45; }
        else if (tipo == VOZ_PERIGO) { strcpy(variante, "+whisper"); p = 30; }
        else if (tipo == VOZ_NARRADOR) { strcpy(variante, "+m3"); p = 50; }
        
        snprintf(comando, sizeof(comando), "espeak-ng -v pt-br%s -p %d -s %d \"%s\" > /dev/null 2>&1", variante, p, s, texto);
        system(comando);
    }
#endif
}

void tocar_efeito(const char *arquivo) {
    if (current_jogador_ptr != NULL && !current_jogador_ptr->audio_ativo) return;
    char comando[256];
#ifdef OS_WINDOWS
    snprintf(comando, sizeof(comando), "powershell -Command \"$ErrorActionPreference = 'SilentlyContinue'; (New-Object Media.SoundPlayer('%s')).PlaySync()\" > $null 2>&1", arquivo);
#else
    snprintf(comando, sizeof(comando), "aplay %s > /dev/null 2>&1 &", arquivo);
#endif
    system(comando);
    printf("[EFEITO SONORO: %s]\n", arquivo);
}

void normalizar_string(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }

    char *src = str;
    char *dst = str;
    while (*src) {
        if ((unsigned char)*src == 0xC3) { 
            src++;
            if ((unsigned char)*src == 0xA1 || (unsigned char)*src == 0xA0 || (unsigned char)*src == 0xA3 || (unsigned char)*src == 0xA2) *dst = 'a';
            else if ((unsigned char)*src == 0xA9 || (unsigned char)*src == 0xAA) *dst = 'e';
            else if ((unsigned char)*src == 0xAD) *dst = 'i';
            else if ((unsigned char)*src == 0xB3 || (unsigned char)*src == 0xB4 || (unsigned char)*src == 0xB5) *dst = 'o';
            else if ((unsigned char)*src == 0xBA || (unsigned char)*src == 0xBC) *dst = 'u';
            else if ((unsigned char)*src == 0xA7) *dst = 'c';
            else *dst = *src;
        } else {
            *dst = *src;
        }
        src++;
        dst++;
    }
    *dst = '\0';

    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
}

bool confirmar_acao(const char *mensagem) {
    falar(mensagem, VOZ_SISTEMA);
    falar("1 para Sim, 2 para Não.", VOZ_SISTEMA);
    char input_buffer[MAX_INPUT_LENGTH];
    if (fgets(input_buffer, sizeof(input_buffer), stdin)) {
        normalizar_string(input_buffer);
        return (strcmp(input_buffer, "1") == 0 || strcmp(input_buffer, "sim") == 0);
    }
    return false;
}

void pausar() {
    printf("\n[ Pressione Enter para continuar ]\n");
    falar("Pressione Enter para continuar.", VOZ_SISTEMA);
    fflush(stdout);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
