#define _USE_MATH_DEFINES
#include "ChargingStation.h"

#include <cmath>
#include <limits>

#include "BeelineStrategy.h"

ChargingStation::ChargingStation(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  available = true;
}

ChargingStation::~ChargingStation() {
}
