# arduino-clock-divider
A clock divider that uses a arduino. It divides by 1; 2; 3; 4; 5; 6; 7; 8; 9 and 10.

Animations:
       1.Activate them by unplugging the clock source.
       2.Use the divide by 10 as a clock input for animations.
       3.To select animations, Send a trigger to the divide by 9 pin.
       4.All of the animations are displayed on the divide by 1 to 8 leds
       5.Even thought it is displaying animations, it is still sending gates.
       6.To get back to dividing, just plug the clock jack back in.
        
THIS DIVIDER WILL NOT WORK WITH STEREO CABLES, as it relies on the fact that the mono jack shorts the second terminal of the stereo jack to ground. So If you want to make it work with stereo cables, than you have to connect the second contact to ground on the other side of the cable.

TO MAKE THI WORK WITH STEREO CABLES, you just need to connect pin A0 to ground. That way the arduino will think you have a jack connected all the time, thus not deploing any animations at all. A optional thing you can do is to add a switch to the A0 that swithecs between 5 and 0 Volts.
