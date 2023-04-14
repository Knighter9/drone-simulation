#include "IEntityBaseDecorator.h"

IEntityBaseDecorator::IEntityBaseDecorator(IEntity* entity){
    this->entity = entity;
}
IEntityBaseDecorator::~IEntityBaseDecorator(){
    delete entity;
}
