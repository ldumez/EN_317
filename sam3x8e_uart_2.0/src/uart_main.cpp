#include "../include/uart.h"
#include "../include/uart_tb.h"
#include <iostream>
#include "systemc.h"
#include "tlm.h"

#define BASE_ADR_UART0 0
#define BASE_ADR_UART1 1
#define BASE_ADR_UART2 2
#define BASE_ADR_UART3 3

int sc_main(int argc, char* argv[]){

uart uart0("uart0");

uart_tb uart_tb0("uart_tb0");

uart_tb0.to_uart_apb_tx.bind( uart0.apb_rx);
uart_tb0.to_uart_rx_tx.bind( uart0.socket_rx );
uart_tb0.to_uart_pmc_tx.bind( uart0.pmc_rx );
uart0.socket_tx.bind( uart_tb0.from_uart_tx_rx );
uart0.apb_tx.bind( uart_tb0.from_uart_apb_rx );
uart0.irq_tx.bind( uart_tb0.from_uart_irq_rx);

sc_start();

uart_tb0.init();
uart_tb0.exec_test();

return 0;

}
