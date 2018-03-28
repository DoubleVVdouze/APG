//
// Created by DoubleVV on 12/02/2018.
//

#include <memory>
#include <vector>
#include <Serveur.hpp>
#include <iostream>
#include <algorithm>
#include <Client.hpp>
#include "Include/DataFile.hpp"

typedef std::vector<Serveur> ListServer;
typedef std::vector<Client> ListClient;

ListServer getUnion(const ListServer& listServer, const Serveur& serveur){
    ListServer tmp(listServer);
    tmp.push_back(serveur);
    return tmp;
}

int eval(const ListServer& listServer){
    if(listServer.empty()){
        return INT_MAX;
    }

    int somme = 0;

    for(Serveur serveur : listServer){
        somme += serveur.getOpeningCost();
    }

    for(int i = 0; i < listServer.begin()->getNbClient(); i++){
        int minimal = listServer[0].getOpeningCost();

        for(Serveur serveur : listServer){
            if(minimal > serveur.getConnectionCost(i)){
                minimal = serveur.getConnectionCost(i);
            }
        }

        somme += minimal;
    }

    return somme;
}

ListServer algoGlouton(ListServer& listServer){
    ListServer O;
    int i = 0;
    int score = 0;
    bool isOver = false;
    int minimal = 0;

    while(!isOver){
        minimal = eval(O);
        isOver = true;

        for(Serveur serveur : listServer){
            if(eval(getUnion(O, serveur)) < minimal){
                minimal = eval(getUnion(O, serveur));
                i = serveur.getID();
                isOver = false;
            }
        }

        if(!isOver){
            O.push_back(listServer[i]);
            listServer[i].openServeur();
        }
    }

    std::cout << eval(O) << std::endl;

    return O;
}

int connectionCost(Client client, ListServer listServer){
    if(listServer.empty()){
        return 0;
    }

    int minimum = INT_MAX;

    for(Serveur serveur : listServer){
        if(serveur.getConnectionCost(client.getID()) < minimum){
            minimum = serveur.getConnectionCost(client.getID());
        }
    }

    return minimum;
}

ListServer algoGloutonRatio(ListServer& listServer, const ListClient& listClient){
    ListClient S = listClient;
    ListClient Y;
    ListClient Ytmp;
    ListServer O;

    std::vector<int> heap;

    int alpha = INT_MAX;
    int beta = INT_MAX;

    int joiningClient = 0;
    int openingServeur = 0;
    int i = 0;
    int ratio = 0;

    bool isBestRatioFound = false;

    while(!S.empty()){
        Y.clear();

        /* Calcul d'alpha */
        for(Client client : S){
            for(Serveur serveur : O){
                if(serveur.getConnectionCost(client.getID()) < alpha){
                    alpha = serveur.getConnectionCost(client.getID());
                    joiningClient = i;
                }
            }
            i++;
        }

        /* Calcul de beta */
        for(Serveur serveur : listServer){
            if(!serveur.isOpen()){
                ratio = 2 * serveur.getOpeningCost();

                for(int client = 0; client < serveur.getNbClient(); client++){
                    heap.push_back(serveur.getConnectionCost(client));
                }

                std::make_heap(heap.begin(), heap.end());
                std::sort_heap(heap.begin(), heap.end());

                for(int client = 0; client < serveur.getNbClient(); client++){
                    if(serveur.getClient(client).hasJoined()){
                        continue;
                    }

                    ratio -= std::max(0, connectionCost(serveur.getClient(client), O) - serveur.getConnectionCost(serveur.getClient(client).getID()));
                }

                i = 1;

                while(!isBestRatioFound){
                    if((ratio + heap[i-1])/i < beta && i < listClient.size()) {
                        i++;
                    }
                    else{
                        ratio = (ratio + heap[i-1])/i;

                        for(int j = 0; j < i-1; j++){
                            for(int k = 0; k < serveur.getNbClient(); k++){
                                if(serveur.getConnectionCost(k) == heap[j]){
                                    Ytmp.push_back(listClient[k]);
                                }
                            }
                        }

                        isBestRatioFound = true;
                    }
                }

                if(ratio < beta){
                    beta = ratio;
                    Y = Ytmp;
                    openingServeur = serveur.getID();
                }

            }
        }

        if(alpha <= beta){
            S[joiningClient].join();
            S.erase(S.begin()+joiningClient);
        }
        else{
            for(auto client : Y){
                for(auto it = S.begin(); it != S.end();){
                    if(it->getID() == client.getID()){
                        it = S.erase(it);
                    }
                    else{
                        it++;
                    }
                }
            }

            listServer[openingServeur].openServeur();

            O.emplace_back(listServer[openingServeur]);
        }
    }

    std::cout << eval(O) << std::endl;

    return O;
}

ListServer algoGloutonRatioTas(const ListServer& listServer, const ListClient& listClient){

}

const ListServer algo(ListServer& listServer, const ListClient& listClient){
//    return algoGlouton(listServer);
    return algoGloutonRatio(listServer, listClient);
}

int main(){

    ListServer listServer;
    ListServer O;
    std::vector<Client> listClient;

    std::unique_ptr<DataFile> dataFile(new DataFile("Data/B/B1.1", listServer, listClient));

    O = algo(listServer, listClient);

    for(const Serveur& serveur : O){
        std::cout << serveur.getID() << std::endl;
    }

    return 0;
}























































