//
// Created by DoubleVV on 12/02/2018.
//

#include <c++/iostream>
#include <loader.hpp>
#include <Serveur.hpp>
#include <c++/bits/unique_ptr.h>
#include "../Include/DataFile.hpp"

DataFile::DataFile(std::string name) {
    std::cout << "Meldrick a une petite bite" << std::endl;
    std::cout << name << std::endl;

    loadFile(name);
}

Data* DataFile::getFile() {
    return file;
}

void DataFile::loadFile(std::string name) {
    file = load_instance(name.c_str());

    printf("%d \n", file->connection[file->facility_count][file->client_count]);
    printf("%d \n", file->opening_cost[1]);

    for(int i = 1; i < file->facility_count + 1; i++){
        Serveur s(i, file->opening_cost[i]);
        for(int j = 1; j < file->client_count + 1; j++){
            std::unique_ptr<Client> client(new Client(s, j));
            s.addClient(std::move(client));
        }
    }
}