//
// Created by DoubleVV on 12/02/2018.
//

#ifndef PROJETAPG_DATAFILE_HPP
#define PROJETAPG_DATAFILE_HPP

#include <string>
#include "../Include/loader.hpp"


class DataFile {
public :
    DataFile(std::string, std::vector<Server>&, std::vector<Client>&);

public:
    Data* getFile();

private:
    void loadFile(std::string, std::vector<Server>&, std::vector<Client>&);

private:
    Data* file;
};


#endif //PROJETAPG_DATA_HPP
