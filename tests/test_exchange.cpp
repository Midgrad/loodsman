#include "link_factory.h"
#include <gtest/gtest.h>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using namespace loodsman;

TEST(intergationTests, SenderConstructorTest)
{
    cout << "Creating sender link" << endl;
    ;
    LinkPtr link_sender;
    int result = factory(link_sender, link_type::udp, 5001, "0.0.0.0", 5000, "127.0.0.1");

    EXPECT_EQ(result, 0);
    ASSERT_NE(link_sender, nullptr);
}

TEST(intergationTests, ReceiveConstructorTest)
{
    cout << "Creating listen link" << endl;
    ;

    LinkPtr link_listen;
    int result = factory(link_listen, link_type::udp, 5000);

    EXPECT_EQ(result, 0);
    ASSERT_NE(link_listen, nullptr);
}

// TODO: clean up cout messages
TEST(intergationTests, ExchangeTest)
{
    cout << "Creating sender link" << endl;
    ;
    LinkPtr link_sender;
    int result = factory(link_sender, link_type::udp, 5001, "0.0.0.0", 5000, "127.0.0.1");

    EXPECT_EQ(result, 0);
    ASSERT_NE(link_sender, nullptr);

    cout << "Creating listen link" << endl;
    ;

    LinkPtr link_listen;
    result = factory(link_listen, link_type::udp, 5000);

    EXPECT_EQ(result, 0);
    ASSERT_NE(link_listen, nullptr);

    string data_to_send{};

    for (int i = 0; i < (MAX_PACKET_LENGTH); i++)
    {
        data_to_send.append("K");
    }

    cout << "Sending... " << endl;
    std::size_t sent_data_size = link_sender->send(data_to_send);
    cout << "Sent bytes: " << sent_data_size << endl;
    cout << "Error messages: " << link_sender->errorMessage() << endl;

    EXPECT_EQ(link_sender->errorCode(), 0);
    EXPECT_EQ(sent_data_size, MAX_PACKET_LENGTH);

    cout << "Listening..." << endl;
    ;
    string received_data(link_listen->receive());
    cout << "Error messages: " << link_listen->errorMessage() << endl;

    EXPECT_EQ(link_listen->errorCode(), 0);
    EXPECT_EQ(received_data.size(), MAX_PACKET_LENGTH);

    data_to_send = "Test message";
    cout << "Sending..." << endl;
    sent_data_size = link_listen->send(data_to_send);
    cout << "Sent bytes: " << sent_data_size << endl;
    cout << "Error messages: " << link_listen->errorMessage() << endl;

    EXPECT_EQ(link_listen->errorCode(), 0);
    EXPECT_EQ(sent_data_size, data_to_send.size());

    cout << "Listening" << endl;
    ;
    received_data = string(link_sender->receive());

    EXPECT_EQ(link_sender->errorCode(), 0);
    EXPECT_EQ(received_data.size(), data_to_send.size());
}
