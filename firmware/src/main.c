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
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

// Melodia Mario

typedef struct {
	char* nome;
	int* notasEDuracoes;
	int tamanho;
} Musica;

int melody_mario[] = {

	// Super Mario Bros theme
	// Score available at https://musescore.com/user/2123/scores/2145
	// Theme by Koji Kondo
	
	
	NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,8, //1
	NOTE_G5,4, REST,4, NOTE_G4,8, REST,4,
	NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 3
	NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
	NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
	REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
	NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 3
	NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
	NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
	REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

	
	REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//7
	REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
	REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
	NOTE_C5,2, REST,2,

	REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//repeats from 7
	REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
	REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
	NOTE_C5,2, REST,2,

	NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,//11
	NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,

	NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,//13
	REST,1,
	NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,
	NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
	NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
	NOTE_G5,4, REST,4, NOTE_G4,4, REST,4,
	NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 19
	
	NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
	NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
	REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

	NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 19
	NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
	NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
	REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

	NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,//23
	NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
	NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
	
	NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //26
	NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
	NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
	NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
	NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,

	NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,//repeats from 23
	NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
	NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
	
	NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //26
	NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
	NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
	NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
	NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
	NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,
	REST,1,

	NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4, //33
	NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
	NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
	NOTE_G5,4, REST,4, NOTE_G4,4, REST,4,
	NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
	NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
	NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
	
	NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //40
	NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
	NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
	NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
	NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
	
	//game over sound
	NOTE_C5,-4, NOTE_G4,-4, NOTE_E4,4, //45
	NOTE_A4,-8, NOTE_B4,-8, NOTE_A4,-8, NOTE_GS4,-8, NOTE_AS4,-8, NOTE_GS4,-8,
	NOTE_G4,8, NOTE_D4,8, NOTE_E4,-2,

};

Musica mario = {"Mario", melody_mario, sizeof(melody_mario)/sizeof(melody_mario[0])};

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
	
	int periodo = 1000000/freq;
	int t = freq*time/1000;
	
	for(int i = 0; i < t; i++){
		pio_set(BUZZER_PIO, BUZZER_PIO_IDX_MASK);  // Liga o buzzer
		delay_us(periodo/2);  // Aguarda meio período
		pio_clear(BUZZER_PIO, BUZZER_PIO_IDX_MASK);  // Desliga o buzzer
		delay_us(periodo/2);  // Aguarda meio período
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