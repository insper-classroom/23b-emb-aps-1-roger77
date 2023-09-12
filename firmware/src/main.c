#include <asf.h>

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

#include "mariobros.h"
#include "starwars.h"
#include "zeldastheme.h"
#include "asabranca.h"
#include "nggyu.h"

#define BUZZER_PIO PIOD
#define BUZZER_PIO_ID ID_PIOD
#define BUZZER_PIO_IDX 27
#define BUZZER_PIO_IDX_MASK (1u << BUZZER_PIO_IDX)

#define BUT1_PIO PIOD
#define BUT1_PIO_ID ID_PIOD
#define BUT1_PIO_IDX 28
#define BUT1_PIO_IDX_MASK (1u << BUT1_PIO_IDX)

#define BUT2_PIO				PIOC
#define BUT2_PIO_ID				ID_PIOC
#define BUT2_PIO_IDX		    31
#define BUT2_PIO_IDX_MASK		(1u << BUT2_PIO_IDX)

#define BUT3_PIO PIOA
#define BUT3_PIO_ID ID_PIOA
#define BUT3_PIO_IDX 19
#define BUT3_PIO_IDX_MASK (1u<< BUT3_PIO_IDX)

//flags

volatile char but1_flag;
volatile char but2_flag;
volatile char but3_flag;
volatile char display_flag;
volatile char pause_display_flag;

//callbacks
void but1_callback(void);
void but2_callback(void);
void but3_callback(void);

void but1_callback(void) {
	but1_flag = 1;
}

void but2_callback(void) {
	but2_flag = !but2_flag;
}

void but3_callback(void) {
	but3_flag = !but3_flag;
}

typedef struct {
	char* nome;
	int* notasEDuracoes;
	int tamanho;
	int tempo;
} Musica;

// Funções
void set_buzzer(){
	pio_set(BUZZER_PIO_ID, BUZZER_PIO_IDX_MASK);
}

void clear_buzzer(){
	pio_clear(BUZZER_PIO_ID, BUZZER_PIO_IDX_MASK);
}

int get_startstop(){
	if(pio_get(BUT2_PIO_ID, PIO_INPUT, BUT2_PIO_IDX_MASK )){
		return 0;
	}
	return 1;
}

int get_selecao(){
	if(pio_get(BUT1_PIO_ID, PIO_INPUT, BUT1_PIO_IDX_MASK )){
		return 0;
	}
	return 1;
}

void buzzer_test(int freq) {
	
	int meia_freq = freq/2;

	while(1) {
		pio_set(BUZZER_PIO, BUZZER_PIO_IDX_MASK);  // Liga o buzzer
		delay_us(meia_freq);  // Aguarda meio período
		pio_clear(BUZZER_PIO, BUZZER_PIO_IDX_MASK);  // Desliga o buzzer
		delay_us(meia_freq);  // Aguarda meio período
	}
}

void tone(int freq, int time){
	
	int periodo = 1000000 / freq;
	int t = freq * time / 1000;
	
	if(freq == 0){
		delay_ms(time);
		return;
	}
	
	for(int i = 0; i < t; i++){
		pio_set(BUZZER_PIO, BUZZER_PIO_IDX_MASK);    // Liga o buzzer
		delay_us(periodo/2);						 // Aguarda meio período
		pio_clear(BUZZER_PIO, BUZZER_PIO_IDX_MASK);  // Desliga o buzzer
		delay_us(periodo/2);						 // Aguarda meio período
	}
}

void loop_musica(){
	
}

// Função init()
void init(void) {
	// Initialize the board clock
	sysclk_init();

	// Desativa WatchDog Timer
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	//Inicializando saída (buzzer)
	pmc_enable_periph_clk(BUZZER_PIO_ID);
	
	pio_set_output(BUZZER_PIO, BUZZER_PIO_IDX_MASK, 0, 0, 0);
	
	pio_pull_up(BUZZER_PIO, BUZZER_PIO_IDX_MASK, 1);
	
	// Inicializando GoBack (botão 1)
	pmc_enable_periph_clk(BUT1_PIO_ID);
	
	pio_set_input(BUT1_PIO, BUT1_PIO_IDX_MASK, PIO_DEFAULT);
	
	pio_pull_up(BUT1_PIO, BUT1_PIO_IDX_MASK, 1);
	
	pio_configure(BUT1_PIO, PIO_INPUT, BUT1_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	
	pio_set_debounce_filter(BUT1_PIO, BUT1_PIO_IDX_MASK, 60);
	
	// Inicializando Start/Stop (botão 2)
	pmc_enable_periph_clk(BUT2_PIO_ID);
	
	pio_set_input(BUT2_PIO, BUT2_PIO_IDX_MASK, PIO_DEFAULT);

	pio_pull_up(BUT2_PIO, BUT2_PIO_IDX_MASK, 1);
	
	pio_configure(BUT2_PIO, PIO_INPUT, BUT2_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	
	pio_set_debounce_filter(BUT2_PIO, BUT2_PIO_IDX_MASK, 60);
	
	// Inicializando GoFoward (botão 2)
	pmc_enable_periph_clk(BUT3_PIO_ID);
	
	pio_set_input(BUT3_PIO, BUT3_PIO_IDX_MASK, PIO_DEFAULT);

	pio_pull_up(BUT3_PIO, BUT3_PIO_IDX_MASK, 1);
	
	pio_configure(BUT3_PIO, PIO_INPUT, BUT3_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	
	pio_set_debounce_filter(BUT3_PIO, BUT3_PIO_IDX_MASK, 60);
	
	// Configura interrupção no pino referente ao botao e associa
	// função de callback caso uma interrupção for gerada		// a função de callback é a: but_callback()
	
	pio_handler_set(BUT1_PIO,
	BUT1_PIO_ID,
	BUT1_PIO_IDX_MASK,
	PIO_IT_FALL_EDGE,
	but1_callback);
	
	pio_handler_set(BUT2_PIO,
	BUT2_PIO_ID,
	BUT2_PIO_IDX_MASK,
	PIO_IT_FALL_EDGE,
	but2_callback);
	
	pio_handler_set(BUT3_PIO,
	BUT3_PIO_ID,
	BUT3_PIO_IDX_MASK,
	PIO_IT_FALL_EDGE,
	but3_callback);
	
	// Ativa interrupção e limpa primeira IRQ gerada na ativacao
	
	pio_enable_interrupt(BUT1_PIO, BUT1_PIO_IDX_MASK);
	pio_get_interrupt_status(BUT1_PIO);
	
	pio_enable_interrupt(BUT2_PIO, BUT2_PIO_IDX_MASK);
	pio_get_interrupt_status(BUT2_PIO);
	
	pio_enable_interrupt(BUT3_PIO, BUT3_PIO_IDX_MASK);
	pio_get_interrupt_status(BUT3_PIO);
	
	// Configura NVIC para receber interrupcoes do PIO do botao
	// com prioridade 4 (quanto mais próximo de 0 maior)
	
	NVIC_EnableIRQ(BUT1_PIO_ID);
	NVIC_SetPriority(BUT1_PIO_ID, 4); // Prioridade 4
	
	NVIC_EnableIRQ(BUT2_PIO_ID);
	NVIC_SetPriority(BUT2_PIO_ID, 4); // Prioridade 4
	
	NVIC_EnableIRQ(BUT3_PIO_ID);
	NVIC_SetPriority(BUT3_PIO_ID, 4); // Prioridade 4

}

int main (void){
	
	board_init();
	sysclk_init();
	delay_init();
	
	init();

	// Init OLED
	gfx_mono_ssd1306_init();
	
	//criando musicas
	Musica mario = {"Mario", melody_mario, sizeof(melody_mario)/sizeof(melody_mario[0]), 350};
	Musica starwars1 = {"ST1", melody_st1, sizeof(melody_st1)/sizeof(melody_st1[0]), 400};
	Musica starwars2 = {"ST2", melody_st2, sizeof(melody_st2)/sizeof(melody_st2[0]), 200};
	Musica zelda = {"Zelda", melody_zelda, sizeof(melody_zelda)/sizeof(melody_zelda[0]), 240};
	Musica asabranca = {"AsaBr.", melody_ab, sizeof(melody_ab)/sizeof(melody_ab[0]), 200};
	Musica nggyu = {"RickA.", melody_nggyu, sizeof(melody_nggyu)/sizeof(melody_nggyu[0]), 200};
	
	Musica musicas[] = {mario, starwars1, starwars2, zelda, asabranca, nggyu};
		
	int id_musica = 0;
	
	Musica musicaAtual = musicas[id_musica];
	
	int tamanho = musicaAtual.tamanho;
	
	int tempo = musicaAtual.tempo;

	int wholenote = (60000 * 4) / tempo;

	int divider = 0, noteDuration = 0;
	
	gfx_mono_draw_string(musicaAtual.nome, 50,16, &sysfont);
	
	/* Insert application code here, after the board has been initialized. */
	while(1) {
		for (int thisNote = 0; thisNote < tamanho; thisNote += 2) {
			pause_display_flag = 1;
			
			while(but2_flag) {
				if(pause_display_flag) {
					gfx_mono_draw_string("    PAUSE    ", 0, 16, &sysfont);
					pause_display_flag = 0;
				}
				display_flag = 1;
			}

			if (but1_flag) {
				id_musica = (id_musica - 1 + 6) % 6; // Volta para a música anterior
				musicaAtual = musicas[id_musica];
				tamanho = musicaAtual.tamanho;
				tempo = musicaAtual.tempo;
				wholenote = (60000 * 4) / tempo;
				thisNote = -2;
				but1_flag = 0; // Reseta a flag
				display_flag = 1; // Define a flag de exibição
			}

			if (but3_flag) {
				id_musica = (id_musica + 1) % 6; // Vai para a próxima música
				musicaAtual = musicas[id_musica];
				tamanho = musicaAtual.tamanho;
				tempo = musicaAtual.tempo;
				wholenote = (60000 * 4) / tempo;
				thisNote = -2;
				but3_flag = 0; // Reseta a flag
				display_flag = 1; // Define a flag de exibição
			}
			
			// Verifica se a flag de exibição está definida
			if (display_flag) {
				gfx_mono_draw_string("            ", 0, 16, &sysfont);
				gfx_mono_draw_string(musicaAtual.nome, 50, 16, &sysfont);
				display_flag = 0; // Limpa a flag de exibição
			}

			// Código existente para tocar uma nota
			int note = musicaAtual.notasEDuracoes[thisNote];
			int duracao = musicaAtual.notasEDuracoes[thisNote + 1];
			divider = duracao;

			if (divider > 0) {
				noteDuration = (wholenote) / divider;
				} else if (divider < 0) {
				noteDuration = (wholenote) / abs(divider);
				noteDuration *= 1.5; // Dotted notes are represented with negative durations
			}

			tone(note, noteDuration*0.9);
			delay_ms(noteDuration);
		}
	}
}