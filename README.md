DIY Console Programs
====================

This repo will hold some programs for a DIY game console project built
at [CHIPLAY 2014](http://chiplay.org/)

The project consists of buttons and LEDs on a breadboard wired into a MSP430G2553 from TI.

Pin layout
----------

Button pins:
```
  2
4   5
  3
```

LED pins:
```
 6  7 13 12
 8  9 15 14
10 19 18 11
```

![Console](https://raw.githubusercontent.com/pR0Ps/diy-console/master/console.jpg)

Programs
========

Test
----
A simple program to make sure everything is wired up properly.
It flashes each LED on, then lights up the first 4 LEDs in response to
button presses

Maze
----
The player (the flashing LED) has to navigate through the maze using
the buttons to move. Lit LEDs are walls.
