#ifndef DATA_COLLECTION_H_
#define DATA_COLLECTION_H_

/* Includes */
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

/**
 * @brief this class is responsible for collecting the data
 */
class DataCollection {
    public:
        static DataCollection& GetInstance() {
            static DataCollection instance;
            return instance;
        }

        // Add data to collection
        void AddData(string strategy, float fuel) {}
        // Write data to file
        void WriteDataToFile(string filename) {}

    private:
        /* Private constructor and destructor to prevent instantiation */
        DataCollection() {
            start_time = chrono::high_resolution_clock::now(); 
        }
        ~DataCollection() {}

        /* Private data members */
        vector<string> strategies;
        vector<float> fuels;
        vector<float> speeds;
        chrono::high_resolution_clock::time_point start_time;

};

#endif

