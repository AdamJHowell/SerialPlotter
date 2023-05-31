# SerialPlotter
This is a simple program to show how the plotter works.

The potentiometer reading will dynamically expand the ceiling and floor.
The ceiling can only increase, and the floor can only decrease.

If the target MCU us an ESP32, the built-in Hall sensor will be used as a 5th printed value.
The Hall sensor reading, like the potentiometer reading, will also expand the ceiling and floor.
Typical hall readings range from +335 (with a small neodymium magnet held very close above) to -213 (with a small neodymium magnet held moderately close below, to avoid contact with the MCU pins).
