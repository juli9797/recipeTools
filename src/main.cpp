#include "Debug.hpp"
#include "Parser.hpp"
#include "Recipe.hpp"
#include "Serializer.hpp"
#include "SerializerJSON.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    Debug::setDebugLevel(Debug::INFO);
    std::cout << "Recipe Toolkit V0.01" << std::endl;
    for (int i = 1; i < argc; i++) {
        std::string f(argv[i]);
        Parser p(argv[i]);
        Recipe rp = p.parse();
        SerializerJSON sj;
        Debug::info(rp.serialize(sj));
    }
    return 0;
}
