
#ifndef class_reg_uart_cr_h
#define class_reg_uart_cr_h

#include "../include/class_reg_32.h"

class class_reg_uart_cr : public class_reg_32
{
  public:
      class_reg_uart_cr();

      void write(int data);

  //private:

    int rstrx;
    const int mask_rstrx = 0x4;
    const int start_rstrx = 2;

    int rsttx;
    const int mask_rsttx = 0x8;
    const int start_rsttx = 3;

    int rxen;
    const int mask_rxen = 0x10;
    const int start_rxen = 4;

    int rxdis;
    const int mask_rxdis = 0x20;
    const int start_rxdis = 5;

    int txen;
    const int mask_txen = 0x40;
    const int start_txen = 6;

    int txdis;
    const int mask_txdis = 0x80;
    const int start_txdis = 7;

    int rststa;
    const int mask_rststa = 0x100;
    const int start_rststa = 8;
};

#endif /* reg_uart_cr_h */
