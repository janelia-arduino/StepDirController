// ----------------------------------------------------------------------------
// 3x2.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef STEP_DIR_CONTROLLER_3X2_CONSTANTS_H
#define STEP_DIR_CONTROLLER_3X2_CONSTANTS_H
#include "Constants.h"


#if defined(__MK20DX256__)

namespace step_dir_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{INTERRUPT_COUNT_MAX=1};

enum {CHANNEL_COUNT=1};

extern const size_t enable_pins[CHANNEL_COUNT];
extern const size_t step_pins[CHANNEL_COUNT];
extern const size_t dir_pins[CHANNEL_COUNT];

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
