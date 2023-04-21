#include "DataCollection.h"

// I have no idea how I'm going to implement this quite yet.

void DataCollection::CollectData() {
    std::ofstream myfile;
    myfile.open("data.csv");
    
    myfile << "Strategy used, Time at pickup, Time at dropoff, Total time, Total battery used, Total battery remaining" << std::endl;


}
