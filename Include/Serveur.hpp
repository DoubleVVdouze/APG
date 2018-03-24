//
// Created by DoubleVV on 05/03/2018.
//

#ifndef PROJETAPG_SERVEUR_HPP
#define PROJETAPG_SERVEUR_HPP

#include "Client.hpp"

class Serveur {

public:
    Serveur(int, int);

    void addClient(Client&);
    void openServeur();

    int getID();

private:
    int mID;

    int mOpeningCost;
    bool mIsOpen;

    std::vector<Client> mListClient;
};


#endif //PROJETAPG_SERVEUR_HPP
