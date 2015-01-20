#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <fstream>
#include <string>

class Position {
public:
    int x, y;  
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        // primitive types are handled automatically
        ar & x;
        ar & y;
    }
};

class Person {
public:
    std::string name;
    Position pos;  
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        // std::string is handled automatically
        ar & name;
        // Position::serialize() will be called by the archive
        ar & pos;
    }
};

int main() {
    {
        // create the person
        Person op = { "John Doe", { 0, 1 } };
        // output file
        std::ofstream ofs("person.dat");
        // text archive wraps the output file
        boost::archive::text_oarchive oar(ofs);
        // write the object to the file
        oar << op;
    }  
    {
        // empty person that will be loaded
        Person ip;
        // input file
        std::ifstream ifs("person.dat");
        // text archive wraps the input file
        boost::archive::text_iarchive iar(ifs);
        // read the object from the file
        iar >> ip;
    }
}