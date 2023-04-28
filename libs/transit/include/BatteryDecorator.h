#ifndef BATTERY_DECORATOR_H_
#define BATTERY_DECORATOR_H_

#include "IEntityBaseDecorator.h"

/**
 * @class BatteryDecorator
 * @brief Represents a decorator for the drone batteries
 */
class BatteryDecorator : public IEntityBaseDecorator {
 public:
  /**
   * @brief Construct a new Battery Decorator object
   * @param entity The entity to decorate onto
   */
  BatteryDecorator(IEntity *entity) : IEntityBaseDecorator(entity) {
    this->batteryLife = 100.0;
    this->charging = false;
  }

  /**
   * @brief BatteryDecorator destructor
   */
  ~BatteryDecorator();

  /**
   * @brief Updates the drone battery
   * @param dt Delta time
   * @param scheduler The list of all entities in the system
   * @param chargingStations The vector of charging stations in the physical
   * system
   */
  void Update(double dt, std::vector<IEntity*> scheduler,
              std::vector<IEntity*> chargingStations);

  /**
   * @brief Determines whether the drone needs to be recharged yet. A drone
   * needs to be recharged if it has 25% or less battery life left.
   * @return True if the drone needs to be recharged, false if the drone
   * does not need to be recharged yet.
   */
  bool NeedRecharge();

  /**
   * @brief Determines if the drone is fully charged or not. A drone is
   * fully charged if battery = 100
   * @return True if the drone is fully charged, false if the drone is not
   * fully charged.
   */
  bool FullyCharged();

  /**
   * @brief Sets the graph object used by the entity in the simulation
   * @param graph The IGraph object to be used
   */
  void SetGraph(const IGraph* graph) override {
    this->graph = graph;
    entity->SetGraph(graph);
  }

  /**
   * @brief Gets the nearest charging station to the drone
   * @param chargingStations The vector of charging stations in the physical
   * system
   */
  void GetNearestChargingStation(std::vector<IEntity*> chargingStations);

  /**
   * @brief Determines if the drone can pick up the next scheduled robot
   * @param dt Delta time
   * @param scheduler The list of all entities in the system
   * @return True if the drone can pick up the next robot, False if the
   * drone cannot pick up the next robot
   */
  bool NextPickupPossible(double dt, std::vector<IEntity*> scheduler);

 private:
  float batteryLife;  // 100 will be fully charged. 0 will be empty.
  bool charging;
  IEntity* nearestChargingStation;
  IStrategy* toChargingStation = nullptr;
};

#endif
