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

  setEnablePolarityHigh();
  setStepPolarityHigh();
  setDirPolarityHigh();

  running_ = false;
  current_pos_ = 0;
  target_pos_ = 0;

  enableOutputs();

  step_bit_mask_ = digitalPinToBitMask(step_pin_);
  step_port_ = digitalPinToPort(step_pin_);
  step_port_reg_ = portOutputRegister(step_port_);

  dir_bit_mask_ = digitalPinToBitMask(dir_pin_);
  dir_port_ = digitalPinToPort(dir_pin_);
  dir_port_reg_ = portOutputRegister(dir_port_);
}

void Stepper::setEnablePolarityHigh()
{
  enable_polarity_low_ = false;
}

void Stepper::setEnablePolarityLow()
{
  enable_polarity_low_ = true;
}

void Stepper::setStepPolarityHigh()
{
  step_polarity_low_ = false;
}

void Stepper::setStepPolarityLow()
{
  step_polarity_low_ = true;
}

void Stepper::setDirPolarityHigh()
{
  dir_polarity_low_ = false;
}

void Stepper::setDirPolarityLow()
{
  dir_polarity_low_ = true;
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

