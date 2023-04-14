#ifndef ChargingStation_H_
#define ChargingStation_H_

#include "IEntity.h"
#include "IStrategy.h"

class ChargingStation : public IEntity {
 public:
  /**
   * @brief ChargingStation are created with a name
   * @param obj JSON object containing the ChargingStations information
   */
  ChargingStation(JsonObject& obj);

  /**
   * @brief Destroy the ChargingStation object
   */
  ~ChargingStation();
  /**
   * @brief Gets the speed of the chargingStation
   * @return The speed of the chargingStation
   */
  float GetSpeed() const { }

  /**
   * @brief Gets the position of the chargingStation
   * @return The position of the chargingStation
   */
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Gets the direction of the chargingStation
   * @return The direction of the chargingStation
   */
  Vector3 GetDirection() const {}
  /**
   * @brief Gets the destination of the chargingStation
   * @return The destination of the chargingStation
   */
  Vector3 GetDestination() const {}

  /**
   * @brief Gets the details information of the chargingStation
   * @return The details information of the chargingStation
   */
  JsonObject GetDetails() const { return details; }

  bool GetAvailability() const { return available; }

  void SetAvalibility(bool choice){
    this->available = choice;
  }

  private:
  JsonObject details;
  Vector3 position;
  bool available;
};

#endif
