
<!-- Google tag (gtag.js) -->
<script async src="https://www.googletagmanager.com/gtag/js?id=G-NK9KNRLF1B"></script>
<script>
  window.dataLayer = window.dataLayer || [];
  function gtag(){dataLayer.push(arguments);}
  gtag('js', new Date());

  gtag('config', 'G-NK9KNRLF1B');
</script>

# **dirforce**
<a href="https://guendouzaimed.github.io/dirforce/changelog/" style="position: absolute;top: 7px;right: 7px;">changelog</a>
<center>
    
<img src="https://i.postimg.cc/RFpZFjVJ/dirforce.png">
    
</center>

## Website Directory Finder Tool

This is a fast command-line tool written in C++ that allows you to search for directories on a website. The tool takes in a URL and outputs a list of all the directories that exist on the website. The tool's performance is optimized thanks to its implementation in C++, making it an efficient solution for locating directories on a website.

### Requirements

    A computer running Linux.
    A working internet connection.
    
### Installation

    git clone https://github.com/guendouzaimed/dirforce.git
    
change working directory to dirforce

    cd dirforce
    bash setup.sh
    
### Usage

To use the dirforce Tool after installation you can run:
    
    dirforce -u/--url [url] -w/--wordlist [wordlist.txt]

The url argument is the website you want to search for directories.
### Options

    -u or -host: Specifies the host (required).
    -w or -wordlist: Specifies the wordlist (required).
    -t or -thread: Specifies the number of threads to create.
    -m or -method: Specifies the HTTP method.
    -r or -request: Specifies to import the request from a file.
    -s or -suffixe: Adds a string at the beginning of every path in the wordlist.
    -p or -preffixe: Adds a string at the end of every path in the wordlist.
    --custom-header-o: Outputs a specific header value.
    -e or -extension: Adds an extension after each word in the wordlist (e.g., -e php,html will send requests to word, word.php, and word.html).
    -f or -filter: Hides responses that contain the specified string.
    --lite: Outputs in lite mode (complete URL, no color, no logo).
    --norobot: Disables the use of the robots.txt file.
    
### choose http method
    
    dirforce -u https://www.example.com -w wordlist.txt -m METHOD
    
For example:

    
    dirforce -u https://www.example.com -w wordlist.txt -m GET
    
note that the default method is HEAD which reveal only the header

### import request from a file
to import request from file you need to create a file containing the request as following:

    
    HEAD PATH HTTP/1.1
    Host: HOSTNAME
    Connection: keep-alive
    
    
and then you can add your custom header like this:

    
    HEAD PATH HTTP/1.1
    Host: HOSTNAME
    Connection: keep-alive
    User-Agent: Mozilla/5.0
    
    
to run the tool:

    
    dirforce -u https://www.example.com/ -w wordlist.txt -r requestFile.txt
    
    
### add suffixe and prefixe
for suffixe:

    
    dirforce -u https://www.example.com/ -w wordlist.txt -s suffixe
    
    
for prefixe:

    
    dirforce -u https://www.example.com/ -w wordlist.txt -p preffixe
    
    
### thread
number of thread is the number of process running in the same time and each process send multiple request to the server, so the more threads you use, the faster dirforce will run.

to specify the number of thread use -t or --thread:

    dirforce -u https://www.example.com/ -w wordlist.txt -t number_of_thread

### output a header value
to output a header value you can specify it with --custom-header-o , example:

    dirforce -u https://www.example.com/ -w wordlist.txt --custom-header-o Content-Type

### add an extension for every word in the wordlist
you can do it with -e or --extension, example:

    dirforce -u https://www.example.com/ -w wordlist.txt -e php,html,js
    
make sure to separate the extensions with "," and do not include space

### Filter
you can filter the output from response that include a specific term like "Content-Length: 0" with -f or --filter

    dirforce -u https://www.example.com/ -w wordlist.txt --filter "Content-Length: 0"

### lite mode
lite mode is an output option that:
    
    output complete url
    no color
    no logo

to use lite mode use --lite example:

    dirforce -u https://www.example.com/ -w wordlist.txt --lite

### robots.txt file
by default the robots.txt file is used to find path you disable this option by using --norobot

        dirforce -u https://www.example.com/ -w wordlist.txt --norobot

### Examples

Search for directories on the website https://www.example.com:

    dirforce -u https://www.example.com -w wordlist.txt
    
Search for directories on the website https://www.example.com with 100 thread:

    dirforce -u https://www.example.com -w wordlist.txt -t 100
    
Search for directories on the website https://www.example.com with POST method:
    
    dirforce -u https://www.example.com -w wordlist.txt -t 100

### Compiling

follow the following steps if you want to compile the tool from source code.

before you compile the source code make sure to have openssl and libcurl installed
    
    g++ -I/usr/local/ssl/include dirforce.cpp -o dirforce -L/usr/local/ssl/lib -lssl -lcrypto -lcurl

### Conclusion

This Website Directory Discovery Tool provides a quick and efficient way to search for directories on a website. With its fast performance due to its implementation in C++, you can quickly and easily locate the directories you need. Its simple command-line interface makes it a convenient solution for reconnaissance you need in no time.

note: use this tool only for ethical purposes.
