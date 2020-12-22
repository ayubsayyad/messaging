#pragma once
#include <type_traits>
#include <variant>
template<template <class InSessionCallback, class InMessageCallback> class Transport, 
         typename WireFormatter,  
         typename SessionCallback, 
         typename MessageCallback>
struct MessageReceiver{
public:

    bool init(){
        return transport_.init();
    }

    bool start(){
        return transport_.start();
    }
    
    void startReading(){
        std::cout << " Message Receiver startReading" << std::endl;
        transport_.startReading();
    }

    struct InternalSessionCallback{};

    struct InternalMessageCallback{
        InternalMessageCallback(MessageReceiver& parent) : parent_(parent){
        }

        void onMessage(const char* msg, uint32_t msglen){
            auto decodedMessage = parent_.formatter_.decode(msg, msglen);
            
            std::visit([this](auto&& arg){
                            parent_.message_callback_(arg);
                        },
                        decodedMessage);
        }

        MessageReceiver& parent_;
    };

    MessageReceiver() : internalMessageCallback_(*this){}
private:
    Transport<InternalSessionCallback, InternalMessageCallback> transport_;
    //Transport transport_;
    WireFormatter formatter_;
    InternalMessageCallback internalMessageCallback_;
    SessionCallback session_callback_;
    MessageCallback message_callback_;
};
