#ifndef DATA_COLLECTION_H_
#define DATA_COLLECTION_H_

/* Includes */
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include "BatteryDecorator.h"

/* namespace */
using namespace std;

/**
 * @class DataCollection
 * @brief This class is responsible for collecting the data
 * from the simulation
 */
class DataCollection : public BatteryDecorator {
 public:
  /**
   * @brief Get instance of the collected data
   * @return DataCollection instance
   */
  static DataCollection& GetInstance() {
    static DataCollection instance;
    return instance;
  }

  /**
   * @brief Add data to collection
   * @param strategy Strategy name
   */
  void AddData(string strategy, float battery, float distance);

  /**
   * @brief Write data to file
   */
  void WriteDataToFile();

  /**
   * @brief Start timer
   */
  void StartTime() {
    start_time = chrono::high_resolution_clock::now();
  }

  /**
   * @brief Get the starting battery
   * @return Battery level at start of trip
   */
  float GetStartingBattery(float battery) {
    battery_start = battery;
  }

 protected:
  /* Private constructor and destructor to prevent instantiation */
  DataCollection() {}
  ~DataCollection() {}

  /* Private data members */
  vector<string> strategies;
  vector<float> batteries;
  vector<float> speeds;
  vector<float> distances;
  chrono::high_resolution_clock::time_point start_time;
  float battery_start;
};

#endif
