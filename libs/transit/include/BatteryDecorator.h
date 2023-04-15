#ifndef BATTERY_DECORATOR_H_
#define BATTERY_DECORATOR_H_

#include "IEntityBaseDecorator.h"

class BatteryDecorator: public IEntityBaseDecorator{
    public: 
        // we want to create a new decorator object; 
        BatteryDecorator(IEntity *entity): IEntityBaseDecorator(entity){
            this->batteryLife = 100.0;
            this->charging = false;
        };
        ~BatteryDecorator();

        void Update(double dt, std::vector<IEntity*> scheduler,std::vector<IEntity*> chargingStations);

        // want to recharge if at 25% of battery
        bool NeedRecharge();
        
        // checks to see if battery is at 100% capacity so that is battery = 100;
        bool FullyCharged();

        void SetGraph(const IGraph* graph)override{
            this->graph = graph;
            entity->SetGraph(graph);
        }

        void GetNearestChargingStation(std::vector<IEntity*> chargingStations);

        bool NextPickupPossible(double dt, std::vector<IEntity*> scheduler);

     private: 
        float batteryLife;// 100 will be fully charged. 0 will be empty.
        bool charging;
        IEntity* nearestChargingStation;
        IStrategy* toChargingStation = nullptr;

};

#endif  