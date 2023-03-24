#include <iostream>
#include <cstring>
using namespace std;

int arguments(int argc, char* argv[], string *url, string *wordlist, int *threadCounter, int *sslOption, string *address)
{
    string urlV = "", wordlistV = "", addressV = "";
    int sslOptionV = 0, threadCounterV = 30;
    
    //std::cout << "Number of arguments: " << argc << std::endl;

    for (int i = 1; i < argc; i++)
    {
        if (strncmp(argv[i], "-u", 2) == 0 || strncmp(argv[i], "--url", 5) == 0)
        {
            //std::cout << "Argument: " << argv[i] << std::endl;
            if (i + 1 < argc) {
                //std::cout << "Value: " << argv[i + 1] << std::endl;
                urlV = argv[i + 1];
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

        if (strncmp(argv[i], "-t", 2) == 0 || strncmp(argv[i], "--thread", 8) == 0)
        {
            if (i + 1 < argc)
            {
                threadCounterV = stoi(argv[i + 1]);
                i++;
            }
        }


    }
    if (urlV.find("https") == string::npos) {
        if (urlV.find("http") == string::npos) {
            sslOptionV = 0;
        } else {
            sslOptionV = 0;
            urlV = urlV.substr(7);
        }
    } else {
        sslOptionV = 1;
        urlV = urlV.substr(8);
    }

    size_t slash_index = urlV.find("/");

    if(slash_index == string::npos) {
        //urlV = urlV
        addressV = "/";
    } else if (slash_index == urlV.size() - 1) {
        urlV = urlV.substr(0, slash_index);
        addressV = "/";
        //cout << "2";
    } else if (slash_index != urlV.size()) {
        if (urlV[urlV.size() - 1] == '/') {//4
            addressV = urlV.substr(slash_index);
            urlV = urlV.substr(0, slash_index);
            //cout << "4";
        } else {
            //cout << "3";
            addressV = urlV.substr(slash_index) + "/";
            urlV = urlV.substr(0, slash_index);
        }
    }
    //cout << endl << addressV << endl << urlV << endl;
    *url = urlV;
    *address = addressV;
    *threadCounter = threadCounterV;
    *sslOption = sslOptionV;
    *wordlist = wordlistV;
    return 0;
}
