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
- Docker Desktop: <https://www.docker.com/products/docker-desktop/>

Note: Using the PlatformIO VSCode extension makes for a more ergonomic development environment, but that is beyond the scope of this readme. Please refer to the beautiful PlatformIO docs for instructions on using.

### Configuring

To configure the firmware before compilation and flashing it to the ESP8266, we
must rename the [config_example.hpp](include/config_example.hpp) file to `config.hpp`
and change the values to match your setup.

### Compiling & Uploading

Configuration for building, uploading, and monitoring over a serial interface is specified in `platformio.ini`

1. Plug ESP8266 into usb port of computer.

2. From the root of this repo, `pio run`, should automatically build, upload, and begin mornitoring the the firmware.

Watch the terminal for logs comming from the board.

## Usage Instructions

The controller has two interfaces through which it can be accessed:

1. the MQTT interface which subscribes to configured MQTT broker and topics.
2. the http interface which provides an intial webpage for network configuration.

Continue reading for how to connect to each of them.

### Example of serial console output as a result of mqtt channel subscription
![](docs/example-exec-serial-console-mqtt.gif)

### Testing the MQTT interface

The `docker-compose.yml` file in the root of this repo will spin up an
`eclipse-mosquitto` image as a container named `mosquitto`. Config, data, and log
directories are mounted from subdirectories of `./mosquito/`.

From the root of the repository, run

`docker compose up`

#### Docker tips

To interact with the broker running in the container, we can execute the mosquitto
binaries already available in the image with `docker exec` commands.

For example:

`docker exec -it mosquitto mosquitto_pub -h 0.0.0.0 -p 1883 -t testtopic/blah -m "hello world"`

For information on how to use the binaries available in the image, please consult
the [mosquitto documentation](https://mosquitto.org/documentation/).

#### MQTT interface definition

The firmware subscribes to the following topics and listens for the respective messages:

- `fish/fluval-flex-9g/lights` messages:
  - `reset` brings the fluval light controller to a known state.
    This is useful because it is not possible to query the state of the actual fishtank without light/color sensors and some fancy math. So every now and then, we can simply `reset` the tank to ensure smooth operation incase the tank's state desynchronized from our controller's state.
  - `day` smoothly transitions from night settings to day settings.
  - `night` smoothly transitions from day settings to night settings.
  - `auto` calculates sunrise and sunset times based on [configured](include/config_example.hpp) location and
  timezone and schedules state transitions to match. ~~ queries preconfigured web APIs for time and sun data to match your location based on your public IP address. ~~
- (COMING SOON!) `fish/fluval-flex-9g/lights/raw` messages:
  - `<hex code>` - known codes are [here](src/_fluval_lights.h)

#### HTTP interrrface description

The firmware exposes an http interface upon first boot to allow for network configuration.

It can be accessed by connecting to the wifi access point with SSID `esp-fluval`.
