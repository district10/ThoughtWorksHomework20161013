#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "GenerateSummary.h"

#define LOCAL 1
// #define LOCAL 0
#if LOCAL
#include "Configs.h"
#endif

using namespace std;

int main()
{
#if LOCAL
    if ( !freopen( INPUT_DIR "/test1.txt", "r", stdin ) ) { return 1; }
#endif
    srand(time(NULL));
    int year, month, day, ndays;
    char buf[100];
    while (4 == scanf("%d %d %d %d", &year, &month, &day, &ndays)) {
        if ( ndays > 0) {
            // --year; --month; --day;
            snprintf(buf, sizeof(buf), "%04d-%02d-%02d-%d", year, month, day, ndays);
            string ifilename = INPUT_DIR + string("/test1-input-")  + buf + ".txt";
            string ofilename = INPUT_DIR + string("/test1-output-") + buf + ".txt";
            ofstream ofsi(ifilename), ofso(ofilename);
            if (!ofsi || !ofso) { continue; }
            printf("<%s> -> <%s>...\n", ifilename.c_str(), ofilename.c_str());
            int income = 0, payment = 0, profit = 0;
            string output = "[Summary]\n\n";
            for (int i = 0; i < ndays; ++i) {
                static int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
                static int plow = 3, phigh = 25;    // 3~25 people
                static int hlow = 9, hhigh = 22;    // 9~22 hour
                int np = rand()%(phigh-plow)+plow;  // num of people
                int h1 = rand()%(hhigh-hlow)+hlow;
                int h2 = rand()%(hhigh-hlow)+hlow;
                if( h1 > h2 ) { swap(h1, h2); }     // h1 <= h2
                ++h2;
                h1 = 9; h2 = 20;
                if( month > 12 ) { month -= 12; ++year; }
                if (day > days[month-1]) {
                    day = 1;
                    ++month;
                    if( month > 12 ) { month -= 12; ++year; }
                }
                snprintf( buf, sizeof(buf), "%04d-%02d-%02d %02d:00~%02d:00 %d\n", year, month, day, h1, h2, np);
                Transaction t;
                t.parse(string(buf));
                income  += t.gain;
                payment += t.cost;
                profit  += t.net;
                output  += t.toString(); output += "\n";
                ofsi << buf;
                ++day;
            }
            ofsi.close();

            output += "\n";
            string conclusion;
            snprintf( buf, sizeof(buf), "Total Income: %d\n",  income  ); conclusion += buf;
            snprintf( buf, sizeof(buf), "Total Payment: %d\n", payment ); conclusion += buf;
            snprintf( buf, sizeof(buf), "Profit: %d\n",        profit  ); conclusion += buf;
            ofso << output << conclusion;
            ofso.close();
            snprintf( buf, sizeof(buf), "Total Income: %d\n",  income  ); output += buf;

            printf("<%s> -> <%s>...done\n", ifilename.c_str(), ofilename.c_str());
            printf("%s\n", conclusion.c_str());
        }
    }
}