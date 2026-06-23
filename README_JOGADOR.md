# Labirinto dos Sussurros - Guia do Jogador

## Bem-vindo ao Labirinto dos Sussurros!

Você acordou em um lugar estranho e escuro. O ar é frio e úmido. Você ouve sussurros distantes ecoando pelas paredes. Você precisa encontrar uma forma de escapar deste labirinto antigo e misterioso.

## Como Jogar

### Iniciando o Jogo

Execute o programa:
```bash
./rpg
```

Você será perguntado se deseja carregar um jogo salvo anteriormente. Digite:
- `1` para SIM (carregar jogo anterior)
- `2` para NÃO (começar novo jogo)

### Navegação

Em cada sala, você verá uma descrição do local e uma lista de opções numeradas. Para facilitar a acessibilidade, você pode escolher uma ação de três formas:

1. **Digitar o número** da opção (ex: `1`, `2`, `3`)
2. **Digitar a letra correspondente** (ex: `a` para opção 1, `b` para opção 2, `c` para opção 3)
3. **Digitar um comando textual** (ex: `ajuda`, `status`, `inventario`)

Esta funcionalidade foi implementada para facilitar o uso do teclado por pessoas com deficiência visual ou motora.

### Comandos Disponíveis

#### Exploração
- `1`, `2`, `3`, etc. - Escolher uma opção numerada
- `repetir` - Repetir a descrição da sala e as opções
- `opcoes` - Listar as opções disponíveis

#### Informações
- `status` - Ver sua sanidade e experiência
- `inventario` - Ver os itens que você coletou
- `examinar [item]` - Examinar um item específico (ex: `examinar chave`)
- `ajuda` - Ver lista de comandos

#### Jogo
- `salvar` - Salvar seu progresso
- `sair` - Sair do jogo

## Mecânicas do Jogo

### Sanidade

Sua sanidade começa em 100%. Ela diminui quando:
- Você comete erros ao responder enigmas
- Você tenta acessar áreas bloqueadas sem os itens necessários
- Você faz escolhas ruins

**Se sua sanidade chegar a 0%, você perde o jogo!**

### Experiência

Você ganha experiência quando:
- Resolve um enigma corretamente (+50 XP)
- Explora uma nova sala (+20 XP)

### Itens

Você pode coletar itens ao explorar. Alguns itens são necessários para progredir:

1. **Chave de Bronze** - Abre o Portão Trancado
2. **Amuleto Antigo** - Protege você na Passagem Sombria
3. **Mapa Rasgado** - Ajuda a encontrar a Forja Abandonada
4. **Martelo Pesado** - Abre o Portão Final

Use o comando `examinar [item]` para aprender mais sobre cada item.

## Dicas de Gameplay

### Exploração
- Explore todas as áreas para coletar itens importantes
- Fale com todos os personagens que encontrar
- Preste atenção às descrições das salas - elas contêm pistas

### Enigmas
- Leia as perguntas com cuidado
- Pense sobre o significado das palavras
- Não tenha medo de tentar respostas diferentes

### Salvamento
- Salve seu jogo frequentemente usando o comando `salvar`
- Você pode carregar seu último save ao iniciar o jogo
- Apenas um save é mantido por vez

## Finais Possíveis

### Final 1: Escapar do Labirinto
Se você encontrar o caminho correto através do labirinto e coletou todos os itens necessários, você pode escapar pela saída principal e ver a luz do sol novamente. **Este é o final "bom".**

### Final 2: Aceitar o Poder
Se você explorar o caminho alternativo e resolver o enigma do Templo Esquecido, você terá a oportunidade de aceitar um poder antigo. Mas cuidado - este poder tem um preço! **Este é o final "alternativo".**

## Guia de Solução (Sem Spoilers)

Se você está preso, aqui estão algumas dicas gerais:

1. **Comece explorando o Hall Ecoante** - Há 4 caminhos diferentes
2. **Colete todos os itens que encontrar** - Você vai precisar deles
3. **Fale com todos os NPCs** - Eles podem dar pistas importantes
4. **Resolva os enigmas com cuidado** - Erros custam sanidade
5. **Explore completamente antes de tomar decisões irreversíveis**

## Acessibilidade

Este jogo foi projetado para ser acessível a todos, incluindo pessoas com deficiência visual:

- ✓ Pode ser jogado apenas com teclado
- ✓ Todas as opções são numeradas
- ✓ Comandos funcionam em maiúsculas ou minúsculas
- ✓ Acentos são removidos automaticamente
- ✓ Você pode repetir descrições e opções a qualquer momento
- ✓ Nenhuma informação depende de cores
- ✓ Não há limite de tempo para responder

## Troubleshooting

### "Entrada não reconhecida"
Você digitou um comando que o jogo não entende. Tente:
- Digitar o número da opção (1, 2, 3, etc.)
- Usar um dos comandos listados em `ajuda`
- Usar `repetir` para ver as opções novamente

### "Você não possui este item"
Você tentou examinar um item que não tem. Use `inventario` para ver quais itens você possui.

### "Uma força invisível bloqueia seu caminho"
Você tentou acessar uma área que requer um item específico. Volte e procure pelo item necessário.

## Perguntas Frequentes

**P: Posso voltar para salas anteriores?**  
R: Sim! A maioria das salas tem uma opção para voltar. Use `repetir` ou `opcoes` se não souber qual é.

**P: Posso perder o jogo?**  
R: Sim. Se sua sanidade chegar a 0%, você perde. Mas você pode salvar e carregar seu jogo!

**P: Quantas horas o jogo leva?**  
R: Depende de você! A primeira vez leva cerca de 30-60 minutos. Você pode explorar mais rápido ou mais lentamente.

**P: Há múltiplos finais?**  
R: Sim! Há pelo menos 2 finais diferentes dependendo de suas escolhas.

**P: Posso jogar novamente?**  
R: Sim! Comece um novo jogo digitando `2` quando perguntado se deseja carregar um save.

## Bom Jogo!

Boa sorte em sua jornada pelo Labirinto dos Sussurros. Espero que você encontre uma forma de escapar... ou talvez aceite seu destino.

---

*"Em cada sussurro, há uma história. Em cada sombra, há uma escolha."*
