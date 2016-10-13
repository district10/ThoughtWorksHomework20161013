#include <cstdio>
#include <string>
#include <vector>

#include "GenerateSummary.h"

using namespace std;

int main()
{
    string input  = getTransactionInfo();
    string output = generateSummary(input);
    printf("%s", output.c_str());
}
