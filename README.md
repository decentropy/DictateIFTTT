# DictateIFTTT
Pebble watch app to dictate speech, and send to IFTTT event. 

Configure your IFTTT recipes with Maker channel to do what you want with the transcribed speech (value1). E.g. email someone, run a command, whatever...

(Requires Pebble Time/Steel/Round or newer)

![Image of Pebble](https://raw.githubusercontent.com/steve-vincent/DictateIFTTT/master/dictate.jpg)

Set up IFTTT:
- Go https://ifttt.com/maker, to get a Maker channel.
- Create a IFTTT recipe, and test with https://maker.ifttt.com/trigger/{event}/with/key/{key}?value1={value}

Install on your watch:
- Go to cloudpebble.net then import this project.
- Edit pebble-js-app.js (lines 2,3) with your own Maker Key and recipe's Event Name.
- Turn 'Developer Connection' on in your Android Pebble app. In cloudpebble, click COMPILATION > PHONE > INSTALL AND RUN.

Run the app, speak, and the transcribed words will be passed as value1 to your IFTTT event.
