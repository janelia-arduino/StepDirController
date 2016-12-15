// ----------------------------------------------------------------------------
// Stepper.cpp
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Stepper.h"


using namespace step_dir_controller;

Stepper::Stepper()
{
}

Stepper::~Stepper()
{
  disableOutputs();
}

void Stepper::setup(const size_t enable_pin, const size_t step_pin, const size_t dir_pin)
{
  enable_pin_ = enable_pin;
  step_pin_ = step_pin;
  dir_pin_ = dir_pin;

  setEnablePolarity(&constants::polarity_high);
  setStepPolarity(&constants::polarity_high);
  setDirPolarity(&constants::polarity_high);

  setPositionMode();
  setDirPositive();

  update_inc_ = 0;
  step_positive_ = true;
  running_ = false;
  position_current_ = 0;
  position_target_ = 0;

  enableOutputs();

  step_bit_mask_ = digitalPinToBitMask(step_pin_);
  step_port_ = digitalPinToPort(step_pin_);
  step_port_reg_ = portOutputRegister(step_port_);

  dir_bit_mask_ = digitalPinToBitMask(dir_pin_);
  dir_port_ = digitalPinToPort(dir_pin_);
  dir_port_reg_ = portOutputRegister(dir_port_);
}

void Stepper::setEnablePolarity(const ConstantString * const polarity_ptr)
{
  if (polarity_ptr == &constants::polarity_low)
  {
    enable_polarity_low_ = true;
  }
  else
  {
    enable_polarity_low_ = false;
  }
}

void Stepper::setStepPolarity(const ConstantString * const polarity_ptr)
{
  if (polarity_ptr == &constants::polarity_low)
  {
    step_polarity_low_ = true;
  }
  else
  {
    step_polarity_low_ = false;
  }
}

void Stepper::setDirPolarity(const ConstantString * const polarity_ptr)
{
  if (polarity_ptr == &constants::polarity_low)
  {
    dir_polarity_low_ = true;
  }
  else
  {
    dir_polarity_low_ = false;
  }
}

void Stepper::setPositionMode()
{
  mode_position_ = true;
}

void Stepper::setVelocityMode()
{
  mode_position_ = false;
  if (velocity_ >= 0)
  {
    setDirPositive();
  }
  else
  {
    setDirNegative();
  }
}

void Stepper::enable()
{
  if (enable_polarity_low_)
  {
    digitalWrite(enable_pin_,LOW);
  }
  else
  {
    digitalWrite(enable_pin_,HIGH);
  }
  enabled_ = true;
}

void Stepper::disable()
{
  stop();
  enabled_ = false;
  if (enable_polarity_low_)
  {
    digitalWrite(enable_pin_,HIGH);
  }
  else
  {
    digitalWrite(enable_pin_,LOW);
  }
}

bool Stepper::enabled()
{
  return enabled_;
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

bool Stepper::running()
{
  return running_;
}

void Stepper::setVelocity(const long steps_per_second)
{
  if (steps_per_second == 0)
  {
    velocity_ = 0;
    stop();
    return;
  }
  velocity_ = steps_per_second;
  long speed = abs(velocity_);
  // (1000000/speed)*(1/2)*(1/constants::step_half_period_us_max)
  update_count_ = 500000/(constants::step_half_period_us_max*speed);
  if (!mode_position_)
  {
    if (velocity_ >= 0)
    {
      setDirPositive();
    }
    else
    {
      setDirNegative();
    }
  }
}

long Stepper::getTargetPosition()
{
  return position_target_;
}

void Stepper::setTargetPosition(const long position)
{
  noInterrupts();
  position_target_ = position;
  interrupts();
}

long Stepper::getCurrentPosition()
{
  return position_current_;
}

void Stepper::setCurrentPosition(const long position)
{
  noInterrupts();
  position_target_ = position;
  position_current_ = position;
  interrupts();
}

void Stepper::zero()
{
  noInterrupts();
  stop();
  setCurrentPosition(0);
  setTargetPosition(0);
  interrupts();
}

void Stepper::enableOutputs()
{
  pinMode(enable_pin_, OUTPUT);
  pinMode(step_pin_, OUTPUT);
  pinMode(dir_pin_, OUTPUT);
}

void Stepper::disableOutputs()
{
  pinMode(enable_pin_, INPUT);
  pinMode(step_pin_, INPUT);
  pinMode(dir_pin_, INPUT);
}

