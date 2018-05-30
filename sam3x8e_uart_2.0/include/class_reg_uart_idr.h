
#ifndef class_reg_uart_idr_h
#define class_reg_uart_idr_h

#include "../include/class_reg_32.h"

class class_reg_uart_idr : public class_reg_32 //Interrupt Disable Register
	{
		public:

			class_reg_uart_idr();

    	void write(int data);


		//private:


			// Disable RXRDY Interrupt
			int rxrdy; 				// 1 bit : 0
			const int mask_rxrdy = 0x1;
			const int start_rxrdy = 0;

			// Disable TXRDY Interrupt
			int txrdy;				// 1 bit : 1
			const int mask_txrdy = 0x2;
			const int start_txrdy = 1;

			// Disable End of Receive Transfer Interrupt
			int endrx;				// 1 bit : 1
			const int mask_endrx = 0x8;
			const int start_endrx = 3;

			// Disable End of Transmit Interrupt
			int endtx;				// 1 bit : 1
			const int mask_endtx = 0x10;
			const int start_endtx = 4;

			// Disable Overrun Error Interrupt
			int ovre;				// 1 bit : 1
			const int mask_ovre = 0x20;
			const int start_ovre = 5;

			// Disable Framing Error Interrupt
			int frame;				// 1 bit : 1
			const int mask_frame = 0x40;
			const int start_frame = 6;

			// Disable Parity Error Interrupt
			int pare;				// 1 bit : 1
			const int mask_pare = 0x80;
			const int start_pare = 7;

			// Disable TXEMPTY Interrupt
			int txempty;				// 1 bit : 1
			const int mask_txempty = 0x200;
			const int start_txempty = 9;

			// Disable Buffer Empty Interrupt
			int txbufe;				// 1 bit : 1
			const int mask_txbufe = 0x800;
			const int start_txbufe = 11;

			// Disable Buffer Full Interrupt
			int rxbuff;				// 1 bit : 1
			const int mask_rxbuff = 0x1000;
			const int start_rxbuff = 12;
};
#endif
