// ----------------------------------------------------------------------------
// Stepper.cpp
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Stepper.h"


Stepper::Stepper()
{
}

Stepper::~Stepper()
{
  disableOutputs();
}

void Stepper::setup(size_t enable_pin, size_t step_pin, size_t dir_pin)
{
  enable_pin_ = enable_pin;
  step_pin_ = step_pin;
  dir_pin_ = dir_pin;

  setStepNormal();
  setDirNormal();

  running_ = false;
  current_pos_ = 0;
  target_pos_ = 0;
  // waypoint_ = 0;

  enableOutputs();

  step_bit_mask_ = digitalPinToBitMask(step_pin_);
  step_port_ = digitalPinToPort(step_pin_);
  step_port_reg_ = portOutputRegister(step_port_);

  dir_bit_mask_ = digitalPinToBitMask(dir_pin_);
  dir_port_ = digitalPinToPort(dir_pin_);
  dir_port_reg_ = portOutputRegister(dir_port_);
}

void Stepper::start()
{
  // Should be called in an atomic block
  running_ = true;
}

void Stepper::stop()
{
  // Should be called in an atomic block
  running_ = false;
}

bool Stepper::isRunning()
{
  return running_;
}

void Stepper::disableOutputs()
{
  digitalWrite(step_pin_, LOW ^ step_inverted_);
  digitalWrite(dir_pin_, LOW ^ dir_inverted_);
}

void Stepper::enableOutputs()
{
  pinMode(step_pin_, OUTPUT);
  pinMode(dir_pin_, OUTPUT);
}

long Stepper::getTargetPosition()
{
  return target_pos_;
}

void Stepper::setTargetPosition(long position)
{
  noInterrupts();
  target_pos_ = position;
  interrupts();
}

long Stepper::getCurrentPosition()
{
  return current_pos_;
}

void Stepper::setCurrentPosition(long position)
{
  noInterrupts();
  target_pos_ = position;
  current_pos_ = position;
  interrupts();
}

void Stepper::setPinsInverted(bool direction, bool step)
{
  dir_inverted_ = direction;
  step_inverted_ = step;
}

void Stepper::setStepNormal()
{
  step_inverted_ = false;
}

void Stepper::setStepInverted()
{
  step_inverted_ = true;
}

void Stepper::setDirNormal()
{
  dir_inverted_ = false;
}

void Stepper::setDirInverted()
{
  dir_inverted_ = true;
}

// void Stepper::goToNextWaypoint()
// {
//   if (!isRunning())
//   {
//     long micro_steps_per_step;
//     globals::modular_server.getPropertyValue(constants::micro_steps_per_step_property_name,micro_steps_per_step);
//     long waypoint_count;
//     globals::modular_server.getPropertyValue(constants::waypoint_count_property_name,waypoint_count);
//     bool reverse_direction;
//     globals::modular_server.getPropertyValue(constants::reverse_direction_property_name,reverse_direction);
//     long next_waypoint_pos;
//     if (!reverse_direction)
//     {
//       next_waypoint_pos = (long(waypoint_ + 1)*constants::steps_per_rev*micro_steps_per_step)/long(waypoint_count);
//     }
//     else
//     {
//       next_waypoint_pos = (long(waypoint_ - 1)*constants::steps_per_rev*micro_steps_per_step)/long(waypoint_count);
//     }
//     setTargetPosition(next_waypoint_pos);
//     start();
//   }
// }

// int Stepper::getCurrentWaypoint()
// {
//   return waypoint_;
// }

// void Stepper::setCurrentWaypoint(int waypoint)
// {
//   noInterrupts();
//   waypoint_ = waypoint;
//   interrupts();
// }

void Stepper::zero()
{
  noInterrupts();
  stop();
  setCurrentPosition(0);
  setTargetPosition(0);
  // setCurrentWaypoint(0);
  interrupts();
}
