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

#include "TimerThree.h"

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

  void setEnablePolarityHigh(const size_t channel);
  void setEnablePolarityLow(const size_t channel);
  void setEnablePolarityHighAll();
  void setEnablePolarityLowAll();

  void setStepPolarityHigh(const size_t channel);
  void setStepPolarityLow(const size_t channel);
  void setStepPolarityHighAll();
  void setStepPolarityLowAll();

  void setDirPolarityHigh(const size_t channel);
  void setDirPolarityLow(const size_t channel);
  void setDirPolarityHighAll();
  void setDirPolarityLowAll();

  void setPositionMode(const size_t channel);
  void setVelocityMode(const size_t channel);
  void setPositionModeAll();
  void setVelocityModeAll();

  void enable(const size_t channel);
  void disable(const size_t channel);
  bool enabled(const size_t channel);
  void enableAll();
  void disableAll();
  Array<bool,step_dir_controller::constants::CHANNEL_COUNT> enabledArray();

  void start(const size_t channel);
  void stop(const size_t channel);
  bool running(const size_t channel);
  void startAll();
  void stopAll();
  bool anyRunning();
  Array<bool,step_dir_controller::constants::CHANNEL_COUNT> runningArray();

  void setVelocity(const size_t channel, const long steps_per_second);

  long getCurrentPosition(const size_t channel);
  Array<long, step_dir_controller::constants::CHANNEL_COUNT> getCurrentPositions();
  void setCurrentPosition(const size_t channel, const long position);
  void setCurrentPositions(Array<long, step_dir_controller::constants::CHANNEL_COUNT> positions);

  long getTargetPosition(const size_t channel);
  Array<long, step_dir_controller::constants::CHANNEL_COUNT> getTargetPositions();
  void setTargetPosition(const size_t channel, const long position);
  void setTargetPositions(Array<long, step_dir_controller::constants::CHANNEL_COUNT> positions);

  void zero(const size_t channel);
  void zeroAll();

private:
  modular_server::Interrupt interrupts_[step_dir_controller::constants::INTERRUPT_COUNT_MAX];

  modular_server::Property properties_[step_dir_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[step_dir_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[step_dir_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[step_dir_controller::constants::CALLBACK_COUNT_MAX];

  Array<Stepper,step_dir_controller::constants::CHANNEL_COUNT> steppers_;
  FunctorCallbacks::Callback isr_;

  // Handlers
  void isrHandler();
  void setEnablePolarityHandler(const size_t index);
  void setStepPolarityHandler(const size_t index);
  void setDirPolarityHandler(const size_t index);
  void setModeHandler(const size_t index);
  void enableHandler();
  void disableHandler();
  void enableAllHandler();
  void disableAllHandler();
  void enabledHandler();

};

#endif
