#include "workFile.hpp"

#include <fstream>

namespace ble_src::file::services {

std::string get_last_line(const std::string fn)
{
    std::string result = "";
    std::ifstream fin;
    fin.open(fn);
    if (fin.is_open()) {
        fin.seekg(-2, std::ios_base::end); // go to one spot before the EOF

        bool keepLooping = true;
        while (keepLooping) {
            char ch;
            fin.get(ch); // Get current byte's data

            if ((int)fin.tellg() <= 1) { // If the data was at or before the 0th byte
                fin.seekg(0); // The first line is the last line
                keepLooping = false; // So stop there
            } else if (ch == '\n') { // If the data was a newline
                keepLooping = false; // Stop at the current position.
            } else { // If the data was neither a newline nor at the 0 byte
                fin.seekg(-2, std::ios_base::cur); // Move to the front of that data, then to the front of the data before it
            }
        }

        getline(fin, result); // Read the current line

        fin.close();
    }

    return result;
}

std::vector<std::string> read_file_from_line(int start_line, const std::string fn)
{
    std::vector<std::string> result;

    std::ifstream file(fn);
    std::string str;
    if (file.is_open()) {
        int index= 0;
        while (std::getline(file, str)) {
            // Process str
            if (index >= start_line){
                result.push_back(str);
            }
            index ++;
        }
    }

    return result;
}

}
