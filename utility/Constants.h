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
enum{PROPERTY_COUNT_MAX=2};
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=3};
enum{CALLBACK_COUNT_MAX=1};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern ConstantString hardware_name;
extern const modular_server::HardwareInfo hardware_info;

extern size_t step_half_period_us_max;

// Interrupts

// Units
// extern ConstantString ms_unit;

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *
extern ConstantString micro_steps_per_step_property_name;
extern const long micro_steps_per_step_min;
extern const long micro_steps_per_step_max;
extern const long micro_steps_per_step_default;

// extern ConstantString enable_polarity_high_property_name;
// extern const bool enable_polarity_high_default;

// Parameters

// Functions
extern ConstantString enable_function_name;
extern ConstantString disable_function_name;
extern ConstantString stop_function_name;

// Callbacks

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
