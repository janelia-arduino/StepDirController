// ----------------------------------------------------------------------------
// TEENSY40.cpp
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#include "TEENSY40.h"


#if defined(__IMXRT1062__) && defined(ARDUINO_TEENSY40)
namespace step_dir_controller
{
namespace constants
{
const modular_server::HardwareInfo hardware_info =
{
  .name_ptr=&hardware_name,
  .part_number=1245,
  .version_major=1,
  .version_minor=0,
};

const size_t chip_select_pins[CONTROLLER_COUNT_MAX] =
{
  10,
};

const size_t enable_pins[CHANNEL_COUNT_MAX] =
{
  33,
  34,
  35,
};

// Pins

// Units

// Properties
const long channel_count_default = CHANNEL_COUNT_MAX;

const long steps_per_position_units_default[CHANNEL_COUNT_MAX] =
{
  steps_per_position_units_element_default,
  steps_per_position_units_element_default,
  steps_per_position_units_element_default,
};

const long velocity_max_default[CHANNEL_COUNT_MAX] =
{
  velocity_max_element_default,
  velocity_max_element_default,
  velocity_max_element_default,
};

const long velocity_min_default[CHANNEL_COUNT_MAX] =
{
  velocity_min_element_default,
  velocity_min_element_default,
  velocity_min_element_default,
};

const long acceleration_max_default[CHANNEL_COUNT_MAX] =
{
  acceleration_max_element_default,
  acceleration_max_element_default,
  acceleration_max_element_default,
};

const ConstantString * const enable_polarity_default[CHANNEL_COUNT_MAX] =
{
  enable_polarity_element_default,
  enable_polarity_element_default,
  enable_polarity_element_default,
};

const bool step_polarity_inverted_default[CONTROLLER_COUNT_MAX] =
{
  step_polarity_inverted_element_default,
};

const bool dir_polarity_inverted_default[CONTROLLER_COUNT_MAX] =
{
  dir_polarity_inverted_element_default,
};

const ConstantString * const switch_active_polarity_default[CONTROLLER_COUNT_MAX] =
{
  switch_active_polarity_element_default,
};

const bool right_switches_enabled_default[CONTROLLER_COUNT_MAX] =
{
  right_switches_enabled_element_default,
};

const bool left_switch_stop_enabled_default[CHANNEL_COUNT_MAX] =
{
  left_switch_stop_enabled_element_default,
  left_switch_stop_enabled_element_default,
  left_switch_stop_enabled_element_default,
};

const bool right_switch_stop_enabled_default[CHANNEL_COUNT_MAX] =
{
  right_switch_stop_enabled_element_default,
  right_switch_stop_enabled_element_default,
  right_switch_stop_enabled_element_default,
};

const bool switch_soft_stop_enabled_default[CHANNEL_COUNT_MAX] =
{
  switch_soft_stop_enabled_element_default,
  switch_soft_stop_enabled_element_default,
  switch_soft_stop_enabled_element_default,
};

const long home_velocity_default[CHANNEL_COUNT_MAX] =
{
  home_velocity_element_default,
  home_velocity_element_default,
  home_velocity_element_default,
};

// Parameters

// Functions

// Callbacks

// Errors
}
}

#endif
