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

void Serveur::addClient(Client &client) {
    mListClient.push_back(client);
}

int Serveur::getID(){
    return mID;
}

void Serveur::openServeur(){
    mIsOpen = true;
}