#include "udp_link.h"
#include <iostream>

// using std::string;
using std::cout;

int main()
{
    std::cout << "Start! \n";

    std::cout << "Creating receiver \n";
    loodsman::UdpLink link_listen(5000);
    // std::cout << "Opening socket \n";
    // link_listen.open();

    std::cout << "Creating sender \n";
    loodsman::UdpLink link_sender("127.0.0.1",5000);
    // std::cout << "Opening socket \n";
    // link_sender.open();

    link_sender.send("kek");

    std::cout << "Listening... \n";

    std::cout << link_listen.receive();

    std::cout << "Exiting! \n";

}