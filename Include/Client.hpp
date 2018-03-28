//
// Created by DoubleVV on 05/03/2018.
//

#ifndef PROJETAPG_CLIENT_HPP
#define PROJETAPG_CLIENT_HPP

class Client {

public:
    explicit Client(int);

    void join();

    int getID() const;
    bool hasJoined() const;
    int getServerID() const;

private:

    int mID;
    bool mHasJoined;
    int mServeur;
};


#endif //PROJETAPG_CLIENT_HPP
