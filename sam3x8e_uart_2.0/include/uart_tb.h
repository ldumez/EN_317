#ifndef uart_tb_h
#define uart_tb_h

#include <string>
#include "systemc"
using namespace sc_core;
using namespace sc_dt;
using namespace std;


#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"
#include "tlm.h"


SC_MODULE(uart_tb)            // declare add sc_module
{

  SC_CTOR(uart_tb)
  {
    from_uart_tx_rx.register_b_transport(this, &uart_tb::receive_data_rx);
    from_uart_apb_rx.register_b_transport(this, &uart_tb::receive_data_apb);
    from_uart_irq_rx.register_b_transport(this, &uart_tb::receive_data_irq);
    init();
    exec_test();
  }

  void send_data_tx(int data, int size);
  void send_data_pmc(int data, int size);
  void send_data_apb(int data_s, int adr, int size, tlm::tlm_command cmd);

  void receive_data_rx( tlm::tlm_generic_payload& trans, sc_time& delay );
  void receive_data_apb( tlm::tlm_generic_payload& trans, sc_time& delay );
  void receive_data_irq( tlm::tlm_generic_payload& trans, sc_time& delay );

  void init();
  void exec_test();

  tlm_utils::simple_initiator_socket<uart_tb> to_uart_rx_tx;
  tlm_utils::simple_target_socket<uart_tb> from_uart_tx_rx;

  tlm_utils::simple_initiator_socket<uart_tb> to_uart_apb_tx;
  tlm_utils::simple_target_socket<uart_tb> from_uart_apb_rx;

  tlm_utils::simple_initiator_socket<uart_tb> to_uart_pmc_tx;

  tlm_utils::simple_target_socket<uart_tb> from_uart_irq_rx;
};
#endif
