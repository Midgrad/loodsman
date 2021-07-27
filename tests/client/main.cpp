#include "udp_link.h"
// #include "types.h"
#include <iostream>

// using std::string;
using std::cout;
using std::endl;

int main()
{
    std::cout << "Start!" << endl;;

    std::cout << "Creating sender" << endl;;
    loodsman::UdpLink link_sender("127.0.0.1",5000);

    std::cout << "Local endpoint is " << link_sender.localAddress() << ":" << link_sender.localPort() << endl;
    std::cout << "Remote endpoint is " << link_sender.remoteAddress() << ":" << link_sender.remotePort() << endl;

    loodsman::bytearray_t data_to_send = "kek!";
    std::cout << "Sending..." << endl;
    std::size_t sent_data_size = link_sender.send(data_to_send);
    std::cout << "Sent bytes: " << sent_data_size << endl;

    std::cout << "Listening" << endl;;
    loodsman::bytearray_t received_data = link_sender.receive();
  
    std::cout << "Local endpoint is " << link_sender.localAddress() << ":" << link_sender.localPort() << endl;    
    std::cout << "Remote endpoint is " << link_sender.remoteAddress() << ":" << link_sender.remotePort() << endl;
 
    std::cout << "Received: " << received_data << endl;

    std::cout << "Exiting!" << endl;;

}