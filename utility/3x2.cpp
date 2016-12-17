// ----------------------------------------------------------------------------
// 3x2.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "3x2.h"


#if defined(__MK20DX256__)

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

size_t step_half_period_us_max = 20;

// Interrupts

// Units

// Properties

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
