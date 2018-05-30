#include "../include/class_reg_uart_mr.h"
class_reg_uart_mr::class_reg_uart_mr() : class_reg_32(), par(0), chmode(0)
	{
	}

void class_reg_uart_mr::write(int data){
	
	par = ( data & mask_par ) >> start_par;
	chmode	= ( data & mask_chmode ) >> start_chmode;
}
