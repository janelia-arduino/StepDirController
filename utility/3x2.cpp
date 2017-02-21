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

const size_t cs_pins[TMC429_COUNT] = {10};
// const size_t enable_pins[CHANNEL_COUNT] = {2,3,4};

// Interrupts

// Units

// Properties
// const ConstantString * const enable_polarity_default[CHANNEL_COUNT] =
//   {
//     &polarity_high,
//   };

// const ConstantString * const step_polarity_default[CHANNEL_COUNT] =
//   {
//     &polarity_high,
//   };

// const ConstantString * const dir_polarity_default[CHANNEL_COUNT] =
//   {
//     &polarity_high,
//   };

const ConstantString * const mode_default[CHANNEL_COUNT] =
  {
    &mode_ramp,
    &mode_ramp,
    &mode_ramp,
  };

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
