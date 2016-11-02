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

// Units

// Fields
CONSTANT_STRING(micro_steps_per_step_field_name,"micro_steps_per_step_count");
const long micro_steps_per_step_min = 1;
const long micro_steps_per_step_max = 256;
const long micro_steps_per_step_default = 256;

CONSTANT_STRING(enable_polarity_high_field_name,"enable_polarity_high");
const bool enable_polarity_high_default = true;

// Parameters

// Methods
CONSTANT_STRING(enable_method_name,"enable");
CONSTANT_STRING(disable_method_name,"disable");
CONSTANT_STRING(stop_method_name,"stop");

// Callbacks

// Errors
}
}
