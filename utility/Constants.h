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

// #include "EventController.h"


namespace step_dir_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=3};
enum{PARAMETER_COUNT_MAX=3};
enum{FUNCTION_COUNT_MAX=15};
enum{CALLBACK_COUNT_MAX=1};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern ConstantString hardware_name;
extern const modular_server::HardwareInfo hardware_info;

extern size_t step_half_period_us_max;

extern ConstantString mode_position;
extern ConstantString mode_velocity;

// Interrupts

// Units
extern ConstantString steps_unit;
extern ConstantString steps_per_second_unit;

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern ConstantString enable_polarity_property_name;
enum{POLARITY_SUBSET_LENGTH=2};
extern ConstantString polarity_high;
extern ConstantString polarity_low;
extern modular_server::SubsetMemberType polarity_ptr_subset[POLARITY_SUBSET_LENGTH];

extern ConstantString step_polarity_property_name;

extern ConstantString dir_polarity_property_name;

// extern ConstantString mode_property_name;
// enum{MODE_SUBSET_LENGTH=2};
// extern ConstantString mode_position;
// extern ConstantString mode_velocity;
// extern modular_server::SubsetMemberType mode_ptr_subset[MODE_SUBSET_LENGTH];

// Parameters
extern ConstantString channel_parameter_name;

extern ConstantString position_parameter_name;

extern ConstantString velocity_parameter_name;
extern const long velocity_min;
extern const long velocity_max;

// Functions
extern ConstantString enable_function_name;
extern ConstantString disable_function_name;
extern ConstantString enable_all_function_name;
extern ConstantString disable_all_function_name;
extern ConstantString enabled_function_name;
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

// Callbacks

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
