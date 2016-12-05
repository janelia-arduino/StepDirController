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


class Stepper
{
public:
  Stepper();
  ~Stepper();

  void setup(size_t enable_pin, size_t step_pin, size_t dir_pin);

  void setEnablePolarityHigh();
  void setEnablePolarityLow();

  void setStepPolarityHigh();
  void setStepPolarityLow();

  void setDirPolarityHigh();
  void setDirPolarityLow();

  void enable();
  void disable();
  bool enabled();

  void start();
  void stop();
  bool running();

  long getTargetPosition();
  void setTargetPosition(long position);
  long getCurrentPosition();
  void setCurrentPosition(long position);

  void zero();

  void updateDirPin();
  void setStepPinHigh();
  void setStepPinLow();
private:
  size_t enable_pin_;
  size_t step_pin_;
  size_t dir_pin_;

  bool enable_polarity_low_;
  bool step_polarity_low_;
  bool dir_polarity_low_;

  bool enabled_;

  uint8_t step_bit_mask_;
  uint8_t dir_bit_mask_;
  uint8_t step_port_;
  uint8_t dir_port_;
  volatile uint8_t *dir_port_reg_;
  volatile uint8_t *step_port_reg_;

  volatile bool running_;
  volatile long current_pos_;   // Steps
  volatile long target_pos_;    // Steps

  void disableOutputs();
  void enableOutputs();

};

inline void Stepper::updateDirPin()
{
  if (running_)
  {
    if (current_pos_ <= target_pos_)
    {
      if (dir_polarity_low_)
      {
        *dir_port_reg_ &= ~ dir_bit_mask_;
      }
      else
      {
        *dir_port_reg_ |= dir_bit_mask_;
      }
      current_pos_ += 1;
    }
    else if (current_pos_ > target_pos_)
    {
      if (dir_polarity_low_)
      {
        *dir_port_reg_ |= dir_bit_mask_;
      }
      else
      {
        *dir_port_reg_ &= ~ dir_bit_mask_;
      }
      current_pos_ -= 1;
    }
  }
}

inline void Stepper::setStepPinHigh()
{
  if (running_)
  {
    if (step_polarity_low_)
    {
      *step_port_reg_ &= ~step_bit_mask_;
    }
    else {
      *step_port_reg_ |= step_bit_mask_;
    }
  }
}

inline void Stepper::setStepPinLow()
{
  if (running_)
  {
    if (step_polarity_low_)
    {
      *step_port_reg_ |= step_bit_mask_;
    }
    else
    {
      *step_port_reg_ &= ~step_bit_mask_;
    }
    if (current_pos_ == target_pos_)
    {
      running_ = false;
    }
  }
}

#endif
