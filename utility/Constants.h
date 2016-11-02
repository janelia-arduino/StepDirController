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

#include "EventController.h"


namespace step_dir_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{FIELD_COUNT_MAX=2};
enum{PARAMETER_COUNT_MAX=1};
enum{METHOD_COUNT_MAX=3};
enum{CALLBACK_COUNT_MAX=1};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern ConstantString hardware_name;
extern const modular_server::HardwareInfo hardware_info;

extern const size_t enable_pin;

// enum{EVENT_COUNT_MAX=8};
// enum{INDEXED_PULSES_COUNT_MAX=4};
// extern const int bad_index;

// struct PulseInfo
// {
//   uint32_t channels;
//   ConstantString * polarity_ptr;
//   EventIdPair event_id_pair;
// };

// Units
// extern ConstantString ms_unit;

// Fields
// Field values must be long, double, bool, long[], double[], bool[], char[], ConstantString *
extern ConstantString micro_steps_per_step_field_name;
extern const long micro_steps_per_step_min;
extern const long micro_steps_per_step_max;
extern const long micro_steps_per_step_default;

extern ConstantString enable_polarity_high_field_name;
extern const bool enable_polarity_high_default;

// Parameters

// Methods
extern ConstantString enable_method_name;
extern ConstantString disable_method_name;
extern ConstantString stop_method_name;

// Callbacks

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
