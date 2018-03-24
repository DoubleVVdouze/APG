//
// Created by DoubleVV on 05/03/2018.
//

#ifndef PROJETAPG_CLIENT_HPP
#define PROJETAPG_CLIENT_HPP


class Client {

public:
    Client(Serveur&, int);

    int getID();

private:
    Serveur mServeur;

    int mID;
};


#endif //PROJETAPG_CLIENT_HPP
