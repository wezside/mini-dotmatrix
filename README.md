mini-dotmatrix
==============

Arduino code for 4x4 LED matrix display. This configuration uses multiplexing with a Shift Register 74hc595.

Animation
---------

Row to animate: 
	
		0110

		0000 0110
		000 0110
		00 0110
		0 0110
		0110
	   0110 
	  0110 0
	 0110 00
	0110 000


	0000 0000 0000
|			  0110
	0000 0000 0110
	>> 8
	0000 0000 0110
	>> 7
	0000 0000 1100
	>> 6
	0000 0000 1100
	>> 5
	0000 0001 1000
