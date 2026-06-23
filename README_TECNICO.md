# Labirinto dos Sussurros - README Técnico

## Descrição

**Labirinto dos Sussurros** é um RPG textual acessível desenvolvido em linguagem C para a disciplina de Introdução à Computação. O jogo oferece uma experiência narrativa interativa com foco em acessibilidade para usuários com deficiência visual.

## Requisitos Técnicos

- **Linguagem:** C (C99 ou superior)
- **Compilador:** GCC 4.8+ ou compatível
- **Sistema Operacional:** Linux, Windows (com MinGW), macOS
- **Terminal:** Qualquer terminal POSIX padrão

## Compilação

### Linux/macOS

```bash
cd labirinto_sussurros_cb
gcc -o rpg main.c item.c jogador.c npc.c sala.c utils.c -I.
```

### Windows (MinGW)

```bash
cd labirinto_sussurros_cb
gcc -o rpg.exe main.c item.c jogador.c npc.c sala.c utils.c -I.
```

### Code::Blocks

Abra o arquivo `labirinto_sussurros_cb.cbp` no Code::Blocks e clique em "Build" ou pressione F9.

## Execução

### Linux/macOS

```bash
./rpg
```

### Windows

```bash
rpg.exe
```

## Estrutura do Código

```
main.c              - Loop principal do jogo, processamento de comandos
sala.c/sala.h       - Definição e inicialização das salas
jogador.c/jogador.h - Estado do jogador, exibição de status
item.c/item.h       - Sistema de inventário e itens
npc.c/npc.h         - Personagens não jogáveis
utils.c             - Funções auxiliares (normalização, I/O)
common.h            - Definições globais e constantes
```

## Conceitos de Programação em C Utilizados

- **Tipos de Dados:** int, char, bool, structs
- **Controle de Fluxo:** if/else, while, for, switch
- **Funções:** Modularização com responsabilidades bem definidas
- **Structs:** Sala, Jogador, Item, NPC
- **Arrays e Vetores:** inventario[], salas[], npcs[]
- **Strings:** Manipulação com strcpy, strcmp, strlen
- **Ponteiros:** Passagem por referência em funções
- **Arquivo:** Salvamento e carregamento de jogo (FILE*)
- **Normalização de Entrada:** Tratamento de acentos e case-insensitivity

## Comandos do Jogo

### Comandos Numéricos
- `1`, `2`, `3`, etc. - Escolher uma opção numerada

### Comandos Textuais
- `ajuda` - Exibir lista de comandos disponíveis
- `status` - Mostrar sanidade e experiência
- `inventario` - Listar itens coletados
- `examinar [item]` - Examinar um item do inventário
- `repetir` - Repetir a última descrição e opções
- `opcoes` - Listar as opções disponíveis
- `salvar` - Salvar o jogo (com confirmação)
- `sair` - Sair do jogo (com confirmação)

## Acessibilidade

### Recursos Implementados

✓ **Teclado Único:** Todas as ações podem ser realizadas apenas com teclado  
✓ **Opções Numeradas:** Todas as escolhas são apresentadas com números  
✓ **Case-Insensitive:** Comandos funcionam em maiúsculas ou minúsculas  
✓ **Remoção de Acentos:** Comandos com acentos são convertidos automaticamente  
✓ **Sem Cores Essenciais:** Nenhuma informação depende de cores  
✓ **Histórico Mantido:** A tela não é limpa excessivamente  
✓ **Comando Repetir:** Permite re-exibir descrições e opções  
✓ **Mensagens Claras:** Erros e avisos são bem descritos  
✓ **Confirmações:** Decisões importantes pedem confirmação  
✓ **Sem Limite de Tempo:** Nenhuma ação tem timeout  
✓ **Sem Áudio Essencial:** Tudo é textual  

### Compatibilidade com Leitores de Tela

O jogo foi projetado para ser compatível com:
- **NVDA** (Windows)
- **Orca** (Linux)
- **VoiceOver** (macOS)

## Sistema de Jogo

### Atributos do Jogador

- **Sanidade (0-100%):** Diminui com erros e decisões ruins. Jogo termina se chegar a 0.
- **Experiência (XP):** Aumenta ao resolver enigmas e explorar. Sem limite máximo.

### Itens

O jogo possui 4 itens coletáveis:
1. **Chave de Bronze** - Necessária para abrir o Portão Trancado
2. **Amuleto Antigo** - Necessário para atravessar a Passagem Sombria
3. **Mapa Rasgado** - Necessário para encontrar a Forja Abandonada
4. **Martelo Pesado** - Necessário para abrir o Portão Final

### Enigmas

1. **Guardião dos Ossos:** "Qual é o som do silêncio?" (Resposta: "nada")
2. **Templo Esquecido:** "O que tem cidades, mas não casas; florestas, mas não árvores; e água, mas não peixes?" (Resposta: "mapa")

### Finais

- **Final 1 (Vitória):** Escapar do Labirinto pela saída principal
- **Final 2 (Alternativo):** Aceitar o poder do Altar Sombrio e se tornar parte do Labirinto

## Salvamento de Jogo

O jogo salva em um arquivo chamado `savegame_final.txt` no diretório atual. O arquivo contém:
- Sala atual
- Sanidade e Experiência
- Estado do inventário
- Estado dos NPCs

## Troubleshooting

### Problema: "gcc: command not found"
**Solução:** Instale o GCC
- Ubuntu/Debian: `sudo apt-get install build-essential`
- Fedora/RHEL: `sudo dnf install gcc`
- macOS: Instale Xcode Command Line Tools

### Problema: Caracteres acentuados aparecem incorretos
**Solução:** Certifique-se de que seu terminal suporta UTF-8

### Problema: Jogo não salva
**Solução:** Verifique as permissões de escrita no diretório

## Notas de Desenvolvimento

- O código foi compilado com `-Wall` para verificar avisos
- Avisos sobre "multi-character character constants" são esperados (UTF-8)
- O projeto usa apenas bibliotecas padrão do C (stdio, stdlib, string, ctype)

## Autor

Desenvolvido como Projeto Final para a disciplina de Introdução à Computação.

## Licença

Este projeto é fornecido para fins educacionais.
