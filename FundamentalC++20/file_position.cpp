#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <iomanip>
/*
Open file mode
+ ios::app - append all output to the end of the file
+ ios::ate - open a file for output and move to the end of the file

Data can be written anywhere in the file.
+ ios::in - input
+ ios::out - output
+ ios::trunc - discard the files' contents (default action for ios::out)
+ ios::binary - open a file for binary

+ ifstream seekg - get pointer -- byte number for next input
+ ofstream seekp - put pointer - byte number for next output
+ intput.seekg(0) - repositions get pointer to the beginning of file
+ input.clear() - clear end-of-file indicator so you can re-read from input

File position pointers:
+ ios::beg
+ ios::cur - position relative to current position
+ ios::end - position backward from end

*/

int main() {
    //create a file for testing 
    std::string fileName{"file_position.txt"};
    std::ofstream output("file_position.txt", std::ios::out);
    // output.op
    if (std::ofstream output(fileName, std::ios::out);output) {
        output << "[ hello, baby, world]\n";
        //output.;
    }
    std::cout << "read file 3 times without closing file";
    if (std::ifstream input(fileName, std::ios::in); input){
        int read_time = 0;
        std::string line;
        while (!input.eof()) {
            std::getline(input,line );
            std::cout << line << std::endl; 
            if (input.eof()) {
                if (read_time < 3) {        
                   input.clear();
                    input.seekg(0);
                    ++read_time;
                }
            }
        }
    }
    std::cout << "append content to file";
    if (std::ofstream ouput(fileName, std::ios::app);output) {
        output.seekp(-2, std::ios::end);
        output << ", newword]";
    }

    std::cout << "quoted text " << std::quoted("Alexander Graham Bell \t Johnson") << std::endl;

    return 0;
}