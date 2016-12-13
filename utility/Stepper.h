// ----------------------------------------------------------------------------
// Stepper.h
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------

#ifndef STEPPER_H
#define STEPPER_H
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <wiring.h>
#endif

#include "Constants.h"


class Stepper
{
public:
  Stepper();
  ~Stepper();

  void setup(const size_t enable_pin, const size_t step_pin, const size_t dir_pin);
  void update();

  void setEnablePolarityHigh();
  void setEnablePolarityLow();

  void setStepPolarityHigh();
  void setStepPolarityLow();

  void setDirPolarityHigh();
  void setDirPolarityLow();

  void setPositionMode();
  void setVelocityMode();

  void enable();
  void disable();
  bool enabled();

  void start();
  void stop();
  bool running();

  void setVelocity(const long steps_per_second);

  long getTargetPosition();
  void setTargetPosition(const long position);
  long getCurrentPosition();
  void setCurrentPosition(const long position);

  void zero();

private:
  size_t enable_pin_;
  size_t step_pin_;
  size_t dir_pin_;

  bool enable_polarity_low_;
  bool step_polarity_low_;
  bool dir_polarity_low_;

  bool mode_position_;

  bool enabled_;

  long velocity_;
  long update_count_;

  uint8_t step_bit_mask_;
  uint8_t dir_bit_mask_;
  uint8_t step_port_;
  uint8_t dir_port_;
  volatile uint8_t *dir_port_reg_;
  volatile uint8_t *step_port_reg_;

  volatile long update_inc_;
  volatile bool step_positive_;
  volatile bool running_;
  volatile bool dir_positive_;
  volatile long position_current_;
  volatile long position_target_;

  void disableOutputs();
  void enableOutputs();

  void setDirPositive();
  void setDirNegative();
  void updateDirPin();
  void setStepPinPositive();
  void setStepPinNegative();

};

inline void Stepper::update()
{
  if (running_)
  {
    ++update_inc_;
    if (update_inc_ >= update_count_)
    {
      update_inc_ = 0;
      if (step_positive_)
      {
        updateDirPin();
        setStepPinPositive();
      }
      else
      {
        setStepPinNegative();
      }
      step_positive_ = !step_positive_;
    }
  }
}

inline void Stepper::setDirPositive()
{
  if (dir_polarity_low_)
  {
    *dir_port_reg_ &= ~ dir_bit_mask_;
  }
  else
  {
    *dir_port_reg_ |= dir_bit_mask_;
  }
  dir_positive_ = true;
}

inline void Stepper::setDirNegative()
{
  if (dir_polarity_low_)
  {
    *dir_port_reg_ |= dir_bit_mask_;
  }
  else
  {
    *dir_port_reg_ &= ~ dir_bit_mask_;
  }
  dir_positive_ = false;
}

inline void Stepper::updateDirPin()
{
  if (mode_position_)
  {
    if (position_current_ <= position_target_)
    {
      setDirPositive();
    }
    else if (position_current_ > position_target_)
    {
      setDirNegative();
    }
  }
}

inline void Stepper::setStepPinPositive()
{
  if (step_polarity_low_)
  {
    *step_port_reg_ &= ~step_bit_mask_;
  }
  else {
    *step_port_reg_ |= step_bit_mask_;
  }
  if (dir_positive_)
  {
    ++position_current_;
  }
  else
  {
    --position_current_;
  }
}

inline void Stepper::setStepPinNegative()
{
  if (step_polarity_low_)
  {
    *step_port_reg_ |= step_bit_mask_;
  }
  else
  {
    *step_port_reg_ &= ~step_bit_mask_;
  }
  if (mode_position_ && (position_current_ == position_target_))
  {
    running_ = false;
  }
}

#endif
