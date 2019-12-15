#include <iostream>

#include "CityMapCli.h"

int main() {
    CityMap::Cli::CityMapCli cli(std::cout, std::cin);
    cli.start();
    return 0;
}
