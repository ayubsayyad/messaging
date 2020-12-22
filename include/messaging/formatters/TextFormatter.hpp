#pragma once
#include <memory>
#include <tuple>
#include <cstdio>
#include <cstring>
#include <cstdlib>

template<size_t SIZE=1024>
struct FormatBuffer{
    static constexpr size_t size = SIZE;
    FormatBuffer(){
        std::memset(buff, 0, sizeof(buff));
    }
    char buff[SIZE];
};

using FormatBufferType = FormatBuffer<1024>;

struct IntTextFormatter{
    IntTextFormatter(FormatBufferType& buf):
        buffer_(buf){}

    auto encode(int data){
        int sz = std::snprintf(buffer_.buff, FormatBufferType::size, "I:%d\n", data);
        return std::tuple{buffer_.buff, sz};
    }

    auto encode(double data){
        int sz = std::snprintf(buffer_.buff, FormatBufferType::size, "D:%f\n", data);
        return std::tuple{buffer_.buff, sz};
    }



    FormatBufferType& buffer_;
};


class TextFormatter
    : public IntTextFormatter
{      
    public:
        TextFormatter(): IntTextFormatter(buffer_){
        }


    private:
        FormatBufferType buffer_;

};

template<typename MessageTypes>
class IntDecoder{
    public:
        IntDecoder(){
        }

        MessageTypes decode(const char* buf, uint32_t size){
            std::cout << "Buf: " << buf << std::endl;
            if(buf[0] == 'I'){
                MessageTypes val = std::atoi(buf+2);

                return val;
            }
            else if(buf[0] == 'D'){
                MessageTypes val = std::atof(buf+2);
                return val;
            }
            MessageTypes val;
            return val;

        }
};


