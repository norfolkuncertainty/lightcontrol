require 'net/http'
require 'json'
require 'time'

response = JSON.parse(Net::HTTP.get('api.sunrise-sunset.org', '/json?lat=-41.2865&lng=174.7762&date=today'))
SUNSET = Time.parse(response['results']['sunset']) + Time.now.utc_offset
SUNSET_HM = SUNSET.strftime("%H:%M")
system"curl http://relay.home/on | at #{SUNSET_HM}"

