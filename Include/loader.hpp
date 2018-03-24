//
// Created by DoubleVV on 12/02/2018.
//

#ifndef PROJETAPG_LOADER_HPP
#define PROJETAPG_LOADER_HPP


/*Exemple de loader que vous pouvez modifier Ã  souhait de maniÃ¨re Ã
 *obtenir une structure de donnÃ©es qui vous correspond.
 *Le but est que vous n'y passiez pas trop de temps. */
typedef struct {
    int client_count;
    int facility_count;
    int* opening_cost;
    int** connection;
} Data;

void skipLine(FILE *fp);
Data* load_instance(const char* filename);
void free_data(Data* data);

#endif //PROJETAPG_LOADER_HPP
