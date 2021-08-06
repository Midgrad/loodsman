#include "link_factory.h"
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using namespace loodsman;

int main()
{
    cout << "Start!" << endl;;

    cout << "Creating sender" << endl;;

    link_ptr link_sender;

    int result = factory(link_sender ,link_type::udp, 5001, "0.0.0.0", 5000, "127.0.0.1");

    if (result != 0)
        {
            cout << "link creation failed, exiting" << endl;
            exit(-1);
        }

    // cout << "Local endpoint is " << link_sender.localAddress() << ":" << link_sender.localPort() << endl;
    // cout << "Remote endpoint is " << link_sender.remoteAddress() << ":" << link_sender.remotePort() << endl;

    string data_to_send{};

    for (int i = 0; i < (MAX_PACKET_LENGTH); i++)
    {
        data_to_send.append("K");
    }

    cout << "Sending... " << endl;
    boost:boost::system::error_code errorCode;
    std::size_t sent_data_size = link_sender->send(data_to_send,errorCode);
    cout << "Sent bytes: " << sent_data_size << endl;
    cout << "Error codes: " << errorCode.message() << endl;

    cout << "Listening" << endl;;
    string received_data(link_sender->receive(errorCode));
  
    // cout << "Received bytes: " << received_data.size() << " , from: " << link_sender.remoteAddress() <<
    // ":" << link_sender.remotePort() << endl;

    cout << "Exiting!" << endl;;

}