#include "udp_link.h"
#include <iostream>

// using std::string;
using std::cout;
using std::endl;

int main()
{
    std::cout << "Start!" << endl;;

    std::cout << "Creating receiver" << endl;;
    loodsman::UdpLink link_listen(5000);

    std::cout << "Local endpoint is " << link_listen.localAddress() << ":" << link_listen.localPort() << endl;    
    std::cout << "Remote endpoint is " << link_listen.remoteAddress() << ":" << link_listen.remotePort() << endl;

    std::cout << "Listening..." << endl;;
    loodsman::bytearray_t received_data = link_listen.receive();

    std::cout << "Received: " << received_data << endl;


    loodsman::bytearray_t data_to_send = "kek!";
    std::cout << "Sending..." << endl;
    std::size_t sent_data_size = link_listen.send(data_to_send);
    std::cout << "Sent bytes: " << sent_data_size << endl;

    std::cout << "Local endpoint is " << link_listen.localAddress() << ":" << link_listen.localPort() << endl;    
    std::cout << "Remote endpoint is " << link_listen.remoteAddress() << ":" << link_listen.remotePort() << endl;
    
    std::cout << "Exiting!" << endl;;

}