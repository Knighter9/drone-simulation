/* DATA COLLECTION IMPLEMENTATION */

/* Includes */
#include "DataCollection.h"

/* namespace */
using namespace std;

void DataCollection::AddData(string strategy) { /*, float fuel*/
    strategies.push_back(strategy);
    /* add back when rdy */
    // fuels.push_back(fuel); 
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    speeds.push_back(static_cast<float>(duration.count())/1000);
}

void DataCollection::WriteDataToFile() {
    string fn = "Data/data.csv"; // Directs to folder/file.csv
    ofstream file(fn);
    if (file.is_open()) {
                                /* add fuel when rdy */
        file << "Strategy, Speed (ms)"/*, Fuel */ << endl;
        for (int i = 0; i < strategies.size(); i++) {
                                                      /* add fuel when rdy */
            file << strategies[i] << "," << speeds[i] /*<< "," << fuels[i]*/ << endl;
        }
        file.close();
        cout << "Data written to file: " << fn << endl;
    } else {
        cout << "Unable to open file: " << fn << endl;
    }
}
        