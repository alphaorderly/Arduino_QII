# QIIDA
##### Open source Distance-based instrument   
##### FOR EVERYONE
  
  
## INTRODUCTION
There's two instrument we made.

###### 1. Percussion Instrument

There's four button each ( LEFT-LEFT, LEFT-RIGHT, RIGHT-LEFT, RIGHT-RIGHT )
which defined on top of the source.

and This instrument use ISD1820 recording module which is directly connected to arduino

you just need to connect Button each, and ground and VIN to Arduino and connect speaker + to amp.

Each button will play Different percussion sound and Dot matrix which connected on Analog pins will be turned on along that button push.

All Pins you need to connect to Arduino Are Completely Defined and has description 

other modules you need is DF Player mini MP3 module, 0.5W Speaker amp module.

###### 1. stringed / wind  Instrument

it'll use VL53l0x as distance sensor. but you can also use any other vl53l(n)x.

all sound file is in Separate folder on Project folder that you need to put on sd card

and sort them with DRIVESORT ( fat 32 sorting program )

other modules you will need is DFPlayer mini, amp Module.

## CIRCUIT GUIDE

- All buttons except recording module use built-in pullups   

- Distance sensor should be connected to SDA, SCL on Arduino board   

- MP3 Module should be connected to 10, 11 and need 10k Ohm resistance between them   


## THINGS TO UPDATE

>  add more instrument        
> optimize percussion code.    
> compatibility for other arduino board.    

