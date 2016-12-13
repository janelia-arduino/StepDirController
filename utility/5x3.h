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
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{INTERRUPT_COUNT_MAX=2};

enum {CHANNEL_COUNT=1};

extern const size_t enable_pins[CHANNEL_COUNT];
extern const size_t step_pins[CHANNEL_COUNT];
extern const size_t dir_pins[CHANNEL_COUNT];

// Interrupts
// extern ConstantString bnc_b_interrupt_name;
// extern const size_t bnc_b_pin;

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *
extern const ConstantString * const enable_polarity_ptrs_default[CHANNEL_COUNT];

extern const ConstantString * const enable_polarity_ptrs_default[CHANNEL_COUNT];

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
