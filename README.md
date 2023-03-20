# ROSNeuro CAR filter

This ROSNeuro filter plugin implements a Common Average Reference filter to remove the average component from all data channels.

## Algorithm:
The filter applies the Common Average Reference to the data. For each provided sample, it substracts the mean value computed across all the channel.

## YAML configuration
```
CarCfgTest:
  name: car
  type: CarFilterFloat
```
*No additional parameters, but name and type*
