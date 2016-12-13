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

  // TimerThree Setup
  FunctorCallbacks::remove(isr_);
  isr_ = FunctorCallbacks::add(makeFunctor((Functor0 *)0,*this,&StepDirController::isrHandler));
  Timer3.initialize(constants::step_half_period_us_max);
  Timer3.attachInterrupt(isr_);

  // Event Controller Setup
  // event_controller_.setup();

  // Pin Setup
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    steppers_[channel].setup(constants::enable_pins[channel],
                             constants::step_pins[channel],
                             constants::dir_pins[channel]);
  }

  // Interrupts
#if defined(__AVR_ATmega2560__)
  // modular_server::Interrupt & bnc_b_interrupt = modular_server_.createInterrupt(constants::bnc_b_interrupt_name,
  //                                                                               constants::bnc_b_pin);


#endif
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

  // Parameters

  // Functions

  // Callbacks

}

void StepDirController::setEnablePolarityHigh(const size_t channel)
{
  if (channel < constants::CHANNEL_COUNT)
  {
    steppers_[channel].setEnablePolarityHigh();
  }
}

void StepDirController::setEnablePolarityLow(const size_t channel)
{
  if (channel < constants::CHANNEL_COUNT)
  {
    steppers_[channel].setEnablePolarityLow();
  }
}

void StepDirController::setEnablePolarityHighAll()
{
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    steppers_[channel].setEnablePolarityHigh();
  }
}

void StepDirController::setEnablePolarityLowAll()
{
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    steppers_[channel].setEnablePolarityLow();
  }
}

void StepDirController::setStepPolarityHigh(const size_t channel)
{
  if (channel < constants::CHANNEL_COUNT)
  {
    steppers_[channel].setStepPolarityHigh();
  }
}

void StepDirController::setStepPolarityLow(const size_t channel)
{
  if (channel < constants::CHANNEL_COUNT)
  {
    steppers_[channel].setStepPolarityLow();
  }
}

void StepDirController::setStepPolarityHighAll()
{
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    steppers_[channel].setStepPolarityHigh();
  }
}

void StepDirController::setStepPolarityLowAll()
{
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    steppers_[channel].setStepPolarityLow();
  }
}

void StepDirController::setDirPolarityHigh(const size_t channel)
{
  if (channel < constants::CHANNEL_COUNT)
  {
    steppers_[channel].setDirPolarityHigh();
  }
}

void StepDirController::setDirPolarityLow(const size_t channel)
{
  if (channel < constants::CHANNEL_COUNT)
  {
    steppers_[channel].setDirPolarityLow();
  }
}

void StepDirController::setDirPolarityHighAll()
{
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    steppers_[channel].setDirPolarityHigh();
  }
}

void StepDirController::setDirPolarityLowAll()
{
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    steppers_[channel].setDirPolarityLow();
  }
}

void StepDirController::setPositionMode(const size_t channel)
{
  if (channel < constants::CHANNEL_COUNT)
  {
    steppers_[channel].setPositionMode();
  }
}

void StepDirController::setVelocityMode(const size_t channel)
{
  if (channel < constants::CHANNEL_COUNT)
  {
    steppers_[channel].setVelocityMode();
  }
}

void StepDirController::setPositionModeAll()
{
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    steppers_[channel].setPositionMode();
  }
}

void StepDirController::setVelocityModeAll()
{
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    steppers_[channel].setVelocityMode();
  }
}

void StepDirController::enable(const size_t channel)
{
  if (channel < constants::CHANNEL_COUNT)
  {
    noInterrupts();
    steppers_[channel].enable();
    interrupts();
  }
}

void StepDirController::disable(const size_t channel)
{
  if (channel < constants::CHANNEL_COUNT)
  {
    noInterrupts();
    steppers_[channel].disable();
    interrupts();
  }
}

bool StepDirController::enabled(const size_t channel)
{
  bool enabled = false;
  if (channel < constants::CHANNEL_COUNT)
  {
    enabled = steppers_[channel].enabled();
  }
  return enabled;
}

void StepDirController::enableAll()
{
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    steppers_[channel].enable();
  }
}

void StepDirController::disableAll()
{
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    steppers_[channel].disable();
  }
}

Array<bool, constants::CHANNEL_COUNT> StepDirController::enabledArray()
{
  Array<bool, constants::CHANNEL_COUNT> enabled_array;
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    noInterrupts();
    enabled_array.push_back(enabled(channel));
    interrupts();
  }
  return enabled_array;
}

void StepDirController::start(const size_t channel)
{
  if (channel < constants::CHANNEL_COUNT)
  {
    noInterrupts();
    steppers_[channel].start();
    interrupts();
  }
}

void StepDirController::stop(const size_t channel)
{
  if (channel < constants::CHANNEL_COUNT)
  {
    noInterrupts();
    steppers_[channel].stop();
    interrupts();
  }
}

bool StepDirController::running(const size_t channel)
{
  bool running = false;
  if (channel < constants::CHANNEL_COUNT)
  {
    running = steppers_[channel].running();
  }
  return running;
}

void StepDirController::startAll()
{
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    steppers_[channel].start();
  }
}

void StepDirController::stopAll()
{
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    steppers_[channel].stop();
  }
}

bool StepDirController::anyRunning()
{
  bool flag = false;
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    if (steppers_[channel].running())
    {
      flag = true;
      break;
    }
  }
  return flag;
}

Array<bool, constants::CHANNEL_COUNT> StepDirController::runningArray()
{
  Array<bool, constants::CHANNEL_COUNT> running_array;
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    noInterrupts();
    running_array.push_back(running(channel));
    interrupts();
  }
  return running_array;
}

void StepDirController::setVelocity(const size_t channel, const long steps_per_second)
{
  if (channel < constants::CHANNEL_COUNT)
  {
    steppers_[channel].setVelocity(steps_per_second);
  }
}

long StepDirController::getCurrentPosition(const size_t channel)
{
  long position = 0;
  if (channel < constants::CHANNEL_COUNT)
  {
    noInterrupts();
    position = steppers_[channel].getCurrentPosition();
    interrupts();
  }
  return position;
}

Array<long, constants::CHANNEL_COUNT> StepDirController::getCurrentPositions()
{
  Array<long, constants::CHANNEL_COUNT> positions;
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    noInterrupts();
    positions.push_back(steppers_[channel].getCurrentPosition());
    interrupts();
  }
  return positions;
}

void StepDirController::setCurrentPosition(const size_t channel, long position)
{
  if (channel < constants::CHANNEL_COUNT)
  {
    steppers_[channel].setCurrentPosition(position);
  }
}

void StepDirController::setCurrentPositions(Array<long, constants::CHANNEL_COUNT> positions)
{
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    setCurrentPosition(channel,positions[channel]);
  }
}

long StepDirController::getTargetPosition(const size_t channel)
{
  long position = 0;
  if (channel < constants::CHANNEL_COUNT)
  {
    noInterrupts();
    position = steppers_[channel].getTargetPosition();
    interrupts();
  }
  return position;
}

Array<long, constants::CHANNEL_COUNT> StepDirController::getTargetPositions()
{
  Array<long, constants::CHANNEL_COUNT> positions;
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    noInterrupts();
    positions.push_back(steppers_[channel].getTargetPosition());
    interrupts();
  }
  return positions;
}

void StepDirController::setTargetPosition(const size_t channel, long position)
{
  if (channel < constants::CHANNEL_COUNT)
  {
    noInterrupts();
    steppers_[channel].setTargetPosition(position);
    interrupts();
  }
}

void StepDirController::setTargetPositions(Array<long,constants::CHANNEL_COUNT> positions)
{
  noInterrupts();
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    steppers_[channel].setTargetPosition(positions[channel]);
  }
  interrupts();
}

void StepDirController::zero(const size_t channel)
{
  if (channel < constants::CHANNEL_COUNT)
  {
    steppers_[channel].zero();
  }
}

void StepDirController::zeroAll()
{
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    steppers_[channel].zero();
  }
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

void StepDirController::isrHandler()
{
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; ++channel)
  {
    steppers_[channel].update();
  }
}
