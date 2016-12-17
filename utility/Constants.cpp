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

CONSTANT_STRING(mode_position,"POSITION");
CONSTANT_STRING(mode_velocity,"VELOCITY");

// Interrupts

// Units
CONSTANT_STRING(steps_unit,"steps");
CONSTANT_STRING(steps_per_second_unit,"steps/s");

// Properties
CONSTANT_STRING(enable_polarity_property_name,"enablePolarity");
CONSTANT_STRING(polarity_high,"HIGH");
CONSTANT_STRING(polarity_low,"LOW");
modular_server::SubsetMemberType polarity_ptr_subset[POLARITY_SUBSET_LENGTH] =
  {
    {.cs_ptr=&polarity_high},
    {.cs_ptr=&polarity_low},
  };

CONSTANT_STRING(step_polarity_property_name,"stepPolarity");

CONSTANT_STRING(dir_polarity_property_name,"dirPolarity");

// CONSTANT_STRING(mode_property_name,"mode");
// CONSTANT_STRING(mode_position,"POSITION");
// CONSTANT_STRING(mode_velocity,"VELOCITY");
// modular_server::SubsetMemberType mode_ptr_subset[MODE_SUBSET_LENGTH] =
//   {
//     {.cs_ptr=&mode_position},
//     {.cs_ptr=&mode_velocity},
//   };

// Parameters
CONSTANT_STRING(channel_parameter_name,"channel");

CONSTANT_STRING(position_parameter_name,"position");

CONSTANT_STRING(velocity_parameter_name,"velocity");
const long velocity_min = -500000/step_half_period_us_max;
const long velocity_max = 500000/step_half_period_us_max;

// Functions
CONSTANT_STRING(enable_function_name,"enable");
CONSTANT_STRING(disable_function_name,"disable");
CONSTANT_STRING(enable_all_function_name,"enableAll");
CONSTANT_STRING(disable_all_function_name,"disableAll");
CONSTANT_STRING(enabled_function_name,"enabled");
CONSTANT_STRING(move_by_function_name,"moveBy");
CONSTANT_STRING(move_to_function_name,"moveTo");
CONSTANT_STRING(move_at_function_name,"moveAt");
CONSTANT_STRING(move_at_function_name,"moveByAt");
CONSTANT_STRING(move_at_function_name,"moveToAt");
CONSTANT_STRING(get_positions_function_name,"getPositions");
CONSTANT_STRING(stop_function_name,"stop");
CONSTANT_STRING(stop_all_function_name,"stopAll");

// Callbacks

// Errors
}
}
