#!/usr/bin/env ruby

require 'open-uri'
require 'json'
require 'time'

#Set Variables
relayHost='ar1.internal'
latitude='-41.1745'
longitude='174.9820'
nightOff='21:45'
randomRange= 1800
delay = rand(0..randomRange)

#Get Sunset time from sunrise-sunset.org for given GPS coordinates
@data = URI.parse("https://api.sunrise-sunset.org/json?lat=#{latitude}&lng=#{longitude}&date=today").read
response = JSON.parse(@data)
#Parse json response and extract the sunset time, adding the systems utc offset to obtain the local time of the sunset
sunset = Time.parse(response['results']['sunset']) + Time.now.utc_offset
#Create 'at' job on local linux box to switch relay on
system"echo curl http://#{relayHost}/on | at #{sunset.strftime("%H:%M")}"

#Parse given off time and add randomly selected delay
offTime = Time.parse(nightOff) + delay
#Create 'at' job on local linux box to switch relay off
system"echo curl http://#{relayHost}/off | at #{offTime.strftime('%H:%M')}"

