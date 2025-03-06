#pragma once

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cstdlib>
#include "ip_filter.h"


std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}




std::list<std::vector<std::string>> lexicographically_sort(const std::vector<std::vector<std::string>>& ips)
{
    std::list<std::vector<std::string>>r;

    if (ips.empty()) return r;

    for (const auto& ip : ips) {
        auto r_ip = r.begin();


        while (r_ip != r.end()) {
            bool is_less = false;

            for (size_t i = 0; i < std::min(ip.size(), r_ip->size()); ++i) {
                int ip_octet = std::stoi(ip[i]);
                int r_ip_octet = std::stoi((*r_ip)[i]);

                if (ip_octet < r_ip_octet) {
                    is_less = true; 
                    break; 
                } else if (ip_octet > r_ip_octet) {
                    is_less = false; 
                    break; 
                }
            }

            if (is_less) {
                break; 
            }

            ++r_ip;
        }


        r.insert(r_ip, ip);
    }

    return r; 
}


std::list<std::vector<std::string>> filter(const std::list<std::vector<std::string>>& ips, ulong octet_index, int octet_value)
{
    std::list<std::vector<std::string>> r {};

    if(ips.size() == 0) return r;
    if((*ips.begin()).size() <= octet_index) return r;

    for(auto& ip:ips){
        if(std::stoi(ip[octet_index]) == octet_value){
            r.push_back(ip);
        }
    }

    return r;
}


std::list<std::vector<std::string>> filter_any(const std::list<std::vector<std::string>>& ips, int octet_value)
{
    std::list<std::vector<std::string>> r {};

    if(ips.size() == 0) return r;

    for(auto& ip:ips){
        for(auto octet_str: ip){
            if(std::stoi(octet_str) == octet_value){
                r.push_back(ip);
                break;
            }
        }
        
    }

    return r;
}




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
