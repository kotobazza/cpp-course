#include <vector>
#include <string>
#include <list>


#define UNUSED(variable) (void)variable

std::vector<std::string> split(const std::string &str, char d);

std::list<std::vector<std::string>> lexicographically_sort(const std::vector<std::vector<std::string>>& ips);

std::list<std::vector<std::string>> filter(const std::list<std::vector<std::string>>& ips, int octet_index, int octet_value);

std::list<std::vector<std::string>> filter_any(const std::list<std::vector<std::string>>& ips, int octet_value);