// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#ifndef STEP_DIR_CONTROLLER_CONSTANTS_H
#define STEP_DIR_CONTROLLER_CONSTANTS_H
#include <ConstantVariable.h>
#include <ModularServer.h>


namespace step_dir_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=14};
enum{PARAMETER_COUNT_MAX=3};
enum{FUNCTION_COUNT_MAX=29};
enum{CALLBACK_COUNT_MAX=1};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern ConstantString hardware_name;
extern const modular_server::HardwareInfo hardware_info;

enum{CHANNELS_PER_CONTROLLER_COUNT=3};

extern const size_t clock_frequency_mhz;

extern ConstantString left_constant_string;
extern ConstantString right_constant_string;

// Pins

// Units
extern ConstantString position_units;
extern ConstantString position_units_per_second_units;
extern ConstantString position_units_per_second_per_second_units;

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern ConstantString channel_count_property_name;
extern const long channel_count_min;
extern const long channel_count_default;

extern ConstantString steps_per_position_units_property_name;
extern const long steps_per_position_units_min;
extern const long steps_per_position_units_max;
extern const long steps_per_position_units_element_default;

extern ConstantString velocity_max_property_name;
extern const long velocity_max_min;
extern const long velocity_max_max;
extern const long velocity_max_element_default;

extern ConstantString velocity_min_property_name;
extern const long velocity_min_min;
extern const long velocity_min_max;
extern const long velocity_min_element_default;

extern ConstantString acceleration_max_property_name;
extern const long acceleration_max_min;
extern const long acceleration_max_max;
extern const long acceleration_max_element_default;

extern ConstantString enable_polarity_property_name;
enum{POLARITY_SUBSET_LENGTH=2};
extern ConstantString polarity_high;
extern ConstantString polarity_low;
extern modular_server::SubsetMemberType polarity_ptr_subset[POLARITY_SUBSET_LENGTH];
extern const ConstantString * const enable_polarity_element_default;

extern ConstantString step_polarity_inverted_property_name;
extern const bool step_polarity_inverted_element_default;

extern ConstantString dir_polarity_inverted_property_name;
extern const bool dir_polarity_inverted_element_default;

extern ConstantString switch_active_polarity_property_name;
extern const ConstantString * const switch_active_polarity_element_default;

extern ConstantString left_switch_stop_enabled_property_name;
extern const bool left_switch_stop_enabled_element_default;

extern ConstantString right_switches_enabled_property_name;
extern const bool right_switches_enabled_element_default;

extern ConstantString right_switch_stop_enabled_property_name;
extern const bool right_switch_stop_enabled_element_default;

extern ConstantString switch_soft_stop_enabled_property_name;
extern const bool switch_soft_stop_enabled_element_default;

extern ConstantString home_velocity_property_name;
extern const long home_velocity_element_default;

// Parameters
extern ConstantString channel_parameter_name;
extern const long channel_min;

extern ConstantString position_parameter_name;

extern ConstantString velocity_parameter_name;

// Functions
extern ConstantString reinitialize_function_name;
extern ConstantString controllers_communicating_function_name;
extern ConstantString enable_function_name;
extern ConstantString disable_function_name;
extern ConstantString enable_all_function_name;
extern ConstantString disable_all_function_name;
extern ConstantString enabled_function_name;
extern ConstantString move_by_function_name;
extern ConstantString move_to_function_name;
extern ConstantString move_at_function_name;
extern ConstantString move_softly_by_function_name;
extern ConstantString move_softly_to_function_name;
extern ConstantString stop_function_name;
extern ConstantString stop_all_function_name;
extern ConstantString zero_function_name;
extern ConstantString zero_all_function_name;
extern ConstantString get_positions_function_name;
extern ConstantString get_target_positions_function_name;
extern ConstantString at_target_positions_function_name;
extern ConstantString get_velocities_function_name;
extern ConstantString get_target_velocities_function_name;
extern ConstantString at_target_velocities_function_name;
extern ConstantString get_velocity_upper_limits_function_name;
extern ConstantString get_acceleration_upper_limits_function_name;
extern ConstantString get_acceleration_lower_limits_function_name;
extern ConstantString switches_active_function_name;
extern ConstantString home_function_name;
extern ConstantString homing_function_name;
extern ConstantString homed_function_name;

// Callbacks

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
