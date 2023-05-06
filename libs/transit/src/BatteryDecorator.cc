#include "routing/astar.h"
#include "DataCollection.h"
#include "BeelineStrategy.h"
#include "BatteryDecorator.h"

// Global Variable
float distToFinalLocation;

BatteryDecorator::~BatteryDecorator() {
    delete entity;
    delete nearestChargingStation;
    delete toChargingStation;
}

bool BatteryDecorator::NeedRecharge() {
    return batteryLife <= 40.0;
}

bool BatteryDecorator::FullyCharged() {
    return batteryLife >= 200;
}

bool BatteryDecorator::NextPickupPossible(double dt,
                       const std::vector<IEntity*> scheduler) {
    // Find the closest entity in the scheduler
    float minDis = std::numeric_limits<float>::max();
    IEntity* closestEntity = nullptr;
    for (auto entity : scheduler) {
        if (entity->GetAvailability()) {
            float disToEntity = this->entity->GetPosition().Distance(
                                entity->GetPosition());
            if (disToEntity <= minDis) {
                minDis = disToEntity;
                closestEntity = entity;
            }
        }
    }

    if (closestEntity) {
        float distToFinalLocation = 0;
        // Check if the flight is possible
        std::vector<std::vector<float>> path;
        Vector3 startVec = closestEntity->GetPosition();
        Vector3 desVec = closestEntity->GetDestination();

        // Get the path using the A* algorithm
        path = graph->GetPath({startVec[0], startVec[1], startVec[2]},
                              {desVec[0], desVec[1], desVec[2]},
                              AStar::Default());

        // Calculate the distance to the final location
        for (int i = 0; i < path.size() - 1; i++) {
            Vector3 curr = Vector3(path[i][0], path[i][1], path[i][2]);
            Vector3 next = Vector3(path[i + 1][0], path[i + 1][1],
                                   path[i + 1][2]);
            distToFinalLocation += curr.Distance(next);
        }

        // Calculate the maximum distance the drone can travel before
        // needing a recharge
        float totalDistance = distToFinalLocation + minDis;
        int maxNumberCalls = floor((batteryLife - 20) / 0.01);
        float maxTotalDistance = maxNumberCalls * entity->GetSpeed() * dt;

        return totalDistance <= maxTotalDistance;
    }

    // Return true if there are no entities in the scheduler
    return true;
}

void BatteryDecorator::GetNearestChargingStation(const
                       std::vector<IEntity*> chargingStations) {
    // Find the nearest charging station
    float minDis = std::numeric_limits<float>::max();
    for (auto station : chargingStations) {
        if (station->GetAvailability()) {
            float disToEntity = this->entity->GetPosition().Distance(
                                station->GetPosition());
            if (disToEntity <= minDis) {
                minDis = disToEntity;
                nearestChargingStation = station;
            }
        }
    }

    if (nearestChargingStation) {
        // Update the drone's and charging station's availability
        nearestChargingStation->SetAvailability(false);
        entity->SetAvailability(false);

        // Create a new strategy to move to the charging station
        toChargingStation = new BeelineStrategy(entity->GetPosition(),
                            nearestChargingStation->GetPosition());
    }
}
void BatteryDecorator::Update(double dt, std::vector<IEntity*> scheduler,std::vector<IEntity*> chargingStations){
    // first check to see if drone is moving, we don't want to have to recharge if the drone is currenly picking up a passenger
    //std::cout << "Battery at: " << batteryLife << std::endl;
    if(batteryLife <= 0){
        std::cout << "sorry no movement possible" << std::endl;
    }
    else if(toChargingStation){
        toChargingStation->Move(this,dt);
        batteryLife = batteryLife - 0.01;
        if(toChargingStation->IsCompleted()){
            // make it so we are in a charging state;
            charging = true;
            delete toChargingStation;
            toChargingStation = nullptr;
        }
    } 
    else if(charging){
        if(FullyCharged()){
            // set status of charging to be false
            // update the drones availbility
            // update the charging stations avalibility
            // make sure to delete nearestCharging station and then set to nullptr. 
            charging = false;
            batteryLife = 200.0;
            this->entity->SetAvailability(true);
            nearestChargingStation->SetAvailability(true);
            nearestChargingStation = nullptr;
        }
        else{
            batteryLife = batteryLife + 5.0;
           // std::cout << "we are recharing" << std::endl;
            //std::cout << "Battery at: " << batteryLife << std::endl;
        }

    }
    else if(entity->GetAvailability()){// we want to check to see if th drone needs to be charged. 
        if(NeedRecharge()){
            //std::cout << "we need to recharge in future we will add logic to send it to charge location" << std::endl;
            //std::cout << "Battery at: " << batteryLife << std::endl;
            // get the current location of the nearest charging station.
            GetNearestChargingStation(chargingStations);

        }
        // simply hovering drains the battery a lot less than movement
        // lets do a simple check to see if going to pick up the robot is possible with our current battery state. 
        else if(NextPickupPossible(dt,scheduler)){
            DataCollection::GetInstance().GetStartingBattery(batteryLife);
            entity->Update(dt,scheduler);
            batteryLife = batteryLife - 0.015;
        }
        else{
            std::cout << "must recharge for upcoming trip." << std::endl;
            std::cout << "battery at: " << batteryLife << std::endl;
            GetNearestChargingStation(chargingStations);
        }
        //std::cout << "The next pickup should be " << NextPickupPossible(dt,scheduler) << std::endl;
        //entity->Update(dt,scheduler);
        //batteryLife = batteryLife - 0.001;
        DataCollection::GetInstance().AddData(batteryLife);
        
        
    } else {
        entity->Update(dt,scheduler);
        batteryLife = batteryLife - 0.01;
    }
    
}

   
 
/*
void BatteryDecorator::Update(double dt, std::vector<IEntity*> scheduler,
                              std::vector<IEntity*> chargingStations) {
    // Charging at station case
    if (charging) {
        if (FullyCharged()) {
            charging = false;
            batteryLife = 100.0;
            entity->SetAvailability(true);
            nearestChargingStation->SetAvailability(true);
            nearestChargingStation = nullptr;
        } else {
            batteryLife = std::min(batteryLife + .1, 100.0);
        }
        entity->Update(dt, scheduler);
        return;
    }

    if (toChargingStation) {
        toChargingStation->Move(this, dt);
        if (toChargingStation->IsCompleted()) {
            charging = true;
            delete toChargingStation;
            toChargingStation = nullptr;
            entity->Update(dt, scheduler);
            return;
        }
        charging = false;
        entity->Update(dt, scheduler);
        return;
    }

    if (entity->GetAvailability()) {
        if (NeedRecharge()) {
            GetNearestChargingStation(chargingStations);
            entity->Update(dt, scheduler);
        } else if (NextPickupPossible(dt, scheduler)) {
            // Start data stuff when pick up is possible
            DataCollection::GetInstance().GetStartingBattery(batteryLife);
            
            entity->Update(dt, scheduler);
            batteryLife -= 0.01;
        } else {
                GetNearestChargingStation(chargingStations);
                entity->Update(dt, scheduler);
                return;
        }
        ///Add data once dropped off 
        DataCollection::GetInstance().AddData(batteryLife);
    }

    entity->Update(dt, scheduler);
    batteryLife -= 0.01;
}
*/