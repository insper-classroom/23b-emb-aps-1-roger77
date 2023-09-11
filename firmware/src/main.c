#include <asf.h>

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

#include "mariobros.h"

#define BUZZER_PIO PIOD
#define BUZZER_PIO_ID ID_PIOD
#define BUZZER_PIO_IDX 27
#define BUZZER_PIO_IDX_MASK (1u << BUZZER_PIO_IDX)

#define BUT2_PIO				PIOC
#define BUT2_PIO_ID				ID_PIOC
#define BUT2_PIO_IDX		    31
#define BUT2_PIO_IDX_MASK		(1u << BUT2_PIO_IDX)

#define BUT1_PIO PIOD
#define BUT1_PIO_ID ID_PIOD
#define BUT1_PIO_IDX 28
#define BUT1_PIO_IDX_MASK (1u << BUT1_PIO_IDX)

// Melodia Mario

typedef struct {
	char* nome;
	int* notasEDuracoes;
	int tamanho;
} Musica;

Musica mario = {"Mario", melody_mario, sizeof(melody_mario)/sizeof(melody_mario[0])};

// Fun��es
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
		delay_us(meia_freq);  // Aguarda meio per�odo
		pio_clear(BUZZER_PIO, BUZZER_PIO_IDX_MASK);  // Desliga o buzzer
		delay_us(meia_freq);  // Aguarda meio per�odo
	}
}

void tone(int freq, int time){
	
	int periodo = 1000000/freq;
	int t = freq*time/1000;
	
	for(int i = 0; i < t; i++){
		pio_set(BUZZER_PIO, BUZZER_PIO_IDX_MASK);  // Liga o buzzer
		delay_us(periodo/2);  // Aguarda meio per�odo
		pio_clear(BUZZER_PIO, BUZZER_PIO_IDX_MASK);  // Desliga o buzzer
		delay_us(periodo/2);  // Aguarda meio per�odo
	}
}

// Fun��o init()
void init(void) {
	// Initialize the board clock
	sysclk_init();

	// Desativa WatchDog Timer
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	//Inicializando sa�da (buzzer)
	pmc_enable_periph_clk(BUZZER_PIO_ID);
	
	pio_set_output(BUZZER_PIO, BUZZER_PIO_IDX_MASK, 0, 0, 0);
	
	pio_pull_up(BUZZER_PIO, BUZZER_PIO_IDX_MASK, 1);
	
	// Inicializando Start/Stop (bot�o 2)
	pmc_enable_periph_clk(BUT2_PIO_ID);
	
	pio_set_input(BUT2_PIO, BUT2_PIO_IDX_MASK, PIO_DEFAULT);

	pio_pull_up(BUT2_PIO, BUT2_PIO_IDX_MASK, 1);
	
	// Inicializando Sele��o (bot�o 1)
	pmc_enable_periph_clk(BUT1_PIO_ID);
	
	pio_set_input(BUT1_PIO, BUT1_PIO_IDX_MASK, PIO_DEFAULT);
	
	pio_pull_up(BUT1_PIO, BUT1_PIO_IDX_MASK, 1);

}

int main (void){
	
	int tempo = 350;

	int notes = sizeof(melody_mario) / sizeof(melody_mario[0]) / 2;

	int wholenote = (60000 * 4) / tempo;

	int divider = 0, noteDuration = 0;
	
	board_init();
	sysclk_init();
	delay_init();
	
	init();

	// Init OLED
	gfx_mono_ssd1306_init();
	
	// Musica atual
	Musica musicaAtual = mario;
	int tamanho = musicaAtual.tamanho;
	
	// Escreve na tela um circulo e um texto
	gfx_mono_draw_filled_circle(20, 16, 16, GFX_PIXEL_SET, GFX_WHOLE);
	gfx_mono_draw_string(musicaAtual.nome, 50,16, &sysfont);
	
	/* Insert application code here, after the board has been initialized. */
	while(1) {
		for (int thisNote = 0; thisNote < tamanho; thisNote += 2) {
			int note = musicaAtual.notasEDuracoes[thisNote];
			int duracao = musicaAtual.notasEDuracoes[thisNote + 1];
			divider = duracao;
			
			if (divider > 0) {
				noteDuration = (wholenote) / divider;
				} else if (divider < 0) {
				noteDuration = (wholenote) / abs(divider);
				noteDuration *= 1.5;
			}

			tone(note, noteDuration*0.9);
			delay_ms(noteDuration);
		}
	}
}