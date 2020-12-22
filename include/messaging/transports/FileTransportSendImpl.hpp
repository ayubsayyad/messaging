#pragma once

#include <fstream>
#include <string>

class FileTransportSendImpl{
    public:
        //FileTransportSendImpl(const std::string& filename) :
        FileTransportSendImpl() :
            file_name_("TestFile.txt")
        {}


        bool init(){
            file_stream_ = std::fstream(file_name_, 
                                                file_stream_.binary | 
                                                file_stream_.trunc | 
                                                file_stream_.out);
            if (!file_stream_.is_open()) {
                std::cout << "failed to open " << file_name_ << '\n';
                return false;
            }

            return true;
        }

        uint32_t send(char* buf, uint32_t buf_len){
            if(started_){
                file_stream_.write(buf, buf_len);
                return 0;
            }

            return 1;
        }

        bool start(){
            started_ = true;
            return started_;
        }

    private:
        std::string file_name_;
        std::fstream file_stream_;
        bool started_;
};
