#include <iostream>
#include <fstream>
#include <string>

int main() {
    int line_num; // Line's number
    std::string toav; // Type of variable
    std::string var_name; // Variable's name
    std::string str_var_content; // Variable's content as string
    int int_var_content; // Variable's content as int
    double double_var_content; // Variable's content as double
    char char_var_content; // Variable's content as char
    long long long_long_var_content; // Variable's content as long long
    std::string token; // Keyword
    std::string str; // Print's content
    char ctrl_char;

    std::ifstream infile("test.htpl");
    std::ofstream outfile("test.cpp");

    if (!infile.is_open() || !outfile.is_open()) {
        std::cerr << "Failed to open files!" << std::endl;
        return 1;
    }

    infile >> line_num;
    while (line_num--) {
        infile >> token;
        if (token == "import-std") {
            outfile << "#include<bits/stdc++.h>\nusing namespace std;\n";
            token="";
        } else if (token == "TS::") {
            outfile << "int main(){\n";
            token="";
        } else if (token == "::TE") {
            outfile << "return 0;\n}\n";
            token="";
        } else if (token == "say:") {
            infile >> ctrl_char;
            if (ctrl_char == '$') {
                infile >> var_name;
                outfile << "cout << " << var_name << ";\n";
            } else if (ctrl_char == '!') {
                std::getline(infile, str); // Read the rest of the line
                outfile << "cout << \"" << str.substr(1) << "\";\n"; // Remove the leading space
            }
            token="";
        } else if (token == "new:") {
            infile >> toav >> var_name;
            if (toav == "string") {
                std::getline(infile, str_var_content); // Read the rest of the line
                outfile << toav << " " << var_name << " = \"" << str_var_content.substr(1) << "\";\n"; // Remove the leading space
            } else if (toav == "int") {
                infile >> int_var_content;
                outfile << toav << " " << var_name << " = " << int_var_content << ";\n";
            } else if (toav == "double") {
                infile >> double_var_content;
                outfile << toav << " " << var_name << " = " << double_var_content << ";\n";
            } else if (toav == "char") {
                infile >> char_var_content;
                outfile << toav << " " << var_name << " = '" << char_var_content << "';\n";
            } else if (toav == "long long") {
                infile >> long_long_var_content;
                outfile << toav << " " << var_name << " = " << long_long_var_content << ";\n";
            }
            token="";
        }
    }
    infile.close();
    outfile.close();
    return 0;
}