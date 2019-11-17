#include "main.cli.h"

#include <iostream>

#include "ds.cli.h"

MainCLI::MainCLI() : CLI{"", {
    new DSCLI
}} {
}

CLI::Status MainCLI::beforeRun() {
    std::cout << "Type (e|x|q|exit|quit) at any point to exit." << std::endl;
    std::cout << "Type test at any point to run tests." << std::endl;
    return CLI::Status::Type::OKAY;
}

void MainCLI::eachRun() {
    std::cout << "Enter one of ds/a: " << std::flush;
}

void MainCLI::afterRun() {
    std::cout << "Bye." << std::endl;
}
