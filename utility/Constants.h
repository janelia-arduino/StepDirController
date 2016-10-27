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
enum{PARAMETER_COUNT_MAX=8};
enum{METHOD_COUNT_MAX=12};
enum{CALLBACK_COUNT_MAX=1};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern ConstantString hardware_name;
extern const modular_server::HardwareInfo hardware_info;

enum{EVENT_COUNT_MAX=8};
enum{INDEXED_PULSES_COUNT_MAX=4};
extern const int bad_index;

struct PulseInfo
{
  uint32_t channels;
  ConstantString * polarity_ptr;
  EventIdPair event_id_pair;
};

// Units
extern ConstantString ms_unit;

// Fields
// Field values must be long, double, bool, long[], double[], bool[], char[], ConstantString *
extern ConstantString polarity_reversed_field_name;

extern ConstantString channels_enabled_field_name;

// Parameters
extern ConstantString channel_parameter_name;

extern ConstantString channels_parameter_name;

extern ConstantString polarity_parameter_name;
enum{POLARITY_SUBSET_LENGTH=2};
extern ConstantString polarity_positive;
extern ConstantString polarity_negative;
extern modular_server::SubsetMemberType polarity_ptr_subset[POLARITY_SUBSET_LENGTH];

extern ConstantString delay_parameter_name;
extern const long delay_min;
extern const long delay_max;

extern ConstantString period_parameter_name;
extern const long period_min;
extern const long period_max;

extern ConstantString on_duration_parameter_name;
extern const long on_duration_min;
extern const long on_duration_max;

extern ConstantString count_parameter_name;
extern const long count_min;
extern const long count_max;

extern ConstantString pwm_index_parameter_name;

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
extern ConstantString pwm_error;
}
}
#include "5x3.h"
#include "3x2.h"
#endif
