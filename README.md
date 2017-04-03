# StepDirController

Authors:

    Peter Polidoro <polidorop@janelia.hhmi.org>

License:

    BSD

[Examples](./examples)

## API

```json
{
  "id":"getApi",
  "result":{
    "firmware":["StepDirController"],
    "functions":[
      "reinitialize",
      "enable",
      "disable",
      "enableAll",
      "disableAll",
      "enabled",
      "moveBy",
      "moveTo",
      "moveAt",
      "moveSoftlyBy",
      "moveSoftlyTo",
      "stop",
      "stopAll",
      "zero",
      "zeroAll",
      "getPositions",
      "getTargetPositions",
      "atTargetPositions",
      "getVelocities",
      "getTargetVelocities",
      "atTargetVelocities",
      "switchesActive",
      "home",
      "homing",
      "homed"
    ],
    "parameters":[
      "channel",
      "position",
      "velocity"
    ],
    "properties":[
      "stepsPerPositionUnit",
      "velocityMax",
      "velocityMin",
      "accelerationMax",
      "enablePolarity",
      "stepPolarityInverted",
      "dirPolarityInverted",
      "switchActivePolarity",
      "leftSwitchStopEnabled",
      "rightSwitchesEnabled",
      "rightSwitchStopEnabled",
      "switchSoftStopEnabled",
      "homeVelocity"
    ],
    "callbacks":[]
  }
}
```

## More Detailed Modular Device Information

[modular-devices](https://github.com/janelia-modular-devices/modular-devices)

## Install Library Dependencies

[arduino-libraries](https://github.com/janelia-arduino/arduino-libraries)
