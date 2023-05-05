/* DATA COLLECTION IMPLEMENTATION */

/* Includes */
#include "DataCollection.h"

/* namespace */
using namespace std;

void DataCollection::AddData(string strategy, float battery, float distance) { /* */
    // Store strategy
    strategies.push_back(strategy);

    // Calculates time
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    speeds.push_back(static_cast<float>(duration.count())/1000);

    // Calculates battery used
    auto battery_used = battery_start - battery;
    batteries.push_back(battery_used);

    // Store Distance
    distances.push_back(distance);
}

void DataCollection::WriteDataToFile() {
    string fn = "data.csv";  // opens data.csv file 
    ofstream file(fn);
    if (file.is_open()) {
        file << "Strategy, Speed (ms), Battery used, Distance" << endl;
        for (int i = 0; i < strategies.size(); i++) {
            file << strategies[i] << ", " << speeds[i] << ", " << batteries[i] << ", " << distances[i] << endl;
        }
        file.close();
        cout << "Data written to file: " << fn << endl;
    } else {
        cout << "Unable to open file: " << fn << endl;
    }
}
