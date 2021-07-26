#include "udp_link.h"
#include <iostream>

// using std::string;
using std::cout;
using std::endl;

int main()
{
    std::cout << "Start!" << endl;;

    std::cout << "Creating sender" << endl;;
    loodsman::UdpLink link_sender("127.0.0.1",5000);

    link_sender.send("kek");

    std::cout << "Exiting!" << endl;;

}