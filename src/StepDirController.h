// ----------------------------------------------------------------------------
// StepDirController.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef STEP_DIR_CONTROLLER_H
#define STEP_DIR_CONTROLLER_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

#include <TMC429.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>

#include "StepDirController/Constants.h"


class StepDirController : public ModularDeviceBase
{
public:
  StepDirController();
  ~StepDirController();
  virtual void setup();
  virtual void update();

  virtual void reinitialize();

  virtual size_t getChannelCount();
  virtual size_t getControllerCount();

  void enable(size_t channel);
  void disable(size_t channel);
  void enableAll();
  void disableAll();
  uint32_t enabled();

  void moveBy(size_t channel,
    long position);
  void moveTo(size_t channel,
    long position);
  void moveAt(size_t channel,
    long velocity);
  void moveSoftlyBy(size_t channel,
    long position);
  void moveSoftlyTo(size_t channel,
    long position);
  void stop(size_t channel);
  void stopAll();

  void zero(size_t channel);
  void zeroAll();

  long getPosition(size_t channel);
  long getTargetPosition(size_t channel);
  bool atTargetPosition(size_t channel);

  long getVelocity(size_t channel);
  long getTargetVelocity(size_t channel);
  bool atTargetVelocity(size_t channel);

  bool leftSwitchActive(size_t channel);
  bool rightSwitchActive(size_t channel);

  virtual bool home(size_t channel);
  bool homing(size_t channel);
  bool anyHoming();
  bool homed(size_t channel);

protected:
  virtual size_t getControllerChipSelectPin(size_t controller);
  virtual size_t getEnablePin(size_t channel);
  virtual long stepsToPositionUnits(size_t channel,
    long steps);
  virtual long positionUnitsToSteps(size_t channel,
    long position_units);

  int32_t getPositionInSteps(size_t channel);
  int32_t getVelocityInHz(size_t channel);

  void setControllerCountLimit(size_t controller_count);

  // Handlers
  void setChannelCountHandler();
  void preUpdateScaledPropertiesHandler(size_t channel);
  void postUpdateScaledPropertiesHandler(size_t channel);

private:
  modular_server::Pin pins_[step_dir_controller::constants::PIN_COUNT_MAX];

  modular_server::Property properties_[step_dir_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[step_dir_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[step_dir_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[step_dir_controller::constants::CALLBACK_COUNT_MAX];

  typedef TMC429 Controller;
  Controller controllers_[step_dir_controller::constants::CONTROLLER_COUNT_MAX];
  bool enabled_[step_dir_controller::constants::CHANNEL_COUNT_MAX];
  bool homing_[step_dir_controller::constants::CHANNEL_COUNT_MAX];
  bool homed_[step_dir_controller::constants::CHANNEL_COUNT_MAX];

  long velocity_min_steps_[step_dir_controller::constants::CHANNEL_COUNT_MAX];
  long velocity_max_steps_[step_dir_controller::constants::CHANNEL_COUNT_MAX];
  long acceleration_max_steps_[step_dir_controller::constants::CHANNEL_COUNT_MAX];
  long home_velocity_steps_[step_dir_controller::constants::CHANNEL_COUNT_MAX];

  size_t channelToControllerIndex(size_t channel);
  size_t channelToMotorIndex(size_t channel);

  // Handlers
  void setLimitsHandler(size_t channel);
  void reinitializeHandler();
  void controllersCommunicatingHandler();
  void setStepPolarityInvertedHandler(size_t controller_index);
  void setDirPolarityInvertedHandler(size_t controller_index);
  void setSwitchActivePolarityHandler(size_t controller_index);
  void setLeftSwitchStopEnabledHandler(size_t channel);
  void setRightSwitchesEnabledHandler(size_t controller_index);
  void setRightSwitchStopEnabledHandler(size_t channel);
  void setSwitchSoftStopEnabledHandler(size_t channel);
  void enableHandler();
  void disableHandler();
  void enableAllHandler();
  void disableAllHandler();
  void enabledHandler();
  void moveByHandler();
  void moveToHandler();
  void moveAtHandler();
  void moveSoftlyByHandler();
  void moveSoftlyToHandler();
  void stopHandler();
  void stopAllHandler();
  void zeroHandler();
  void zeroAllHandler();
  void getPositionsHandler();
  void getTargetPositionsHandler();
  void atTargetPositionsHandler();
  void getVelocitiesHandler();
  void getTargetVelocitiesHandler();
  void atTargetVelocitiesHandler();
  void switchesActiveHandler();
  void homeHandler();
  void homingHandler();
  void homedHandler();

};

#endif
