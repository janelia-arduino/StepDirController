// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace step_dir_controller
{
namespace constants
{
CONSTANT_STRING(device_name,"step_dir_controller");

CONSTANT_STRING(firmware_name,"StepDirController");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
  {
    .name_ptr=&firmware_name,
    .version_major=1,
    .version_minor=0,
    .version_patch=0,
  };

CONSTANT_STRING(hardware_name,"step_dir_controller");

size_t step_half_period_us_max = 100;

// Interrupts

// Units

// Properties
CONSTANT_STRING(micro_steps_per_step_property_name,"micro_steps_per_step_count");
const long micro_steps_per_step_min = 1;
const long micro_steps_per_step_max = 256;
const long micro_steps_per_step_default = 256;

// CONSTANT_STRING(enable_polarity_high_property_name,"enable_polarity_high");
// const bool enable_polarity_high_default = true;

// Parameters

// Functions
CONSTANT_STRING(enable_function_name,"enable");
CONSTANT_STRING(disable_function_name,"disable");
CONSTANT_STRING(stop_function_name,"stop");

// Callbacks

// Errors
}
}
