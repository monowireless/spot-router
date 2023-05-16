<a href="https://mono-wireless.com/jp/index.html">
    <img src="https://mono-wireless.com/common/images/logo/logo-land.svg" alt="mono wireless logo" title="MONO WIRELESS" align="right" height="60" />
</a>

# spot-router

**Mono Wireless TWELITE SPOT Local Router Example**

[![MW-OSSLA](https://img.shields.io/badge/License-MW--OSSLA-e4007f)](LICENSE.md)

[日本語版はこちら](README_J.md)

## Contents

- [About](#about)
- [Usage](#usage)
- [Dependencies](#dependencies)
- [Extra](#extra)
- [License](#license)

## About

Set ESP32 as a websocket client.

You can transfer packet data string (same as App_Wings output, ModBus ASCII format) to the websocket server in the LAN.

## Usage

1. Modify Wi-Fi / WebSocket configs in the sketch file.
2. Run a WebSocket server in the LAN.
3. Upload & Run the sketch.

## Dependencies

### TWELITE BLUE on the TWELITE SPOT

- Firmware
  - App_Wings (>= 1.3.0)

### ESP32-WROOM-32 on the TWELITE SPOT

- Environment
  - [Arduino IDE](https://github.com/arduino/Arduino) (1.x)
  - [ESP32 Arduino core](https://github.com/espressif/arduino-esp32) (>= 2.0.5)
- Libraries
  - [MWings](https://github.com/monowireless/mwings_arduino) (>= 1.0.0)
  - [arduinoWebSockets](https://github.com/Links2004/arduinoWebSockets) (>= 2.3.6)

## Extra

### Python WebSocket server example

`extra/python-websocket-server/server.py` is an example script for receiving data from ESP32.

#### How to run

```shell
$ pip3 install websocket-server
$ python3 server.py
```

#### Features

- Display a message when a new client connects
- Display packet string when new data arrives

## License

``` plain
Copyright (C) 2023 Mono Wireless Inc. All Rights Reserved.
Released under MW-OSSLA-1J,1E (MONO WIRELESS OPEN SOURCE SOFTWARE LICENSE AGREEMENT).
```
