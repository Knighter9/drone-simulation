#ifndef IEntityBase_DECORATOR_H_
#define IEntityBase_DECORATOR_H_

#include "IEntity.h"
#include "Drone.h"

/**
 * @class IEntityBaseDecorator
 * @brief Basic decorator for which we can implement concrete decorators like
 * a battery. The battery decorator will implment this abstract decorator.
 */
class IEntityBaseDecorator : public IEntity {
 public:
  /**
   * @brief Construct a new IEntity Decorator object
   * @param entity The entity to decorate onto
   */
  IEntityBaseDecorator(IEntity* entity);

  /**
   * @brief IEntityBaseDecorator destructor
   */
  ~IEntityBaseDecorator();

  /**
   * @brief Gets the speed of the entity
   * @return The speed of the entity
   */
  float GetSpeed() const { return entity->GetSpeed(); }

  /**
   * @brief Gets the position of the entity
   * @return The position of the entity
   */
  Vector3 GetPosition() const { return entity->GetPosition(); }

  /**
   * @brief Gets the direction of the entity
   * @return The direction of the entity
   */
  Vector3 GetDirection() const { return entity->GetDirection(); }

  /**
   * @brief Gets the destination of the entity
   * @return The destination of the entity
   */
  Vector3 GetDestination() const { return entity->GetDestination(); }

  /**
   * @brief Gets the details information of the entity
   * @return The details information of the entity
   */
  JsonObject GetDetails() const { return entity->GetDetails(); }

  /**
   * @brief Gets the availability of the entity
   * @return The availability of the entity
   */
  bool GetAvailability() const { return entity->GetAvailability(); }

  /**
   * @brief Sets the position of the entity
   * @param pos_ The new position of the entity
   */
  void SetPosition(Vector3 pos_) { entity->SetPosition(pos_); }

  /**
   * @brief Get the Strategy Name
   * @return Strategy name
   */
  std::string GetStrategyName() const { entity->GetStrategyName(); }

  /**
   * @brief Set the Strategy Name
   * @param strategyName_ Strategy name
   */
  void setStrategyName(std::string strategyName_) {
    entity->SetStrategyName(strategyName_);
  }

  /**
   * @brief Sets the direction of the entity
   * @param dir_ The new direction of the entity
   */
  void SetDirection(Vector3 dir_) { entity->SetDirection(dir_); }

  /**
   * @brief Sets the availability of the entity
   * @param choice True if available, False if not available
   */
  void SetAvailability(bool choice) { entity->SetAvailability(choice); }

  /**
   * @brief Sets the destination of the entity
   * @param des_ The new destination of the entity
   */
  void SetDestination(Vector3 des_) { entity->SetDestination(des_); }

  /**
   * @brief Sets the color of the entity
   * @param col_ The new color of the entity
   */
  void SetColor(std::string col_) { entity->SetColor(col_); }

  /**
   * @brief Rotates the entity
   * @param angle The angle by which the entity should be rotated
   */
  void Rotate(double angle) { entity->Rotate(angle); }

  /**
   * @brief Makes the entity jump
   * @param height The height at which the entity should jump
   */
  void Jump(double height) { entity->Jump(height); }

  /**
   * @brief Updates the entity's position
   * @param dt Delta time
   * @param scheduler Vector containing all the entities in the system
   */
  virtual void Update(double dt, std::vector<IEntity*> scheduler) {}

 protected:
  IEntity* entity;
};

#endif
