#include "BatteryDecorator.h"
#include "BeelineStrategy.h"
#include "routing/astar.h"

BatteryDecorator::~BatteryDecorator() {
    delete entity;
    delete nearestChargingStation;
    delete toChargingStation;
}
bool BatteryDecorator::NeedRecharge() {
    return batteryLife <= 30.0;
}

bool BatteryDecorator::FullyCharged() {
    return batteryLife >= 100.0;
}

bool BatteryDecorator::NextPickupPossible(double dt,
  std::vector<IEntity*> scheduler) {
    // I belive update is called once every second, so a
    // rough approximation can be used.
    // step 1, determine the nearest entity
    float minDis = std::numeric_limits<float>::max();
    IEntity * closestEntity = nullptr;
    for (auto entity : scheduler) {
        if (entity->GetAvailability()) {
            float disToEntity =
              this->entity->GetPosition().Distance(entity->GetPosition());
            if (disToEntity <= minDis) {
                minDis = disToEntity;
                closestEntity = entity;
            }
        }
    }
    if (closestEntity) {
        // check to see if the the flight is possible.
        float distToFinalLocation = 0;
        std::vector<std::vector<float>> path;
        Vector3 startVec = closestEntity->GetPosition();
        Vector3 desVec = closestEntity->GetDestination();

        // can expand later on but right now just checking A star strategy path
        std::vector<float> start = {startVec[0], startVec[1], startVec[2]};
        std::vector<float> end   = {desVec[0], desVec[1], desVec[2]};

        path = graph->GetPath(start, end, AStar::Default());

        for (int i = 0; i < path.size()-1; i++) {
            Vector3 curr = Vector3(path[i][0], path[i][1], path[i][2]);
            Vector3 next = Vector3(path[i+1][0], path[i+1][1], path[i+1][2]);
            distToFinalLocation += curr.Distance(next);
        }

        // adding a simple multiplier on to accout for travel to the charging
        // station we don't ever want to fall below 20% for battery life.
        // lets say max distance is the number of calls to update possible with
        // current battery life * the speed * dt.
        // we must factor in time it takes to get to the charging station.
        float totalDistance = (distToFinalLocation + minDis);
        int maxNumberCalls = floor((batteryLife - 20)/0.005);
        float maxTotalDistance = maxNumberCalls * this->entity->GetSpeed()*dt;

        return (totalDistance <= maxTotalDistance);
    }
    // no closest entity so just return true
    return true;
}
void BatteryDecorator::GetNearestChargingStation(
  std::vector<IEntity*> chargingStations) {
    float minDis = std::numeric_limits<float>::max();
    for (auto station : chargingStations) {
        if (station->GetAvailability()) {
            float disToEntity =
              this->entity->GetPosition().Distance(station->GetPosition());
            if (disToEntity <= minDis) {
                minDis = disToEntity;
                nearestChargingStation = station;
            }
        }
    }
    if (nearestChargingStation) {
        nearestChargingStation->SetAvailability(false);
        this->entity->SetAvailability(false);
        toChargingStation = new BeelineStrategy(this->entity->GetPosition(),
          nearestChargingStation->GetPosition());
    }
}

// implement the update function
void BatteryDecorator::Update(double dt, std::vector<IEntity*> scheduler,
  std::vector<IEntity*> chargingStations) {
    // first check to see if drone is moving, we don't want to have to recharge
    // if the drone is currenly picking up a passenger
    // std::cout << "Battery at: " << batteryLife << std::endl;
    if (batteryLife <= 0) {
        std::cout << "sorry no movement possible" << std::endl;
    } else if (toChargingStation) {
        toChargingStation->Move(this, dt);
        batteryLife = batteryLife - 0.005;
        if (toChargingStation->IsCompleted()) {
            // make it so we are in a charging state;
            charging = true;
            delete toChargingStation;
            toChargingStation = nullptr;
        }
    } else if (charging) {
        if (FullyCharged()) {
            // set status of charging to be false
            // update the drones availbility
            // update the charging stations avalibility
            // make sure to delete nearestCharging station and then
            // set to nullptr.
            charging = false;
            batteryLife = 100.0;
            this->entity->SetAvailability(true);
            nearestChargingStation->SetAvailability(true);
            nearestChargingStation = nullptr;
        } else {
            batteryLife = batteryLife + 1.0;
            // std::cout << "we are recharing" << std::endl;
            // std::cout << "Battery at: " << batteryLife << std::endl;
        }

    // want to check to see if drone needs to be charged
    } else if (entity->GetAvailability()) {
        if (NeedRecharge()) {
            // std::cout << "we need to recharge in future we will add logic
            //  to send it to charge location" << std::endl;
            std::cout << "Battery at: " << batteryLife << std::endl;
            // get the current location of the nearest charging station.
            GetNearestChargingStation(chargingStations);

        } else if (NextPickupPossible(dt, scheduler)) {
            // simply hovering drains battery a lot less than movement, lets
            // do a simple check to see if going to pick up the robot is
            // possible with our current battery state.
            entity->Update(dt, scheduler);
            batteryLife = batteryLife - 0.001;
        } else {
            // std::cout << "must recharge for upcoming trip." << std::endl;
            // std::cout << "battery at: " << batteryLife << std::endl;
            GetNearestChargingStation(chargingStations);
        }
        // std::cout << "The next pickup should be " <<
          // NextPickupPossible(dt,scheduler) << std::endl;
        // entity->Update(dt,scheduler);
        // batteryLife = batteryLife - 0.001;
    } else {
        entity->Update(dt, scheduler);
        batteryLife = batteryLife - 0.005;
    }
}
