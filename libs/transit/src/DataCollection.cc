/* DATA COLLECTION IMPLEMENTATION */

/* Includes */
#include "DataCollection.h"

/* namespace */
using namespace std;

void DataCollection::AddData(float battery) {

    // Calculates time
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    speeds.push_back(static_cast<float>(duration.count())/1000);

    // Calculates battery used
    float battery_used = battery_start - battery;
    batteries.push_back(battery_used);

}

void DataCollection::WriteDataToFile() {
    string fn = "data.csv";  // opens data.csv file 
    ofstream file(fn);
    if (file.is_open()) {
        file << "Strategy, Speed (ms), Battery used, Distance" << endl;
        for (int i = 0; i < strategies.size(); i++) {
            file << strategies[i] << ", " << speeds[i] << ", " << batteries[i] << ", " << distances[i+1] << endl;
        }
        file.close();
        cout << "Data written to file: " << fn << endl;
    } else {
        cout << "Unable to open file: " << fn << endl;
    }
}

void DataCollection::GetStratName(string strategy) {
    strategies.push_back(strategy);
}

void DataCollection::GetDistance(float dist) {
    distances.push_back(dist);
}