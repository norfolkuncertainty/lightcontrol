#!/usr/bin/env python
import json
import urllib3
from datetime import datetime
import pytz

LAT="0"
LONG="0"
DATE="today"
localFormat = "%H:%M:%S %p"


def utc_to_local(utc_dt):
    return utc_dt.replace(tzinfo=timezone.utc).astimezone(tz=None)

http = urllib3.PoolManager()
response = http.request('GET', "https://api.sunrise-sunset.org/json?lat=-41.2865&lng=174.7762&date=today")
parsed_json = json.loads(response.data)
SUNSET=parsed_json['results']['sunset']
print(SUNSET)
utcmoment_naive = datetime.strptime(SUNSET, localFormat)
utcmoment = utcmoment_naive.replace(tzinfo=pytz.utc)

localDatetime = utcmoment.astimezone(pytz.timezone('Pacific/Auckland'))
print(localDatetime)
print(localDatetime.strftime(localFormat))
