#include "../include/class_reg_uart_sr.h"

class_reg_uart_sr::class_reg_uart_sr() : class_reg_32(), rxrdy(0),
txrdy(0),	endrx(0),	endtx(0),	ovre(0), frame(0),	pare(0), txempty(0),
txbufe(0), rxbuff(0)
	{
	}

void class_reg_uart_sr::write(int data){
	//nothing to do
}
