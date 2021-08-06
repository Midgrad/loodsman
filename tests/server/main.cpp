#include "link_factory.h"
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using namespace loodsman;

int main()
{
    cout << "Start!" << endl;;
    cout << "Creating receiver" << endl;;

    link_ptr link_listen;

    int result = factory(link_listen,link_type::udp, 5000);

    if (result != 0)
    {
        cout << "link creation failed, exiting" << endl;
        exit(-1);
    }

    // cout << "Local endpoint is " << link_listen->localAddress() << ":" << link_listen->localPort() << endl;

    boost:boost::system::error_code errorCode;

    cout << "Listening..." << endl;;
    string received_data(link_listen->receive(errorCode));
    cout << "Error codes: " << errorCode.message() << endl;

    // // cout << "Received bytes: " << received_data.size() << " , from: " << link_listen->remoteAddress() <<
    // // ":" << link_listen->remotePort() << endl;

    string data_to_send = "kek!";
    cout << "Sending..." << endl;
    std::size_t sent_data_size = link_listen->send(data_to_send,errorCode);
    cout << "Sent bytes: " << sent_data_size << endl;
    cout << "Error codes: " << errorCode.message() << endl;

    cout << "Exiting!" << endl;;

}