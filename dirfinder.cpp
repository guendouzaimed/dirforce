#include <iostream>
#include <curl/curl.h>
#include <fstream>
#include <string>
using namespace std;

size_t noop_cb(void *ptr, size_t size, size_t nmemb, void *data) {
  return size * nmemb;
}
int main() {
  CURL *curl;
  CURLcode res;
  string word;
  ifstream wordlist("dirlist.txt");
  string str = "http://www.google.com/";
  while(getline(wordlist, word)) {
    curl = curl_easy_init();
    if(curl) {
      str = "http://www.google.com/" + word;
      curl_easy_setopt(curl, CURLOPT_URL, str.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, noop_cb);
      curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 0);
      res = curl_easy_perform(curl);

      long http_code = 0;
      char *url = NULL;
      curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
      curl_easy_getinfo(curl, CURLINFO_REDIRECT_URL, &url); //CURLINFO_EFFECTIVE_URL
      string color;

      if (http_code < 200) {color = "\033[1;34m"; /* yellow */}
      else if (http_code < 300) {color = "\033[1;32m"; /* green */}
      else if (http_code < 400) {color = "\033[1;33m"; /* blue */}
      else if (http_code < 500) {color = "\033[1;35m"; /* purple */}
      else if (http_code < 600) {color = "\033[1;31m"; /* red */}
      if (http_code != 404) {
        cout << color << http_code << "   \033[0;37m/" << word;
        if (url) {
          cout << "   --> " <<"\033[0;34m" << url << endl;
        } else {cout << "\n";}
      }
      curl_easy_cleanup(curl);
    }
  }
  return 0;
}
