

#ifndef class_reg_uart_mr_h
#define class_reg_uart_mr_h

#include "../include/class_reg_32.h"

class class_reg_uart_mr : public class_reg_32 // Mode Register
	{
		public:

			class_reg_uart_mr();

    	void write(int data);

	//	private:


			// Parity Type
			int par; 				// 3 bits : 9 à 11
			const int mask_par = 0xE00;
			const int start_par = 9;

			// Channel Mode
			int chmode;				// 2 bits : 14 et 15
			const int mask_chmode = 0xC000;
			const int start_chmode = 14;
	};
#endif
