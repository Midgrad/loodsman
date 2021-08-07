#include <gtest/gtest.h>
#include "link_factory.h"
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using namespace loodsman;

TEST(intergationTests, SenderConstructorTest)
{
    cout << "Creating sender link" << endl;;
    link_ptr link_sender;
    int result = factory(link_sender ,link_type::udp, 5001, "0.0.0.0", 5000, "127.0.0.1");

    EXPECT_EQ(result, 0);
    ASSERT_NE(link_sender, nullptr);

}

TEST(intergationTests, ReceiveConstructorTest)
{
    cout << "Creating listen link" << endl;;

    link_ptr link_listen;
    int result = factory(link_listen,link_type::udp, 5000);

    EXPECT_EQ(result, 0);
    ASSERT_NE(link_listen, nullptr);

}

// TODO: clean up cout messages
TEST(intergationTests, ExchangeTest)
{
    cout << "Creating sender link" << endl;;
    link_ptr link_sender;
    int result = factory(link_sender ,link_type::udp, 5001, "0.0.0.0", 5000, "127.0.0.1");

    EXPECT_EQ(result, 0);
    ASSERT_NE(link_sender, nullptr);

    cout << "Creating listen link" << endl;;

    link_ptr link_listen;
    result = factory(link_listen,link_type::udp, 5000);

    EXPECT_EQ(result, 0);
    ASSERT_NE(link_listen, nullptr);

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

    EXPECT_EQ(errorCode.value(), 0);
    EXPECT_EQ(sent_data_size, MAX_PACKET_LENGTH);

    cout << "Listening..." << endl;;
    string received_data(link_listen->receive(errorCode));
    cout << "Error codes: " << errorCode.message() << endl;

    EXPECT_EQ(errorCode.value(), 0);
    EXPECT_EQ(received_data.size(), MAX_PACKET_LENGTH);

    data_to_send = "Test message";
    cout << "Sending..." << endl;
    sent_data_size = link_listen->send(data_to_send,errorCode);
    cout << "Sent bytes: " << sent_data_size << endl;
    cout << "Error codes: " << errorCode.message() << endl;

    EXPECT_EQ(errorCode.value(), 0);
    EXPECT_EQ(sent_data_size, data_to_send.size());

    cout << "Listening" << endl;;
    received_data = string(link_sender->receive(errorCode));

    EXPECT_EQ(errorCode.value(), 0);
    EXPECT_EQ(received_data.size(), data_to_send.size());

}
