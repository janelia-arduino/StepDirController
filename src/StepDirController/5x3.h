// ----------------------------------------------------------------------------
// 5x3.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef STEP_DIR_CONTROLLER_5X3_CONSTANTS_H
#define STEP_DIR_CONTROLLER_5X3_CONSTANTS_H
#include "Constants.h"


#if defined(__MK64FX512__)

namespace step_dir_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PIN_COUNT_MAX=1};

enum {CONTROLLER_COUNT_MAX=2};
// CHANNEL_COUNT_MAX = CONTROLLER_COUNT_MAX*CHANNELS_PER_CONTROLLER_COUNT
// CHANNELS_PER_CONTROLLER_COUNT = 3
enum {CHANNEL_COUNT_MAX=6};

extern const size_t cs_pins[CONTROLLER_COUNT_MAX];
extern const size_t enable_pins[CHANNEL_COUNT_MAX];

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const long steps_per_position_units_default[CHANNEL_COUNT_MAX];

extern const long velocity_max_default[CHANNEL_COUNT_MAX];

extern const long velocity_min_default[CHANNEL_COUNT_MAX];

extern const long acceleration_max_default[CHANNEL_COUNT_MAX];

extern const ConstantString * const enable_polarity_default[CHANNEL_COUNT_MAX];

extern const bool left_switch_stop_enabled_default[CHANNEL_COUNT_MAX];

extern const bool right_switch_stop_enabled_default[CHANNEL_COUNT_MAX];

extern const bool switch_soft_stop_enabled_default[CHANNEL_COUNT_MAX];

extern const long home_velocity_default[CHANNEL_COUNT_MAX];

// Parameters

// Functions

// Callbacks

// Errors
}
}

#endif
#endif
