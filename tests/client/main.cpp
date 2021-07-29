#include "link_factory.h"
// #include "types.h"
#include <iostream>

// using std::string;
using std::cout;
using std::endl;
using std::rand;
using namespace loodsman;

#define RAND_MAX 255

int main()
{
    std::cout << "Start!" << endl;;

    std::cout << "Creating sender" << endl;;
    link_ptr link_sender = factory(link_type::udp, 5001, "0.0.0.0", 5000, "127.0.0.1");

    // loodsman::UdpLink link_sender("127.0.0.1",5002);

    // std::cout << "Local endpoint is " << link_sender.localAddress() << ":" << link_sender.localPort() << endl;
    // std::cout << "Remote endpoint is " << link_sender.remoteAddress() << ":" << link_sender.remotePort() << endl;

    loodsman::bytearray_t data_to_send{};

    for (int i = 0; i < (MAX_PACKET_LENGTH); i++)
    {
        data_to_send.append("K");
    }

    std::cout << "Sending... " << endl;
    std::size_t sent_data_size = link_sender->send(data_to_send);
    std::cout << "Sent bytes: " << sent_data_size << endl;

    std::cout << "Listening" << endl;;
    loodsman::bytearray_t received_data = link_sender->receive();
  
    // std::cout << "Received bytes: " << received_data.size() << " , from: " << link_sender.remoteAddress() <<
    // ":" << link_sender.remotePort() << endl;

    std::cout << "Exiting!" << endl;;

}