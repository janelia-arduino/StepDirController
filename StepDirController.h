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
  virtual void setup();

  void setStepDirPins(size_t step_pin, size_t dir_pin);

  void start();
  void stop();
  bool isRunning();

  void disableOutputs();
  void enableOutputs();

  long getTargetPosition();
  void setTargetPosition(long position);
  long getCurrentPosition();
  void setCurrentPosition(long position);

  void setPinsInverted(bool direction, bool step);
  void setDirInverted();
  void setDirNormal();

  void zero();

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

  void updateDirPin();
  void setStepPinHigh();
  void setStepPinLow();

  // Handlers

};

#endif
