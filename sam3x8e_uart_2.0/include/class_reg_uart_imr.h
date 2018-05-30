
#ifndef class_reg_uart_imr_h
#define class_reg_uart_imr_h

#include "../include/class_reg_32.h"

class class_reg_uart_imr : public class_reg_32 //Interrupt Enable Register
	{
		public:

			class_reg_uart_imr();

    	void write(int data);

		//private:

			// Mask RXRDY Interrupt
			int rxrdy; 				// 1 bit : 0
			const int mask_rxrdy = 0x1;
			const int start_rxrdy = 0;

			// Mask TXRDY Interrupt
			int txrdy;				// 1 bit : 1
			const int mask_txrdy = 0x2;
			const int start_txrdy = 1;

			// Mask End of Receive Transfer Interrupt
			int endrx;				// 1 bit : 1
			const int mask_endrx = 0x8;
			const int start_endrx = 3;

			// Mask End of Transmit Interrupt
			int endtx;				// 1 bit : 1
			const int mask_endtx = 0x10;
			const int start_endtx = 4;

			// Mask Overrun Error Interrupt
			int ovre;				// 1 bit : 1
			const int mask_ovre = 0x20;
			const int start_ovre = 5;

			// Mask Framing Error Interrupt
			int frame;				// 1 bit : 1
			const int mask_frame = 0x40;
			const int start_frame = 6;

			// Mask Parity Error Interrupt
			int pare;				// 1 bit : 1
			const int mask_pare = 0x80;
			const int start_pare = 7;

			// Mask TXEMPTY Interrupt
			int txempty;				// 1 bit : 1
			const int mask_txempty = 0x200;
			const int start_txempty = 9;

			// Mask TXBUFE Interrupt
			int txbufe;				// 1 bit : 1
			const int mask_txbufe = 0x800;
			const int start_txbufe = 11;

			// Mask RXBUFF Interrupt
			int rxbuff;				// 1 bit : 1
			const int mask_rxbuff = 0x1000;
			const int start_rxbuff = 12;
	};
#endif
