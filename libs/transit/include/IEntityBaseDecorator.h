#ifndef IEntityBase_DECORATOR_H_
#define IEneityBase_DECORATOR_H_

#include "IEntity.h"
#include "Drone.h"

// basic decorator for which we can implement concrete decorators like a battery. 
// the batter decorator will implment this abstract decorator. 
class IEntityBaseDecorator : public IEntity {
    protected: 
        IEntity* entity;

    public: 
        IEntityBaseDecorator(IEntity* entity);

        ~IEntityBaseDecorator();

        float GetSpeed() const {return entity->GetSpeed();}

        Vector3 GetPosition() const {return entity->GetPosition();}

        Vector3 GetDirection() const {return entity->GetDirection();}

        Vector3 GetDestination() const {return entity->GetDestination();}

        JsonObject GetDetails() const {return entity->GetDetails();}

        bool GetAvailability() const { return entity->GetAvailability(); }

        void SetPosition(Vector3 pos_) { entity->SetPosition(pos_); }

        std::string GetStrategyName() const {entity->GetStrategyName(); }

        void setStrategyName(std::string strategyName_) { entity->SetStrategyName(strategyName_); }

        void SetDirection(Vector3 dir_) { entity->SetDirection(dir_); }

        void SetAvailability(bool choice) {entity->SetAvailability(choice); }

        void SetDestination(Vector3 des_) { entity->SetDestination(des_); }

        void SetColor(std::string col_) { entity->SetColor(col_); }

        void Rotate(double angle) {entity->Rotate(angle); }

        void Jump(double height ) {entity->Jump(height); }




        

        virtual void Update(double dt, std::vector<IEntity*> scheduler){}
};

#endif  