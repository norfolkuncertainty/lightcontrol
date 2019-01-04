# Lightcontrol

A ruby script to get the sunset time for the given GPS coordinates and send an on/off to an esp8266 relay

Uses sunrise-sunset.org for the sunset times

Designed to be run on a linux system running `atd`

TODO:

- Document esp8266 portion
- Read in config file/command line flags
- Add a sunrise function to allow a light to be turned on in the morning when required in winter
- Error check ie what happens if the offtime is before the on time
- Move this to run entirely on an ESP8266 rather than using at jobs