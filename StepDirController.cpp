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
  for (int motor_index=0; motor_index<constants::MOTOR_COUNT; motor_index++)
  {
    // steppers_[motor_index] = Stepper();
    steppers_[motor_index].setup(constants::step_pins[motor_index],
                                 constants::dir_pins[motor_index]);
  }

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware Info
  modular_server_.addHardwareInfo(constants::hardware_info);

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
                              fields_,
                              parameters_,
                              methods_,
                              callbacks_);
  // Fields

  // Parameters

  // Methods

  // Callbacks

}

void StepDirController::enable()
{
  setSpeed();

  bool enable_polarity_high;
  globals::modular_server.getFieldValue(constants::enable_polarity_high_field_name,enable_polarity_high);
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
  globals::modular_server.getFieldValue(constants::enable_polarity_high_field_name,enable_polarity_high);
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

void StepDirController::stop(unsigned int motor_index)
{
  if (motor_index<constants::MOTOR_COUNT)
  {
    noInterrupts();
    steppers_[motor_index].stop();
    interrupts();
  }
}

void StepDirController::start(unsigned int motor_index)
{
  if (motor_index<constants::MOTOR_COUNT)
  {
    noInterrupts();
    steppers_[motor_index].start();
    interrupts();
  }
}

void StepDirController::stopAll()
{
  noInterrupts();
  for (int motor_index=0; motor_index<constants::MOTOR_COUNT; motor_index++)
  {
    steppers_[motor_index].stop();
  }
  interrupts();
}

void StepDirController::startAll()
{
  noInterrupts();
  for (int motor_index=0; motor_index<constants::MOTOR_COUNT; motor_index++)
  {
    steppers_[motor_index].start();
  }
  interrupts();
}

bool StepDirController::areAnyRunning()
{
  bool flag = false;
  for (int motor_index=0; motor_index<constants::MOTOR_COUNT; motor_index++)
  {
    if (steppers_[motor_index].isRunning())
    {
      flag = true;
    }
  }
  return flag;
}

bool StepDirController::isRunning(unsigned int motor_index)
{
  return steppers_[motor_index].isRunning();
}

Array<bool, constants::MOTOR_COUNT> StepDirController::isRunningAll()
{
  Array<bool, constants::MOTOR_COUNT> is_running;
  for (int motor_index=0; motor_index<constants::MOTOR_COUNT; motor_index++)
  {
    noInterrupts();
    is_running[motor_index] = isRunning(motor_index);
    interrupts();
  }
  return is_running;
}

// void StepDirController::setSpeed(unsigned int v)
//{
//   long period = 1000000/v;
//   Timer1.setPeriod(period);
// }

void StepDirController::setDirection(unsigned int motor_index, char dir)
{
  if (motor_index < constants::MOTOR_COUNT)
  {
    if (dir == constants::orientation_inverted)
    {
      steppers_[motor_index].setDirInverted();
    }
    else
    {
      steppers_[motor_index].setDirNormal();
    }
  }
}
void StepDirController::setDirectionAll(Array<char,constants::MOTOR_COUNT> dir)
{
  for (int motor_index=0; motor_index<constants::MOTOR_COUNT; motor_index++)
  {
    setDirection(motor_index,dir[motor_index]);
  }
}

long StepDirController::getCurrentPosition(unsigned int motor_index)
{
  long rtn_val = 0;
  if (motor_index < constants::MOTOR_COUNT)
  {
    noInterrupts();
    rtn_val = steppers_[motor_index].getCurrentPosition();
    interrupts();
  }
  return rtn_val;
}

Array<long, constants::MOTOR_COUNT> StepDirController::getCurrentPositionAll()
{
  Array<long, constants::MOTOR_COUNT> position;
  for (int motor_index=0; motor_index<constants::MOTOR_COUNT; motor_index++)
  {
    noInterrupts();
    position[motor_index] = steppers_[motor_index].getCurrentPosition();
    interrupts();
  }
  return position;
}

void StepDirController::setCurrentPosition(unsigned int motor_index, long pos)
{
  if (motor_index < constants::MOTOR_COUNT)
  {
    steppers_[motor_index].setCurrentPosition(pos);
  }
}

void StepDirController::setCurrentPositionAll(Array<long, constants::MOTOR_COUNT> pos)
{
  for (int motor_index=0; motor_index<constants::MOTOR_COUNT; motor_index++)
  {
    setCurrentPosition(motor_index,pos[motor_index]);
  }
}

long StepDirController::getTargetPosition(unsigned int motor_index)
{
  long rtn_val = 0;
  if (motor_index < constants::MOTOR_COUNT)
  {
    noInterrupts();
    rtn_val = steppers_[motor_index].getTargetPosition();
    interrupts();
  }
  return rtn_val;
}

Array<long, constants::MOTOR_COUNT> StepDirController::getTargetPositionAll()
{
  Array<long, constants::MOTOR_COUNT> position;
  for (int motor_index=0; motor_index<constants::MOTOR_COUNT; motor_index++)
  {
    noInterrupts();
    position[motor_index] = steppers_[motor_index].getTargetPosition();
    interrupts();
  }
  return position;
}

void StepDirController::setTargetPosition(unsigned int motor_index, long pos)
{
  if (motor_index < constants::MOTOR_COUNT)
  {
    noInterrupts();
    steppers_[motor_index].setTargetPosition(pos);
    interrupts();
  }
}

void StepDirController::setTargetPositionAll(Array<long,constants::MOTOR_COUNT> pos)
{
  noInterrupts();
  for (int motor_index=0; motor_index<constants::MOTOR_COUNT; motor_index++)
  {
    steppers_[motor_index].setTargetPosition(pos[motor_index]);
  }
  interrupts();
}

// int StepDirController::getCurrentWaypoint(unsigned int motor_index)
// {
//   int rtn_val = 0;
//   if (motor_index < constants::MOTOR_COUNT)
//   {
//     noInterrupts();
//     rtn_val = steppers_[motor_index].getCurrentWaypoint();
//     interrupts();
//   }
//   return rtn_val;
// }

// Array<int, constants::MOTOR_COUNT> StepDirController::getCurrentWaypointAll()
// {
//   Array<int, constants::MOTOR_COUNT> waypoint;
//   for (int motor_index=0; motor_index<constants::MOTOR_COUNT; motor_index++)
//   {
//     noInterrupts();
//     waypoint[motor_index] = steppers_[motor_index].getCurrentWaypoint();
//     interrupts();
//   }
//   return waypoint;
// }

void StepDirController::setSpeed()
{
  // constants::ModeType mode;
  // globals::globals::modular_server.getSavedVariableValue(constants::mode_name,mode);
  // if (mode == constants::WAYPOINT)
  if (true)
  {
    long waypoint_travel_duration;
    globals::modular_server.getFieldValue(constants::waypoint_travel_duration_field_name,waypoint_travel_duration);
    long micro_steps_per_step;
    globals::modular_server.getFieldValue(constants::micro_steps_per_step_field_name,micro_steps_per_step);
    long waypoint_count;
    globals::modular_server.getFieldValue(constants::waypoint_count_field_name,waypoint_count);
    long timer_period = ((long)waypoint_travel_duration*waypoint_count*1000)/(constants::steps_per_rev*long(micro_steps_per_step));
    Timer1.setPeriod(timer_period);
  }
}

// void StepDirController::goToNextWaypoint(unsigned int motor_index)
// {
//   if (enabled_flag_)
//   {
//     if (motor_index < constants::MOTOR_COUNT)
//     {
//       steppers_[motor_index].goToNextWaypoint();
//     }
//   }
// }

void StepDirController::zero(unsigned int motor_index)
{
  if (motor_index < constants::MOTOR_COUNT)
  {
    steppers_[motor_index].zero();
  }
}

void StepDirController::zeroAll()
{
  for (int motor_index=0; motor_index<constants::MOTOR_COUNT; motor_index++)
  {
    steppers_[motor_index].zero();
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
// modular_server_.field(field_name).getValue(value) value type must match the field default type
// modular_server_.field(field_name).setValue(value) value type must match the field default type
// modular_server_.field(field_name).getElementValue(value) value type must match the field array element default type
// modular_server_.field(field_name).setElementValue(value) value type must match the field array element default type

