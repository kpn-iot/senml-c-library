**:warning: DEPRECATED :warning: This repository has been discontinued in favor of our [KPN Things Device SDK](https://github.com/kpn-iot/thingsml-c-library), an evolution of this library that also supports ThingsML, HTTP POST to KPN Things, and Firmware over the air through KPN Things. [Learn more about the KPN Things Device SDK](https://docs.kpnthings.com/dm/devices/sdk).**

# Introduction

The KPN SenML library helps you create and parse [senml documents](https://tools.ietf.org/html/draft-ietf-core-senml-13)
in both json and cbor format.

# key features

- Object oriented design.
- built in support for [senml's unit registry](https://tools.ietf.org/html/draft-ietf-core-senml-12#section-12.1)
- extensible for new data types
- makes use of (but doesn't restrict to) KPN's predefined list of record names.
- direct support to read/write in json and cbor format.
- automatically adjusts record data with respect to base time, base value & base sum.

Please visit our [docs site](https://kpn-iot.github.io/senml-c-library) for more info.

