//
// Created by DoubleVV on 12/02/2018.
//

#include <memory>
#include <vector>
#include <Server.hpp>
#include <iostream>
#include <algorithm>
#include <climits>
#include <ctime>
#include "Include/DataFile.hpp"

typedef std::vector<Server> ListServer;
typedef std::vector<Client> ListClient;

ListServer getUnion(const ListServer& listServer, const Server& server){
    ListServer listWithUnion(listServer);
    listWithUnion.push_back(server);
    return listWithUnion;
}

int eval(const ListServer& listServer){
    if(listServer.empty()){
        return INT_MAX;
    }

    int sum = 0;
    int minimalCost;

    for(Server server : listServer){
        sum += server.getOpeningCost();
    }

    for(int i = 0; i < listServer.begin()->getNbClient(); i++){
        minimalCost = listServer[0].getOpeningCost();

        for(Server server : listServer){
            if(minimalCost > server.getConnectionCost(i)){
                minimalCost = server.getConnectionCost(i);
            }
        }

        sum += minimalCost;
    }

    return sum;
}

ListServer algoGlouton(ListServer& listServer){
    ListServer openedServer;
    int i = 0;
    bool isOver = false;
    int minimalScore = 0;

    while(!isOver){
        minimalScore = eval(openedServer);
        isOver = true;

        for(Server server : listServer){
            if(eval(getUnion(openedServer, server)) < minimalScore){
                minimalScore = eval(getUnion(openedServer, server));
                i = server.getID();
                isOver = false;
            }
        }

        if(!isOver){
            openedServer.push_back(listServer[i]);
            listServer[i].openServeur();
        }
    }

    std::cout << eval(openedServer) << std::endl;

    return openedServer;
}

int connectionCost(Client client, ListServer listServer){
    if(listServer.empty()){
        return 0;
    }

    int minimum = INT_MAX;

    for(Server &server : listServer){
        if(server.getConnectionCost(client.getID()) < minimum){
            minimum = server.getConnectionCost(client.getID());
        }
    }

    return minimum;
}

int calculAlpha(ListServer openedServer, ListClient clientNotJoined, int& joiningClient){
    if(openedServer.empty()){
        return INT_MAX;
    }

    int serverIndex = 0;
    int minimalScore = INT_MAX;

    for(Server server : openedServer){
        serverIndex = 0;
        for(Client client : clientNotJoined) {
            if (minimalScore > server.getConnectionCost(client.getID())) {
                minimalScore = server.getConnectionCost(client.getID());
                joiningClient = serverIndex;
            }
            serverIndex++;
        }
    }

    return minimalScore;
}

int calculBeta(ListServer& openedServer, ListServer& listServer, ListClient& joiningClientList, ListClient& clientNotJoined, ListClient listClient, int& openingServeur){
    joiningClientList.clear();

    ListClient joiningClientListOfMinimum;

    std::vector<int> listCost;

    int result;
    int sumOfClientJoining;
    int sumOfClientConnections = 0;
    int minimalCost = INT_MAX;
    int ratio;
    int currentScore;

    int serverIndex = 0;
    bool isBestRatioFound = false;

    std::vector<int> heap;

    for(Server& server : listServer) {
        if (server.isOpen()) {
            continue;
        }

        heap.clear();
        listCost.clear();
        joiningClientListOfMinimum.clear();
        serverIndex = 0;
        sumOfClientJoining = 0;
        ratio = 0;
        isBestRatioFound = false;

        result = 1 * server.getOpeningCost();

        for (Client client : clientNotJoined) {
            sumOfClientJoining += std::max(0, connectionCost(server.getClient(client.getID()), openedServer) -
                                  server.getConnectionCostById(server.getClient(client.getID()).getID()));
        }

        for (Client client : clientNotJoined) {
            heap.push_back(server.getConnectionCostById(client.getID()));
        }

        std::make_heap(heap.begin(), heap.end());
        std::sort_heap(heap.begin(), heap.end());

        while (!isBestRatioFound) {
            if(heap.empty()){
                break;
            }

            listCost.push_back(heap[serverIndex]);

            ratio = result - sumOfClientJoining + listCost[serverIndex];
            serverIndex++;

            sumOfClientConnections = 0;
            for (int cost : listCost) {
                sumOfClientConnections += cost;
            }

            currentScore = (result + sumOfClientConnections - sumOfClientJoining) / (int)listCost.size();

            if (currentScore < ratio && serverIndex > heap.size()) {
                serverIndex++;
                ratio = currentScore;
            }
            else {
                isBestRatioFound = true;
                for (int cost : listCost) {
                    for (Client client : listClient) {
                        if (server.getConnectionCostById(client.getID()) == cost) {
                            joiningClientListOfMinimum.push_back(client);
                            break;
                        }
                    }
                }
            }
        }
        if(ratio < minimalCost){
            minimalCost = ratio;
            joiningClientList = joiningClientListOfMinimum;
            openingServeur = server.getID();
//            std::cout << "server : " <<  server.getID() << std::endl;
        }
//        std::cout << "server : " <<  server.getID() << "  /  " << ratio << std::endl;

    }
    return minimalCost;
}

ListServer algoGloutonRatio(ListServer& listServer, const ListClient& listClient){
    ListClient clientNotJoined = listClient;
    ListClient joiningClientList;
    ListServer openedServer;

    std::vector<int> heap;

    int alpha = 0;
    int beta = 0;

    int joiningClient = 0;
    int openingServeur = 0;

    while(!(clientNotJoined.empty())){
        alpha = calculAlpha(openedServer, clientNotJoined, joiningClient);
        beta = calculBeta(openedServer, listServer, joiningClientList, clientNotJoined, listClient, openingServeur);

        if(alpha <= beta){
            clientNotJoined[joiningClient].join();
            clientNotJoined.erase(clientNotJoined.begin()+joiningClient);
        }
        else{
            for(auto client : joiningClientList){
                for(auto iterator = clientNotJoined.begin(); iterator != clientNotJoined.end();){
                    if(iterator->getID() == client.getID()){
                        iterator = clientNotJoined.erase(iterator);
                    }
                    else{
                        iterator++;
                    }
                }
            }

            listServer[openingServeur].openServeur();

            openedServer.emplace_back(listServer[openingServeur]);
        }
    }

    std::cout << eval(openedServer) << std::endl;

    return openedServer;
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
        ListServer openedServer;
        std::vector<Client> listClient;

        std::cout << "lancement de l'algo pour le fichier B1." << index << std::endl;

        std::unique_ptr<DataFile> dataFile(new DataFile("Data/B/B1."+std::to_string(index), listServer, listClient));

        clock_t begin = clock();

        openedServer = algo(listServer, listClient);

        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

        std::cout << "temps écoulé : " << elapsed_secs << "s" << std::endl;

        for (const Server &server : openedServer) {
            std::cout << server.getID() << std::endl;
        }

        std::cout << "fin de l'algo pour le fichier B1." << index << std::endl << std::endl;
    }
    return 0;
}