#include <regex>
#include <string>

// Extract a header value from a raw HTTP header using a regular expression
std::string extract_header_value(const std::string& header, const std::string& field_name) {
    // Create a regular expression pattern that matches the header field name
    std::string pattern = field_name + R"(:\s*(.+)\r\n)";

    // Apply the regular expression to the raw HTTP header
    std::regex regex(pattern);
    std::smatch match;
    if (std::regex_search(header, match, regex)) {
        // Extract the captured value from the regex match object
        return match[1].str();
    }
    return "";
}
