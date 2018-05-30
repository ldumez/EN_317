#include "../include/class_reg_uart_idr.h"

class_reg_uart_idr::class_reg_uart_idr() : class_reg_32(),rxrdy(0),	txrdy(0),	endrx(0),	endtx(0),	ovre(0),	frame(0),
	pare(0), txempty(0), txbufe(0),	rxbuff(0)
	{
	}

void class_reg_uart_idr::write(int data){
	rxrdy = ( data & mask_rxrdy ) >> start_rxrdy;
	txrdy = ( data & mask_txrdy ) >> start_txrdy;
	endrx = ( data & mask_endrx ) >> start_endrx;
	endtx = ( data & mask_endtx ) >> start_endtx;
	ovre = ( data & mask_ovre ) >> start_ovre;
	frame = ( data & mask_frame ) >> start_frame;
	pare = ( data & mask_pare ) >> start_pare;
	txempty = ( data & mask_txempty ) >> start_txempty;
	txbufe = ( data & mask_txbufe ) >> start_txbufe;
	rxbuff = ( data & mask_rxbuff ) >> start_rxbuff;
}
