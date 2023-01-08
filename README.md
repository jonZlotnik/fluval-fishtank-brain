# IoT Controller for Fluval Flex 9g on ESP8266

## Build Instructions

### Hardware Requirements

- Node MCU (ESP8266)
- IR LED
- C1815 transitor (NPN)
- 220 Ohm resistor

### Software Requirements

Drivers:

- ESP8266's usb to uart: <https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers>

Developer environment:

- PlatformIO Core CLI: <https://docs.platformio.org/en/latest/core/installation/methods/installer-script.html#local-download-macos-linux-windows>

Note: Using the PlatformIO VSCode extension makes for a more ergonomic development environment, but that is beyond the scope of this readme. Please refer to the beautiful PlatformIO docs for instructions on using.

### Compiling & Uploading

Configuration for building, uploading, and monitoring over a serial interface is specified in `platformio.ini`

1. Plug ESP8266 into usb port of computer.

2. From the root of this repo, `pio run`, should automatically build, upload, and begin mornitoring the the firmware.

Watch the terminal for logs comming from the board.

## Usage Instructions

The controller has two interfaces through which it can be accessed:

1. the MQTT interface which subscribes to a configured MQTT broker and topic.
2. the http interface which provides a GUI for accessing the controller's features.

Continue reading for how to connect to each of them.