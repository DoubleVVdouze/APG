//
// Created by DoubleVV on 12/02/2018.
//

#ifndef PROJETAPG_DATAFILE_HPP
#define PROJETAPG_DATAFILE_HPP

#include <c++/string>
#include "../Include/loader.hpp"


class DataFile {
public :
    DataFile(std::string);

public:
    Data* getFile();

private:
    void loadFile(std::string);

private:
    Data* file;
};


#endif //PROJETAPG_DATA_HPP