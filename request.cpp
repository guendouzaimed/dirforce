int output(string response, string path) {
    //if filterStr is in the response d'ont output anything
    if (filterOption && response.find(filterStr) != string::npos) return 0;
    //else output the response
    string status = response.substr(response.find("HTTP/") + 9, 3);
    string custom_header = extract_header_value(response, custom_header_str);
    string redirect = extract_header_value(response, "Location");
    if (stoi(status) != 404) {
        int http_code = stoi(status);
        string color, color2;
        if (http_code < 200) {color = "\033[1;34m"; /* yellow */}
        else if (http_code < 300) {color = "\033[1;32m";color2 = "\033[0;32m"; /* green */}
        else if (http_code < 400) {color = "\033[1;33m";color2 = "\033[0;33m"; /* blue */}
        else if (http_code < 500) {color = "\033[1;35m";color2 = "\033[0;35m"; /* purple */}
        else if (http_code < 600) {color = "\033[1;31m";color2 = "\033[0;31m"; /* red */}
        
        if (liteOutput) {
            if (sslOption == 0) {
                string output = "http://" + host + path + "\n"; 
                cout << output;
            } else {
                string output = "https://" + host + path + "\n"; 
                cout << output;
            }
            return 0;
        }

        if (redirect != "")
            redirect = "  -> " + redirect;
        stringstream output;
        output << left << setw(15) << setfill(' ') << color + status << setw(custom_header_str.size() + 2) << setfill(' ') << "- " + custom_header + " -"<< setw(15) << setfill(' ') << color2 + path << setw(20) << setfill(' ') << redirect + "\n";
        cout.flush();
        cout << output.str();
    }
    return 0;
}

int request(const struct sockaddr *dest_addr, socklen_t addrlen)
{
    //create and connect a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Failed to create socket\n";
        return 1;
    }

    if (connect(sock, dest_addr, addrlen) == -1) {
        std::cerr << "Error connecting to server\n";
        return -1;
    }

    if (sslOption == 1) {
        //initialize ssl library
        SSL_library_init();
        SSL_load_error_strings();
        //create a new SSL_CTX object and initializes it for a TLS client
        SSL_CTX* ssl_ctx = SSL_CTX_new(TLS_client_method());
        if (ssl_ctx == nullptr) {
            std::cerr << "Error creating SSL context\n";
            return -1;
        }
        //create a new SSL object that is associated with the previously created SSL_CTX object
        SSL* ssl = SSL_new(ssl_ctx);
        if (ssl == nullptr) {
            std::cerr << "Error creating SSL connection\n";
            return -1;
        }
        //associates the SSL object ssl with the file descriptor sockfd
        if (SSL_set_fd(ssl, sock) == 0) {
            std::cerr << "Error attaching SSL connection to socket\n";
            return -1;
        }
    
        if (SSL_connect(ssl) != 1) {
            std::cerr << "Error performing SSL handshake\n";
            return -1;
        }
        // Check if the wordlist file is open
        if (!wordlist.is_open()) {
            std::cerr << "Failed to open wordlist file\n";
            return 1;
        }

        string word;
        bool loop = true;
        while(loop) {
            wordlist_lock.lock();
            getline(wordlist, word);
            wordlist_lock.unlock();
            //remove "/" in the begining if exist
            if (word[0] == '/') {
                word = word.substr(1);
            }
            if (wordlist.eof()) {
                break;
            }
            for (auto& ext : extension) {
                string path = address + preffixe + word + suffixe + ext;
                string rawrequest;
                if (requestOption == 0) {
                    rawrequest = http_method + " " + path + " HTTP/1.1\r\nHost: " + host + "\r\n" + "Connection: keep-alive\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3\r\n\r\n";
                } else {
                    rawrequest = readrequest.substr(0, readrequest.find("PATH")) + path + readrequest.substr(readrequest.find("PATH") + 4);
                    rawrequest = rawrequest.substr(0, rawrequest.find("HOSTNAME")) + host + rawrequest.substr(rawrequest.find("HOSTNAME") + 8);
                }
                int n = SSL_write(ssl, rawrequest.c_str(), rawrequest.size());
                if (n <= 0) {
                    std::cerr << "Error sending HTTP request\n";
                    return -1;
                }
        
                char buf[2000];
                int len;
                string response;
                while ((len = SSL_read(ssl, buf, sizeof(buf))) > 0) {
                    response.append(buf, len);
                    if (response.find("\r\n\r\n") != string::npos) break;

                }
                if (response.find("HTTP/") != string::npos) {
                    output(response, path);
                    if(!liteOutput) {
                        progresslock.lock();
                        progress();
                        progresslock.unlock();
                    }
                } else {//if the server close the connection create new socket connection
                    request(dest_addr, addrlen);
                    loop = false;
                    break;
                }
            }
        }
    } else {
        string word;
        bool loop = true;
        while(loop) {
            wordlist_lock.lock();
            getline(wordlist, word);
            //remove "/" in the begining if exist
            if (word[0] == '/') {
                word = word.substr(1);
            }
            wordlist_lock.unlock();
            if (wordlist.eof()) {
                break;
            }
            for (auto& ext : extension) {
                string path = address + preffixe + word + suffixe + ext;
                string rawrequest;
                if (requestOption == 0) {
                    rawrequest = http_method + " " + path + " HTTP/1.1\r\nHost: " + host + "\r\n" + "Connection: keep-alive\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3\r\n\r\n";
                } else {
                    rawrequest = readrequest.substr(0, readrequest.find("PATH")) + path + readrequest.substr(readrequest.find("PATH") + 3);
                }
                // Send the HTTP request  without ssl
                if (send(sock, rawrequest.c_str(), rawrequest.size(), 0) == -1) {
                    cout << "error \n";
                    return 0;
                }

                // Receive the response to the request
                std::string response;
                char buf[4096];
                int num_bytes;
                while ((num_bytes = recv(sock, buf, sizeof(buf), 0)) > 0) {
                    response.append(buf, num_bytes);
                    if (response.find("\r\n\r\n") != string::npos) break;
                }
                if (response.find("HTTP/") != string::npos) {
                    output(response, path);
                    if(!liteOutput) {
                        progresslock.lock();
                        progress();
                        progresslock.unlock();
                    }
                } else { //if the server close the connection create new socket connection
                    request(dest_addr, addrlen);
                    loop = false;
                    break;
                }
            }
        }
    }
    close(sock);
    return 0;
}