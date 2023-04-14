#include "BatteryDecorator.h"
#include "BeelineStrategy.h"

BatteryDecorator::~BatteryDecorator(){
    delete entity;
    delete nearestChargingStation;
    delete toChargingStation;
}
bool BatteryDecorator::NeedRecharge(){
    return batteryLife <= 30.0;
}
bool BatteryDecorator::FullyCharged(){
    return batteryLife >= 100.0;
}
void BatteryDecorator::GetNearestChargingStation(std::vector<IEntity*> chargingStations){
    float minDis = std::numeric_limits<float>::max();
    for (auto station : chargingStations) {
        if (station->GetAvailability()) {
            float disToEntity = this->entity->GetPosition().Distance(station->GetPosition());
            if (disToEntity <= minDis) {
                minDis = disToEntity;
                nearestChargingStation = station;
            }
        }
    }
    if(nearestChargingStation){
        nearestChargingStation->SetAvailability(false);
        this->entity->SetAvailability(false);

        toChargingStation = new BeelineStrategy(this->entity->GetPosition(),nearestChargingStation->GetPosition());
    }


}
// implement the update function 
void BatteryDecorator::Update(double dt, std::vector<IEntity*> scheduler,std::vector<IEntity*> chargingStations){
    // first check to see if drone is moving, we don't want to have to recharge if the drone is currenly picking up a passenger
    //std::cout << "Battery at: " << batteryLife << std::endl;
    if(charging){
        if(FullyCharged()){
            // set status of charging to be false
            // update the drones availbility
            // update the charging stations avalibility
            // make sure to delete nearestCharging station and then set to nullptr. 
            charging = false;
            batteryLife = 100.0;
            this->entity->SetAvailability(true);
            nearestChargingStation->SetAvailability(true);
            nearestChargingStation = nullptr;
        }
        else{
            batteryLife = batteryLife + 0.05;
            std::cout << "we are recharing" << std::endl;
            std::cout << "Battery at: " << batteryLife << std::endl;
        }

    }
    else if(toChargingStation){
        toChargingStation->Move(this,dt);
        batteryLife = batteryLife - 0.005;
        if(toChargingStation->IsCompleted()){
            // make it so we are in a charging state;
            charging = true;
            delete toChargingStation;
            toChargingStation = nullptr;
        }
    } else if(entity->GetAvailability()){// we want to check to see if th drone needs to be charged. 
        if(NeedRecharge()){
            std::cout << "we need to recharge in future we will add logic to send it to charge location" << std::endl;
            std::cout << "Battery at: " << batteryLife << std::endl;
            // get the current location of the nearest charging station.
            GetNearestChargingStation(chargingStations);

        }
        // simply hovering drains the battery a lot less than movement
        entity->Update(dt,scheduler);
        batteryLife = batteryLife - 0.005;

    } else {
        entity->Update(dt,scheduler);
        batteryLife = batteryLife - 0.05;
    }
    
}
