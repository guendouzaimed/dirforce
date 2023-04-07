int lineCounter(std::string filename) {
    std::ifstream infile(filename);
    int line_count = 0;
    std::string line;
    while (std::getline(infile, line)) {
        line_count++;
    }
    return line_count;
}