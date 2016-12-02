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
  enabled_flag_ = false;
}

StepDirController::~StepDirController()
{
  disable();
}

void StepDirController::setup()
{
  // Parent Setup
  ModularDevice::setup();

  // Event Controller Setup
  // event_controller_.setup();

  // Pin Setup
  pinMode(constants::enable_pin, OUTPUT);

  // Assign pins (step, dir) to motors
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; channel++)
  {
    // steppers_[channel] = Stepper();
    steppers_[channel].setup(constants::step_pins[channel],
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

void StepDirController::enable()
{
  // setSpeed();

  bool enable_polarity_high;
  modular_server_.property(constants::enable_polarity_high_property_name).getValue(enable_polarity_high);
  if (enable_polarity_high)
  {
    digitalWrite(constants::enable_pin,HIGH);
  }
  else
  {
    digitalWrite(constants::enable_pin,LOW);
  }
  enabled_flag_ = true;
}

void StepDirController::disable()
{
  enabled_flag_ = false;
  bool enable_polarity_high;
  modular_server_.property(constants::enable_polarity_high_property_name).getValue(enable_polarity_high);
  if (enable_polarity_high)
  {
    digitalWrite(constants::enable_pin,LOW);
  }
  else
  {
    digitalWrite(constants::enable_pin,HIGH);
  }
  stopAll();
}

bool StepDirController::isEnabled()
{
  return enabled_flag_;
}

void StepDirController::stop(const size_t channel)
{
  if (channel<constants::CHANNEL_COUNT)
  {
    noInterrupts();
    steppers_[channel].stop();
    interrupts();
  }
}

void StepDirController::start(const size_t channel)
{
  if (channel<constants::CHANNEL_COUNT)
  {
    noInterrupts();
    steppers_[channel].start();
    interrupts();
  }
}

void StepDirController::stopAll()
{
  noInterrupts();
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; channel++)
  {
    steppers_[channel].stop();
  }
  interrupts();
}

void StepDirController::startAll()
{
  noInterrupts();
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; channel++)
  {
    steppers_[channel].start();
  }
  interrupts();
}

bool StepDirController::anyRunning()
{
  bool flag = false;
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; channel++)
  {
    if (steppers_[channel].isRunning())
    {
      flag = true;
    }
  }
  return flag;
}

bool StepDirController::isRunning(const size_t channel)
{
  return steppers_[channel].isRunning();
}

Array<bool, constants::CHANNEL_COUNT> StepDirController::isRunningAll()
{
  Array<bool, constants::CHANNEL_COUNT> is_running;
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; channel++)
  {
    noInterrupts();
    is_running[channel] = isRunning(channel);
    interrupts();
  }
  return is_running;
}

// void StepDirController::setSpeed(unsigned int v)
//{
//   long period = 1000000/v;
//   Timer1.setPeriod(period);
// }

void StepDirController::setDirection(const size_t channel, char dir)
{
  if (channel < constants::CHANNEL_COUNT)
  {
    if (dir == constants::orientation_inverted)
    {
      steppers_[channel].setDirInverted();
    }
    else
    {
      steppers_[channel].setDirNormal();
    }
  }
}
void StepDirController::setDirectionAll(Array<char,constants::CHANNEL_COUNT> dir)
{
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; channel++)
  {
    setDirection(channel,dir[channel]);
  }
}

long StepDirController::getCurrentPosition(const size_t channel)
{
  long rtn_val = 0;
  if (channel < constants::CHANNEL_COUNT)
  {
    noInterrupts();
    rtn_val = steppers_[channel].getCurrentPosition();
    interrupts();
  }
  return rtn_val;
}

Array<long, constants::CHANNEL_COUNT> StepDirController::getCurrentPositionAll()
{
  Array<long, constants::CHANNEL_COUNT> position;
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; channel++)
  {
    noInterrupts();
    position[channel] = steppers_[channel].getCurrentPosition();
    interrupts();
  }
  return position;
}

void StepDirController::setCurrentPosition(const size_t channel, long pos)
{
  if (channel < constants::CHANNEL_COUNT)
  {
    steppers_[channel].setCurrentPosition(pos);
  }
}

void StepDirController::setCurrentPositionAll(Array<long, constants::CHANNEL_COUNT> pos)
{
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; channel++)
  {
    setCurrentPosition(channel,pos[channel]);
  }
}

long StepDirController::getTargetPosition(const size_t channel)
{
  long rtn_val = 0;
  if (channel < constants::CHANNEL_COUNT)
  {
    noInterrupts();
    rtn_val = steppers_[channel].getTargetPosition();
    interrupts();
  }
  return rtn_val;
}

Array<long, constants::CHANNEL_COUNT> StepDirController::getTargetPositionAll()
{
  Array<long, constants::CHANNEL_COUNT> position;
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; channel++)
  {
    noInterrupts();
    position[channel] = steppers_[channel].getTargetPosition();
    interrupts();
  }
  return position;
}

void StepDirController::setTargetPosition(const size_t channel, long pos)
{
  if (channel < constants::CHANNEL_COUNT)
  {
    noInterrupts();
    steppers_[channel].setTargetPosition(pos);
    interrupts();
  }
}

void StepDirController::setTargetPositionAll(Array<long,constants::CHANNEL_COUNT> pos)
{
  noInterrupts();
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; channel++)
  {
    steppers_[channel].setTargetPosition(pos[channel]);
  }
  interrupts();
}

// int StepDirController::getCurrentWaypoint(const size_t channel)
// {
//   int rtn_val = 0;
//   if (channel < constants::CHANNEL_COUNT)
//   {
//     noInterrupts();
//     rtn_val = steppers_[channel].getCurrentWaypoint();
//     interrupts();
//   }
//   return rtn_val;
// }

// Array<int, constants::CHANNEL_COUNT> StepDirController::getCurrentWaypointAll()
// {
//   Array<int, constants::CHANNEL_COUNT> waypoint;
//   for (size_t channel=0; channel<constants::CHANNEL_COUNT; channel++)
//   {
//     noInterrupts();
//     waypoint[channel] = steppers_[channel].getCurrentWaypoint();
//     interrupts();
//   }
//   return waypoint;
// }

void StepDirController::setSpeed()
{
  // constants::ModeType mode;
  // modular_server_.getSavedVariableValue(constants::mode_name,mode);
  // if (mode == constants::WAYPOINT)
  if (true)
  {
    // long waypoint_travel_duration;
    // modular_server_.property(constants::waypoint_travel_duration_property_name).getValue(waypoint_travel_duration);
    // long micro_steps_per_step;
    // modular_server_.property(constants::micro_steps_per_step_property_name).getValue(micro_steps_per_step);
    // long waypoint_count;
    // modular_server_.property(constants::waypoint_count_property_name).getValue(waypoint_count);
    // long timer_period = ((long)waypoint_travel_duration*waypoint_count*1000)/(constants::steps_per_rev*long(micro_steps_per_step));
    // Timer1.setPeriod(timer_period);
  }
}

// void StepDirController::goToNextWaypoint(const size_t channel)
// {
//   if (enabled_flag_)
//   {
//     if (channel < constants::CHANNEL_COUNT)
//     {
//       steppers_[channel].goToNextWaypoint();
//     }
//   }
// }

void StepDirController::zero(const size_t channel)
{
  if (channel < constants::CHANNEL_COUNT)
  {
    steppers_[channel].zero();
  }
}

void StepDirController::zeroAll()
{
  for (size_t channel=0; channel<constants::CHANNEL_COUNT; channel++)
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
