#include <iostream>

#include "CityMapCli.h"

int main() {
    citymap::cli::CityMapCli cli(std::cout, std::cin);
    cli.start();
    return 0;
}
