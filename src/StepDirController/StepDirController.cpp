// ----------------------------------------------------------------------------
// StepDirController.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "../StepDirController.h"


using namespace step_dir_controller;

StepDirController::StepDirController()
{
}

StepDirController::~StepDirController()
{
  // disable();
}

void StepDirController::setup()
{
  // Parent Setup
  ModularDeviceBase::setup();

  // Reset Watchdog
  resetWatchdog();

  // Variable Setup

  // Controller Setup
  for (size_t controller_index=0; controller_index<constants::CONTROLLER_COUNT_MAX; ++controller_index)
  {
    Controller & controller = controllers_[controller_index];
    controller.setup(getControllerChipSelectPin(controller_index),constants::clock_frequency_mhz);
  }

  // Pin Setup
  for (size_t channel=0; channel<constants::CHANNEL_COUNT_MAX; ++channel)
  {
    pinMode(getEnablePin(channel),OUTPUT);
    enabled_[channel] = false;
    pre_homing_[channel] = false;
    homing_[channel] = false;
    homed_[channel] = false;
  }

  // Pins

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware
  modular_server_.addHardware(constants::hardware_info,
    pins_);

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
    properties_,
    parameters_,
    functions_,
    callbacks_);

  // Properties
  modular_server::Property & channel_count_property = modular_server_.createProperty(constants::channel_count_property_name,constants::channel_count_default);
  channel_count_property.setRange(constants::channel_count_min,constants::CHANNEL_COUNT_MAX);
  channel_count_property.attachPostSetValueFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::setChannelCountHandler));

  modular_server::Property & steps_per_position_units_property = modular_server_.createProperty(constants::steps_per_position_units_property_name,constants::steps_per_position_units_default);
  steps_per_position_units_property.setRange(constants::steps_per_position_units_min,constants::steps_per_position_units_max);
  steps_per_position_units_property.attachPreSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&StepDirController::preUpdateScaledPropertiesHandler));
  steps_per_position_units_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&StepDirController::postUpdateScaledPropertiesHandler));

  modular_server::Property & velocity_max_property = modular_server_.createProperty(constants::velocity_max_property_name,constants::velocity_max_default);
  velocity_max_property.setUnits(constants::position_units_per_second_units);
  velocity_max_property.setRange(constants::velocity_max_min,constants::velocity_max_max);
  velocity_max_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&StepDirController::setLimitsHandler));

  modular_server::Property & velocity_min_property = modular_server_.createProperty(constants::velocity_min_property_name,constants::velocity_min_default);
  velocity_min_property.setUnits(constants::position_units_per_second_units);
  velocity_min_property.setRange(constants::velocity_min_min,constants::velocity_min_max);
  velocity_min_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&StepDirController::setLimitsHandler));

  modular_server::Property & acceleration_max_property = modular_server_.createProperty(constants::acceleration_max_property_name,constants::acceleration_max_default);
  acceleration_max_property.setUnits(constants::position_units_per_second_per_second_units);
  acceleration_max_property.setRange(constants::acceleration_max_min,constants::acceleration_max_max);
  acceleration_max_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&StepDirController::setLimitsHandler));

  modular_server::Property & enable_polarity_property = modular_server_.createProperty(constants::enable_polarity_property_name,constants::enable_polarity_default);
  enable_polarity_property.setSubset(constants::polarity_ptr_subset);

  modular_server::Property & step_polarity_inverted_property = modular_server_.createProperty(constants::step_polarity_inverted_property_name,constants::step_polarity_inverted_default);
  step_polarity_inverted_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&StepDirController::setStepPolarityInvertedHandler));

  modular_server::Property & dir_polarity_inverted_property = modular_server_.createProperty(constants::dir_polarity_inverted_property_name,constants::dir_polarity_inverted_default);
  dir_polarity_inverted_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&StepDirController::setDirPolarityInvertedHandler));

  modular_server::Property & switch_active_polarity_property = modular_server_.createProperty(constants::switch_active_polarity_property_name,constants::switch_active_polarity_default);
  switch_active_polarity_property.setSubset(constants::polarity_ptr_subset);
  switch_active_polarity_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&StepDirController::setSwitchActivePolarityHandler));

  modular_server::Property & left_switch_stop_enabled_property = modular_server_.createProperty(constants::left_switch_stop_enabled_property_name,constants::left_switch_stop_enabled_default);
  left_switch_stop_enabled_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&StepDirController::setLeftSwitchStopEnabledHandler));

  modular_server::Property & right_switches_enabled_property = modular_server_.createProperty(constants::right_switches_enabled_property_name,constants::right_switches_enabled_default);
  right_switches_enabled_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&StepDirController::setRightSwitchesEnabledHandler));

  modular_server::Property & right_switch_stop_enabled_property = modular_server_.createProperty(constants::right_switch_stop_enabled_property_name,constants::right_switch_stop_enabled_default);
  right_switch_stop_enabled_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&StepDirController::setRightSwitchStopEnabledHandler));

  modular_server::Property & switch_soft_stop_enabled_property = modular_server_.createProperty(constants::switch_soft_stop_enabled_property_name,constants::switch_soft_stop_enabled_default);
  switch_soft_stop_enabled_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&StepDirController::setSwitchSoftStopEnabledHandler));

  modular_server::Property & home_velocity_property = modular_server_.createProperty(constants::home_velocity_property_name,constants::home_velocity_default);
  home_velocity_property.setUnits(constants::position_units_per_second_units);
  home_velocity_property.setRange(-constants::velocity_max_max,constants::velocity_max_max);

  // Parameters
  modular_server::Parameter & channel_parameter = modular_server_.createParameter(constants::channel_parameter_name);
  channel_parameter.setTypeLong();

  modular_server::Parameter & position_parameter = modular_server_.createParameter(constants::position_parameter_name);
  position_parameter.setUnits(constants::position_units);
  position_parameter.setTypeLong();

  modular_server::Parameter & velocity_parameter = modular_server_.createParameter(constants::velocity_parameter_name);
  velocity_parameter.setUnits(constants::position_units_per_second_units);
  velocity_parameter.setTypeLong();

  setChannelCountHandler();
  reinitialize();

  // Functions
  modular_server::Function & reinitialize_function = modular_server_.createFunction(constants::reinitialize_function_name);
  reinitialize_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::reinitializeHandler));

  modular_server::Function & controllers_communicating_function = modular_server_.createFunction(constants::controllers_communicating_function_name);
  controllers_communicating_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::controllersCommunicatingHandler));
  controllers_communicating_function.setResultTypeArray();
  controllers_communicating_function.setResultTypeBool();

  modular_server::Function & enable_function = modular_server_.createFunction(constants::enable_function_name);
  enable_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::enableHandler));
  enable_function.addParameter(channel_parameter);

  modular_server::Function & disable_function = modular_server_.createFunction(constants::disable_function_name);
  disable_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::disableHandler));
  disable_function.addParameter(channel_parameter);

  modular_server::Function & enable_all_function = modular_server_.createFunction(constants::enable_all_function_name);
  enable_all_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::enableAllHandler));

  modular_server::Function & disable_all_function = modular_server_.createFunction(constants::disable_all_function_name);
  disable_all_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::disableAllHandler));

  modular_server::Function & enabled_function = modular_server_.createFunction(constants::enabled_function_name);
  enabled_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::enabledHandler));
  enabled_function.setResultTypeArray();
  enabled_function.setResultTypeBool();

  modular_server::Function & move_by_function = modular_server_.createFunction(constants::move_by_function_name);
  move_by_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::moveByHandler));
  move_by_function.addParameter(channel_parameter);
  move_by_function.addParameter(position_parameter);

  modular_server::Function & move_to_function = modular_server_.createFunction(constants::move_to_function_name);
  move_to_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::moveToHandler));
  move_to_function.addParameter(channel_parameter);
  move_to_function.addParameter(position_parameter);

  modular_server::Function & move_at_function = modular_server_.createFunction(constants::move_at_function_name);
  move_at_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::moveAtHandler));
  move_at_function.addParameter(channel_parameter);
  move_at_function.addParameter(velocity_parameter);

  modular_server::Function & move_softly_by_function = modular_server_.createFunction(constants::move_softly_by_function_name);
  move_softly_by_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::moveSoftlyByHandler));
  move_softly_by_function.addParameter(channel_parameter);
  move_softly_by_function.addParameter(position_parameter);

  modular_server::Function & move_softly_to_function = modular_server_.createFunction(constants::move_softly_to_function_name);
  move_softly_to_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::moveSoftlyToHandler));
  move_softly_to_function.addParameter(channel_parameter);
  move_softly_to_function.addParameter(position_parameter);

  modular_server::Function & stop_function = modular_server_.createFunction(constants::stop_function_name);
  stop_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::stopHandler));
  stop_function.addParameter(channel_parameter);

  modular_server::Function & stop_all_function = modular_server_.createFunction(constants::stop_all_function_name);
  stop_all_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::stopAllHandler));

  modular_server::Function & zero_function = modular_server_.createFunction(constants::zero_function_name);
  zero_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::zeroHandler));
  zero_function.addParameter(channel_parameter);

  modular_server::Function & zero_all_function = modular_server_.createFunction(constants::zero_all_function_name);
  zero_all_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::zeroAllHandler));

  modular_server::Function & get_positions_function = modular_server_.createFunction(constants::get_positions_function_name);
  get_positions_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::getPositionsHandler));
  get_positions_function.setResultUnits(constants::position_units);
  get_positions_function.setResultTypeArray();
  get_positions_function.setResultTypeLong();

  modular_server::Function & get_target_positions_function = modular_server_.createFunction(constants::get_target_positions_function_name);
  get_target_positions_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::getTargetPositionsHandler));
  get_target_positions_function.setResultUnits(constants::position_units);
  get_target_positions_function.setResultTypeArray();
  get_target_positions_function.setResultTypeLong();

  modular_server::Function & at_target_positions_function = modular_server_.createFunction(constants::at_target_positions_function_name);
  at_target_positions_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::atTargetPositionsHandler));
  at_target_positions_function.setResultTypeArray();
  at_target_positions_function.setResultTypeBool();

  modular_server::Function & get_velocities_function = modular_server_.createFunction(constants::get_velocities_function_name);
  get_velocities_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::getVelocitiesHandler));
  get_velocities_function.setResultUnits(constants::position_units_per_second_units);
  get_velocities_function.setResultTypeArray();
  get_velocities_function.setResultTypeLong();

  modular_server::Function & get_target_velocities_function = modular_server_.createFunction(constants::get_target_velocities_function_name);
  get_target_velocities_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::getTargetVelocitiesHandler));
  get_target_velocities_function.setResultUnits(constants::position_units_per_second_units);
  get_target_velocities_function.setResultTypeArray();
  get_target_velocities_function.setResultTypeBool();

  modular_server::Function & at_target_velocities_function = modular_server_.createFunction(constants::at_target_velocities_function_name);
  at_target_velocities_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::atTargetVelocitiesHandler));
  at_target_velocities_function.setResultTypeArray();
  at_target_velocities_function.setResultTypeBool();

  modular_server::Function & get_velocity_upper_limits_function = modular_server_.createFunction(constants::get_velocity_upper_limits_function_name);
  get_velocity_upper_limits_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::getVelocityUpperLimitsHandler));
  get_velocity_upper_limits_function.setResultUnits(constants::position_units_per_second_units);
  get_velocity_upper_limits_function.setResultTypeArray();
  get_velocity_upper_limits_function.setResultTypeLong();

  modular_server::Function & get_acceleration_upper_limits_function = modular_server_.createFunction(constants::get_acceleration_upper_limits_function_name);
  get_acceleration_upper_limits_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::getAccelerationUpperLimitsHandler));
  get_acceleration_upper_limits_function.addParameter(velocity_parameter);
  get_acceleration_upper_limits_function.setResultUnits(constants::position_units_per_second_per_second_units);
  get_acceleration_upper_limits_function.setResultTypeArray();
  get_acceleration_upper_limits_function.setResultTypeLong();

  modular_server::Function & get_acceleration_lower_limits_function = modular_server_.createFunction(constants::get_acceleration_lower_limits_function_name);
  get_acceleration_lower_limits_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::getAccelerationLowerLimitsHandler));
  get_acceleration_lower_limits_function.addParameter(velocity_parameter);
  get_acceleration_lower_limits_function.setResultUnits(constants::position_units_per_second_per_second_units);
  get_acceleration_lower_limits_function.setResultTypeArray();
  get_acceleration_lower_limits_function.setResultTypeLong();

  modular_server::Function & switches_active_function = modular_server_.createFunction(constants::switches_active_function_name);
  switches_active_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::switchesActiveHandler));
  switches_active_function.setResultTypeArray();
  switches_active_function.setResultTypeBool();

  modular_server::Function & home_function = modular_server_.createFunction(constants::home_function_name);
  home_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::homeHandler));
  home_function.addParameter(channel_parameter);
  home_function.setResultTypeBool();

  modular_server::Function & homing_function = modular_server_.createFunction(constants::homing_function_name);
  homing_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::homingHandler));
  homing_function.setResultTypeArray();
  homing_function.setResultTypeBool();

  modular_server::Function & homed_function = modular_server_.createFunction(constants::homed_function_name);
  homed_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&StepDirController::homedHandler));
  homed_function.setResultTypeArray();
  homed_function.setResultTypeBool();

  // Callbacks

}

void StepDirController::update()
{
  // Parent Update
  ModularDeviceBase::update();

  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    if (pre_homing_[channel])
    {
      if (!homeSwitchActive(channel))
      {
        stop(channel);
        pre_homing_[channel] = false;
        home(channel);
        return;
      }
    }
    if (homing_[channel])
    {
      size_t controller_index = channelToControllerIndex(channel);
      size_t motor_index = channelToMotorIndex(channel);
      Controller & controller = controllers_[controller_index];
      bool latch_position_waiting = controller.latchPositionWaiting(motor_index);
      if (!latch_position_waiting)
      {
        stop(channel);
        homing_[channel] = false;
        homed_[channel] = true;
        zero(channel);
        homedHandler(channel);
      }
    }
  }
}

void StepDirController::reinitialize()
{
  for (size_t controller_index=0; controller_index<getControllerCount(); ++controller_index)
  {
    Controller & controller = controllers_[controller_index];
    controller.initialize();
    setStepPolarityInvertedHandler(controller_index);
    setDirPolarityInvertedHandler(controller_index);
    setSwitchActivePolarityHandler(controller_index);
    setRightSwitchesEnabledHandler(controller_index);
  }
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    setLeftSwitchStopEnabledHandler(channel);
    setRightSwitchStopEnabledHandler(channel);
    setSwitchSoftStopEnabledHandler(channel);
    setLimitsHandler(channel);
  }
  enableAll();
}

size_t StepDirController::getChannelCount()
{
  long channel_count;
  modular_server_.property(constants::channel_count_property_name).getValue(channel_count);

  return channel_count;
}

size_t StepDirController::getControllerCount()
{
  size_t channel_count = getChannelCount();
  size_t controller_count = channel_count / constants::CHANNELS_PER_CONTROLLER_COUNT;
  if ((channel_count % constants::CHANNELS_PER_CONTROLLER_COUNT) != 0)
  {
    ++controller_count;
  }
  return controller_count;
}

void StepDirController::enable(size_t channel)
{
  if (channel >= getChannelCount())
  {
    return;
  }
  const ConstantString * polarity_ptr;
  modular_server_.property(constants::enable_polarity_property_name).getElementValue(channel,polarity_ptr);
  if (polarity_ptr == &constants::polarity_high)
  {
    digitalWrite(getEnablePin(channel),HIGH);
  }
  else
  {
    digitalWrite(getEnablePin(channel),LOW);
  }
  enabled_[channel] = true;
}

void StepDirController::disable(size_t channel)
{
  if (channel >= getChannelCount())
  {
    return;
  }
  stop(channel);
  const ConstantString * polarity_ptr;
  modular_server_.property(constants::enable_polarity_property_name).getElementValue(channel,polarity_ptr);
  if (polarity_ptr == &constants::polarity_high)
  {
    digitalWrite(getEnablePin(channel),LOW);
  }
  else
  {
    digitalWrite(getEnablePin(channel),HIGH);
  }
  enabled_[channel] = false;
}

void StepDirController::enableAll()
{
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    enable(channel);
  }
}

void StepDirController::disableAll()
{
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    disable(channel);
  }
}

uint32_t StepDirController::enabled()
{
  uint32_t channels_enabled = 0;
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    bool channel_enabled = enabled_[channel];
    if (channel_enabled)
    {
      channels_enabled |= 1 << channel;
    }
  }
  return channels_enabled;
}

void StepDirController::moveBy(size_t channel,
  long position)
{
  if (channel >= getChannelCount())
  {
    return;
  }
  size_t controller_index = channelToControllerIndex(channel);
  size_t motor_index = channelToMotorIndex(channel);
  Controller & controller = controllers_[controller_index];
  controller.setRampMode(motor_index);
  long position_actual = controller.getActualPosition(motor_index);
  long position_target = positionUnitsToSteps(channel,position) + position_actual;
  controller.setTargetPosition(motor_index,position_target);
  homing_[channel] = false;
}

void StepDirController::moveTo(size_t channel,
  long position)
{
  if (channel >= getChannelCount())
  {
    return;
  }
  size_t controller_index = channelToControllerIndex(channel);
  size_t motor_index = channelToMotorIndex(channel);
  Controller & controller = controllers_[controller_index];
  controller.setRampMode(motor_index);
  controller.setTargetPosition(motor_index,positionUnitsToSteps(channel,position));
  homing_[channel] = false;
}

void StepDirController::moveAt(size_t channel,
  long velocity)
{
  if (channel >= getChannelCount())
  {
    return;
  }
  size_t controller_index = channelToControllerIndex(channel);
  size_t motor_index = channelToMotorIndex(channel);
  Controller & controller = controllers_[controller_index];
  controller.setVelocityMode(motor_index);
  controller.setTargetVelocityInHz(motor_index,positionUnitsToSteps(channel,velocity));
  homing_[channel] = false;
}

void StepDirController::moveSoftlyBy(size_t channel,
  long position)
{
  if (channel >= getChannelCount())
  {
    return;
  }
  size_t controller_index = channelToControllerIndex(channel);
  size_t motor_index = channelToMotorIndex(channel);
  Controller & controller = controllers_[controller_index];
  controller.setSoftMode(motor_index);
  long position_actual = controller.getActualPosition(motor_index);
  long position_target = positionUnitsToSteps(channel,position) + position_actual;
  controller.setTargetPosition(motor_index,position_target);
  homing_[channel] = false;
}

void StepDirController::moveSoftlyTo(size_t channel,
  long position)
{
  if (channel >= getChannelCount())
  {
    return;
  }
  size_t controller_index = channelToControllerIndex(channel);
  size_t motor_index = channelToMotorIndex(channel);
  Controller & controller = controllers_[controller_index];
  controller.setSoftMode(motor_index);
  controller.setTargetPosition(motor_index,positionUnitsToSteps(channel,position));
  homing_[channel] = false;
}

void StepDirController::stop(size_t channel)
{
  if (channel >= getChannelCount())
  {
    return;
  }
  size_t controller_index = channelToControllerIndex(channel);
  size_t motor_index = channelToMotorIndex(channel);
  Controller & controller = controllers_[controller_index];
  controller.stop(motor_index);
  homing_[channel] = false;
}

void StepDirController::stopAll()
{
  for (size_t controller_index=0; controller_index<getControllerCount(); ++controller_index)
  {
    Controller & controller = controllers_[controller_index];
    controller.stopAll();
  }
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    homing_[channel] = false;
  }
}

void StepDirController::zero(size_t channel)
{
  if (channel >= getChannelCount())
  {
    return;
  }
  size_t controller_index = channelToControllerIndex(channel);
  size_t motor_index = channelToMotorIndex(channel);
  Controller & controller = controllers_[controller_index];
  controller.setVelocityMode(motor_index);
  controller.setActualPosition(motor_index,0);
  controller.setTargetPosition(motor_index,0);
}

void StepDirController::zeroAll()
{
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    zero(channel);
  }
}

long StepDirController::getPosition(size_t channel)
{
  long position = 0;
  if (channel >= getChannelCount())
  {
    return position;
  }
  position = getPositionInSteps(channel);
  return stepsToPositionUnits(channel,position);
}

long StepDirController::getTargetPosition(size_t channel)
{
  long position = 0;
  if (channel >= getChannelCount())
  {
    return position;
  }
  size_t controller_index = channelToControllerIndex(channel);
  size_t motor_index = channelToMotorIndex(channel);
  Controller & controller = controllers_[controller_index];
  position = controller.getTargetPosition(motor_index);
  return stepsToPositionUnits(channel,position);
}

bool StepDirController::atTargetPosition(size_t channel)
{
  bool at_target_position = true;
  if (channel >= getChannelCount())
  {
    return at_target_position;
  }
  size_t controller_index = channelToControllerIndex(channel);
  size_t motor_index = channelToMotorIndex(channel);
  Controller & controller = controllers_[controller_index];
  at_target_position = controller.atTargetPosition(motor_index);
  return at_target_position;
}

long StepDirController::getVelocity(size_t channel)
{
  long velocity = 0;
  if (channel >= getChannelCount())
  {
    return velocity;
  }
  velocity = getVelocityInHz(channel);
  return stepsToPositionUnits(channel,velocity);
}

long StepDirController::getTargetVelocity(size_t channel)
{
  long velocity = 0;
  if (channel >= getChannelCount())
  {
    return velocity;
  }
  size_t controller_index = channelToControllerIndex(channel);
  size_t motor_index = channelToMotorIndex(channel);
  Controller & controller = controllers_[controller_index];
  velocity = controller.getTargetVelocityInHz(motor_index);
  return stepsToPositionUnits(channel,velocity);
}

bool StepDirController::atTargetVelocity(size_t channel)
{
  bool at_target_velocity = true;
  if (channel >= getChannelCount())
  {
    return at_target_velocity;
  }
  size_t controller_index = channelToControllerIndex(channel);
  size_t motor_index = channelToMotorIndex(channel);
  Controller & controller = controllers_[controller_index];
  at_target_velocity = controller.atTargetVelocity(motor_index);
  return at_target_velocity;
}

long StepDirController::getVelocityUpperLimit(size_t channel)
{
  long velocity_upper_limit = 0;
  if (channel >= getChannelCount())
  {
    return velocity_upper_limit;
  }
  size_t controller_index = channelToControllerIndex(channel);
  Controller & controller = controllers_[controller_index];
  velocity_upper_limit = controller.getVelocityMaxUpperLimitInHz();
  return stepsToPositionUnits(channel,velocity_upper_limit);
}

long StepDirController::getAccelerationUpperLimit(size_t channel,
  long velocity_max)
{
  long acceleration_upper_limit = 0;
  if (channel >= getChannelCount())
  {
    return acceleration_upper_limit;
  }
  size_t controller_index = channelToControllerIndex(channel);
  Controller & controller = controllers_[controller_index];
  velocity_max = positionUnitsToSteps(channel,abs(velocity_max));
  acceleration_upper_limit = controller.getAccelerationMaxUpperLimitInHzPerS(velocity_max);
  return stepsToPositionUnits(channel,acceleration_upper_limit);
}

long StepDirController::getAccelerationLowerLimit(size_t channel,
  long velocity_max)
{
  long acceleration_lower_limit = 0;
  if (channel >= getChannelCount())
  {
    return acceleration_lower_limit;
  }
  size_t controller_index = channelToControllerIndex(channel);
  Controller & controller = controllers_[controller_index];
  velocity_max = positionUnitsToSteps(channel,abs(velocity_max));
  acceleration_lower_limit = controller.getAccelerationMaxLowerLimitInHzPerS(velocity_max);
  return stepsToPositionUnits(channel,acceleration_lower_limit);
}

bool StepDirController::leftSwitchActive(size_t channel)
{
  bool left_switch_active = false;
  if (channel >= getChannelCount())
  {
    return left_switch_active;
  }
  size_t controller_index = channelToControllerIndex(channel);
  size_t motor_index = channelToMotorIndex(channel);
  Controller & controller = controllers_[controller_index];
  left_switch_active = controller.leftSwitchActive(motor_index);
  return left_switch_active;
}

bool StepDirController::rightSwitchActive(size_t channel)
{
  bool right_switch_active = false;
  if (channel >= getChannelCount())
  {
    return right_switch_active;
  }
  size_t controller_index = channelToControllerIndex(channel);
  size_t motor_index = channelToMotorIndex(channel);
  Controller & controller = controllers_[controller_index];
  right_switch_active = controller.rightSwitchActive(motor_index);
  return right_switch_active;
}

bool StepDirController::home(size_t channel)
{
  if (channel >= getChannelCount())
  {
    return false;
  }
  size_t controller_index = channelToControllerIndex(channel);
  size_t motor_index = channelToMotorIndex(channel);
  Controller & controller = controllers_[controller_index];

  modular_server::Property & home_velocity_property = modular_server_.property(constants::home_velocity_property_name);
  long home_velocity;
  home_velocity_property.getElementValue(channel,home_velocity);

  bool home_switch_enabled = false;
  bool home_switch_active = false;
  if (home_velocity < 0)
  {
    bool left_switch_stop_enabled = controller.leftSwitchStopEnabled(motor_index);
    home_switch_enabled = left_switch_stop_enabled;
    if (home_switch_enabled)
    {
      controller.setReferenceSwitchToLeft(motor_index);
      home_switch_active = leftSwitchActive(channel);
    }
  }
  else
  {
    bool right_switches_enabled = controller.rightSwitchesEnabled();
    bool right_switch_stop_enabled = controller.rightSwitchStopEnabled(motor_index);
    home_switch_enabled = right_switches_enabled && right_switch_stop_enabled;
    if (home_switch_enabled)
    {
      controller.setReferenceSwitchToRight(motor_index);
      home_switch_active = rightSwitchActive(channel);
    }
  }
  if (!home_switch_enabled)
  {
    return false;
  }
  if (home_switch_active)
  {
    pre_homing_[channel] = true;
    homing_[channel] = true;
    homed_[channel] = false;
    moveAt(channel,-home_velocity);
    return true;
  }

  controller.startLatchPositionWaiting(motor_index);
  moveAt(channel,home_velocity);
  pre_homing_[channel] = false;
  homing_[channel] = true;
  homed_[channel] = false;
  return true;
}

bool StepDirController::homing(size_t channel)
{
  if (channel >= getChannelCount())
  {
    return false;
  }
  return homing_[channel];
}

bool StepDirController::anyHoming()
{
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    if (homing_[channel])
    {
      return true;
    }
  }
  return false;
}

bool StepDirController::homed(size_t channel)
{
  if (channel >= getChannelCount())
  {
    return false;
  }
  return homed_[channel];
}

void StepDirController::temporarilyEnableHomeSwitch(size_t channel)
{
  if (channel >= getChannelCount())
  {
    return;
  }
  modular_server::Property & home_velocity_property = modular_server_.property(constants::home_velocity_property_name);
  long home_velocity;
  home_velocity_property.getElementValue(channel,home_velocity);

  size_t controller_index = channelToControllerIndex(channel);
  size_t motor_index = channelToMotorIndex(channel);
  Controller & controller = controllers_[controller_index];

  if (home_velocity < 0)
  {
    controller.enableLeftSwitchStop(motor_index);
  }
  else
  {
    controller.enableRightSwitches();
    controller.enableRightSwitchStop(motor_index);
  }
}

void StepDirController::restoreHomeSwitch(size_t channel)
{
  if (channel >= getChannelCount())
  {
    return;
  }
  size_t controller_index = channelToControllerIndex(channel);

  setLeftSwitchStopEnabledHandler(channel);
  setRightSwitchesEnabledHandler(controller_index);
  setRightSwitchStopEnabledHandler(channel);
}

bool StepDirController::homeSwitchActive(size_t channel)
{
  if (channel >= getChannelCount())
  {
    return false;
  }
  modular_server::Property & home_velocity_property = modular_server_.property(constants::home_velocity_property_name);
  long home_velocity;
  home_velocity_property.getElementValue(channel,home_velocity);

  if (home_velocity < 0)
  {
    return leftSwitchActive(channel);
  }
  else
  {
    return rightSwitchActive(channel);
  }
}

void StepDirController::temporarilySetLimits(size_t channel,
  long velocity_min,
  long velocity_max,
  long acceleration_max)
{
  if (channel >= getChannelCount())
  {
    return;
  }
  setLimits(channel,velocity_min,velocity_max,acceleration_max);
}

void StepDirController::restoreLimits(size_t channel)
{
  if (channel >= getChannelCount())
  {
    return;
  }
  setLimitsHandler(channel);
}

size_t StepDirController::getControllerChipSelectPin(size_t controller)
{
  return constants::chip_select_pins[controller];
}

size_t StepDirController::getEnablePin(size_t channel)
{
  return constants::enable_pins[channel];
}

long StepDirController::stepsToPositionUnits(size_t channel,
  long steps)
{
  modular_server::Property & steps_per_position_units_property = modular_server_.property(constants::steps_per_position_units_property_name);
  long steps_per_position_units;
  steps_per_position_units_property.getElementValue(channel,steps_per_position_units);

  return steps/steps_per_position_units;
}

long StepDirController::positionUnitsToSteps(size_t channel,
  long position_units)
{
  modular_server::Property & steps_per_position_units_property = modular_server_.property(constants::steps_per_position_units_property_name);
  long steps_per_position_units;
  steps_per_position_units_property.getElementValue(channel,steps_per_position_units);

  return position_units*steps_per_position_units;
}

int32_t StepDirController::getPositionInSteps(size_t channel)
{
  int32_t position = 0;
  if (channel >= getChannelCount())
  {
    return position;
  }
  size_t controller_index = channelToControllerIndex(channel);
  size_t motor_index = channelToMotorIndex(channel);
  Controller & controller = controllers_[controller_index];
  position = controller.getActualPosition(motor_index);
  return position;
}

int32_t StepDirController::getVelocityInHz(size_t channel)
{
  int32_t velocity = 0;
  if (channel >= getChannelCount())
  {
    return velocity;
  }
  size_t controller_index = channelToControllerIndex(channel);
  size_t motor_index = channelToMotorIndex(channel);
  Controller & controller = controllers_[controller_index];
  velocity = controller.getActualVelocityInHz(motor_index);
  return velocity;
}

void StepDirController::setControllerCountLimit(size_t controller_count)
{
  if (controller_count <= constants::CONTROLLER_COUNT_MAX)
  {
    modular_server::Property & channel_count_property = modular_server_.property(constants::channel_count_property_name);
    channel_count_property.disableFunctors();
    channel_count_property.setRange(constants::channel_count_min,controller_count*constants::CHANNELS_PER_CONTROLLER_COUNT);
    channel_count_property.reenableFunctors();
    setChannelCountHandler();
  }
}

size_t StepDirController::channelToControllerIndex(size_t channel)
{
  return channel/constants::CHANNELS_PER_CONTROLLER_COUNT;
}

size_t StepDirController::channelToMotorIndex(size_t channel)
{
  return channel%constants::CHANNELS_PER_CONTROLLER_COUNT;
}

void StepDirController::setLimits(size_t channel,
  long velocity_min,
  long velocity_max,
  long acceleration_max)
{
  size_t controller_index = channelToControllerIndex(channel);
  size_t motor_index = channelToMotorIndex(channel);
  Controller & controller = controllers_[controller_index];

  controller.setLimitsInHz(motor_index,
    positionUnitsToSteps(channel,abs(velocity_min)),
    positionUnitsToSteps(channel,abs(velocity_max)),
    positionUnitsToSteps(channel,abs(acceleration_max)));
}

// Handlers must be non-blocking (avoid 'delay')
//
// modular_server_.parameter(parameter_name).getValue(value) value type must be either:
// fixed-point number (int, long, etc.)
// floating-point number (float, double)
// bool
// const char *
// ArduinoJson::JsonArray
// ArduinoJson::JsonObject
// const ConstantString *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type

void StepDirController::setChannelCountHandler()
{
  size_t channel_count = getChannelCount();
  size_t controller_count = getControllerCount();

  modular_server::Property & steps_per_position_units_property = modular_server_.property(constants::steps_per_position_units_property_name);
  steps_per_position_units_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Property & velocity_max_property = modular_server_.property(constants::velocity_max_property_name);
  velocity_max_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Property & velocity_min_property = modular_server_.property(constants::velocity_min_property_name);
  velocity_min_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Property & acceleration_max_property = modular_server_.property(constants::acceleration_max_property_name);
  acceleration_max_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Property & enable_polarity_property = modular_server_.property(constants::enable_polarity_property_name);
  enable_polarity_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Property & step_polarity_inverted_property = modular_server_.property(constants::step_polarity_inverted_property_name);
  step_polarity_inverted_property.setArrayLengthRange(controller_count,controller_count);

  modular_server::Property & dir_polarity_inverted_property = modular_server_.property(constants::dir_polarity_inverted_property_name);
  dir_polarity_inverted_property.setArrayLengthRange(controller_count,controller_count);

  modular_server::Property & switch_active_polarity_property = modular_server_.property(constants::switch_active_polarity_property_name);
  switch_active_polarity_property.setArrayLengthRange(controller_count,controller_count);

  modular_server::Property & left_switch_stop_enabled_property = modular_server_.property(constants::left_switch_stop_enabled_property_name);
  left_switch_stop_enabled_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Property & right_switches_enabled_property = modular_server_.property(constants::right_switches_enabled_property_name);
  right_switches_enabled_property.setArrayLengthRange(controller_count,controller_count);

  modular_server::Property & right_switch_stop_enabled_property = modular_server_.property(constants::right_switch_stop_enabled_property_name);
  right_switch_stop_enabled_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Property & switch_soft_stop_enabled_property = modular_server_.property(constants::switch_soft_stop_enabled_property_name);
  switch_soft_stop_enabled_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Property & home_velocity_property = modular_server_.property(constants::home_velocity_property_name);
  home_velocity_property.setArrayLengthRange(channel_count,channel_count);

  modular_server::Parameter & channel_parameter = modular_server_.parameter(constants::channel_parameter_name);
  channel_parameter.setRange(constants::channel_min,(long)(channel_count-1));

}

void StepDirController::preUpdateScaledPropertiesHandler(size_t channel)
{
  modular_server::Property & velocity_min_property = modular_server_.property(constants::velocity_min_property_name);
  long velocity_min;
  velocity_min_property.getElementValue(channel,velocity_min);
  velocity_min_steps_[channel] = positionUnitsToSteps(channel,velocity_min);

  modular_server::Property & velocity_max_property = modular_server_.property(constants::velocity_max_property_name);
  long velocity_max;
  velocity_max_property.getElementValue(channel,velocity_max);
  velocity_max_steps_[channel] = positionUnitsToSteps(channel,velocity_max);

  modular_server::Property & acceleration_max_property = modular_server_.property(constants::acceleration_max_property_name);
  long acceleration_max;
  acceleration_max_property.getElementValue(channel,acceleration_max);
  acceleration_max_steps_[channel] = positionUnitsToSteps(channel,acceleration_max);

  modular_server::Property & home_velocity_property = modular_server_.property(constants::home_velocity_property_name);
  long home_velocity;
  home_velocity_property.getElementValue(channel,home_velocity);
  home_velocity_steps_[channel] = positionUnitsToSteps(channel,home_velocity);
}

void StepDirController::postUpdateScaledPropertiesHandler(size_t channel)
{
  modular_server::Property & velocity_min_property = modular_server_.property(constants::velocity_min_property_name);

  modular_server::Property & velocity_max_property = modular_server_.property(constants::velocity_max_property_name);

  modular_server::Property & acceleration_max_property = modular_server_.property(constants::acceleration_max_property_name);

  modular_server::Property & home_velocity_property = modular_server_.property(constants::home_velocity_property_name);

  velocity_min_property.disableFunctors();
  velocity_max_property.disableFunctors();
  acceleration_max_property.disableFunctors();
  home_velocity_property.disableFunctors();

  velocity_min_property.setElementValue(channel,stepsToPositionUnits(channel,velocity_min_steps_[channel]));

  velocity_max_property.setElementValue(channel,stepsToPositionUnits(channel,velocity_max_steps_[channel]));

  acceleration_max_property.setElementValue(channel,stepsToPositionUnits(channel,acceleration_max_steps_[channel]));

  home_velocity_property.setElementValue(channel,stepsToPositionUnits(channel,home_velocity_steps_[channel]));

  velocity_min_property.reenableFunctors();
  velocity_max_property.reenableFunctors();
  acceleration_max_property.reenableFunctors();
  home_velocity_property.reenableFunctors();

  setLimitsHandler(channel);
}

void StepDirController::homedHandler(size_t channel)
{
}

void StepDirController::setLimitsHandler(size_t channel)
{
  modular_server::Property & velocity_min_property = modular_server_.property(constants::velocity_min_property_name);
  long velocity_min;
  velocity_min_property.getElementValue(channel,velocity_min);

  modular_server::Property & velocity_max_property = modular_server_.property(constants::velocity_max_property_name);
  long velocity_max;
  velocity_max_property.getElementValue(channel,velocity_max);

  modular_server::Property & acceleration_max_property = modular_server_.property(constants::acceleration_max_property_name);
  long acceleration_max;
  acceleration_max_property.getElementValue(channel,acceleration_max);

  setLimits(channel,velocity_min,velocity_max,acceleration_max);
}

void StepDirController::reinitializeHandler()
{
  reinitialize();
}

void StepDirController::controllersCommunicatingHandler()
{
  modular_server_.response().writeResultKey();

  modular_server_.response().beginArray();

  for (size_t controller_index=0; controller_index<getControllerCount(); ++controller_index)
  {
    Controller & controller = controllers_[controller_index];
    modular_server_.response().write(controller.communicating());
  }

  modular_server_.response().endArray();
}

void StepDirController::setStepPolarityInvertedHandler(size_t controller_index)
{
  bool inverted;
  modular_server_.property(constants::step_polarity_inverted_property_name).getElementValue(controller_index,inverted);
  Controller & controller = controllers_[controller_index];
  if (inverted)
  {
    controller.enableInverseStepPolarity();
  }
  else
  {
    controller.disableInverseStepPolarity();
  }
}

void StepDirController::setDirPolarityInvertedHandler(size_t controller_index)
{
  bool inverted;
  modular_server_.property(constants::dir_polarity_inverted_property_name).getElementValue(controller_index,inverted);
  Controller & controller = controllers_[controller_index];
  if (inverted)
  {
    controller.enableInverseDirPolarity();
  }
  else
  {
    controller.disableInverseDirPolarity();
  }
}

void StepDirController::setSwitchActivePolarityHandler(size_t controller_index)
{
  const ConstantString * polarity_ptr;
  modular_server_.property(constants::switch_active_polarity_property_name).getElementValue(controller_index,polarity_ptr);
  Controller & controller = controllers_[controller_index];
  if (polarity_ptr == &constants::polarity_high)
  {
    controller.setSwitchesActiveHigh();
  }
  else if (polarity_ptr == &constants::polarity_low)
  {
    controller.setSwitchesActiveLow();
  }
}

void StepDirController::setLeftSwitchStopEnabledHandler(size_t channel)
{
  bool enabled;
  modular_server_.property(constants::left_switch_stop_enabled_property_name).getElementValue(channel,enabled);
  size_t controller_index = channelToControllerIndex(channel);
  size_t motor_index = channelToMotorIndex(channel);
  Controller & controller = controllers_[controller_index];
  if (enabled)
  {
    controller.enableLeftSwitchStop(motor_index);
  }
  else
  {
    controller.disableLeftSwitchStop(motor_index);
  }
}

void StepDirController::setRightSwitchesEnabledHandler(size_t controller_index)
{
  bool enabled;
  modular_server_.property(constants::right_switches_enabled_property_name).getElementValue(controller_index,enabled);
  Controller & controller = controllers_[controller_index];
  if (enabled)
  {
    controller.enableRightSwitches();
  }
  else
  {
    controller.disableRightSwitches();
  }
}

void StepDirController::setRightSwitchStopEnabledHandler(size_t channel)
{
  bool enabled;
  modular_server_.property(constants::right_switch_stop_enabled_property_name).getElementValue(channel,enabled);
  size_t controller_index = channelToControllerIndex(channel);
  size_t motor_index = channelToMotorIndex(channel);
  Controller & controller = controllers_[controller_index];
  if (enabled)
  {
    controller.enableRightSwitchStop(motor_index);
  }
  else
  {
    controller.disableRightSwitchStop(motor_index);
  }
}

void StepDirController::setSwitchSoftStopEnabledHandler(size_t channel)
{
  bool enabled;
  modular_server_.property(constants::right_switch_stop_enabled_property_name).getElementValue(channel,enabled);
  size_t controller_index = channelToControllerIndex(channel);
  size_t motor_index = channelToMotorIndex(channel);
  Controller & controller = controllers_[controller_index];
  if (enabled)
  {
    controller.enableSwitchSoftStop(motor_index);
  }
  else
  {
    controller.disableSwitchSoftStop(motor_index);
  }
}

void StepDirController::enableHandler()
{
  long channel;
  modular_server_.parameter(constants::channel_parameter_name).getValue(channel);
  enable(channel);
}

void StepDirController::disableHandler()
{
  long channel;
  modular_server_.parameter(constants::channel_parameter_name).getValue(channel);
  disable(channel);
}

void StepDirController::enableAllHandler()
{
  enableAll();
}

void StepDirController::disableAllHandler()
{
  disableAll();
}

void StepDirController::enabledHandler()
{
  uint32_t channels_enabled = enabled();
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  int bit = 1;
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    bool channel_enabled = (bit << channel) & channels_enabled;
    modular_server_.response().write(channel_enabled);
  }
  modular_server_.response().endArray();
}

void StepDirController::moveByHandler()
{
  long channel;
  modular_server_.parameter(constants::channel_parameter_name).getValue(channel);
  long position;
  modular_server_.parameter(constants::position_parameter_name).getValue(position);
  moveBy(channel,position);
}

void StepDirController::moveToHandler()
{
  long channel;
  modular_server_.parameter(constants::channel_parameter_name).getValue(channel);
  long position;
  modular_server_.parameter(constants::position_parameter_name).getValue(position);
  moveTo(channel,position);
}

void StepDirController::moveAtHandler()
{
  long channel;
  modular_server_.parameter(constants::channel_parameter_name).getValue(channel);
  long velocity;
  modular_server_.parameter(constants::velocity_parameter_name).getValue(velocity);
  moveAt(channel,velocity);
}

// void StepDirController::moveByAtHandler()
// {
//   long channel;
//   modular_server_.parameter(constants::channel_parameter_name).getValue(channel);
//   long position;
//   modular_server_.parameter(constants::position_parameter_name).getValue(position);
//   long velocity;
//   modular_server_.parameter(constants::velocity_parameter_name).getValue(velocity);
//   moveByAt(channel,position,velocity);
// }

// void StepDirController::moveToAtHandler()
// {
//   long channel;
//   modular_server_.parameter(constants::channel_parameter_name).getValue(channel);
//   long position;
//   modular_server_.parameter(constants::position_parameter_name).getValue(position);
//   long velocity;
//   modular_server_.parameter(constants::velocity_parameter_name).getValue(velocity);
//   moveToAt(channel,position,velocity);
// }

void StepDirController::moveSoftlyByHandler()
{
  long channel;
  modular_server_.parameter(constants::channel_parameter_name).getValue(channel);
  long position;
  modular_server_.parameter(constants::position_parameter_name).getValue(position);
  moveSoftlyBy(channel,position);
}

void StepDirController::moveSoftlyToHandler()
{
  long channel;
  modular_server_.parameter(constants::channel_parameter_name).getValue(channel);
  long position;
  modular_server_.parameter(constants::position_parameter_name).getValue(position);
  moveSoftlyTo(channel,position);
}

void StepDirController::stopHandler()
{
  long channel;
  modular_server_.parameter(constants::channel_parameter_name).getValue(channel);
  stop(channel);
}

void StepDirController::stopAllHandler()
{
  stopAll();
}

void StepDirController::zeroHandler()
{
  long channel;
  modular_server_.parameter(constants::channel_parameter_name).getValue(channel);
  zero(channel);
}

void StepDirController::zeroAllHandler()
{
  zeroAll();
}

void StepDirController::getPositionsHandler()
{
  long position;
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    position = getPosition(channel);
    modular_server_.response().write(position);
  }
  modular_server_.response().endArray();
}

void StepDirController::getTargetPositionsHandler()
{
  long position;
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    position = getTargetPosition(channel);
    modular_server_.response().write(position);
  }
  modular_server_.response().endArray();
}

void StepDirController::atTargetPositionsHandler()
{
  bool at_target_position;
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    at_target_position = atTargetPosition(channel);
    modular_server_.response().write(at_target_position);
  }
  modular_server_.response().endArray();
}

void StepDirController::getVelocitiesHandler()
{
  long velocity;
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    velocity = getVelocity(channel);
    modular_server_.response().write(velocity);
  }
  modular_server_.response().endArray();
}

void StepDirController::getTargetVelocitiesHandler()
{
  long velocity;
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    velocity = getTargetVelocity(channel);
    modular_server_.response().write(velocity);
  }
  modular_server_.response().endArray();
}

void StepDirController::atTargetVelocitiesHandler()
{
  bool at_target_velocity;
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    at_target_velocity = atTargetVelocity(channel);
    modular_server_.response().write(at_target_velocity);
  }
  modular_server_.response().endArray();
}

void StepDirController::getVelocityUpperLimitsHandler()
{
  long velocity_upper_limit;
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    velocity_upper_limit = getVelocityUpperLimit(channel);
    modular_server_.response().write(velocity_upper_limit);
  }
  modular_server_.response().endArray();
}

void StepDirController::getAccelerationUpperLimitsHandler()
{
  long velocity;
  modular_server_.parameter(constants::velocity_parameter_name).getValue(velocity);

  long acceleration_upper_limit;
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    acceleration_upper_limit = getAccelerationUpperLimit(channel,velocity);
    modular_server_.response().write(acceleration_upper_limit);
  }
  modular_server_.response().endArray();
}

void StepDirController::getAccelerationLowerLimitsHandler()
{
  long velocity;
  modular_server_.parameter(constants::velocity_parameter_name).getValue(velocity);

  long acceleration_lower_limit;
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    acceleration_lower_limit = getAccelerationLowerLimit(channel,velocity);
    modular_server_.response().write(acceleration_lower_limit);
  }
  modular_server_.response().endArray();
}

void StepDirController::switchesActiveHandler()
{
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  size_t controller_index;
  size_t motor_index;
  bool left_switch_active;
  bool right_switch_active;
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    controller_index = channelToControllerIndex(channel);
    motor_index = channelToMotorIndex(channel);
    Controller & controller = controllers_[controller_index];
    modular_server_.response().beginObject();
    left_switch_active = controller.leftSwitchActive(motor_index);
    modular_server_.response().write(constants::left_constant_string,left_switch_active);
    right_switch_active = controller.rightSwitchActive(motor_index);
    modular_server_.response().write(constants::right_constant_string,right_switch_active);
    modular_server_.response().endObject();
  }
  modular_server_.response().endArray();
}

void StepDirController::homeHandler()
{
  long channel;
  modular_server_.parameter(constants::channel_parameter_name).getValue(channel);
  bool is_homing = home(channel);
  modular_server_.response().returnResult(is_homing);
}

void StepDirController::homingHandler()
{
  bool is_homing;
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    is_homing = homing(channel);
    modular_server_.response().write(is_homing);
  }
  modular_server_.response().endArray();
}

void StepDirController::homedHandler()
{
  bool is_homed;
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();
  for (size_t channel=0; channel<getChannelCount(); ++channel)
  {
    is_homed = homed(channel);
    modular_server_.response().write(is_homed);
  }
  modular_server_.response().endArray();
}
