#include <sstream>
#include <iostream>
#include "filet.h"

Filet::Filet() {

}

Filet::Filet(std::istream *istream, std::string delim) {
    read(istream, delim);
}

void Filet::read(std::istream *istream, std::string delim) {
    std::string line;

    while (!istream->eof() && !istream->fail()) {
        std::getline(*istream, line, '\n');

        std::vector<std::string> row;
        size_t pos = 0;

        while ((pos = line.find(delim)) != std::string::npos) {
            row.push_back(line.substr(0, pos));
            line.erase(0, pos + delim.size());
        }

        row.push_back(line);

        push_back(row);
    }
}

void Filet::write(std::ofstream *ostream, std::string delim) {
    std::string output = "";

    for (std::vector <std::string> &row: *this) {
        for (std::string &value: row) {
            output += value + delim;
        }

        output = output.substr(0, output.size() - delim.size());
        output += "\n";
    }
    output = output.substr(0, output.size() - 1);

    *ostream << output;
}
