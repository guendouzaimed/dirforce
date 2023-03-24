#include <iostream>
#include <curl/curl.h>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

// Define a callback function that will be called by libcurl for each chunk of data received
size_t WriteCallback(char* ptr, size_t size, size_t nmemb, std::string* data)
{
    // Append the received data to the string
    data->append(ptr, size * nmemb);
    return size * nmemb;
}

int robotxt(string rburl, int sslOption) {
    string host = rburl;
    rburl = rburl + "/robots.txt";
    CURL *curl;
    curl = curl_easy_init();
    string response;
    curl_easy_setopt(curl, CURLOPT_URL, rburl.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    // Set the user-defined data pointer that will be passed to the callback function
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_perform(curl);
    
    std::istringstream iss(response);
    std::string line;
    string str;
    string output;
    vector<string> url;
    while (std::getline(iss, line)) {
        if (line.find(":") != string::npos) {
            str = line.substr(line.find(":") + 2);
            if (str.find("/") != string::npos) {
                for(int i = 0;i < str.size(); i++) {
                    if (str[i] != ' ') {
                        output += str[i]; 
                    }
                }
                //std::cout << output << '\n';
                if (output.find("?") != string::npos) {
                    url.push_back(output.substr(0, output.find("?")));
                } else {
                    url.push_back(output);
                }
                output = "";
            }
        }
    }

    std::sort(url.begin(), url.end()); // Sort the vector
    auto it = std::unique(url.begin(), url.end()); // Remove adjacent duplicates
    url.erase(it, url.end()); // Erase the remaining duplicates

    cout << "\033[1;37m[-] from robots.txt file: \n\033[0;37m";
    string http = "http://";
    long http_code = 0;
    string color, color2;
    if (sslOption == 1) http = "https://";
    for (const auto& s : url) {
        curl_easy_setopt(curl, CURLOPT_URL, (http + host + s).c_str());
        curl_easy_perform(curl);
        curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
        if (http_code < 200) {color = "\033[1;34m"; /* yellow */}
        else if (http_code < 300) {color = "\033[1;32m";color2 = "\033[0;32m"; /* green */}
        else if (http_code < 400) {color = "\033[1;33m";color2 = "\033[0;33m"; /* blue */}
        else if (http_code < 500) {color = "\033[1;35m";color2 = "\033[0;35m"; /* purple */}
        else if (http_code < 600) {color = "\033[1;31m";color2 = "\033[0;31m"; /* red */}
        string output = color + to_string(http_code) + "   " + color2 + s + "\n";
        cout << output;
    }
    return 0;
}