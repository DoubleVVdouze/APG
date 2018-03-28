//
// Created by DoubleVV on 05/03/2018.
//

#include <vector>

#include "Serveur.hpp"

Serveur::Serveur(int id, int openingCost):
        mID(id),
        mOpeningCost(openingCost),
        mIsOpen(false) {

}

void Serveur::addClient(Client client, int clientConnectionCost) {
    mListClient.emplace_back(client);
    mListClientCost.emplace_back(clientConnectionCost);
}

int Serveur::getID() const{
    return mID;
}

void Serveur::openServeur(){
    mIsOpen = true;
}

int Serveur::getOpeningCost() const{
    return mOpeningCost;
}

int Serveur::getNbClient() const{
    return mListClient.size();
}

int Serveur::getConnectionCost(int client) const{
    return mListClientCost[client];
}

bool Serveur::isOpen() const {
    return mIsOpen;
}

Client Serveur::getClient(int client) const {
    return mListClient[client];
}


