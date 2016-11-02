// ----------------------------------------------------------------------------
// 5x3.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "5x3.h"


#if defined(__AVR_ATmega2560__)

namespace step_dir_controller
{
namespace constants
{
const modular_server::HardwareInfo hardware_info =
  {
    .name_ptr=&hardware_name,
    .part_number=0,
    .version_major=1,
    .version_minor=0,
  };

const size_t enable_pin = 49;

const size_t step_pins[MOTOR_COUNT] = {53};
const size_t dir_pins[MOTOR_COUNT] = {51};

// Units

// Fields

// Parameters

// Methods

// Callbacks

// Errors
}
}
#endif
