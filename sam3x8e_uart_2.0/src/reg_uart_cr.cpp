#include "../include/class_reg_uart_cr.h"

class_reg_uart_cr::class_reg_uart_cr() : class_reg_32(),rstrx(0), rsttx(1),
 rxen(0),rxdis(0), txen(0), txdis(0),rststa(0)
{
}

void class_reg_uart_cr::write(int data){
  set_reg_value(data);
  rstrx  = ( data &  mask_rstrx ) >>  start_rstrx;
  rsttx  = ( data &  mask_rsttx ) >>  start_rsttx;
  rxen  = ( data &  mask_rxen ) >>  start_rxen;
  rxdis  = ( data &  mask_rxdis ) >>  start_rxdis;
  txen  = ( data &  mask_txen ) >>  start_txen;
  txdis  = ( data & mask_txdis ) >>  start_txdis;
  rststa  = ( data & mask_rststa ) >>  start_rststa;
}
