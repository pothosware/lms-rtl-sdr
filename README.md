# LimeSuite fork of the RTL-SDR library

This fork builds a version of librtlsdr.so that supports LimeSuite.
This is an experiment to support LimeSuite in some RTL-SDR based apps.

## Warnings

There is not always a 1:1 ratio of controls for RTL and LMS7 devices.
Be warned that it replaces the existing librtlsdr.so on your system.

## Build

* Install LimeSuite https://github.com/myriadrf/LimeSuite
* Install this project with cmake
