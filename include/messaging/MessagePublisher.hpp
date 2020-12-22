#pragma once

template<typename Transport, typename WireFormatter>
struct MessagePublisher{
public:
    bool init(){
        return transport_.init();
    }

    bool start(){
        return transport_.start();
    }
    
    template<typename Object>
    bool send(Object& obj){
        auto [buf, buf_len] = formatter_.encode(obj);
        return transport_.send(buf, buf_len);
    }

private:
        Transport transport_;
        WireFormatter formatter_;
};
