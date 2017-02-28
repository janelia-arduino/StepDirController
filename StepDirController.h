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

#include "ModularServer.h"
#include "ModularDevice.h"

#include "utility/Constants.h"


class StepDirController : public ModularDevice
{
public:
  StepDirController();
  ~StepDirController();
  virtual void setup();

  virtual void reinitialize();

  // void setEnablePolarity(const size_t channel, const ConstantString & polarity);
  // void setEnablePolarityAll(const ConstantString & polarity);
  // void setStepPolarity(const size_t channel, const ConstantString & polarity);
  // void setStepPolarityAll(const ConstantString & polarity);
  // void setDirPolarity(const size_t channel, const ConstantString & polarity);
  // void setDirPolarityAll(const ConstantString & polarity);

  // void enable(const size_t channel);
  // void disable(const size_t channel);
  // void enableAll();
  // void disableAll();
  // uint32_t enabled();

  // void moveBy(const size_t channel, const long position);
  // void moveTo(const size_t channel, const long position);
  void moveAt(const size_t channel, const double velocity);
  // void moveByAt(const size_t channel, const long position, const long speed);
  // void moveToAt(const size_t channel, const long position, const long speed);
  void stop(const size_t channel);
  void stopAll();
  void zero(const size_t channel);
  void zeroAll();


  double getPosition(const size_t channel);
  double getPositionTarget(const size_t channel);
  double getVelocity(const size_t channel);
  double getVelocityTarget(const size_t channel);

protected:
  virtual double stepsToPositionUnits(const size_t channel, const double steps);
  virtual double positionUnitsToSteps(const size_t channel, const double position_units);

  // Handlers
  void preUpdateLimitsHandler(const size_t channel);
  void postUpdateLimitsHandler(const size_t channel);

private:
  modular_server::Interrupt interrupts_[step_dir_controller::constants::INTERRUPT_COUNT_MAX];

  modular_server::Property properties_[step_dir_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[step_dir_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[step_dir_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[step_dir_controller::constants::CALLBACK_COUNT_MAX];

  TMC429 tmc429s_[step_dir_controller::constants::TMC429_COUNT];
  // bool enabled_[step_dir_controller::constants::CHANNEL_COUNT];

  size_t channelToTmc429Index(const size_t channel);
  size_t channelToMotorIndex(const size_t channel);

  // Handlers
  void setLimitsHandler(const size_t channel);
  void reinitializeHandler();
  // void setEnablePolarityHandler(const size_t index);
  // void setStepPolarityHandler(const size_t index);
  // void setDirPolarityHandler(const size_t index);
  // void setModeHandler(const size_t index);
  // void enableHandler();
  // void disableHandler();
  // void enableAllHandler();
  // void disableAllHandler();
  // void enabledHandler();
  // void moveByHandler();
  // void moveToHandler();
  void moveAtHandler();
  // void moveByAtHandler();
  // void moveToAtHandler();
  void stopHandler();
  void stopAllHandler();
  void zeroHandler();
  void zeroAllHandler();
  void getPositionsHandler();
  void getPositionTargetsHandler();
  void getVelocitiesHandler();
  void getVelocityTargetsHandler();

};

#endif
