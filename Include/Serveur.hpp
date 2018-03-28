//
// Created by DoubleVV on 05/03/2018.
//

#ifndef PROJETAPG_SERVEUR_HPP
#define PROJETAPG_SERVEUR_HPP

#include <vector>
#include "Client.hpp"

class Serveur {

public:
    Serveur(int, int);

    void addClient(Client, int);
    void openServeur();

    int getID() const;
    int getOpeningCost() const;
    int getNbClient() const;
    int getConnectionCost(int) const;
    bool isOpen() const;
    Client getClient(int) const;


private:
    int mID;

    int mOpeningCost;
    bool mIsOpen;

    std::vector<Client> mListClient;
    std::vector<int> mListClientCost;
};


#endif //PROJETAPG_SERVEUR_HPP
