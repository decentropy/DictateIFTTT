# DictateIFTTT
Pebble watch app to dictate speech, and send to IFTTT event.

(Requires Pebble Time/Steel/Round or newer)

![Image of Pebble](https://raw.githubusercontent.com/steve-vincent/DictateIFTTT/master/dictate.jpg)

To install on your watch:
- Go https://ifttt.com/maker, to get a Maker channel.
- Create a IFTTT recipe, and test with https://maker.ifttt.com/trigger/{event}/with/key/{key}?value1={value}
- Go to cloudpebble.net then import this project.
- Edit pebble-js-app.js (lines 2,3) with your own Maker Key and recipe's Event Name.
- Configure your IFTTT recipes with Maker channel to do what you want with the transcribed speech (value1). E.g. email someone, run a command, whatever...
