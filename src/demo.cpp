#include <cstdio>
#include <string>
#include <vector>

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
    if ( !freopen( INPUT_DIR "/demo.txt", "r", stdin ) ) { return 1; }
#endif
    string input  = getTransactionInfo();
    printf("input: \n\n---\n%s...\n", input.c_str());
    string output = generateSummary(input);
    printf("\n");
    printf("output:\n\n---\n%s...\n", output.c_str());
}