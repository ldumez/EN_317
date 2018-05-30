#include "../include/uart.h"
#include <iostream>
#include "systemc.h"
#define BASE_ADR_UART0 0
#define BASE_ADR_UART1 1
#define BASE_ADR_UART2 2
#define BASE_ADR_UART3 3

int sc_main(int argc, char* argv[]){

uart uart0("uart0");
uart uart1("uart1");
uart uart2("uart2");
uart uart3("uart3");

sc_start();

return 0;

}
