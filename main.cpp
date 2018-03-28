//
// Created by DoubleVV on 12/02/2018.
//

#include <memory>
#include <vector>
#include <Serveur.hpp>
#include <iostream>
#include <algorithm>
#include <Client.hpp>
#include <climits>
#include <ctime>
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

int calculAlpha(ListServer O, ListClient S, int& joiningClient){
    if(O.empty()){
        return INT_MAX;
    }

    int index = 0;
    int minimal = INT_MAX;

    for(Serveur serveur : O){
        index = 0;
        for(Client client : S) {
            if (minimal > serveur.getConnectionCost(client.getID())) {
                minimal = serveur.getConnectionCost(client.getID());
                joiningClient = index;
            }
            index++;
        }
    }

    return minimal;
}

int calculBeta(ListServer& O, ListServer& listServer, ListClient& Y, ListClient& S, ListClient listClient, int& openingServeur){
    Y.clear();

    ListClient Ytmp;

    std::vector<int> listCost;

    int result;
    int somme1 = 0;
    int somme2 = 0;
    int minimum = INT_MAX;
    int ratio;
    int test;

    int i = 0;
    bool isBestRatioFound = false;

    std::vector<int> heap;

    for(Serveur serveur : listServer) {
        if (serveur.isOpen()) {
            continue;
        }

        heap.clear();
        listCost.clear();
        Ytmp.clear();
        i = 0;
        somme1 = 0;
        somme2 = 0;
        test = 0;
        result = 0;
        isBestRatioFound = false;

        result = 2 * serveur.getOpeningCost();

        for (Client client : S) {
            somme1 += std::max(0, connectionCost(serveur.getClient(client.getID()), O) -
                                  serveur.getConnectionCostById(serveur.getClient(client.getID()).getID()));
        }

//        somme1 = std::max(0, somme1);

        for (Client client : S) {
            heap.push_back(serveur.getConnectionCostById(client.getID()));
        }

        std::make_heap(heap.begin(), heap.end());
        std::sort_heap(heap.begin(), heap.end());

        listCost.push_back(heap[0]);

        ratio = result - somme1 + listCost[0];
        i++;

        while (!isBestRatioFound) {
            listCost.push_back(heap[i]);

            somme2 = 0;
            for (int cost : listCost) {
                somme2 += cost;
            }

            test = (result + somme2 - somme1) / listCost.size();

            if (test < ratio) {
                i++;
                ratio = test;
            }
            else {
                isBestRatioFound = true;
                for (int cost : listCost) {
                    for (Client client : listClient) {
                        if (serveur.getConnectionCostById(client.getID()) == cost) {
                            Ytmp.push_back(client);
                            break;
                        }
                    }
                }
            }
        }
        if(ratio < minimum){
            minimum = ratio;
            Y = Ytmp;
            openingServeur = serveur.getID();
//            std::cout << "serveur : " <<  serveur.getID() << std::endl;
        }
//        std::cout << "serveur : " <<  serveur.getID() << "  /  " << ratio << std::endl;

    }
    return minimum;
}

ListServer algoGloutonRatio(ListServer& listServer, const ListClient& listClient){
    ListClient S = listClient;
    ListClient Y;
    ListClient Ytmp;
    ListServer O;

    std::vector<int> heap;

    int alpha = 0;
    int beta = 0;

    int joiningClient = 0;
    int openingServeur = 0;
    int i = 0;
    int ratio = 0;

    bool isBestRatioFound = false;

    while(!(S.empty())){
        alpha = calculAlpha(O, S, joiningClient);
        beta = calculBeta(O, listServer, Y, S, listClient, openingServeur);

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
    for (int index = 1 ; index <= 10 ; index++) {
        ListServer listServer;
        ListServer O;
        std::vector<Client> listClient;

        std::cout << "lancement de l'algo pour le fichier B1." << index << std::endl;

        std::unique_ptr<DataFile> dataFile(new DataFile("Data/B/B1."+std::to_string(index), listServer, listClient));

        clock_t begin = clock();

        O = algo(listServer, listClient);

        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

        std::cout << "temps écoulé : " << elapsed_secs << "s" << std::endl;

        for (const Serveur &serveur : O) {
            std::cout << serveur.getID() << std::endl;
        }

        std::cout << "fin de l'algo pour le fichier B1." << index << std::endl << std::endl;
    }
    return 0;
}