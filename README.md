# **dirforce**
## Website Directory Finder Tool

This is a fast and simple command-line tool written in C++ that allows you to search for directories on a website. The tool takes in a URL and outputs a list of all the directories that exist on the website. The tool's performance is optimized thanks to its implementation in C++, making it an efficient solution for locating directories on a website.
### Features

    Search for directories on a website.
    Specify custom wordlist.
    Fast performance due to its implementation in C++.
    Find directory from robots.txt file.

### Requirements

    A computer running a modern version of Windows, macOS, or Linux.
    A working internet connection.
    
### Installation

    git clone https://github.com/guendouzaimed/dirforce.git

### Usage

To use the dirforce Tool, simply compile the source code and run the resulting binary with the following command:
    
    chmod +x dirforce
    ./dirforce -u/--url [url] -w/--wordlist [wordlist.txt]

The url argument is the website you want to search for directories.
### Options

    -t or --thread specify how many thread to create
    -u or --url specify the url     (required)
    -w or --wordlist specify the wordlist   (required)

### Examples

Search for directories on the website https://www.example.com:


    ./dirforce -u https://www.example.com -w wordlist.txt


### Conclusion

This Website Directory Brute-forcing Tool provides a quick and efficient way to search for directories on a website. With its fast performance due to its implementation in C++, you can quickly and easily locate the directories you need. Its simple command-line interface makes it a convenient solution for reconnaissance you need in no time.
