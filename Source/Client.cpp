//
// Created by DoubleVV on 05/03/2018.
//

#include "Client.hpp"

#include <Serveur.hpp>

Client::Client(Serveur& serveur, int id) :
        mServeur(serveur),
        mID(id) {

}

int Client::getID() {
    return mID;
}