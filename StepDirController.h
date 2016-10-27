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
#include "EventController.h"

#include "ModularServer.h"
#include "ModularDevice.h"

#include "utility/Constants.h"


class StepDirController : public ModularDevice
{
public:
  StepDirController();
  virtual void setup();
  void setChannelOn(const size_t channel, const ConstantString * const polarity_ptr);
  void setChannelOff(const size_t channel);
  void setChannelsOn(const uint32_t channels, const ConstantString * const polarity_ptr);
  void setChannelsOff(const uint32_t channels);
  void setAllChannelsOn(const ConstantString * const polarity_ptr);
  void setAllChannelsOff();
  int addPwm(const uint32_t channels,
             const ConstantString * const polarity_ptr,
             const long delay,
             const long period,
             const long on_duration,
             const long count);
  int startPwm(const uint32_t channels,
               const ConstantString * const polarity_ptr,
               const long delay,
               const long period,
               const long on_duration);
  int addTogglePwm(const uint32_t channels,
                   const ConstantString * const polarity_ptr,
                   const long delay,
                   const long period,
                   const long on_duration,
                   const long count);
  int startTogglePwm(const uint32_t channels,
                     const ConstantString * const polarity_ptr,
                     const long delay,
                     const long period,
                     const long on_duration);
  void stopPwm(const int pwm_index);
  void stopAllPwm();
  uint32_t arrayToChannels(ArduinoJson::JsonArray & channels_array);
  ConstantString * const stringToPolarityPtr(const char * string);

  // Handlers
  virtual void startPwmHandler(int index);
  virtual void stopPwmHandler(int index);

private:
  modular_server::Field fields_[step_dir_controller::constants::FIELD_COUNT_MAX];
  modular_server::Parameter parameters_[step_dir_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Method methods_[step_dir_controller::constants::METHOD_COUNT_MAX];
  modular_server::Callback callbacks_[modular_device::constants::CALLBACK_COUNT_MAX];

  EventController<step_dir_controller::constants::EVENT_COUNT_MAX> event_controller_;

  IndexedContainer<step_dir_controller::constants::PulseInfo,
                   step_dir_controller::constants::INDEXED_PULSES_COUNT_MAX> indexed_pulses_;

  // Handlers
  void setChannelOnHandler();
  void setChannelOffHandler();
  void setChannelsOnHandler();
  void setChannelsOffHandler();
  void setAllChannelsOnHandler();
  void setAllChannelsOffHandler();
  void addPwmHandler();
  void startPwmHandler();
  void addTogglePwmHandler();
  void startTogglePwmHandler();
  void stopPwmHandler();
  void stopAllPwmHandler();
  void setChannelsOnHandler(int index);
  void setChannelsOffHandler(int index);
  void setChannelsOnReversedHandler(int index);

};

#endif
