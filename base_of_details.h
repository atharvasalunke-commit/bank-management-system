#ifndef base_of_details_H
#define base_of_details_H
#include<iostream>
#include<string>
class details{
    private:
    std::string email_id;
    std::string name;
    int password;
    public:
    void insitialize_emaild_id(std::string);
    void insitialize_name(std::string);
    void insitialize_password(int);
    std::string get_email_id();
    std::string get_name();
    int  get_password();
    std::string get_string_pd();
};
#endif
extern details detail;