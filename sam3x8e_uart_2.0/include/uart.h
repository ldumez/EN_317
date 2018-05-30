#ifndef uart_h
#define uart_h

#include <iostream>
#include "systemc"
#include "class_reg_uart_mr.h"
#include "class_reg_uart_sr.h"
#include "class_reg_uart_cr.h"
#include "class_reg_uart_idr.h"
#include "class_reg_uart_imr.h"
#include "class_reg_uart_ier.h"
#include "class_reg_uart_thr.h"
#include "class_reg_32.h"
#include <string>
using namespace sc_core;
using namespace sc_dt;
using namespace std;


#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"
#include "tlm.h"

SC_MODULE(uart)            // declare add sc_module
{
public:
  SC_CTOR(uart) : reg_uart_cr(class_reg_uart_cr()),
  reg_uart_mr(class_reg_uart_mr()),
  reg_uart_ier(class_reg_uart_ier()),
  reg_uart_idr(class_reg_uart_idr()),
  reg_uart_rhr(class_reg_32()),
  reg_uart_brgr(class_reg_32()),
  reg_uart_thr(class_reg_uart_thr()),
  reg_uart_imr(class_reg_uart_imr()),
  reg_uart_sr(class_reg_uart_sr())
  {
    socket_rx.register_b_transport(this, &uart::receive_data_rx);
    apb_rx.register_b_transport(this, &uart::receive_data_apb);
    pmc_rx.register_b_transport(this, &uart::receive_data_pmc);
  }
  void  write (int data, int offset);
  int   read  (int offset);
  int   reset ();

  void send_data_tx(int data, int size);
  void send_data_irq(int data, int size);
  void send_data_apb(int data, int size);

  void receive_data_rx( tlm::tlm_generic_payload& trans, sc_time& delay );
  void receive_data_pmc( tlm::tlm_generic_payload& trans, sc_time& delay );
  void receive_data_apb( tlm::tlm_generic_payload& trans, sc_time& delay );

  tlm_utils::simple_initiator_socket<uart> socket_tx;
  tlm_utils::simple_target_socket<uart> socket_rx;

  tlm_utils::simple_initiator_socket<uart> apb_tx;
  tlm_utils::simple_target_socket<uart> apb_rx;

  tlm_utils::simple_initiator_socket<uart> irq_tx;

  tlm_utils::simple_target_socket<uart> pmc_rx;

  class_reg_uart_cr  	reg_uart_cr;
  class_reg_uart_mr 	reg_uart_mr;
  class_reg_uart_ier 	reg_uart_ier;
  class_reg_uart_idr 	reg_uart_idr;
  class_reg_32        reg_uart_rhr;
  class_reg_32      	reg_uart_brgr;
  class_reg_uart_thr  reg_uart_thr;
  class_reg_uart_imr  reg_uart_imr;
  class_reg_uart_sr   reg_uart_sr;

  int base_adr;
  int pmc_enable;
};
#endif
