#ifndef base_of_details_H
#define base_of_details_H
#include<iostream>
#include<string>
class details{
    private:
    std::string email_id;
    std::string name;
    std::string password;
    public:
    void insitialize_email_id(std::string);
    void insitialize_name(std::string);
    void insitialize_password(std::string);
    std::string get_email_id();
    std::string get_name();
    std::string get_password();
};
extern details detail;
#endif
