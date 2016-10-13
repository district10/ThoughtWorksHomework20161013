#ifndef GENERATE_SUMMARY_H
#define GENERATE_SUMMARY_H

#include <string>
#include <vector>
#include "Utils.h"
#include "Transaction.h"

// 打印交易信息，收支和利润
// 从 input 读入，输出到 output，都是 string 类型
std::string generateSummary(const std::string &input) {
    using namespace std;
    int income = 0, payment = 0, profit = 0;
    vector<string> transactions = unpackTransactions(input);
    string output = "[Summary]\n\n";
    for (int i = 0; i < transactions.size(); ++i) {
        Transaction t;
        t.parse(transactions[i]);
        income  += t.gain;
        payment += t.cost;
        profit  += t.net;
        output  += t.toString(); output += "\n";
    }
    output += "\n";
    char buf[100];
    snprintf( buf, sizeof(buf), "Total Income: %d\n",  income  ); output += buf;
    snprintf( buf, sizeof(buf), "Total Payment: %d\n", payment ); output += buf;
    snprintf( buf, sizeof(buf), "Profit: %d\n",        profit  ); output += buf;
    return output;
}

#endif // GENERATE_SUMMARY_H
