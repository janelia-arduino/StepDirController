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
enum{FIELD_COUNT_MAX=1};
enum{PARAMETER_COUNT_MAX=1};
enum{METHOD_COUNT_MAX=12};
enum{CALLBACK_COUNT_MAX=1};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern ConstantString hardware_name;
extern const modular_server::HardwareInfo hardware_info;

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
extern ConstantString polarity_reversed_field_name;

// Parameters

// Methods
extern ConstantString set_channel_on_method_name;
extern ConstantString set_channel_off_method_name;
extern ConstantString set_channels_on_method_name;
extern ConstantString set_channels_off_method_name;
extern ConstantString set_all_channels_on_method_name;
extern ConstantString set_all_channels_off_method_name;
extern ConstantString add_pwm_method_name;
extern ConstantString start_pwm_method_name;
extern ConstantString add_toggle_pwm_method_name;
extern ConstantString start_toggle_pwm_method_name;
extern ConstantString stop_pwm_method_name;
extern ConstantString stop_all_pwm_method_name;

// Callbacks

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
