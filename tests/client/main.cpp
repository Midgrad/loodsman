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

    std::cout << "Local endpoint is " << link_sender.address() << ":" << link_sender.port() << endl;

    link_sender.send("kek");

    std::cout << "Local endpoint is " << link_sender.address() << ":" << link_sender.port() << endl;
    
    std::cout << "Listening" << endl;;

    loodsman::bytearray_t received_data = link_sender.receive();
    

    std::cout << "Received: " << received_data << endl;


    std::cout << "Exiting!" << endl;;

}