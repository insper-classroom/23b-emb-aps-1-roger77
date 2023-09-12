/*
 * utils.c
 *
 * Created: 12/09/2023 14:31:27
 *  Author: Gabriel
 */ 
#include "utils.h"

void set_buzzer(){
	pio_set(BUZZER_PIO, BUZZER_PIO_IDX_MASK);
}

void clear_buzzer(){
	pio_clear(BUZZER_PIO, BUZZER_PIO_IDX_MASK);
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
	
	// Inicializando GoFoward (botão 3)
	pmc_enable_periph_clk(BUT3_PIO_ID);
	
	pio_set_input(BUT3_PIO, BUT3_PIO_IDX_MASK, PIO_DEFAULT);

	pio_pull_up(BUT3_PIO, BUT3_PIO_IDX_MASK, 1);
	
	pio_configure(BUT3_PIO, PIO_INPUT, BUT3_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	
	pio_set_debounce_filter(BUT3_PIO, BUT3_PIO_IDX_MASK, 60);
	
	// LED que pisca junto às notas
	pmc_enable_periph_clk(LED_PIO_ID);
	
	pio_configure(LED_PIO, PIO_OUTPUT_0,LED_PIO_IDX_MASK, PIO_DEFAULT);
	
	pmc_enable_periph_clk(LED1_PIO_ID);
	
	pio_configure(LED1_PIO, PIO_OUTPUT_0,LED1_PIO_IDX_MASK, PIO_DEFAULT);
	
	pmc_enable_periph_clk(LED2_PIO_ID);
	
	pio_configure(LED2_PIO, PIO_OUTPUT_0,LED2_PIO_IDX_MASK, PIO_DEFAULT);
	
	pmc_enable_periph_clk(LED3_PIO_ID);
	
	pio_configure(LED3_PIO, PIO_OUTPUT_0,LED3_PIO_IDX_MASK, PIO_DEFAULT);
	
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

void tone(int freq, int time){
	int periodo = 1000000 / freq;
	int t = freq * time / 1000;
	
	if(freq == 0){
		delay_ms(time);
		return;
	}
	
	for(int i = 0; i < t; i++){
		set_buzzer();                               // Liga o buzzer
		
		pio_clear(LED_PIO, LED_PIO_IDX_MASK);
		pio_clear(LED1_PIO, LED1_PIO_IDX_MASK);
		pio_clear(LED2_PIO, LED2_PIO_IDX_MASK);
		pio_clear(LED3_PIO, LED3_PIO_IDX_MASK);
		
		delay_us(periodo/2);						 // Aguarda meio período
		
		clear_buzzer();                               // Desliga o buzzer
		
		delay_us(periodo/2);						 // Aguarda meio período
		
		pio_set(LED_PIO, LED_PIO_IDX_MASK);
		pio_set(LED1_PIO, LED1_PIO_IDX_MASK);
		pio_set(LED2_PIO, LED2_PIO_IDX_MASK);
		pio_set(LED3_PIO, LED3_PIO_IDX_MASK);
	}
}

void loop_musica(int tamanho, int id_musica, int tempo, int wholenote, int divider, int noteDuration, Musica musicaAtual, Musica musicas[]){
	while(1) {
		for (int thisNote = 0; thisNote < tamanho; thisNote += 2) {
			pause_display_flag = 1;
			
			// Cálculo do progresso atual
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

			if (but1_flag) {
				id_musica = (id_musica - 1 + 6) % 6;  // Volta para a música anterior
				musicaAtual = musicas[id_musica];
				tamanho = musicaAtual.tamanho;
				tempo = musicaAtual.tempo;
				wholenote = (60000 * 4) / tempo;
				thisNote = -2;
				but1_flag = 0;                        // Reseta a flag
				display_flag = 1;                     // Define a flag de exibição
			}

			if (but3_flag) {
				id_musica = (id_musica + 1) % 6;      // Vai para a próxima música
				musicaAtual = musicas[id_musica];
				tamanho = musicaAtual.tamanho;
				tempo = musicaAtual.tempo;
				wholenote = (60000 * 4) / tempo;
				thisNote = -2;
				but3_flag = 0;                        // Reseta a flag
				display_flag = 1;                     // Define a flag de exibição
			}
			
			// Verifica se a flag de exibição está definida
			if (display_flag) {
				gfx_mono_draw_string("            ", 0, 16, &sysfont);
				gfx_mono_draw_string(musicaAtual.nome, 50, 16, &sysfont);
				display_flag = 0;                     // Limpa a flag de exibição
			}

			// Código existente para tocar uma nota
			int note = musicaAtual.notasEDuracoes[thisNote];
			int duracao = musicaAtual.notasEDuracoes[thisNote + 1];
			divider = duracao;

			if (divider > 0) {
				noteDuration = (wholenote) / divider;
				} else if (divider < 0) {
				noteDuration = (wholenote) / abs(divider);
				noteDuration *= 1.5;                  // Dotted notes are represented with negative durations
			}

			tone(note, noteDuration*0.9);
			delay_ms(noteDuration);
		}
	}
}