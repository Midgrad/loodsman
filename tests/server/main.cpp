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

    std::cout << "Listening..." << endl;;

    std::cout << "Received: " << link_listen.receive() << endl;

    std::cout << "Exiting!" << endl;;

}