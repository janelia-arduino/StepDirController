// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
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
  .version_major=2,
  .version_minor=7,
  .version_patch=2,
};

CONSTANT_STRING(hardware_name,"step_dir_controller");

const size_t clock_frequency_mhz = 32;

CONSTANT_STRING(left_constant_string,"left");
CONSTANT_STRING(right_constant_string,"right");

// Pins

// Units
CONSTANT_STRING(position_units,"position_units");
CONSTANT_STRING(position_units_per_second_units,"position_units/s");
CONSTANT_STRING(position_units_per_second_per_second_units,"position_units/s/s");

// Properties
CONSTANT_STRING(channel_count_property_name,"channelCount");
const long channel_count_min = 1;

CONSTANT_STRING(steps_per_position_units_property_name,"stepsPerPositionUnits");
const long steps_per_position_units_min = 1;
const long steps_per_position_units_max = 1000000000;
const long steps_per_position_units_element_default = 1;

CONSTANT_STRING(velocity_max_property_name,"velocityMax");
const long velocity_max_min = 1;
const long velocity_max_max = 1000000;
const long velocity_max_element_default = 200000;

CONSTANT_STRING(velocity_min_property_name,"velocityMin");
const long velocity_min_min = 1;
const long velocity_min_max = 1000000;
const long velocity_min_element_default = 20000;

CONSTANT_STRING(acceleration_max_property_name,"accelerationMax");
const long acceleration_max_min = 1;
const long acceleration_max_max = 1000000;
const long acceleration_max_element_default = 200000;

CONSTANT_STRING(enable_polarity_property_name,"enablePolarity");
CONSTANT_STRING(polarity_high,"HIGH");
CONSTANT_STRING(polarity_low,"LOW");
modular_server::SubsetMemberType polarity_ptr_subset[POLARITY_SUBSET_LENGTH] =
{
  {.cs_ptr=&polarity_high},
  {.cs_ptr=&polarity_low},
};
const ConstantString * const enable_polarity_element_default = &polarity_high;

CONSTANT_STRING(step_polarity_inverted_property_name,"stepPolarityInverted");
const bool step_polarity_inverted_element_default = false;

CONSTANT_STRING(dir_polarity_inverted_property_name,"dirPolarityInverted");
const bool dir_polarity_inverted_element_default = false;

CONSTANT_STRING(switch_active_polarity_property_name,"switchActivePolarity");
const ConstantString * const switch_active_polarity_element_default = &polarity_low;

CONSTANT_STRING(left_switch_stop_enabled_property_name,"leftSwitchStopEnabled");
const bool left_switch_stop_enabled_element_default = false;

CONSTANT_STRING(right_switches_enabled_property_name,"rightSwitchesEnabled");
const bool right_switches_enabled_element_default = false;

CONSTANT_STRING(right_switch_stop_enabled_property_name,"rightSwitchStopEnabled");
const bool right_switch_stop_enabled_element_default = false;

CONSTANT_STRING(switch_soft_stop_enabled_property_name,"switchSoftStopEnabled");
const bool switch_soft_stop_enabled_element_default = false;

CONSTANT_STRING(home_velocity_property_name,"homeVelocity");
const long home_velocity_element_default = -50000;

// Parameters
CONSTANT_STRING(channel_parameter_name,"channel");
const long channel_min = 0;

CONSTANT_STRING(position_parameter_name,"position");

CONSTANT_STRING(velocity_parameter_name,"velocity");

// Functions
CONSTANT_STRING(reinitialize_function_name,"reinitialize");
CONSTANT_STRING(controllers_communicating_function_name,"controllersCommunicating");
CONSTANT_STRING(enable_function_name,"enable");
CONSTANT_STRING(disable_function_name,"disable");
CONSTANT_STRING(enable_all_function_name,"enableAll");
CONSTANT_STRING(disable_all_function_name,"disableAll");
CONSTANT_STRING(enabled_function_name,"enabled");
CONSTANT_STRING(move_by_function_name,"moveBy");
CONSTANT_STRING(move_to_function_name,"moveTo");
CONSTANT_STRING(move_at_function_name,"moveAt");
CONSTANT_STRING(move_softly_by_function_name,"moveSoftlyBy");
CONSTANT_STRING(move_softly_to_function_name,"moveSoftlyTo");
CONSTANT_STRING(stop_function_name,"stop");
CONSTANT_STRING(stop_all_function_name,"stopAll");
CONSTANT_STRING(zero_function_name,"zero");
CONSTANT_STRING(zero_all_function_name,"zeroAll");
CONSTANT_STRING(get_positions_function_name,"getPositions");
CONSTANT_STRING(get_target_positions_function_name,"getTargetPositions");
CONSTANT_STRING(at_target_positions_function_name,"atTargetPositions");
CONSTANT_STRING(get_velocity_upper_limits_function_name,"getVelocityUpperLimits");
CONSTANT_STRING(get_acceleration_upper_limits_function_name,"getAccelerationUpperLimits");
CONSTANT_STRING(get_acceleration_lower_limits_function_name,"getAccelerationLowerLimits");
CONSTANT_STRING(get_velocities_function_name,"getVelocities");
CONSTANT_STRING(get_target_velocities_function_name,"getTargetVelocities");
CONSTANT_STRING(at_target_velocities_function_name,"atTargetVelocities");
CONSTANT_STRING(switches_active_function_name,"switchesActive");
CONSTANT_STRING(home_function_name,"home");
CONSTANT_STRING(homing_function_name,"homing");
CONSTANT_STRING(homed_function_name,"homed");

// Callbacks

// Errors
}
}
