//
// Created by DoubleVV on 12/02/2018.
//

#include <c++/iostream>
#include <loader.hpp>
#include <Serveur.hpp>
#include <c++/bits/unique_ptr.h>
#include <Client.hpp>
#include "../Include/DataFile.hpp"

DataFile::DataFile(std::string name, std::vector<Serveur>& listServer, std::vector<Client>& listClient) {
    std::cout << name << std::endl;

    loadFile(name, listServer, listClient);
}

Data* DataFile::getFile() {
    return file;
}

void DataFile::loadFile(std::string name, std::vector<Serveur>& listServer, std::vector<Client>& listClient) {
    file = load_instance(name.c_str());

    for(int i = 1; i < file->facility_count + 1; i++){
        Serveur s(i-1, file->opening_cost[i]);
        for(int j = 1; j < file->client_count + 1; j++){
            Client client(j-1);
            s.addClient(client, file->connection[i][j]);
        }
        listServer.push_back(s);
    }

    for(int i = 1; i < file->client_count + 1; i++){
        Client client(i-1);
        listClient.push_back(client);
    }
}