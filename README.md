# Seneye-HASS

[![Build status](https://github.com/83noit/Seneye-HASS/actions/workflows/c-cpp.yml/badge.svg?branch=main)](https://github.com/83noit/seneye-hass/actions)

To collect [Seneye USB device](https://www.seneye.com/store/seneye-reef.html)
('SUD') readings and broadcast them via MQTT.  C++ prototype under development.

The aim is to have an implementation which integrates nicely with [Home
Assistant](https://www.home-assistant.io/).

## Requirements

### [HIDAPI](https://github.com/libusb/hidapi)

HIDAPI is a multi-platform library which allows an application to interface
with USB HID-Class devices.

HIDAPI has several back-ends. Seneye-HASS has been tested with libusb.

```sudo apt-get install libhidapi-libusb0 libhidapi-dev```

### [Mosquitto](https://mosquitto.org)

The Mosquitto project is primarily a message broker that implements the MQTT
protocol. It also provides a C/C++ libraries for implementing MQTT clients,
which is used by Seneye-HASS.

```sudo apt-get install libmosquittopp1 libmosquittopp-dev```

## Resources

The resources folder contains:
- An example of a systemd service.
- An example of a Home Assistant configuration, declaring entities for the
    readings sent over MQTT.
- An example of a Home Assistant dashboard using these entities.

## WIP/TODO
- Implement [Home Assistant MQTT discovery](https://www.home-assistant.io/docs/mqtt/discovery/).
- Deal with several Seneye devices.
- Make the logging flexible.

## Related projects

* https://github.com/seneye/SUDDriver
* https://github.com/mcclown/pyseneye
* https://github.com/dhallgb/Seneye-MQTT
