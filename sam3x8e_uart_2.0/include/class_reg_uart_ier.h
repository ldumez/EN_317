#ifndef CLASS_REG_UART_IER_H
#define CLASS_REG_UART_IER_H

#include "../include/class_reg_32.h"

class class_reg_uart_ier : public class_reg_32 //Interrupt Enable Register
	{
		public:
			class_reg_uart_ier();

	    void write(int data);

		//private:

			// Enable RXRDY Interrupt
			int rxrdy; 				// 1 bit : 0
			const int mask_rxrdy = 0x1;
			const int start_rxrdy = 0;

			// Enable TXRDY Interrupt
			int txrdy;				// 1 bit : 1
			const int mask_txrdy = 0x2;
			const int start_txrdy = 1;

			// Enable End of Receive Transfer Interrupt
			int endrx;				// 1 bit : 1
			const int mask_endrx = 0x8;
			const int start_endrx = 3;

			// Enable End of Transmit Interrupt
			int endtx;				// 1 bit : 1
			const int mask_endtx = 0x10;
			const int start_endtx = 4;

			// Enable Overrun Error Interrupt
			int ovre;				// 1 bit : 1
			const int mask_ovre = 0x20;
			const int start_ovre = 5;

			// Enable Framing Error Interrupt
			int frame;				// 1 bit : 1
			const int mask_frame = 0x40;
			const int start_frame = 6;

			// Enable Parity Error Interrupt
			int pare;				// 1 bit : 1
			const int mask_pare = 0x80;
			const int start_pare = 7;

			// Enable TXEMPTY Interrupt
			int txempty;				// 1 bit : 1
			const int mask_txempty = 0x200;
			const int start_txempty = 9;

			// Enable Buffer Empty Interrupt
			int txbufe;				// 1 bit : 1
			const int mask_txbufe = 0x800;
			const int start_txbufe = 11;

			// Enable Buffer Full Interrupt
			int rxbuff;				// 1 bit : 1
			const int mask_rxbuff = 0x1000;
			const int start_rxbuff = 12;
};

#endif
