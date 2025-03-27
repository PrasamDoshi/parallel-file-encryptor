#include <iostream>
#include "Cryption.hpp"
#include "../processes/Task.hpp"
#include "../fileHandling/ReadEnv.cpp"
#include <ctime>
#include <iomanip>

int executeCryption(const std::string  &taskData) {
    Task task = Task::fromString(taskData);
    ReadEnv env;

    std::string envKey = env.getenv();
    
    int key = std::stoi(envKey);
    if(task.action == Action::ENCRYPT){
        char ch;
        while(task.f_stream.get(ch)){
            ch = (ch+key)%256;
            task.f_stream.seekp(-1,std::ios::cur);
            task.f_stream.put(ch);
        }
        task.f_stream.close();
    }
    else{
        char ch;
        while(task.f_stream.get(ch)){
            ch = (ch-key+256)%256;
            task.f_stream.seekp(-1,std::ios::cur);
            task.f_stream.put(ch);
        }
        task.f_stream.close();
    }

    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    // std::tm now;
    // localtime_r(&t, &now);
    // change below to &now for using localtime_r
    std::cout << "Exiting the encryption/decryption process at: " << std::put_time(now,"%Y-%m-%d %H:%M:%S") << std::endl;

    
    return 0;
}