# SingleDigitDrawer
## Motivation
I'm working on project that will eventually become a digital clock widget-like app for personal use. While doing that I ran across a problem: turned out I had no nice-looking digits for the clock's face. That's why I made this utility that can draw a single digit imitating a seven segment display.

## Installation
The app uses SDL2 library so SDL2 is required to build and run it. Use my Makefile or write the gcc command manually.

## Usage
This utility is meant mostly for my personal use so it is pretty junky and I don't plan on adding a -\-help  flag or anything. Either way if you want to play around with it this is what you should know:
1) You can set height and width of the window with -h and -w flags respectively (naturally you'll need to enter an integer after each flag)
2) After that the program will expect you to enter a digit that you want it to display. If you enter a number larger than 9 it will take its last digit and draw that.
3) To quit enter any negative number (no, it does not accept ctrl+C signal and it doesn't read any input from your mouse. <sub><sup> It's SDL, baby, those buttons aren't functional till I say so! B-) </sup></sub> )
