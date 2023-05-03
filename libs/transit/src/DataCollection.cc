/* DATA COLLECTION IMPLEMENTATION */

/* Includes */
#include "DataCollection.h"

/* namespace */
using namespace std;

void DataCollection::AddData(string strategy) { /*, float battery*/
    int counter = 0;
    strategies.push_back(strategy);
    cout << "strat: " << strategies.at(counter) << endl;
    /* add back when rdy */
    // batteries.push_back(battery);
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    speeds.push_back(static_cast<float>(duration.count())/1000);
    cout << "speeds: " << speeds.at(counter) << endl;
    counter++;
}

void DataCollection::WriteDataToFile() {
    string fn = "data.csv";  // opens data.csv file 
    ofstream file(fn);
    if (file.is_open()) {
                                /* add battery when rdy */
        file << "Strategy, Speed (ms)"/*, Battery used */ << endl;
        for (int i = 0; i < strategies.size(); i++) {
                                                      /* add battery when rdy */
            file << strategies[i] << ", " << speeds[i] /*<< "," << batteries[i]*/ << endl;
        }
        file.close();
        cout << "Data written to file: " << fn << endl;
    } else {
        cout << "Unable to open file: " << fn << endl;
    }
}
