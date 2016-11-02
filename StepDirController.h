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

// #include "IndexedContainer.h"
// #include "FunctorCallbacks.h"
// #include "EventController.h"

#include "ModularServer.h"
#include "ModularDevice.h"

#include "utility/Constants.h"


class StepDirController : public ModularDevice
{
public:
  StepDirController();
  ~StepDirController();
  virtual void setup();

  void enable();
  void disable();
  bool isEnabled();

  void stop(unsigned int motor_index);
  void start(unsigned int motor_index);
  void stopAll();
  void startAll();
  bool areAnyRunning();
  bool isRunning(unsigned int motor_index);
  Array<bool,constants::MOTOR_COUNT> isRunningAll();

  void setSpeed();

  void setDirection(unsigned int motor_index, char dir);
  void setDirectionAll(Array<char, constants::MOTOR_COUNT> dir);

  long getCurrentPosition(unsigned int motor_index);
  Array<long, constants::MOTOR_COUNT> getCurrentPositionAll();
  void setCurrentPosition(unsigned int motor_index, long pos);
  void setCurrentPositionAll(Array<long, constants::MOTOR_COUNT> pos);

  long getTargetPosition(unsigned int motor_index);
  Array<long, constants::MOTOR_COUNT> getTargetPositionAll();
  void setTargetPosition(unsigned int motor_index, long pos);
  void setTargetPositionAll(Array<long, constants::MOTOR_COUNT> pos);

  // int getCurrentWaypoint(unsigned int motor_index);
  // Array<int, constants::MOTOR_COUNT> getCurrentWaypointAll();

  // void goToNextWaypoint(unsigned int motor_index);
  void zero(unsigned int motor_index);
  void zeroAll();

  // Handlers
  // virtual void startPwmHandler(int index);
  // virtual void stopPwmHandler(int index);

private:
  modular_server::Field fields_[step_dir_controller::constants::FIELD_COUNT_MAX];
  modular_server::Parameter parameters_[step_dir_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Method methods_[step_dir_controller::constants::METHOD_COUNT_MAX];
  modular_server::Callback callbacks_[modular_device::constants::CALLBACK_COUNT_MAX];

  // EventController<step_dir_controller::constants::EVENT_COUNT_MAX> event_controller_;

  // IndexedContainer<step_dir_controller::constants::PulseInfo,
  //                  step_dir_controller::constants::INDEXED_PULSES_COUNT_MAX> indexed_pulses_;

  Array<Stepper,constants::MOTOR_COUNT> steppers_;
  bool enabled_flag_;

  void update();

  // Handlers

};

#endif
