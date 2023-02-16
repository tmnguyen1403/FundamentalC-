#include <iostream>
#include <string>
#include "zip_file.hpp"

int main() {
    std::cout << "Enter a ZIP file name: ";
    std::string zipFileName;
    std::getline(std::cin, zipFileName);

    std::string content{
        "Learning about new C++20 feature "
        ".The white space at the end of the string literal "
        "will be converted in to a giant string by C++ "
        ".I think this is a very neat feature that I did not know"
    };

    std::cout << content << std::endl;

    miniz_cpp::zip_file output;

    output.writestr("c++tip.txt", content); // write the file to zip file with content
    output.save(zipFileName);

    miniz_cpp::zip_file input{zipFileName};

    std::cout << "ZIP file's name: " << input.get_filename()
        <<"\n\nZIP file's directory listing:\n";
    input.printdir();

    miniz_cpp::zip_info info{input.getinfo("c++tip.txt")};

    std::cout << "\nFile name: " << info.filename
        << "\nOriginal size:" << info.file_size 
        << "\nCompressed size: " << info.compress_size;
    
    std::string extractedContent{input.read(info)};

    std::cout << "\n\n Original contents of intro.txt:\n"
        << extractedContent << std::endl;
    return 0;

}