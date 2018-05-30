#include "../include/uart.h"

void uart::write(int data, int offset){
  if ( pmc_enable != 1 )
  {
    return;
  }

  switch(offset) {
    case 0x0000 : // Control Register
      reg_uart_cr.write(data);
    break;

    case 0x0004 : // Mode Register
      reg_uart_mr.write(data);
    break;

    case 0x0008 : // Interrupt Enable Register
      reg_uart_ier.write(data);
    break;

    case 0x000C : // Interrupt Disable Register
      reg_uart_idr.write(data);
    break;

    case 0x001C : // Transmit Holding Register
      reg_uart_thr.write(data);
    if ( reg_uart_cr.txen == 1 && reg_uart_cr.txdis == 0 )
    {
      send_data_tx(data, 1);
    }
    break;

    case 0x0020 : // Baud Rate Generator Register
      reg_uart_brgr.write(data);
    break;

    default : // Not Applicable => Read-only registers
    // 0x0010 : Interrupt Mask Register
    // 0x0014 : Status Register
    // 0x0018 : Receive Holding Register
    return;
    break;
  }
}

int uart::read(int offset){

  int data = 0;

  if ( pmc_enable != 1 )
	{
		return 0;
	}
  if ( reg_uart_cr.rxen != 1 || reg_uart_cr.rxdis != 0 )
	{
		return 0; // receiver enabled
	}

  switch(offset) {
	case 0x0000 : // Control Register
		data = reg_uart_cr.read();
		break;

	case 0x0004 : // Mode Register
		data = reg_uart_mr.read();
		break;

	case 0x0008 : // Interrupt Enable Register
		data = reg_uart_ier.read();
		break;

	case 0x000C : // Interrupt Disable Register
		data = reg_uart_idr.read();
		break;

	case 0x0010 : // Interrupt mask register
		data = reg_uart_imr.read();
		break;

	case 0x0014 : //Status register
		data = reg_uart_sr.read();
		break;

	case 0x0018 : // Receive Holding Register
		if ( reg_uart_sr.rxrdy == 1 )
		{
			data = reg_uart_rhr.read(); // read off RHR
			reg_uart_sr.rxrdy = 0; // RXRDY set to 0 once RHR red
		}
		break;

	case 0x0020 : // Baud Rate Generator Register
		data = reg_uart_brgr.read();
		break;

 default : // Not Applicable => Write-only registers
		// 0x001C : Transmit Holding Register
		break;
}
return data;
}

void uart::send_data_tx(int data_s, int size)
{
  // TLM-2 generic payload transaction, reused across calls to b_transport
  tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
  sc_time delay = sc_time(10, SC_NS);


    trans->set_data_ptr( reinterpret_cast<unsigned char*>(&data_s) );
    trans->set_data_length( size );
    trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE ); // Mandatory initial value

    socket_tx->b_transport( *trans, delay );  // Blocking transport call

    // Initiator obliged to check response status and delay
    if ( trans->is_response_error() )
      SC_REPORT_ERROR("TLM-2", "Response error from b_transport");

    cout << "trans : " << " data = " << data_s << endl;

    // Realize the delay annotated onto the transport call
    wait(delay);
}

void uart::send_data_irq(int data_s, int size)
{
  // TLM-2 generic payload transaction, reused across calls to b_transport
  tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
  sc_time delay = sc_time(10, SC_NS);


    trans->set_data_ptr( reinterpret_cast<unsigned char*>(&data_s) );
    trans->set_data_length( size );
    trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE ); // Mandatory initial value

    irq_tx->b_transport( *trans, delay );  // Blocking transport call

    // Initiator obliged to check response status and delay
    if ( trans->is_response_error() )
      SC_REPORT_ERROR("TLM-2", "Response error from b_transport");

    cout << "trans : " << " data = " << data_s << endl;

    // Realize the delay annotated onto the transport call
    wait(delay);
}

void uart::send_data_apb(int data_s, int size)
{
  // TLM-2 generic payload transaction, reused across calls to b_transport
  tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
  sc_time delay = sc_time(10, SC_NS);


    trans->set_data_ptr( reinterpret_cast<unsigned char*>(&data_s) );
    trans->set_data_length( size );
    trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE ); // Mandatory initial value

    apb_tx->b_transport( *trans, delay );  // Blocking transport call

    // Initiator obliged to check response status and delay
    if ( trans->is_response_error() )
      SC_REPORT_ERROR("TLM-2", "Response error from b_transport");

    cout << "trans : " << " data = " << data_s << endl;

    // Realize the delay annotated onto the transport call
    wait(delay);
}

  void uart::receive_data_rx( tlm::tlm_generic_payload& trans, sc_time& delay )
{
  unsigned char*   ptr = trans.get_data_ptr();
  unsigned int     len = trans.get_data_length();


  if (len = 0)
    SC_REPORT_ERROR("TLM-2", "Target does not support given generic payload transaction");

  reg_uart_rhr.set_reg_value(*ptr);
  reg_uart_sr.rxrdy = 1;
  send_data_irq(1, 1);

  // Obliged to set response status to indicate successful completion
  trans.set_response_status( tlm::TLM_OK_RESPONSE );
}


void uart::receive_data_pmc( tlm::tlm_generic_payload& trans, sc_time& delay )
{
  unsigned char*   ptr = trans.get_data_ptr();
  unsigned int     len = trans.get_data_length();

  if (len = 0)
    SC_REPORT_ERROR("TLM-2", "Target does not support given generic payload transaction");

  pmc_enable = *ptr;
  // Obliged to set response status to indicate successful completion
  trans.set_response_status( tlm::TLM_OK_RESPONSE );
}


  void uart::receive_data_apb( tlm::tlm_generic_payload& trans, sc_time& delay )
{
  unsigned char*   ptr = trans.get_data_ptr();
  unsigned int     len = trans.get_data_length();
  sc_dt::uint64    adr = trans.get_address();
  tlm::tlm_command cmd = trans.get_command();

  if (len = 0)
    SC_REPORT_ERROR("TLM-2", "Target does not support given generic payload transaction");
  if ( cmd == tlm::TLM_READ_COMMAND )
      read(adr);
  else if ( cmd == tlm::TLM_WRITE_COMMAND )
      write(*ptr, adr);

  // Obliged to set response status to indicate successful completion
  trans.set_response_status( tlm::TLM_OK_RESPONSE );
}
