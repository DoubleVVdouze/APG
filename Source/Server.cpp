//
// Created by DoubleVV on 05/03/2018.
//

#include <vector>

#include "Server.hpp"

Server::Server(int id, int openingCost):
        mID(id),
        mOpeningCost(openingCost),
        mIsOpen(false) {

}

void Server::addClient(Client client, int clientConnectionCost) {
    mListClient.emplace_back(client);
    mListClientCost.emplace_back(clientConnectionCost);
}

int Server::getID() const{
    return mID;
}

void Server::openServeur(){
    mIsOpen = true;
}

int Server::getOpeningCost() const{
    return mOpeningCost;
}

int Server::getNbClient() const{
    return mListClient.size();
}

int Server::getConnectionCost(int client) const{
    return mListClientCost[client];
}

int Server::getConnectionCostById(int id) const{
    int i = 0;
    for(Client client : mListClient){
        if(client.getID() == id){
            return mListClientCost[i];
        }
        i++;
    }
}

bool Server::isOpen() const {
    return mIsOpen;
}

Client Server::getClient(int client) const {
    return mListClient[client];
}


