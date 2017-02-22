// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef STEP_DIR_CONTROLLER_CONSTANTS_H
#define STEP_DIR_CONTROLLER_CONSTANTS_H
#include "ConstantVariable.h"
#include "ModularServer.h"


namespace step_dir_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=4};
enum{PARAMETER_COUNT_MAX=3};
enum{FUNCTION_COUNT_MAX=15};
enum{CALLBACK_COUNT_MAX=1};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern ConstantString hardware_name;
extern const modular_server::HardwareInfo hardware_info;

extern const size_t clock_frequency_mhz;
extern const size_t channels_per_tmc429_count;

// Interrupts

// Units
extern ConstantString steps_unit;
extern ConstantString steps_per_second_unit;
extern ConstantString steps_per_second_per_second_unit;

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
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

// extern ConstantString enable_polarity_property_name;
// enum{POLARITY_SUBSET_LENGTH=2};
// extern ConstantString polarity_high;
// extern ConstantString polarity_low;
// extern modular_server::SubsetMemberType polarity_ptr_subset[POLARITY_SUBSET_LENGTH];

// extern ConstantString step_polarity_property_name;

// extern ConstantString dir_polarity_property_name;

// extern ConstantString mode_property_name;
// enum{MODE_SUBSET_LENGTH=4};
// extern ConstantString mode_ramp;
// extern ConstantString mode_soft;
// extern ConstantString mode_velocity;
// extern ConstantString mode_hold;
// extern modular_server::SubsetMemberType mode_ptr_subset[MODE_SUBSET_LENGTH];

// Parameters
extern ConstantString channel_parameter_name;
extern const long channel_min;
extern const long channel_max;

extern ConstantString position_parameter_name;

extern ConstantString velocity_parameter_name;
extern const long velocity_parameter_min;
extern const long velocity_parameter_max;

// Functions
// extern ConstantString enable_function_name;
// extern ConstantString disable_function_name;
// extern ConstantString enable_all_function_name;
// extern ConstantString disable_all_function_name;
// extern ConstantString enabled_function_name;
extern ConstantString move_by_function_name;
extern ConstantString move_to_function_name;
extern ConstantString move_at_function_name;
extern ConstantString move_by_at_function_name;
extern ConstantString move_to_at_function_name;
extern ConstantString stop_function_name;
extern ConstantString stop_all_function_name;
extern ConstantString zero_function_name;
extern ConstantString zero_all_function_name;
extern ConstantString get_positions_function_name;
extern ConstantString get_position_targets_function_name;
extern ConstantString get_velocities_function_name;
extern ConstantString get_velocity_targets_function_name;

// Callbacks

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
