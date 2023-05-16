<a href="https://mono-wireless.com/jp/index.html">
    <img src="https://mono-wireless.com/common/images/logo/logo-land.svg" alt="mono wireless logo" title="MONO WIRELESS" align="right" height="60" />
</a>

# spot-router

**Mono Wireless TWELITE SPOT Local Router Example**

[![MW-OSSLA](https://img.shields.io/badge/License-MW--OSSLA-e4007f)](LICENSE.md)

## 目次

- [概要](#概要)
- [使用方法](#使用方法)
- [依存関係](#依存関係)
- [付録](#付録)
- [ライセンス](#ライセンス)

## 概要

ESP32 を WebSocket クライアントとして使います。

TWELITE から受信したパケットデータ文字列（App_Wings 出力と同一の ModBus ASCII形式）を LAN 内の WebSocket サーバへ中継できます。

## 使用方法

1. スケッチ内の無線 LAN 及び WebSocket 設定を変更します
2. WebSocket サーバを LAN 内で起動します
3. スケッチを書き込み、実行します

## 依存関係

### TWELITE SPOT 内の TWELITE BLUE

- ファームウェア
  - App_Wings (>= 1.3.0)

### TWELITE SPOT 内の ESP32-WROOM-32

- 環境
  - [Arduino IDE](https://github.com/arduino/Arduino) (1.x)
  - [ESP32 Arduino core](https://github.com/espressif/arduino-esp32) (>= 2.0.5)
- ライブラリ
  - [MWings](https://github.com/monowireless/mwings_arduino) (>= 1.0.0)
  - [arduinoWebSockets](https://github.com/Links2004/arduinoWebSockets) (>= 2.3.6)

## 付録

### Python による WebSocket サーバのサンプル

`extra/python-websocket-server/server.py` は、ESP32 から データを受信するためのサンプルスクリプトです。

#### 実行方法

```shell
$ pip3 install websocket-server
$ python3 server.py
```

#### 機能

- 新たなクライアントの接続時にメッセージを表示
- 新たなデータの受信時にパケットデータ文字列を表示

## ライセンス

``` plain
Copyright (C) 2023 Mono Wireless Inc. All Rights Reserved.
Released under MW-OSSLA-1J,1E (MONO WIRELESS OPEN SOURCE SOFTWARE LICENSE AGREEMENT).
```
