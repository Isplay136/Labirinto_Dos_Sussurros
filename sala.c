#include <stdio.h>
#include <string.h>
#include "sala.h"
#include "npc.h"
#include "item.h"

void inicializar_mundo(Sala salas[], NPC npcs[]) {
    // Inicialização dos NPCs
    strcpy(npcs[0].nome, "Guardião Silencioso");
    strcpy(npcs[0].fala, "Um vulto parado no canto da sala, observando-o com olhos vazios. Ele não parece querer conversar.");
    npcs[0].item_com_ele = -1;
    npcs[0].ja_falou = false;

    strcpy(npcs[1].nome, "Eremita Sábio");
    strcpy(npcs[1].fala, "Um velho eremita, com barba longa e olhos profundos, murmura: 'A chave para a saída está na sua mente, não em suas mãos.'");
    npcs[1].item_com_ele = 0; // Dá a Chave de Bronze
    npcs[1].ja_falou = false;

    strcpy(npcs[2].nome, "Guardião dos Ossos");
    strcpy(npcs[2].fala, "Uma figura esquelética com armadura enferrujada. 'Para passar, você deve provar sua inteligência.'");
    npcs[2].item_com_ele = -1;
    npcs[2].ja_falou = false;

    strcpy(npcs[3].nome, "Voz Misteriosa");
    strcpy(npcs[3].fala, "Uma voz etérea ecoa: 'O caminho para a luz é um, mas o caminho para o poder é outro. Qual você busca?'");
    npcs[3].item_com_ele = -1;
    npcs[3].ja_falou = false;

    // Inicialização das Salas
    // Sala 0: Hall Ecoante (Ponto de partida)
    salas[0].id = 0;
    strcpy(salas[0].descricao, "Você está no Hall Ecoante. As paredes são úmidas e um cheiro de mofo preenche o ar. Há três passagens à sua frente.");
    strcpy(salas[0].opcoes[0], "Ir para a Passagem da Névoa.");
    strcpy(salas[0].opcoes[1], "Ir para a Ala dos Ecos Perdidos.");
    strcpy(salas[0].opcoes[2], "Ir para a Entrada das Catacumbas.");
    strcpy(salas[0].opcoes[3], "Explorar uma fresta escura na parede (Câmara dos Segredos)."); // Nova opção
    salas[0].destinos[0] = 1; salas[0].destinos[1] = 2; salas[0].destinos[2] = 6; salas[0].destinos[3] = 14; // Novo destino
    salas[0].num_opcoes = 4; salas[0].npc_id = -1; salas[0].item_necessario = -1; salas[0].item_coletavel = -1;
    strcpy(salas[0].enigma_pergunta, ""); strcpy(salas[0].enigma_resposta, ""); salas[0].enigma_resolvido = false;

    // Sala 1: Passagem da Névoa
    salas[1].id = 1;
    strcpy(salas[1].descricao, "A Passagem da Névoa é densa e úmida. Você mal consegue ver um palmo à frente. Há um vulto parado no canto da sala.");
    strcpy(salas[1].opcoes[0], "Falar com o vulto.");
    strcpy(salas[1].opcoes[1], "Voltar para o Hall Ecoante.");
    salas[1].destinos[0] = 2; salas[1].destinos[1] = 0;  // CORRIGIDO: Era 1, agora vai para sala 2
    salas[1].num_opcoes = 2; salas[1].npc_id = 0; salas[1].item_necessario = -1; salas[1].item_coletavel = -1;
    strcpy(salas[1].enigma_pergunta, ""); strcpy(salas[1].enigma_resposta, ""); salas[1].enigma_resolvido = false;

    // Sala 2: Ala dos Ecos Perdidos
    salas[2].id = 2;
    strcpy(salas[2].descricao, "A Ala dos Ecos Perdidos é um corredor longo com portas em ambos os lados. Um sussurro distante parece vir de uma delas.");
    strcpy(salas[2].opcoes[0], "Entrar na porta à esquerda (Câmara dos Sussurros).");
    strcpy(salas[2].opcoes[1], "Entrar na porta à direita (Passagem Sombria).");
    strcpy(salas[2].opcoes[2], "Voltar para o Hall Ecoante.");
    salas[2].destinos[0] = 3; salas[2].destinos[1] = 4; salas[2].destinos[2] = 0;
    salas[2].num_opcoes = 3; salas[2].npc_id = -1; salas[2].item_necessario = -1; salas[2].item_coletavel = -1;
    strcpy(salas[2].enigma_pergunta, ""); strcpy(salas[2].enigma_resposta, ""); salas[2].enigma_resolvido = false;

    // Sala 3: Câmara dos Sussurros (NPC Eremita Sábio)
    salas[3].id = 3;
    strcpy(salas[3].descricao, "A Câmara dos Sussurros é fria e o ar vibra com vozes inaudíveis. Um eremita sábio está sentado no centro.");
    strcpy(salas[3].opcoes[0], "Falar com o Eremita Sábio.");
    strcpy(salas[3].opcoes[1], "Voltar para a Ala dos Ecos Perdidos.");
    salas[3].destinos[0] = 2; salas[3].destinos[1] = 2;  // CORRIGIDO: Era 3 (loop), agora volta para sala 2
    salas[3].num_opcoes = 2; salas[3].npc_id = 1; salas[3].item_necessario = -1; salas[3].item_coletavel = -1;
    strcpy(salas[3].enigma_pergunta, ""); strcpy(salas[3].enigma_resposta, ""); salas[3].enigma_resolvido = false;

    // Sala 4: Passagem Sombria (Requer Amuleto Antigo)
    salas[4].id = 4;
    strcpy(salas[4].descricao, "Passagem Sombria. O ar é pesado e maligno. O amuleto brilha suavemente em seu peito, protegendo-o.");
    strcpy(salas[4].opcoes[0], "Avançar para o Portão Trancado.");
    strcpy(salas[4].opcoes[1], "Voltar para a Ala dos Ecos Perdidos.");
    salas[4].destinos[0] = 5; salas[4].destinos[1] = 2;
    salas[4].num_opcoes = 2; salas[4].npc_id = -1; salas[4].item_necessario = 1; salas[4].item_coletavel = -1;
    strcpy(salas[4].enigma_pergunta, ""); strcpy(salas[4].enigma_resposta, ""); salas[4].enigma_resolvido = false;

    // Sala 5: Portão Trancado (Requer Chave de Bronze)
    salas[5].id = 5;
    strcpy(salas[5].descricao, "Portão Trancado. Um portão de ferro maciço bloqueia o caminho. Você ouve sons de rio e pássaros do outro lado.");
    strcpy(salas[5].opcoes[0], "Usar a chave de bronze.");
    strcpy(salas[5].opcoes[1], "Voltar para a Passagem Sombria.");
    salas[5].destinos[0] = 7; // Destino temporário, será ajustado
    salas[5].destinos[1] = 4;
    salas[5].num_opcoes = 2; salas[5].npc_id = -1; salas[5].item_necessario = 0; salas[5].item_coletavel = -1;
    strcpy(salas[5].enigma_pergunta, ""); strcpy(salas[5].enigma_resposta, ""); salas[5].enigma_resolvido = false;

    // Salas - Capítulo 2: As Catacumbas Esquecidas
    salas[6].id = 6;
    strcpy(salas[6].descricao, "Entrada das Catacumbas. Cheiro de terra úmida e ossos. Uma escada desce para a escuridão.");
    strcpy(salas[6].opcoes[0], "Descer para o Corredor dos Ossos.");
    strcpy(salas[6].opcoes[1], "Voltar ao Hall Ecoante.");
    salas[6].destinos[0] = 7; salas[6].destinos[1] = 0;
    salas[6].num_opcoes = 2; salas[6].npc_id = -1; salas[6].item_necessario = -1; salas[6].item_coletavel = -1;
    strcpy(salas[6].enigma_pergunta, ""); strcpy(salas[6].enigma_resposta, ""); salas[6].enigma_resolvido = false;

    salas[7].id = 7;
    strcpy(salas[7].descricao, "Corredor dos Ossos. O chão range sob seus pés. O Guardião dos Ossos observa seus movimentos. Um sussurro ameaçador vem de uma abertura à direita.");
    strcpy(salas[7].opcoes[0], "Falar com o Guardião.");
    strcpy(salas[7].opcoes[1], "Ir para a Câmara do Silêncio.");
    strcpy(salas[7].opcoes[2], "Voltar para a Entrada das Catacumbas.");
    salas[7].destinos[0] = 8; salas[7].destinos[1] = 8; salas[7].destinos[2] = 6;  // CORRIGIDO: Ambas opções vão para sala 8 (enigma)
    salas[7].num_opcoes = 3; salas[7].npc_id = 2; salas[7].item_necessario = -1; salas[7].item_coletavel = -1;
    strcpy(salas[7].enigma_pergunta, "O Guardião dos Ossos pergunta: 'Qual é o som do silêncio?'");
    strcpy(salas[7].enigma_resposta, "nada");
    salas[7].enigma_resolvido = false;

    salas[8].id = 8;
    strcpy(salas[8].descricao, "Câmara do Silêncio. Um silêncio opressor. Você sente paredes lisas e frias. Há uma pequena fresta na parede que emite um som agudo e constante.");
    strcpy(salas[8].opcoes[0], "Tentar encontrar uma passagem secreta (requer Mapa Rasgado).");
    strcpy(salas[8].opcoes[1], "Voltar ao Corredor dos Ossos.");
    salas[8].destinos[0] = 10; salas[8].destinos[1] = 7;
    salas[8].num_opcoes = 2; salas[8].npc_id = -1; salas[8].item_necessario = 2; salas[8].item_coletavel = -1;
    strcpy(salas[8].enigma_pergunta, ""); strcpy(salas[8].enigma_resposta, ""); salas[8].enigma_resolvido = false;

    salas[10].id = 10;
    strcpy(salas[10].descricao, "Forja Abandonada. O som de metal batendo ecoa. O ar é quente e cheira a ferro. Um martelo pesado repousa sobre a bigorna.");
    strcpy(salas[10].opcoes[0], "Pegar o martelo.");
    strcpy(salas[10].opcoes[1], "Ir para o Túnel Escuro.");
    strcpy(salas[10].opcoes[2], "Voltar para a Câmara do Silêncio.");
    salas[10].destinos[0] = 11; salas[10].destinos[1] = 11; salas[10].destinos[2] = 8;  // CORRIGIDO: Pegar martelo vai para sala 11
    salas[10].num_opcoes = 3; salas[10].npc_id = -1; salas[10].item_necessario = -1; salas[10].item_coletavel = 3;
    strcpy(salas[10].enigma_pergunta, ""); strcpy(salas[10].enigma_resposta, ""); salas[10].enigma_resolvido = false;

    // Salas - Capítulo 3: A Prova Final
    salas[11].id = 11;
    strcpy(salas[11].descricao, "Túnel Escuro. O som de água corrente indica a proximidade da saída. Um zumbido estranho ecoa.");
    strcpy(salas[11].opcoes[0], "Seguir o som da água (Câmara do Eco Final).");
    strcpy(salas[11].opcoes[1], "Explorar o zumbido (Armadilha).");
    strcpy(salas[11].opcoes[2], "Voltar para a Forja Abandonada.");
    salas[11].destinos[0] = 12; salas[11].destinos[1] = 13; salas[11].destinos[2] = 10;
    salas[11].num_opcoes = 3; salas[11].npc_id = -1; salas[11].item_necessario = -1; salas[11].item_coletavel = -1;
    strcpy(salas[11].enigma_pergunta, ""); strcpy(salas[11].enigma_resposta, ""); salas[11].enigma_resolvido = false;

    salas[12].id = 12;
    strcpy(salas[12].descricao, "Câmara do Eco Final. Um portão gigantesco bloqueia a saída. Há um mecanismo complexo que exige força bruta.");
    strcpy(salas[12].opcoes[0], "Usar o martelo pesado no mecanismo.");
    strcpy(salas[12].opcoes[1], "Voltar para o Túnel Escuro.");
    salas[12].destinos[0] = 19; salas[12].destinos[1] = 11;
    salas[12].num_opcoes = 2; salas[12].npc_id = -1; salas[12].item_necessario = 3; salas[12].item_coletavel = -1;
    strcpy(salas[12].enigma_pergunta, ""); strcpy(salas[12].enigma_resposta, ""); salas[12].enigma_resolvido = false;

    salas[13].id = 13;
    strcpy(salas[13].descricao, "Armadilha! Você cai em um buraco. O chão é escorregadio e você sente a dor de uma queda.");
    strcpy(salas[13].opcoes[0], "Tentar subir de volta.");
    salas[13].destinos[0] = 11; // Retorna ao Túnel Escuro
    salas[13].num_opcoes = 1; salas[13].npc_id = -1; salas[13].item_necessario = -1; salas[13].item_coletavel = -1;
    strcpy(salas[13].enigma_pergunta, ""); strcpy(salas[13].enigma_resposta, ""); salas[13].enigma_resolvido = false;

    salas[19].id = 19; // Sala de Vitória
    strcpy(salas[19].descricao, "A luz do sol aquece seu rosto. O cheiro de grama fresca e o som de pássaros enchem o ar. Você escapou do Labirinto dos Sussurros!");
    salas[19].num_opcoes = 0; salas[19].npc_id = -1; salas[19].item_necessario = -1; salas[19].item_coletavel = -1;
    strcpy(salas[19].enigma_pergunta, ""); strcpy(salas[19].enigma_resposta, ""); salas[19].enigma_resolvido = false;

    // --- Novo Capítulo: O Abismo Esquecido (Final Alternativo) ---
    salas[14].id = 14;
    strcpy(salas[14].descricao, "Câmara dos Segredos. Uma sala pequena e escura, onde uma Voz Misteriosa ecoa de todas as direções.");
    strcpy(salas[14].opcoes[0], "Ouvir a Voz Misteriosa.");
    strcpy(salas[14].opcoes[1], "Ignorar a voz e voltar ao Hall Ecoante.");
    salas[14].destinos[0] = 15; salas[14].destinos[1] = 0;  // CORRIGIDO: Era 14 (loop), agora vai para sala 15
    salas[14].num_opcoes = 2; salas[14].npc_id = 3; salas[14].item_necessario = -1; salas[14].item_coletavel = -1;
    strcpy(salas[14].enigma_pergunta, ""); strcpy(salas[14].enigma_resposta, ""); salas[14].enigma_resolvido = false;

    salas[15].id = 15;
    strcpy(salas[15].descricao, "Caminho Obscuro. A voz o guiou para uma passagem estreita e escura. Você sente uma energia estranha e poderosa.");
    strcpy(salas[15].opcoes[0], "Avançar para o Templo Esquecido.");
    strcpy(salas[15].opcoes[1], "Voltar para a Câmara dos Segredos.");
    salas[15].destinos[0] = 16; salas[15].destinos[1] = 14;
    salas[15].num_opcoes = 2; salas[15].npc_id = -1; salas[15].item_necessario = -1; salas[15].item_coletavel = -1;
    strcpy(salas[15].enigma_pergunta, ""); strcpy(salas[15].enigma_resposta, ""); salas[15].enigma_resolvido = false;

    salas[16].id = 16;
    strcpy(salas[16].descricao, "Templo Esquecido. Um altar antigo e coberto de runas. Você sente uma presença ancestral. Um enigma se manifesta em sua mente.");
    strcpy(salas[16].opcoes[0], "Tentar resolver o enigma.");
    strcpy(salas[16].opcoes[1], "Recuar para o Caminho Obscuro.");
    salas[16].destinos[0] = 17; // Se resolver o enigma
    salas[16].destinos[1] = 15;
    salas[16].num_opcoes = 2; salas[16].npc_id = -1; salas[16].item_necessario = -1; salas[16].item_coletavel = -1;
    strcpy(salas[16].enigma_pergunta, "O que tem cidades, mas não casas; florestas, mas não árvores; e água, mas não peixes?");
    strcpy(salas[16].enigma_resposta, "mapa");
    salas[16].enigma_resolvido = false;

    salas[17].id = 17;
    strcpy(salas[17].descricao, "Altar Sombrio. Ao resolver o enigma, o altar se ilumina com uma luz púrpura. Você sente um poder imenso, mas também uma escuridão que o consome.");
    strcpy(salas[17].opcoes[0], "Aceitar o poder (Final Alternativo).");
    strcpy(salas[17].opcoes[1], "Rejeitar o poder e tentar voltar.");
    salas[17].destinos[0] = 18; // Final alternativo
    salas[17].destinos[1] = 16;
    salas[17].num_opcoes = 2; salas[17].npc_id = -1; salas[17].item_necessario = -1; salas[17].item_coletavel = -1;
    strcpy(salas[17].enigma_pergunta, ""); strcpy(salas[17].enigma_resposta, ""); salas[17].enigma_resolvido = false;

    salas[18].id = 18; // Final Alternativo: Consumido pela Escuridão
    strcpy(salas[18].descricao, "Você aceita o poder, mas a escuridão o consome. Seu corpo se torna um receptáculo para a antiga força, e você se torna parte do Labirinto. Este é o seu novo fim.");
    salas[18].num_opcoes = 0; salas[18].npc_id = -1; salas[18].item_necessario = -1; salas[18].item_coletavel = -1;
    strcpy(salas[18].enigma_pergunta, ""); strcpy(salas[18].enigma_resposta, ""); salas[18].enigma_resolvido = false;
}
