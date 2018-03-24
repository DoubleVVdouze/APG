//
// Created by DoubleVV on 12/02/2018.
//

#include <c++/memory>
#include "Include/DataFile.hpp"

int main(){

    std::unique_ptr<DataFile> dataFile(new DataFile("Data/B/B1.1"));

    return 0;
}