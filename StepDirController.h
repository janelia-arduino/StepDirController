// ----------------------------------------------------------------------------
// StepDirController.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef STEP_DIR_CONTROLLER_H
#define STEP_DIR_CONTROLLER_H
#include "Flash.h"
#include <EEPROM.h>
#include "Streaming.h"
#include "ArduinoJson.h"
#include "JsonSanitizer.h"
#include "JsonStream.h"
#include "Array.h"
#include "Vector.h"
#include "MemoryFree.h"
#include "ConstantVariable.h"
#include "SavedVariable.h"
#include "Functor.h"
#include "IndexedContainer.h"
#include "FunctorCallbacks.h"

#include "SPI.h"
#include "TMC429.h"

#include "ModularClient.h"

#include "ModularServer.h"
#include "ModularDeviceBase.h"

#include "utility/Constants.h"


class StepDirController : public ModularDeviceBase
{
public:
  StepDirController();
  ~StepDirController();
  virtual void setup();
  virtual void update();

  virtual void reinitialize();

  virtual size_t getChannelCount();

  void enable(const size_t channel);
  void disable(const size_t channel);
  void enableAll();
  void disableAll();
  uint32_t enabled();

  void moveBy(const size_t channel, const long position);
  void moveTo(const size_t channel, const long position);
  void moveAt(const size_t channel, const long velocity);
  void moveSoftlyBy(const size_t channel, const long position);
  void moveSoftlyTo(const size_t channel, const long position);
  void stop(const size_t channel);
  void stopAll();

  void zero(const size_t channel);
  void zeroAll();

  long getPosition(const size_t channel);
  long getTargetPosition(const size_t channel);
  bool atTargetPosition(const size_t channel);

  long getVelocity(const size_t channel);
  long getTargetVelocity(const size_t channel);
  bool atTargetVelocity(const size_t channel);

  bool leftSwitchActive(const size_t channel);
  bool rightSwitchActive(const size_t channel);

  bool home(const size_t channel);
  bool homing(const size_t channel);
  bool anyHoming();
  bool homed(const size_t channel);

protected:
  virtual long stepsToPositionUnits(const size_t channel, const long steps);
  virtual long positionUnitsToSteps(const size_t channel, const long position_units);

  int32_t getPositionInSteps(const size_t channel);
  int32_t getVelocityInHz(const size_t channel);

  void setControllerCount(const size_t controller_count);

  // Handlers
  void setChannelCountHandler();
  void preUpdateScaledPropertiesHandler(const size_t channel);
  void postUpdateScaledPropertiesHandler(const size_t channel);

private:
  modular_server::Interrupt interrupts_[step_dir_controller::constants::INTERRUPT_COUNT_MAX];

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
  size_t controller_count_;

  size_t channelToControllerIndex(const size_t channel);
  size_t channelToMotorIndex(const size_t channel);

  // Handlers
  void setLimitsHandler(const size_t channel);
  void reinitializeHandler();
  void controllersCommunicatingHandler();
  void setStepPolarityInvertedHandler();
  void setDirPolarityInvertedHandler();
  void setSwitchActivePolarityHandler();
  void setLeftSwitchStopEnabledHandler(const size_t channel);
  void setRightSwitchesEnabledHandler();
  void setRightSwitchStopEnabledHandler(const size_t channel);
  void setSwitchSoftStopEnabledHandler(const size_t channel);
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
