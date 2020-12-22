#include <iostream>
#include <variant>
#include <thread>
#include <chrono>

#include <messaging/MessagePublisher.hpp>
#include <messaging/MessageReceiver.hpp>
#include <messaging/transports/FileTransportSendImpl.hpp>
#include <messaging/transports/FileTransportRecvImpl.hpp>
#include <messaging/formatters/TextFormatter.hpp>

struct Type{
};
struct SessionCallback{};
struct MessageCallback{
    void operator()(int m){
        std::cout << "Int Message Received: " << m << std::endl;
    };
    void operator()(double m){
        std::cout << "Double Message Received: " << m << std::endl;
    }
    void operator()(std::string){}
    void operator()(Type){}
};


int main(){
{
    MessagePublisher<FileTransportSendImpl, TextFormatter> t;
    t.init();
    t.start();
    int i = 100;
    for(int i =0; i < 10000; i++){
        t.send(i);
        double j = i;
        t.send(j);
    }
}
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(100000s);

    using MessageTypes = std::variant<int, double, std::string, Type>;
    using Decoder = IntDecoder<MessageTypes>;

    MessageReceiver<FileTransportReceiveImpl, Decoder, SessionCallback, MessageCallback> recv;
    recv.init();
    recv.start();
    recv.startReading();

    return 0;
}
