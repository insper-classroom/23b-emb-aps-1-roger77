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
		for (int thisNote = 0; thisNote < tamanho; thisNote += 2) {
			pause_display_flag = 1;
			
			// C?lculo do progresso atual
			float progress = (float)thisNote / (float)tamanho;
			int progressWidth = (int)(progress * 128);

			// Desenhando a barra de progresso
			gfx_mono_draw_filled_rect(0, 0, progressWidth, 10, GFX_PIXEL_SET);
			gfx_mono_draw_filled_rect(progressWidth, 0, 128 - progressWidth, 10, GFX_PIXEL_CLR);
			
			while(but2_flag) {
				if(pause_display_flag) {
					gfx_mono_draw_string("    PAUSE    ", 0, 16, &sysfont);
					pause_display_flag = 0;
				}
				display_flag = 1;
			}

			if (but1_flag || but3_flag) {
				if (but1_flag) {
					id_musica = (id_musica - 1 + 6) % 6;  // Volta para a música anterior
					but1_flag = 0;                        // Reseta a flag
					} else if (but3_flag) {
					id_musica = (id_musica + 1) % 6;      // Vai para a próxima música
					but3_flag = 0;                        // Reseta a flag
				}

				// Código comum entre but1_flag e but3_flag
				musicaAtual = musicas[id_musica];
				tamanho = musicaAtual.tamanho;
				tempo = musicaAtual.tempo;
				wholenote = (60000 * 4) / tempo;
				thisNote = -2;
				display_flag = 1;                         // Define a flag de exibição
			}
			
			// Verifica se a flag de exibi??o est? definida
			if (display_flag) {
				gfx_mono_draw_string("            ", 0, 16, &sysfont);
				gfx_mono_draw_string(musicaAtual.nome, 50, 16, &sysfont);
				display_flag = 0;                     // Limpa a flag de exibi??o
			}

			// C?digo existente para tocar uma nota
			int note = musicaAtual.notasEDuracoes[thisNote];
			int duracao = musicaAtual.notasEDuracoes[thisNote + 1];
			divider = duracao;

			if (divider > 0) {
				noteDuration = (wholenote) / divider;
				} else if (divider < 0) {
				noteDuration = (wholenote) / abs(divider);
				noteDuration *= 1.5;                  // Dotted notes are represented with negative durations
			}

			tone(note, noteDuration);
			delay_ms(0.1*noteDuration);
		}
	}
}