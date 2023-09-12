# 21a-emb-aps1

Embarcados - APS 1 - Musical!

Para maiores informações acesse:

https://insper.github.io/ComputacaoEmbarcada/APS-1-Musical/

Issues serão abertos neste repositório para guiar o desenvolvimento
da dupla. **Vocês não devem fechar os issues, apenas a equipe de professores!**, porém devem referenciar nos commits quando um issue 
foi concluído! Isso gerará um PR no classroom que será avaliado pela equipe.

## Documentação

TODO: Aualizar pinos

| Função  | PINO (ex: PA11) |
|---------|-----------------|
| BUZZER  |      PD27       |
| START   |    PC31         |
| SELEÇÃO |       PD28      |

### Instruções de uso

1. Clone o repositório do projeto (https://github.com/insper-classroom/23b-emb-aps-1-roger77.git).
   
2. Dentro da pasta do projeto, entre em firmware, e selecione o arquivo OLED1.atsln para abrir no Microchip Studio. Abra o arquivo main.c localizado dentro da pasta src.

3. Conecte o buzzer à protoboard, 2 jumpers conectando a entrada e saida do buzzer ao pino PD27 da SAM E70 e ao GND, respectivamente, como evidenciado na imagem abaixo e conecte o display OLED à saída EXT1.

4. Conecte a placa SAM E70, ao computador utilizando a entrada "debug" da placa e rode o main.c utilizando a função debug do software.

5. Desfrute das músicas incluidas no programa, levando utilizando o botão 2 para PAUSE/PLAY, o botão 3 para ir para a próxima música e o botão 1 para voltar para a música anterior!

### Imagem da montagem

![image](https://github.com/insper-classroom/23b-emb-aps-1-roger77/assets/67804009/dfe00cf6-e73e-451c-a3c4-0205deeb329c)

### Estrutura do código

Funções notáveis:

init(): Inicializa o relógio da placa, desativa o WDT, configura os periféricos (buzzer e botões), define as interrupções, e configura os LEDs.

tone(int freq, int time): Gera um tom através do buzzer em uma frequência e duração especificadas, controlando também os LEDs.

loop_musica(... variáveis ...): Responsável por executar um loop infinito que toca as músicas contidas no array musicas segundo as interações do usuário com os botões, além de exibir uma interface de progresso e informações sobre a música atual no display.

Arquivos:

utils.c: Contém a implementação principal do programa, incluindo a configuração de periféricos e as funções init, tone e loop_musica.

main.c: Este arquivo contém a função main que define as músicas e configura a exibição inicial no display OLED. É aqui que é chamada a função loop_musica() para iniciar a reprodução da música.

notas.h: Este arquivo contém as definições para todas as notas musicais que serão utilizadas no projeto. Cada nota é definida com um valor específico, que será usado pela função tone() para gerar o tom correspondente. A definição 'REST' é utilizada para representar uma pausa na música.

### Vídeo do projeto

https://youtu.be/igsYZiQTl4k?si=lO17ktFUY3dtdy9n

### Músicas e Direitos autorais

Musicas retiradas do repositório https://github.com/robsoncouto/arduino-songs/tree/3b8ed10f644cb150bc3fe39c854546f5b9331f71 de Robson Couto:

- Luiz Gonzaga - Asa Branca

- Starwars - Cantina Band Song

- Starwars - Imperial March

- Rick Astley - Never Gonna Give You Up

- Super Mario Bros - Overworld Theme
The Legend of Zelda - Main Theme



