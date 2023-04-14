#include "ChargingStationFactory.h"

IEntity* ChargingStationFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("charging station") == 0) {
    std::cout << "charging station Created" << std::endl;
    return new ChargingStation(entity);
  }
  return nullptr;
}
