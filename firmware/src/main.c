#include <asf.h>

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

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

//Notas

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55

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
	
	int meia_freq = freq/2;
	
	for(int i = 0; i < time; i++){
		pio_set(BUZZER_PIO, BUZZER_PIO_IDX_MASK);  // Liga o buzzer
		delay_us(meia_freq);  // Aguarda meio período
		pio_clear(BUZZER_PIO, BUZZER_PIO_IDX_MASK);  // Desliga o buzzer
		delay_us(meia_freq);  // Aguarda meio período
	}
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
	
	// Inicializando Start/Stop (botão 2)
	pmc_enable_periph_clk(BUT2_PIO_ID);
	
	pio_set_input(BUT2_PIO, BUT2_PIO_IDX_MASK, PIO_DEFAULT);

	pio_pull_up(BUT2_PIO, BUT2_PIO_IDX_MASK, 1);
	
	// Inicializando Seleção (botão 1)
	pmc_enable_periph_clk(BUT1_PIO_ID);
	
	pio_set_input(BUT1_PIO, BUT1_PIO_IDX_MASK, PIO_DEFAULT);
	
	pio_pull_up(BUT1_PIO, BUT1_PIO_IDX_MASK, 1);
}

int main (void)
{
	board_init();
	sysclk_init();
	delay_init();
	
	init();

	// Init OLED
	gfx_mono_ssd1306_init();
	
	// Escreve na tela um circulo e um texto
	gfx_mono_draw_filled_circle(20, 16, 16, GFX_PIXEL_SET, GFX_WHOLE);
	gfx_mono_draw_string("Issue 5", 50,16, &sysfont);
	
	for (int freq=200; freq<5000; freq+=500){
		tone(freq, 200 + freq/2);
		delay_ms(200);
	}
	
	/* Insert application code here, after the board has been initialized. */
	while(1) {

	}
}
