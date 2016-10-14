#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <ctime>
#include <cstdio>
#include <string>

// 价格表，9 点到 22 点，第一行为工作日，第二行为周末
static const int price_table[][24] = {
    // 9 ~ 12         12 ~ 18        18 ~ 22
    { 30,30,30, 50,50,50,50,50,50, 80,80,60,60 }, // mon~fri
    { 40,40,40, 50,50,50,50,50,50, 60,60,60,60 }, // sat,sun
};

// 交易信息
class Transaction {
public:
    int year, month, day;   // date
    int hour0, hour1;       // duration: hour0~hour1
    int npeople;            // #people
    int gain, cost, net;

    // 读取交易信息，格式为 "2016-06-02 20:00~22:00 7"
    // 并计算交易的收支和利润
    void parse(const std::string &input) {
        year    = str2int(input, 0, 4);
        month   = str2int(input, 5, 7);
        day     = str2int(input, 8, 10);
        hour0   = str2int(input, 11, 13);
        hour1   = str2int(input, 17, 19);
        npeople = str2int(input, 23, input.size());

        int ntable = calcNumOfTable(npeople);
        int tab = isWeekend(year, month, day) ? 1 : 0;
        gain = ntable == 0 ? 0 : npeople * 30;
        cost = 0;
        for (int i = hour0; i < hour1; ++i) {
            cost += ntable * price_table[tab][i - 9];
        }
        net = gain - cost;
    }

    // 打印收入、支出、利润
    std::string toString() {
        std::string ret;
        char buf[100];
        snprintf( buf, sizeof(buf),
                  "%04d-%02d-%02d %02d:00~%02d:00 +%d -%d",
                  year, month, day, hour0, hour1, gain, cost );
        ret += buf;
        if (net == 0) {
            snprintf( buf, sizeof(buf), " %d", net);
        } else if (net > 0) {
            snprintf( buf, sizeof(buf), " +%d", net);
        } else {
            snprintf( buf, sizeof(buf), " %d", net);
        }
        ret += buf;
        return ret;
    }

private:
    // 判断某年某月某日是否是周末
    bool isWeekend(int year, int month, int day) {
        std::tm date;
        date.tm_year = year - 1900;
        date.tm_mon  = month - 1;
        date.tm_mday = day;
        date.tm_hour = 12;
        std::mktime( &date );
        int dw = date.tm_wday;          // day of the week
        return dw == 0 || dw == 6;      // is sun, or sat?
    }

    // 根据报名人数计算需要借的羽毛球场的数量
    int calcNumOfTable(int m) {
        int ret = 0;
        int T = m / 6;
        int X = m % 6;
        switch (T) {
        case 0:
            ret = X < 4 ? 0 : 1;
            break;
        case 1:
            ret = 2;
            break;
        case 2: case 3:
            ret = X < 4 ? T : T + 1;
            break;
        default:
            ret = T;
        }
        return ret;
    }

    // 计算字符串 str[start, end) 对应的数字
    int str2int(const std::string &str, int start, int end) {
        int ret = 0;
        for (int i = start; i < end; ++i) {
            ret = ret * 10 + (str.at(i) - '0');
        }
        return ret;
    }
};

#endif // TRANSACTION_H
