#include <asf.h>

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

#include "asabranca.h"
#include "mariobros.h"
#include "starwars.h"
#include "music.h"
#include "nggyu.h"
#include "utils.h"
#include "zeldastheme.h"

// Flags
volatile char but1_flag;
volatile char but2_flag;
volatile char but3_flag;
volatile char display_flag;
volatile char pause_display_flag;

// Callbacks
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

int main (void){
	board_init();
	sysclk_init();
	delay_init();
	
	init();

	// Init OLED
	gfx_mono_ssd1306_init();
	
	// Criando músicas
	Musica mario = {"Mario", melody_mario, sizeof(melody_mario)/sizeof(melody_mario[0]), 200};
	Musica starwars1 = {"ST1", melody_st1, sizeof(melody_st1)/sizeof(melody_st1[0]), 200};
	Musica starwars2 = {"ST2", melody_st2, sizeof(melody_st2)/sizeof(melody_st2[0]), 120};
	Musica zelda = {"Zelda", melody_zelda, sizeof(melody_zelda)/sizeof(melody_zelda[0]), 120};
	Musica asabranca = {"AsaBr.", melody_ab, sizeof(melody_ab)/sizeof(melody_ab[0]), 100};
	Musica nggyu = {"RickA.", melody_nggyu, sizeof(melody_nggyu)/sizeof(melody_nggyu[0]), 110};
	
	Musica musicas[] = {mario, starwars1, starwars2, zelda, asabranca, nggyu};
	
	int id_musica = 0;
	
	Musica musicaAtual = musicas[id_musica];
	
	int tamanho = musicaAtual.tamanho;
	
	int tempo = musicaAtual.tempo;

	int wholenote = (60000 * 4) / tempo;

	int divider = 0, noteDuration = 0;
	
	gfx_mono_draw_string(musicaAtual.nome, 50,16, &sysfont);
	
	while(1) {
		loop_musica(tamanho, id_musica, tempo, wholenote, divider, noteDuration, musicaAtual, musicas);
	}
}