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

    std::cout << "Local endpoint is " << link_listen.address() << ":" << link_listen.port() << endl;;

    std::cout << "Listening..." << endl;;

    loodsman::bytearray_t received_data = link_listen.receive();

    std::cout << "Received: " << received_data << endl;

    link_listen.send("kek");

    std::cout << "Exiting!" << endl;;

}