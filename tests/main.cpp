#include "udp_link.h"
#include <iostream>

int main()
{
    std::cout << "Start!";

    std::cout << "Creating receiver";
    loodsman::UdpLink link_listen(5000);

    std::cout << "Creating sender";
    loodsman::UdpLink link_sender("127.0.0.1",5000);

    link_sender.send("kek");

    std::cout << link_listen.receive();

}