#!/usr/bin/env ruby

require 'net/http'
require 'json'
require 'time'

#Set Variables
relayHost='relay.home'
latitude='-41.1745'
longitude='174.9820'
nightOff='21:45'
randomRange= 1800
delay = rand(0..randomRange)

#Get Sunset time from sunrise-sunset.org for given GPS coordinates
response = JSON.parse(Net::HTTP.get('api.sunrise-sunset.org', "/json?lat=#{latitude}&lng=#{longitude}&date=today"))
#Parse json response and extract the sunset time, adding the systems utc offset to obtain the local time of the sunset
sunset = Time.parse(response['results']['sunset']) + Time.now.utc_offset
#Create 'at' job on local linux box to switch relay on
system"echo 'curl http://relay.home/on' | at #{sunset.strftime("%H:%M")}"

#Parse given off time and add randomly selected delay
offTime = Time.parse(nightOff) + delay
#Create 'at' job on local linux box to switch relay off
system"echo 'curl http://relay.home/off' | at #{offTime.strftime('%H:%M')}"

