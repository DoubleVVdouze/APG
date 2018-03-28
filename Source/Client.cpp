//
// Created by DoubleVV on 05/03/2018.
//

#include "Client.hpp"

Client::Client(int id) :
        mID(id),
        mHasJoined(false),
        mServeur(0) {

}

void Client::join(){
//    mServeur = server;
    mHasJoined = true;
}

bool Client::hasJoined() const{
    return mHasJoined;
}

int Client::getID() const{
    return mID;
}

int Client::getServerID() const{
    return mServeur;
}