#include "SimulationModel.h"

#include "DroneFactory.h"
#include "RobotFactory.h"
#include "HumanFactory.h"
#include "HelicopterFactory.h"
#include "ChargingStationFactory.h"

SimulationModel::SimulationModel(IController& controller)
    : controller(controller) {
  compFactory = new CompositeFactory();
  AddFactory(new DroneFactory());
  AddFactory(new RobotFactory());
  AddFactory(new HumanFactory());
  AddFactory(new HelicopterFactory());
  AddFactory(new ChargingStationFactory());
}

SimulationModel::~SimulationModel() {
  // Delete dynamically allocated variables
  for (int i = 0; i < entities.size(); i++) {
    delete entities[i];
  }
  for (int i = 0; i < scheduler.size(); i++) {
    delete scheduler[i];
  }
  for (int i = 0; i < chargingStations.size(); i++) {
    delete chargingStations[i];
  }
  delete graph;
  delete compFactory;
}

void SimulationModel::CreateEntity(JsonObject& entity) {
  controller.SendEventToView("observer",  entity);
  std::string type = entity["type"];
  std::string name = entity["name"];
  JsonArray position = entity["position"];
  std::cout << name << ": " << position << std::endl;
  IEntity* myNewEntity = compFactory->CreateEntity(entity);
  myNewEntity->SetGraph(graph);
  if (type.compare("charging station") == 0) {
    std::cout << "adding a new charging station " << std::endl;
    chargingStations.push_back(myNewEntity);
    controller.AddEntity(*myNewEntity);
    return;
  }

  // Call AddEntity to add it to the view
  controller.AddEntity(*myNewEntity);
  entities.push_back(myNewEntity);
}

/// Schedules a trip for an object in the scene
void SimulationModel::ScheduleTrip(JsonObject& details) {
  std::string name = details["name"];
  JsonArray start = details["start"];
  JsonArray end = details["end"];
  std::cout << name << ": " << start << " --> " << end << std::endl;

  for (auto entity : entities) {  // Add the entity to the scheduler
    JsonObject detailsTemp = entity->GetDetails();
    std::string nameTemp = detailsTemp["name"];
    std::string typeTemp = detailsTemp["type"];
    if (name.compare(nameTemp) == 0 && typeTemp.compare("robot") == 0 &&
        entity->GetAvailability()) {
      std::string strategyName = details["search"];
      entity->SetDestination(Vector3(end[0], end[1], end[2]));
      entity->SetStrategyName(strategyName);
      scheduler.push_back(entity);
      break;
    }
  }
  controller.SendEventToView("TripScheduled", details);
  controller.SendEventToView("observe", details);  // send to frontend
}

/// Updates the simulation
void SimulationModel::Update(double dt) {
  for (int i = 0; i < entities.size(); i++) {
    JsonObject detailsTemp = entities[i]->GetDetails();
    std::string typeTemp = detailsTemp["type"];
    if (typeTemp.compare("drone") == 0) {
      entities[i]->Update(dt, scheduler, chargingStations);
    } else {
      entities[i]->Update(dt, scheduler);
    }
    controller.UpdateEntity(*entities[i]);
  }
}

void SimulationModel::AddFactory(IEntityFactory* factory) {
  compFactory->AddFactory(factory);
}
