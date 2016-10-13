#ifndef UTILS_H
#define UTILS_H

// 一些工具

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

// 从流中获取交易信息，格式为 "2016-06-02 20:00~22:00 7"，并打包，分隔符为 "\n"
std::string getTransactionInfo(std::istream &is = std::cin) {
    using namespace std;
    string ret, line;
    while (getline(is, line)) {
        if (line.at(4) == '-' && line.at(16) == '~') {   // 进行简单的校检
            ret += line + "\n";
        }
    }
    return ret;
}

// 把打包好的交易信息拆开成一条一条，用 vector 组织起来
std::vector<std::string> unpackTransactions(const std::string &info) {
    using namespace std;
    vector<string> ret;
    size_t last = 0, index;
    while ( (index = info.find_first_of('\n', last)) != string::npos ) {
        ret.push_back(info.substr(last, index-last));
        last = index + 1;
    }
    return ret;
}

#endif // UTILS_H
