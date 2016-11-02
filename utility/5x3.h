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


#if defined(__AVR_ATmega2560__)

namespace step_dir_controller
{
namespace constants
{
enum {MOTOR_COUNT=1};

extern const size_t step_pins[MOTOR_COUNT];
extern const size_t dir_pins[MOTOR_COUNT];

// Units

// Fields
// Field values must be long, double, bool, long[], double[], bool[], char[], ConstantString *

// Parameters

// Methods

// Callbacks

// Errors
}
}
#endif
#endif
