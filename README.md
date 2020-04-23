# Social-Distance-Warning-Sensor
A just for fun project that warns when objects are less than 6 feet away.
## Overview
This is just a quickly put together project to have a little fun with social distancing. The project uses an ultrasonic distance sensor, microcontroller, and an RGB LED. The set-up is hot glued to a piece of cardboard, with a battery pack glued to the folded over part that fits in a shirt pocket. If it doesn’t detect anything within 10 feet, the LED is off. If it detects something between 8 and 10 feet, it lights up green, indicating a proper social distance is being maintained. Between 8 and 8 feet, it turns yellow, and if it detects something 6 feet or less away, it flashes red to warn both parties that the proper social distance is not being maintained.

Read more, including a description of the hardware, at https://www.mcgurrin.info/robots/667/

As I mentioned, it’s just for fun, and isn’t very practical, as the sensor reacts to anything in front of it, not just another person.
## Hardware
* RCWL-1601 Ultrasonic Sensor
* The system uses an Adafruit RCWL-1601 distance sensor. A nice thing about this sensor is that it can operate at either 3V or 5V. The sensor has four pins: Vin, Ground, Trigger, and Echo. You send a trigger pulse to make a measurement, and then the length of the return pulse on the Echo line tells you the distance.
* The microcontroller is a Teensy 2.0 that I had lying around.  Pretty much any Arduino compatible board will work.
* The battery input is run through a 7805 voltage regulator to put our a steady 5V. I should be providing a bit higher voltage as input, but the 6V does seem to work.
* The RGB LED is one I had around, I don’t remember the model.
Everything is wired up using a breadboard and then the components hot-glued to the cardboard “pocket protector.”
## The Software
The software is very straight-forward. The one minor twist is that I decided that when the sensor detected something 6 feet or less away, it would flash, not just have a steady light. Because it also needed to be continually sensing, I couldn’t use delay() to do this. Normally one uses millis() and continually loop and checking on each pass whether or not enough time had passed to turn the LED on or off. In this case, however, I decided to measure distance four times a second (every 250 milliseconds) and also have the duration of each on or off period also be 250 milliseconds. This makes the already simple code a little simpler, but at the expense of flexibility.

You can see a demonstration video at https://www.mcgurrin.info/robots/667/

