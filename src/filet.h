#include <fstream>
#include <vector>

class Filet : public std::vector<std::vector<std::string>> {
public:
    Filet();

    Filet(std::istream *istream, std::string delim = ",");

    void read(std::istream *istream, std::string delim = ",");

    void write(std::ofstream *ostream, std::string delim = ",");
};