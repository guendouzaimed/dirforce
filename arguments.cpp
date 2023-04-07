#include <iostream>
#include <cstring>
using namespace std;
string version = "v0.3";
void showhelp() {
    cout << "Version: " << version << "\n"
         << "Usage: dirforce -u/--host [host] -w/--wordlist [wordlist.txt]\n\n"
         << "\033[1;37mOptions: \033[0;37m\n"
         << "   -u or -host: Specifies the host (required).\n"
         << "   -w or -wordlist: Specifies the wordlist (required).\n"
         << "   -t or -thread: Specifies the number of threads to create.\n"
         << "   -m or -method: Specifies the HTTP method.\n"
         << "   -r or -request: Specifies to import the request from a file.\n"
         << "   -s or -suffixe: Adds a string at the beginning of every path in the wordlist.\n"
         << "   -p or -preffixe: Adds a string at the end of every path in the wordlist.\n"
         << "   --custom-header-o: Outputs a specific header value.\n"
         << "   -e or -extension: Adds an extension after each word in the wordlist (e.g., -e php,html will send requests to word, word.php, and word.html).\n"
         << "   -f or -filter: Hides responses that contain the specified string.\n"
         << "   --lite: Outputs in lite mode (complete URL, no color, no logo).\n"
         << "   --norobot: Disables the use of the robots.txt file.\n"
         << "\033[1;37mDocumentation:\033[0;37m https://github.com/guendouzaimed/dirforce\n"
         << "Please report any bug or issue in the tool.";
    exit(0);
}

int arguments(int argc, char* argv[])
{
    //set default variable
    http_method = "HEAD"; custom_header_str = "Content-Length";
    sslOption = 0; threadCounter = 30; requestOption = 0;
    extension.push_back("");
    
    for (int i = 1; i < argc; i++){
        if (strncmp(argv[i], "-u", 2) == 0 || strncmp(argv[i], "--host", 5) == 0){
            if (i + 1 < argc) {
                host = argv[i + 1];
                i++;
            }
        }
        
        if (strncmp(argv[i], "-w", 2) == 0 || strncmp(argv[i], "--wordlist", 10) == 0){
            if (i + 1 < argc){
                wordlistfile = argv[i + 1];
                i++;
            }
        }

        if (strncmp(argv[i], "-t", 2) == 0 || strncmp(argv[i], "--thread", 8) == 0){
            if (i + 1 < argc){
                threadCounter = stoi(argv[i + 1]);
                i++;
            }
        }

        if (strncmp(argv[i], "-m", 2) == 0 || strncmp(argv[i], "--method", 8) == 0){
            if (i + 1 < argc){
                http_method = argv[i + 1];
                i++;
            }
        }

        if (strncmp(argv[i], "-r", 2) == 0 || strncmp(argv[i], "--request", 9) == 0){
            if (i + 1 < argc){
                requestOption = 1;
                string line;
                ifstream requestfile(argv[i+1]);
                while (getline(requestfile, line)) {
                    readrequest += line + "\n";
                }
                readrequest += "\n";
                i++;
            }
        }

        if (strncmp(argv[i], "-s", 2) == 0 || strncmp(argv[i], "--suffixe", 9) == 0){
            if (i + 1 < argc){
                suffixe = argv[i + 1];
                i++;
            }
        }

        if (strncmp(argv[i], "-p", 2) == 0 || strncmp(argv[i], "--preffixe", 10) == 0){
            if (i + 1 < argc){
                preffixe = argv[i + 1];
                i++;
            }
        }

        if (strncmp(argv[i], "--custom-header-o", 17) == 0){
            if (i + 1 < argc){
                custom_header_str = argv[i + 1];
                i++;
            }
        }

        if (strncmp(argv[i], "-e", 2) == 0 || strncmp(argv[i], "--extension", 11) == 0){
            if (i + 1 < argc){
                string str = argv[i + 1];
                stringstream ss(str);
                string ext;
                while(getline(ss, ext, ',')) {
                    extension.push_back("." + ext);
                }
                i++;
            }
        }

        if (strncmp(argv[i], "-f", 2) == 0 || strncmp(argv[i], "--filter", 8) == 0){
            if (i + 1 < argc){
                filterOption = true;
                filterStr = argv[i + 1];
            }
        }

        if (strncmp(argv[i], "--lite", 6) == 0) {
            liteOutput = true;
        }

        if (strncmp(argv[i], "--norobot", 9) == 0) {
            robotxtOption = false;
        }

        if (strncmp(argv[i], "-h", 2) == 0 || strncmp(argv[i], "--help", 6) == 0){
            showhelp();
        }

    }
    if (host.find("https") == string::npos) {
        if (host.find("http") == string::npos) {
            sslOption = 0;
        } else {
            sslOption = 0;
            host = host.substr(7);
        }
    } else {
        sslOption = 1;
        host = host.substr(8);
    }

    size_t slash_index = host.find("/");

    if(slash_index == string::npos) {
        //*host = *host
        address = "/";
    } else if (slash_index == host.size() - 1) {
        host = host.substr(0, slash_index);
        address = "/";
        //cout << "2";
    } else if (slash_index != host.size()) {
        if (host[host.size() - 1] == '/') {//4
            address = host.substr(slash_index);
            host = host.substr(0, slash_index);
            //cout << "4";
        } else {
            //cout << "3";
            address = host.substr(slash_index) + "/";
            host = host.substr(0, slash_index);
        }
    }
    return 0;
}
