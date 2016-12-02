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

// #include "EventController.h"

#include "ModularServer.h"
#include "ModularDevice.h"

#include "utility/Constants.h"
#include "utility/Stepper.h"


class StepDirController : public ModularDevice
{
public:
  StepDirController();
  ~StepDirController();
  virtual void setup();

  void enable();
  void disable();
  bool isEnabled();

  void stop(const size_t channel);
  void start(const size_t channel);
  void stopAll();
  void startAll();
  bool anyRunning();
  bool isRunning(const size_t channel);
  Array<bool,step_dir_controller::constants::CHANNEL_COUNT> isRunningAll();

  void setSpeed();

  void setDirection(const size_t channel, char dir);
  void setDirectionAll(Array<char, step_dir_controller::constants::CHANNEL_COUNT> dir);

  long getCurrentPosition(const size_t channel);
  Array<long, step_dir_controller::constants::CHANNEL_COUNT> getCurrentPositionAll();
  void setCurrentPosition(const size_t channel, long pos);
  void setCurrentPositionAll(Array<long, step_dir_controller::constants::CHANNEL_COUNT> pos);

  long getTargetPosition(const size_t channel);
  Array<long, step_dir_controller::constants::CHANNEL_COUNT> getTargetPositionAll();
  void setTargetPosition(const size_t channel, long pos);
  void setTargetPositionAll(Array<long, step_dir_controller::constants::CHANNEL_COUNT> pos);

  // int getCurrentWaypoint(const size_t channel);
  // Array<int, step_dir_controller::constants::CHANNEL_COUNT> getCurrentWaypointAll();

  // void goToNextWaypoint(const size_t channel);
  void zero(const size_t channel);
  void zeroAll();

  // Handlers
  // virtual void startPwmHandler(int index);
  // virtual void stopPwmHandler(int index);

private:
  modular_server::Interrupt interrupts_[step_dir_controller::constants::INTERRUPT_COUNT_MAX];

  modular_server::Property properties_[step_dir_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[step_dir_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[step_dir_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[step_dir_controller::constants::CALLBACK_COUNT_MAX];

  // EventController<step_dir_controller::constants::EVENT_COUNT_MAX> event_controller_;

  // IndexedContainer<step_dir_controller::constants::PulseInfo,
  //                  step_dir_controller::constants::INDEXED_PULSES_COUNT_MAX> indexed_pulses_;

  Array<Stepper,step_dir_controller::constants::CHANNEL_COUNT> steppers_;
  bool enabled_flag_;

  // Handlers

};

#endif
