#pragma once

#include <fstream>
#include <string>

template <typename SessionCallback, typename MessageCallback>
class FileTransportReceiveImpl{
    public:
        //FileTransportReceiveImpl(const std::string& filename) :
        FileTransportReceiveImpl() :
            file_name_("TestFile.txt")
        {}


        bool init(){
            file_stream_ = std::fstream(file_name_, 
                                                file_stream_.binary | 
                                                file_stream_.in);
            if (!file_stream_.is_open()) {
                std::cout << "failed to open " << file_name_ << '\n';
                return false;
            }

            return true;
        }

        void registerSessionCallback(SessionCallback* sessionCallback){
            session_callback_ = sessionCallback;
        }

        void registerMessageCallback(MessageCallback* messageCallback){
            message_callback_ = messageCallback;
        }

        void startReading(){
            std::string line;
			while (std::getline(file_stream_, line))
			{
                onMessage(line.c_str(), line.size()); 
			}
        }

        void onMessage(const char* msg, uint32_t msglen){
           message_callback_->onMessage(msg, msglen);
        }

        bool start(){
            started_ = true;
            return started_;
        }

    private:
        std::string file_name_;
        std::fstream file_stream_;
        SessionCallback* session_callback_;
        MessageCallback* message_callback_;
        bool started_;
};
