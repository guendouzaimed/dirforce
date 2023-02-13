#include <iostream>
#include <cstring>
using namespace std;

int arguments(int argc, char* argv[], string *url, int *max_conn, string *wordlist)
{
    string urlV = "", wordlistV = "";
    int max_connV = 15;
    //std::cout << "Number of arguments: " << argc << std::endl;

    for (int i = 1; i < argc; i++)
    {
        if (strncmp(argv[i], "-u", 2) == 0 || strncmp(argv[i], "--url", 5) == 0)
        {
            //std::cout << "Argument: " << argv[i] << std::endl;
            if (i + 1 < argc)
            {
              if (strncmp(argv[i + 1], "--", 2) != 0 && strncmp(argv[i + 1], "-", 1) != 0)
              {
                //std::cout << "Value: " << argv[i + 1] << std::endl;
                urlV = argv[i + 1];
                i++;
              }
            }
        }
        if (strncmp(argv[i], "--max-conn", 11) == 0) {
            if (i + 1 < argc) {
                max_connV = strtol(argv[i + 1], nullptr, 10);
                i++;
            }
        }

        if (strncmp(argv[i], "-w", 2) == 0 || strncmp(argv[i], "--wordlist", 10) == 0)
        {
            if (i + 1 < argc)
            {
                wordlistV = argv[i + 1];
                i++;
            }
        }

    }
    
    *url = urlV;
    *max_conn = max_connV;
    *wordlist = wordlistV;
    return 0;
}
