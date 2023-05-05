#ifndef DATA_COLLECTION_H_
#define DATA_COLLECTION_H_

/* Includes */
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono> // NOLINT [build/c++11]
#include "BatteryDecorator.h"

/* namespace */
using namespace std;

/**
 * @class DataCollection
 * @brief This class is responsible for collecting the data
 * from the simulation
 */
class DataCollection {
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
  void AddData(float battery);

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
   * @param battery The battery level
   * @return Battery level at start of trip
   */
  float GetStartingBattery(float battery) {
    battery_start = battery;
  }

  /**
   * @brief Gets the strategy name used
   * @param strategy The name of the strategy
   */
  void GetStratName(string strategy);

  /**
   * @brief Gets the distance traveled
   * @param dist The distance traveled
   */
  void GetDistance(float dist);

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
