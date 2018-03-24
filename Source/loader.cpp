//
// Created by DoubleVV on 12/02/2018.
//

#include <c++/cstdlib>
#include <c++/cstdio>
#include "../Include/loader.hpp"

void skipLine(FILE *fp)
{
    while (fgetc(fp)!='\n');
}

Data* load_instance(const char* filename){
    FILE *fp;
    fp=fopen(filename, "r");
    skipLine(fp);
    Data* data=(Data*)std::malloc(sizeof(Data));
    int nothing;
    fscanf(fp,"%d %d %d", &data->facility_count, &data->client_count, &nothing);
    data->opening_cost=(int*)std::malloc((1+data->facility_count)*sizeof(int));
    data->connection=(int**)std::malloc((1+data->facility_count)*sizeof(int*));
    for (int fac=1;fac<=data->facility_count;fac++){
        fscanf(fp,"%d %d",&nothing, &data->opening_cost[fac]);
        data->connection[fac]=(int*)std::malloc((1+data->client_count)*sizeof(int));
        for(int client=1;client<=data->client_count; client++) {
            fscanf(fp,"%d", &data->connection[fac][client]);
        }
    }
    fclose(fp);
    return data;
}

void free_data(Data* data){
    for (int fac=1; fac<=data->facility_count;fac++)
        free(data->connection[fac]);
    free(data->connection);
    free(data->opening_cost);
    free(data);

    return;
}
