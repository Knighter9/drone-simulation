/* DATA COLLECTION IMPLEMENTATION */

/* Includes */
#include "DataCollection.h"

/* namespace */
using namespace std;

void DataCollection::AddData(string strategy, float fuel) {
    strategies.push_back(strategy);
    fuels.push_back(fuel);
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    speeds.push_back(static_cast<float>(duration.count())/1000);
}

void DataCollection::WriteDataToFile(string filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "Strategy,Speed (ms),Fuel" << endl;
        for (int i = 0; i < strategies.size(); i++) {
            file << strategies[i] << "," << speeds[i] << "," << fuels[i] << endl;
        }
        file.close();
        cout << "Data written to file: " << filename << endl;
    } else {
        cout << "Unable to open file: " << filename << endl;
    }
}
        