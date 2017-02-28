// ----------------------------------------------------------------------------
// StepDirController.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "StepDirController.h"


using namespace step_dir_controller;

StepDirController::StepDirController()
{
}

StepDirController::~StepDirController()
{
  // disable();
}

void StepDirController::setup()
{
  // Parent Setup
  ModularDevice::setup();

  // TMC429 Setup
  for (size_t tmc429_i=0; tmc429_i<constants::TMC429_COUNT; ++tmc429_i)
  {
    TMC429 & tmc429 = tmc429s_[tmc429_i];
    tmc429.setup(constants::cs_pins[tmc429_i],constants::clock_frequency_mhz);
  }

  // Pin Setup
  // for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  // {
  //   pinMode(enable_pins_[channel], INPUT);
  //   enabled_[channel] = false;
  // }

  // Interrupts
  // #if defined(__AVR_ATmega2560__)
  // modular_server::Interrupt & bnc_b_interrupt = modular_server_.createInterrupt(constants::bnc_b_interrupt_name,
  //                                                                               constants::bnc_b_pin);


  // #endif
  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware
  modular_server_.addHardware(constants::hardware_info,
                              interrupts_);

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
                              properties_,
                              parameters_,
                              functions_,
                              callbacks_);
  // Properties
  modular_server::Property & velocity_max_property = modular_server_.createProperty(constants::velocity_max_property_name,constants::velocity_max_default);
  velocity_max_property.setUnits(constants::steps_per_second_unit);
  velocity_max_property.setRange(constants::velocity_max_min,constants::velocity_max_max);
  velocity_max_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&StepDirController::setLimitsHandler));

  modular_server::Property & velocity_min_property = modular_server_.createProperty(constants::velocity_min_property_name,constants::velocity_min_default);
  velocity_min_property.setUnits(constants::steps_per_second_unit);
  velocity_min_property.setRange(constants::velocity_min_min,constants::velocity_min_max);
  velocity_min_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&StepDirController::setLimitsHandler));

  modular_server::Property & acceleration_max_property = modular_server_.createProperty(constants::acceleration_max_property_name,constants::acceleration_max_default);
  acceleration_max_property.setUnits(constants::steps_per_second_per_second_unit);
  acceleration_max_property.setRange(constants::acceleration_max_min,constants::acceleration_max_max);
  acceleration_max_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&StepDirController::setLimitsHandler));

  // modular_server::Property & enable_polarity_property = modular_server_.createProperty(constants::enable_polarity_property_name,constants::enable_polarity_default);
  // enable_polarity_property.setSubset(constants::polarity_ptr_subset);
  // enable_polarity_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&StepDirController::setEnablePolarityHandler));

  // modular_server::Property & step_polarity_property = modular_server_.createProperty(constants::step_polarity_property_name,constants::step_polarity_default);
  // step_polarity_property.setSubset(constants::polarity_ptr_subset);
  // step_polarity_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&StepDirController::setStepPolarityHandler));

  // modular_server::Property & dir_polarity_property = modular_server_.createProperty(constants::dir_polarity_property_name,constants::dir_polarity_default);
  // dir_polarity_property.setSubset(constants::polarity_ptr_subset);
  // dir_polarity_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&StepDirController::setDirPolarityHandler));

  // modular_server::Property & mode_property = modular_server_.createProperty(constants::mode_property_name,constants::mode_default);
  // mode_property.setSubset(constants::mode_ptr_subset);
  // mode_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<const size_t> *)0,*this,&StepDirController::setModeHandler));

  reinitialize();
  // disableAll();

  // Parameters
  modular_server::Parameter & channel_parameter = modular_server_.createParameter(constants::channel_parameter_name);
  channel_parameter.setRange(constants::channel_min,constants::channel_max);

  modular_server::Parameter & position_parameter = modular_server_.createParameter(constants::position_parameter_name);
  position_parameter.setTypeLong();

  modular_server::Parameter & velocity_parameter = modular_server_.createParameter(constants::velocity_parameter_name);
  velocity_parameter.setRange(constants::velocity_parameter_min,constants::velocity_parameter_max);

  // Functions
  modular_server::Function & reinitialize_function = modular_server_.createFunction(constants::reinitialize_function_name);
  reinitialize_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::reinitializeHandler));

  // modular_server::Function & enable_function = modular_server_.createFunction(constants::enable_function_name);
  // enable_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::enableHandler));
  // enable_function.addParameter(channel_parameter);

  // modular_server::Function & disable_function = modular_server_.createFunction(constants::disable_function_name);
  // disable_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::disableHandler));
  // disable_function.addParameter(channel_parameter);

  // modular_server::Function & enable_all_function = modular_server_.createFunction(constants::enable_all_function_name);
  // enable_all_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::enableAllHandler));

  // modular_server::Function & disable_all_function = modular_server_.createFunction(constants::disable_all_function_name);
  // disable_all_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::disableAllHandler));

  // modular_server::Function & enabled_function = modular_server_.createFunction(constants::enabled_function_name);
  // enabled_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::enabledHandler));
  // enabled_function.setReturnTypeArray();

  // modular_server::Function & move_by_function = modular_server_.createFunction(constants::move_by_function_name);
  // move_by_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::moveByHandler));
  // move_by_function.addParameter(channel_parameter);
  // move_by_function.addParameter(position_parameter);

  // modular_server::Function & move_to_function = modular_server_.createFunction(constants::move_to_function_name);
  // move_to_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::moveToHandler));
  // move_to_function.addParameter(channel_parameter);
  // move_to_function.addParameter(position_parameter);

  modular_server::Function & move_at_function = modular_server_.createFunction(constants::move_at_function_name);
  move_at_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::moveAtHandler));
  move_at_function.addParameter(channel_parameter);
  move_at_function.addParameter(velocity_parameter);

  // modular_server::Function & move_by_at_function = modular_server_.createFunction(constants::move_by_at_function_name);
  // move_by_at_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::moveByAtHandler));
  // move_by_at_function.addParameter(channel_parameter);
  // move_by_at_function.addParameter(position_parameter);
  // move_by_at_function.addParameter(velocity_parameter);

  // modular_server::Function & move_to_at_function = modular_server_.createFunction(constants::move_to_at_function_name);
  // move_to_at_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::moveToAtHandler));
  // move_to_at_function.addParameter(channel_parameter);
  // move_to_at_function.addParameter(position_parameter);
  // move_to_at_function.addParameter(velocity_parameter);

  modular_server::Function & stop_function = modular_server_.createFunction(constants::stop_function_name);
  stop_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::stopHandler));
  stop_function.addParameter(channel_parameter);

  modular_server::Function & stop_all_function = modular_server_.createFunction(constants::stop_all_function_name);
  stop_all_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::stopAllHandler));

  modular_server::Function & zero_function = modular_server_.createFunction(constants::zero_function_name);
  zero_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::zeroHandler));
  zero_function.addParameter(channel_parameter);

  modular_server::Function & zero_all_function = modular_server_.createFunction(constants::zero_all_function_name);
  zero_all_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::zeroAllHandler));

  modular_server::Function & get_positions_function = modular_server_.createFunction(constants::get_positions_function_name);
  get_positions_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::getPositionsHandler));
  get_positions_function.setReturnTypeArray();

  modular_server::Function & get_position_targets_function = modular_server_.createFunction(constants::get_position_targets_function_name);
  get_position_targets_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::getPositionTargetsHandler));
  get_position_targets_function.setReturnTypeArray();

  modular_server::Function & get_velocities_function = modular_server_.createFunction(constants::get_velocities_function_name);
  get_velocities_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::getVelocitiesHandler));
  get_velocities_function.setReturnTypeArray();

  modular_server::Function & get_velocity_targets_function = modular_server_.createFunction(constants::get_velocity_targets_function_name);
  get_velocity_targets_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::getVelocityTargetsHandler));
  get_velocity_targets_function.setReturnTypeArray();

  // Callbacks

}

void StepDirController::reinitialize()
{
  for (size_t tmc429_i=0; tmc429_i<constants::TMC429_COUNT; ++tmc429_i)
  {
    TMC429 & tmc429 = tmc429s_[tmc429_i];
    tmc429.setStepDirOutput();
    for (size_t motor_i=0; motor_i<constants::CHANNELS_PER_TMC429_COUNT; ++motor_i)
    {
      tmc429.disableLeftSwitchStop(motor_i);
      tmc429.disableRightSwitchStop(motor_i);
    }
  }
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    setLimitsHandler(channel);
  }
}

// void StepDirController::setEnablePolarity(const size_t channel, const ConstantString & polarity)
// {
//   if (channel < constants::CHANNEL_COUNT)
//   {
//     steppers_[channel].setEnablePolarity(polarity);
//   }
// }

// void StepDirController::setEnablePolarityAll(const ConstantString & polarity)
// {
//   for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
//   {
//     steppers_[channel].setEnablePolarity(polarity);
//   }
// }

// void StepDirController::setStepPolarity(const size_t channel, const ConstantString & polarity)
// {
//   if (channel < constants::CHANNEL_COUNT)
//   {
//     steppers_[channel].setStepPolarity(polarity);
//   }
// }

// void StepDirController::setStepPolarityAll(const ConstantString & polarity)
// {
//   for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
//   {
//     steppers_[channel].setStepPolarity(polarity);
//   }
// }

// void StepDirController::setDirPolarity(const size_t channel, const ConstantString & polarity)
// {
//   if (channel < constants::CHANNEL_COUNT)
//   {
//     steppers_[channel].setDirPolarity(polarity);
//   }
// }

// void StepDirController::setDirPolarityAll(const ConstantString & polarity)
// {
//   for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
//   {
//     steppers_[channel].setDirPolarity(polarity);
//   }
// }

// void StepDirController::enable(const size_t channel)
// {
//   if (channel < constants::CHANNEL_COUNT)
//   {
//     noInterrupts();
//     steppers_[channel].enable();
//     interrupts();
//   }
// }

// void StepDirController::disable(const size_t channel)
// {
//   if (channel < constants::CHANNEL_COUNT)
//   {
//     noInterrupts();
//     steppers_[channel].disable();
//     interrupts();
//   }
// }

// void StepDirController::enableAll()
// {
//   for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
//   {
//     steppers_[channel].enable();
//   }
// }

// void StepDirController::disableAll()
// {
//   for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
//   {
//     steppers_[channel].disable();
//   }
// }

// uint32_t StepDirController::enabled()
// {
//   uint32_t channels_enabled = 0;
//   for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
//   {
//     noInterrupts();
//     bool channel_enabled = steppers_[channel].enabled();
//     interrupts();
//     if (channel_enabled)
//     {
//       channels_enabled |= 1 << channel;
//     }
//   }
//   return channels_enabled;
// }

// void StepDirController::moveBy(const size_t channel, const long position)
// {
//   if (channel < constants::CHANNEL_COUNT)
//   {
//     Stepper & stepper = steppers_[channel];
//     stepper.stop();
//     stepper.setPositionMode();
//     stepper.setVelocity(10000);
//     stepper.setTargetPositionRelative(position);
//     stepper.start();
//   }
// }

// void StepDirController::moveTo(const size_t channel, const long position)
// {
//   if (channel < constants::CHANNEL_COUNT)
//   {
//     Stepper & stepper = steppers_[channel];
//     stepper.stop();
//     stepper.setPositionMode();
//     stepper.setVelocity(10000);
//     stepper.setTargetPosition(position);
//     stepper.start();
//   }
// }

void StepDirController::moveAt(const size_t channel, const long velocity)
{
  if (channel < constants::CHANNEL_COUNT)
  {
    size_t tmc429_i = channelToTmc429Index(channel);
    size_t motor_i = channelToMotorIndex(channel);
    TMC429 & tmc429 = tmc429s_[tmc429_i];
    tmc429.setMode(motor_i,TMC429::VELOCITY_MODE);
    tmc429.setVelocityTargetInHz(motor_i,velocity);
  }
}

// void StepDirController::moveByAt(const size_t channel, const long position, const long speed)
// {
//   if (channel < constants::CHANNEL_COUNT)
//   {
//     Stepper & stepper = steppers_[channel];
//     stepper.stop();
//     stepper.setPositionMode();
//     stepper.setVelocity(speed);
//     stepper.setTargetPositionRelative(position);
//     stepper.start();
//   }
// }

// void StepDirController::moveToAt(const size_t channel, const long position, const long speed)
// {
//   if (channel < constants::CHANNEL_COUNT)
//   {
//     Stepper & stepper = steppers_[channel];
//     stepper.stop();
//     stepper.setPositionMode();
//     stepper.setVelocity(speed);
//     stepper.setTargetPosition(position);
//     stepper.start();
//   }
// }

void StepDirController::stop(const size_t channel)
{
  if (channel < constants::CHANNEL_COUNT)
  {
    size_t tmc429_i = channelToTmc429Index(channel);
    size_t motor_i = channelToMotorIndex(channel);
    TMC429 & tmc429 = tmc429s_[tmc429_i];
    tmc429.stop(motor_i);
  }
}

void StepDirController::stopAll()
{
  for (size_t tmc429_i=0; tmc429_i<constants::TMC429_COUNT; ++tmc429_i)
  {
    TMC429 & tmc429 = tmc429s_[tmc429_i];
    tmc429.stopAll();
  }
}

void StepDirController::zero(const size_t channel)
{
  if (channel < constants::CHANNEL_COUNT)
  {
    size_t tmc429_i = channelToTmc429Index(channel);
    size_t motor_i = channelToMotorIndex(channel);
    TMC429 & tmc429 = tmc429s_[tmc429_i];
    tmc429.setMode(motor_i,TMC429::VELOCITY_MODE);
    tmc429.setPositionActual(motor_i,0);
  }
}

void StepDirController::zeroAll()
{
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    zero(channel);
  }
}

long StepDirController::getPosition(const size_t channel)
{
  long position = 0;
  if (channel < constants::CHANNEL_COUNT)
  {
    size_t tmc429_i = channelToTmc429Index(channel);
    size_t motor_i = channelToMotorIndex(channel);
    TMC429 & tmc429 = tmc429s_[tmc429_i];
    position = tmc429.getPositionActual(motor_i);
  }
  return position;
}

long StepDirController::getPositionTarget(const size_t channel)
{
  long position = 0;
  if (channel < constants::CHANNEL_COUNT)
  {
    size_t tmc429_i = channelToTmc429Index(channel);
    size_t motor_i = channelToMotorIndex(channel);
    TMC429 & tmc429 = tmc429s_[tmc429_i];
    position = tmc429.getPositionTarget(motor_i);
  }
  return position;
}

long StepDirController::getVelocity(const size_t channel)
{
  long velocity = 0;
  if (channel < constants::CHANNEL_COUNT)
  {
    size_t tmc429_i = channelToTmc429Index(channel);
    size_t motor_i = channelToMotorIndex(channel);
    TMC429 & tmc429 = tmc429s_[tmc429_i];
    velocity = tmc429.getVelocityActualInHz(motor_i);
  }
  return velocity;
}

long StepDirController::getVelocityTarget(const size_t channel)
{
  long velocity = 0;
  if (channel < constants::CHANNEL_COUNT)
  {
    size_t tmc429_i = channelToTmc429Index(channel);
    size_t motor_i = channelToMotorIndex(channel);
    TMC429 & tmc429 = tmc429s_[tmc429_i];
    velocity = tmc429.getVelocityTargetInHz(motor_i);
  }
  return velocity;
}

// TMC429 & StepDirController::getTmc429(const size_t channel)
// {
//   size_t tmc429_i = channelToTmc429Index(channel);
//   size_t motor_i = channelToMotorIndex(channel);
//   TMC429 & tmc429 = tmc429s_[tmc429_i];
// }

size_t StepDirController::channelToTmc429Index(const size_t channel)
{
  return channel/constants::CHANNELS_PER_TMC429_COUNT;
}

size_t StepDirController::channelToMotorIndex(const size_t channel)
{
  return channel%constants::CHANNELS_PER_TMC429_COUNT;
}

// Handlers must be non-blocking (avoid 'delay')
//
// modular_server_.parameter(parameter_name).getValue(value) value type must be either:
// fixed-point number (int, long, etc.)
// floating-point number (float, double)
// bool
// const char *
// ArduinoJson::JsonArray *
// ArduinoJson::JsonObject *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(value) value type must match the property array element default type

void StepDirController::setLimitsHandler(const size_t channel)
{
  stopAll();

  modular_server::Property & velocity_min_property = modular_server_.property(constants::velocity_min_property_name);
  long velocity_min;
  velocity_min_property.getElementValue(channel,velocity_min);

  modular_server::Property & velocity_max_property = modular_server_.property(constants::velocity_max_property_name);
  long velocity_max;
  velocity_max_property.getElementValue(channel,velocity_max);

  modular_server::Property & acceleration_max_property = modular_server_.property(constants::acceleration_max_property_name);
  long acceleration_max;
  acceleration_max_property.getElementValue(channel,acceleration_max);

  size_t tmc429_i = channelToTmc429Index(channel);
  size_t motor_i = channelToMotorIndex(channel);
  TMC429 & tmc429 = tmc429s_[tmc429_i];

  tmc429.setLimitsInHz(motor_i,
                       velocity_min,
                       velocity_max,
                       acceleration_max);

  velocity_min_property.disableFunctors();
  velocity_max_property.disableFunctors();
  acceleration_max_property.disableFunctors();

  velocity_min = tmc429.getVelocityMinInHz(motor_i);
  velocity_min_property.setElementValue(channel,velocity_min);

  velocity_max = tmc429.getVelocityMaxInHz(motor_i);
  velocity_max_property.setElementValue(channel,velocity_max);

  acceleration_max = tmc429.getAccelerationMaxInHzPerS(motor_i);
  acceleration_max_property.setElementValue(channel,acceleration_max);

  velocity_min_property.reenableFunctors();
  velocity_max_property.reenableFunctors();
  acceleration_max_property.reenableFunctors();
}

void StepDirController::reinitializeHandler()
{
  reinitialize();
}

// void StepDirController::setEnablePolarityHandler(const size_t index)
// {
//   const ConstantString * polarity_ptr;
//   modular_server_.property(constants::enable_polarity_property_name).getElementValue(index,polarity_ptr);
//   if ((polarity_ptr == &constants::polarity_high) || (polarity_ptr == &constants::polarity_high))
//   {
//     setEnablePolarity(index,*polarity_ptr);
//   }
// }

// void StepDirController::setStepPolarityHandler(const size_t index)
// {
//   const ConstantString * polarity_ptr;
//   modular_server_.property(constants::step_polarity_property_name).getElementValue(index,polarity_ptr);
//   if ((polarity_ptr == &constants::polarity_high) || (polarity_ptr == &constants::polarity_high))
//   {
//     setStepPolarity(index,*polarity_ptr);
//   }
// }

// void StepDirController::setDirPolarityHandler(const size_t index)
// {
//   const ConstantString * polarity_ptr;
//   modular_server_.property(constants::dir_polarity_property_name).getElementValue(index,polarity_ptr);
//   if ((polarity_ptr == &constants::polarity_high) || (polarity_ptr == &constants::polarity_high))
//   {
//     setDirPolarity(index,*polarity_ptr);
//   }
// }

// void StepDirController::setModeHandler(const size_t index)
// {
//   const ConstantString * mode_ptr;
//   modular_server_.property(constants::mode_property_name).getElementValue(index,mode_ptr);
//   if (mode_ptr == &constants::mode_position)
//   {
//     setPositionMode(index);
//   }
//   else if (mode_ptr == &constants::mode_velocity)
//   {
//     setVelocityMode(index);
//   }
// }

// void StepDirController::enableHandler()
// {
//   long channel;
//   modular_server_.property(constants::channel_parameter_name).getValue(channel);
//   enable(channel);
// }

// void StepDirController::disableHandler()
// {
//   long channel;
//   modular_server_.property(constants::channel_parameter_name).getValue(channel);
//   disable(channel);
// }

// void StepDirController::enableAllHandler()
// {
//   enableAll();
// }

// void StepDirController::disableAllHandler()
// {
//   disableAll();
// }

// void StepDirController::enabledHandler()
// {
//   uint32_t channels_enabled = enabled();
//   modular_server_.response().writeResultKey();
//   modular_server_.response().beginArray();
//   int bit = 1;
//   for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
//   {
//     bool channel_enabled = (bit << channel) & channels_enabled;
//     modular_server_.response().write(channel_enabled);
//   }
//   modular_server_.response().endArray();
// }

// void StepDirController::moveByHandler()
// {
//   long channel;
//   modular_server_.parameter(constants::channel_parameter_name).getValue(channel);
//   long position;
//   modular_server_.parameter(constants::position_parameter_name).getValue(position);
//   moveBy(channel,position);
// }

// void StepDirController::moveToHandler()
// {
//   long channel;
//   modular_server_.parameter(constants::channel_parameter_name).getValue(channel);
//   long position;
//   modular_server_.parameter(constants::position_parameter_name).getValue(position);
//   moveTo(channel,position);
// }

void StepDirController::moveAtHandler()
{
  long channel;
  modular_server_.parameter(constants::channel_parameter_name).getValue(channel);
  long velocity;
  modular_server_.parameter(constants::velocity_parameter_name).getValue(velocity);
  moveAt(channel,velocity);
}

// void StepDirController::moveByAtHandler()
// {
//   long channel;
//   modular_server_.parameter(constants::channel_parameter_name).getValue(channel);
//   long position;
//   modular_server_.parameter(constants::position_parameter_name).getValue(position);
//   long velocity;
//   modular_server_.parameter(constants::velocity_parameter_name).getValue(velocity);
//   moveByAt(channel,position,velocity);
// }

// void StepDirController::moveToAtHandler()
// {
//   long channel;
//   modular_server_.parameter(constants::channel_parameter_name).getValue(channel);
//   long position;
//   modular_server_.parameter(constants::position_parameter_name).getValue(position);
//   long velocity;
//   modular_server_.parameter(constants::velocity_parameter_name).getValue(velocity);
//   moveToAt(channel,position,velocity);
// }

void StepDirController::stopHandler()
{
  long channel;
  modular_server_.parameter(constants::channel_parameter_name).getValue(channel);
  stop(channel);
}

void StepDirController::stopAllHandler()
{
  stopAll();
}

void StepDirController::zeroHandler()
{
  long channel;
  modular_server_.parameter(constants::channel_parameter_name).getValue(channel);
  zero(channel);
}

void StepDirController::zeroAllHandler()
{
  zeroAll();
}

void StepDirController::getPositionsHandler()
{
  long position;
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    position = getPosition(channel);
    modular_server_.response().write(position);
  }
  modular_server_.response().endArray();
}

void StepDirController::getPositionTargetsHandler()
{
  long position;
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    position = getPosition(channel);
    modular_server_.response().write(position);
  }
  modular_server_.response().endArray();
}

void StepDirController::getVelocitiesHandler()
{
  long velocity;
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    velocity = getVelocity(channel);
    modular_server_.response().write(velocity);
  }
  modular_server_.response().endArray();
}

void StepDirController::getVelocityTargetsHandler()
{
  long velocity;
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    velocity = getVelocityTarget(channel);
    modular_server_.response().write(velocity);
  }
  modular_server_.response().endArray();
}
