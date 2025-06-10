# clocky

Simple desk and gym timer made with a LilyGO T-Display-S3-Long on Esphome.

I'm using an 18650 battery to power the display and I 3D printed a small enclosure for it all (STL File included) plus added a small USB C socket on the back which i soldered onto the VCC and GND terminals next to the USB C socket on the rear of the display. 
Just a note that the USB C socket will only work on chargers that aren't "smart" like power delivery. I use an old iPhone charging brick.

# Functions

Stopwatch 

Timer - Presets at the bottom of the display for 1, 2, 3 and 5 minutes

Interval - Select workout time of 1, 2, 3 minutes, cycles of 1, 2 or 3, and rest times of 30 seconds, 1 and 2 minutes.

Pomodoro - Basic Pomodoro timer. 25 minutes "BUSY", 5 minutes "REST"

Notifications - Notifications from Home Assistant are availible. I have phone calls make the screen red and say "ON A CALL"

# Issues that were resolved

Esphome removed external componants, but luckily there is now a native componant for the display.

Display must be set as 20Mhz. Any higher wont show correctly

Timers resetting themselves - I noticed that the screen is pushing against the enclosure which was causing ghost touches. Just had to pull the screen forward a bit.
