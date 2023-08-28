#include <asf.h>

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

#define BUZZER_PIO PIOD
#define BUZZER_PIO_ID ID_PIOD
#define BUZZER_PIO_IDX 27
#define BUZZER_PIO_IDX_MASK (1u << BUZZER_PIO_IDX)

//Funcoes

void set_buzzer(Pio *p_pio, const uint32_t ul_mask){
	p_pio->PIO_SODR = ul_mask;
}

void clear_buzzer(Pio *p_pio, const uint32_t ul_mask)
{
	p_pio->PIO_CODR = ul_mask;
}

void init(void){
	  // Initialize the board clock
	  sysclk_init();

	  // Desativa WatchDog Timer
	  WDT->WDT_MR = WDT_MR_WDDIS;
	  
	  //Inicializando saida
	  pmc_enable_periph_clk(BUZZER_PIO_ID);
	  
	  pio_set_output(BUZZER_PIO, BUZZER_PIO_IDX_MASK, 0, 0, 0);
	  
	  
}

int main (void)
{
	board_init();
	sysclk_init();
	delay_init();

  // Init OLED
	gfx_mono_ssd1306_init();
  
  // Escreve na tela um circulo e um texto
	gfx_mono_draw_filled_circle(20, 16, 16, GFX_PIXEL_SET, GFX_WHOLE);
  gfx_mono_draw_string("mundo", 50,16, &sysfont);

  /* Insert application code here, after the board has been initialized. */
	while(1) {

	}
}
