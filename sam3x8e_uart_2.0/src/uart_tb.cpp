#include "../include/uart_tb.h"


#define APB_READ tlm::TLM_READ_COMMAND
#define APB_WRITE tlm::TLM_WRITE_COMMAND

int ret_val = 0;


void uart_tb::send_data_apb(int data_s, int adr, int size, tlm::tlm_command cmd)
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


  if (len == 0)
    SC_REPORT_ERROR("TLM-2", "Target does not support given generic payload transaction");
  // Obliged to set response status to indicate successful completion
  trans.set_response_status( tlm::TLM_OK_RESPONSE );
}


  void uart_tb::receive_data_irq( tlm::tlm_generic_payload& trans, sc_time& delay )
{
  unsigned char*   ptr = trans.get_data_ptr();
  unsigned int     len = trans.get_data_length();

  if (len == 0)
    SC_REPORT_ERROR("TLM-2", "Target does not support given generic payload transaction");
  // Obliged to set response status to indicate successful completion
  trans.set_response_status( tlm::TLM_OK_RESPONSE );
    printf("IRQ : %d\n", *ptr);
}


  void uart_tb::receive_data_apb( tlm::tlm_generic_payload& trans, sc_time& delay )
{
  unsigned char*   ptr = trans.get_data_ptr();
  unsigned int     len = trans.get_data_length();
  sc_dt::uint64    adr = trans.get_address();

  if (len == 0)
    SC_REPORT_ERROR("TLM-2", "Target does not support given generic payload transaction");
  // Obliged to set response status to indicate successful completion
  trans.set_response_status( tlm::TLM_OK_RESPONSE );
  ret_val = *ptr;
  printf("APB_READ : %d\n", *ptr);
}

void uart_tb::init(){

  send_data_pmc(0,1);

  send_data_apb(0x12, 0x00, 4, APB_WRITE);
  //activer UART
  send_data_pmc(1,1);

  send_data_apb(0x40, 0x00, 4, APB_WRITE);
}

void uart_tb::exec_test(){

  //Envoie
  send_data_apb(0xAA, 0x1C, 4, APB_WRITE);

//initialiser RX
  send_data_apb(0x50, 0x00, 4, APB_WRITE);

  printf("Envoie d une donnee : 24\n");
  send_data_tx(24, 4);
  //test IRQ de l uart levé

  send_data_apb(0x00, 0x14, 4, APB_READ);
  //Test de RX_READY
  if(ret_val & 0x01 )
    printf("RX_READY Ok \n");
  else
    printf("RX_READY NOk \n");

//Verification des donneess lues
 send_data_apb(0x00, 0x18, 4, APB_READ);
 if(ret_val == 24)
   printf("Valeur Lue OK \n");
 else
   printf("Valeur Lue Nok \n");

}
