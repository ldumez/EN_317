#include "../include/uart_tb.h"

void uart_tb::send_data_apb(int data_s, int adr, int size)
{
  // TLM-2 generic payload transaction, reused across calls to b_transport
  tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
  sc_time delay = sc_time(10, SC_NS);


    trans->set_data_ptr( reinterpret_cast<unsigned char*>(&data_s) );
    trans->set_data_length( size );
    trans->set_address( adr );
    trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE ); // Mandatory initial value

    to_uart_apb_tx->b_transport( *trans, delay );  // Blocking transport call

    // Initiator obliged to check response status and delay
    if ( trans->is_response_error() )
      SC_REPORT_ERROR("TLM-2", "Response error from b_transport");

    cout << "trans : " << " data = " << data_s << endl;

    // Realize the delay annotated onto the transport call
    wait(delay);
}

void uart_tb::send_data_tx(int data_s, int size)
{
  // TLM-2 generic payload transaction, reused across calls to b_transport
  tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
  sc_time delay = sc_time(10, SC_NS);


    trans->set_data_ptr( reinterpret_cast<unsigned char*>(&data_s) );
    trans->set_data_length( size );
    trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE ); // Mandatory initial value

    to_uart_rx_tx->b_transport( *trans, delay );  // Blocking transport call

    // Initiator obliged to check response status and delay
    if ( trans->is_response_error() )
      SC_REPORT_ERROR("TLM-2", "Response error from b_transport");

    cout << "trans : " << " data = " << data_s << endl;

    // Realize the delay annotated onto the transport call
    wait(delay);
}

void uart_tb::send_data_pmc(int data_s, int size)
{
  // TLM-2 generic payload transaction, reused across calls to b_transport
  tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
  sc_time delay = sc_time(10, SC_NS);


    trans->set_data_ptr( reinterpret_cast<unsigned char*>(&data_s) );
    trans->set_data_length( size );
    trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE ); // Mandatory initial value

    to_uart_pmc_tx->b_transport( *trans, delay );  // Blocking transport call

    // Initiator obliged to check response status and delay
    if ( trans->is_response_error() )
      SC_REPORT_ERROR("TLM-2", "Response error from b_transport");

    cout << "trans : " << " data = " << data_s << endl;

    // Realize the delay annotated onto the transport call
    wait(delay);
}

  void uart_tb::receive_data_rx( tlm::tlm_generic_payload& trans, sc_time& delay )
{
  unsigned char*   ptr = trans.get_data_ptr();
  unsigned int     len = trans.get_data_length();


  if (len = 0)
    SC_REPORT_ERROR("TLM-2", "Target does not support given generic payload transaction");
  // Obliged to set response status to indicate successful completion
  trans.set_response_status( tlm::TLM_OK_RESPONSE );
}


  void uart_tb::receive_data_irq( tlm::tlm_generic_payload& trans, sc_time& delay )
{
  unsigned char*   ptr = trans.get_data_ptr();
  unsigned int     len = trans.get_data_length();

  if (len = 0)
    SC_REPORT_ERROR("TLM-2", "Target does not support given generic payload transaction");
  // Obliged to set response status to indicate successful completion
  trans.set_response_status( tlm::TLM_OK_RESPONSE );
}


  void uart_tb::receive_data_apb( tlm::tlm_generic_payload& trans, sc_time& delay )
{
  unsigned char*   ptr = trans.get_data_ptr();
  unsigned int     len = trans.get_data_length();
  sc_dt::uint64    adr = trans.get_address();

  if (len = 0)
    SC_REPORT_ERROR("TLM-2", "Target does not support given generic payload transaction");
  // Obliged to set response status to indicate successful completion
  trans.set_response_status( tlm::TLM_OK_RESPONSE );
}
