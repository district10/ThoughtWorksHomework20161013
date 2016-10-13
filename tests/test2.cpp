#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>

#include "GenerateSummary.h"

#define LOCAL 1
// #define LOCAL 0
#if LOCAL
#include "Configs.h"
#endif

using namespace std;

int main( int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "Usage: %s input.txt output.txt\n", argv[0]);
        return 1;
    }

    ifstream input(argv[1]);
    ifstream output(argv[2], ios::binary);
    if (!input || !output) { return 1; }

    streampos begin = output.tellg(); output.seekg(0, ios::end);
    streampos end   = output.tellg(); output.seekg(0);
    char *buf = (char *)malloc(end - begin+1);
    output.read(buf, end - begin+1);
    string loadedoutput = string(buf);
    loadedoutput[end - begin] = '\0';
    loadedoutput.resize(end - begin);
    free(buf);
    string myoutput = generateSummary(getTransactionInfo(input));
    fprintf(stderr, "testing (%s, %s)...", argv[1], argv[2]);
    if ( strcmp(loadedoutput.c_str(), myoutput.c_str()) == 0 ) {
        fprintf(stderr, "testing (%s, %s)...succeed.", argv[1], argv[2]);
    } else {
        fprintf(stderr, "testing (%s, %s)...failed.",  argv[1], argv[2]);
        printf("loaded output: \n'%s'.\n", loadedoutput.c_str());
        printf("my output: \n'%s'.", myoutput.c_str());
    }
}
