# AC-remote

## TODO

- Investigate current state of tls1.2 support
- Look for a way to connect esp8266 thing to the aws-iot 


## About

Small project for home automation. Main goal - a client device that accepts air condition modes on Serial port and sends them through IR.

Command structure:

mode,fan,temperature,state;

* mode - one of the available modes: cooling / dehumidification / auto / heating
* fan - fan speed
* temperature
* state - on / off

It's a work in progress project
