#include "ip_filter.h"
#include <iostream>



int main(int argc, char const *argv[])
{
    try
    {
        std::vector<std::vector<std::string> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        std::list<std::vector<std::string>> ip_pool2;

        ip_pool2 = lexicographically_sort(ip_pool);

        for(const auto& ip: ip_pool2){
            for(const auto& octet: ip){
                std::cout<<octet<<".";
            }
            std::cout<<"\n";
        }




        std::cout<<"FILTER_1\n";

        auto ip_pool3 = filter(ip_pool2, 0, 1);
        for(const auto& ip: ip_pool3){
            for(const auto& octet: ip){
                std::cout<<octet<<".";
            }
            std::cout<<"\n";
        }


        std::cout<<"FILTER_2\n";

        ip_pool3 = filter(filter(ip_pool2, 0, 46), 1, 70);
        for(const auto& ip: ip_pool3){
            for(const auto& octet: ip){
                std::cout<<octet<<".";
            }
            std::cout<<"\n";
        }



        std::cout<<"FILTER_3\n";

        ip_pool3 = filter_any(ip_pool2, 46);
        for(const auto& ip: ip_pool3){
            for(const auto& octet: ip){
                std::cout<<octet<<".";
            }
            std::cout<<"\n";
        }

   
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    UNUSED(argc);
    UNUSED(argv);

    return 0;


}
