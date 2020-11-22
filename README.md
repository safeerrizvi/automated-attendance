# **automated-attendance**

*An automated attendance system prototype made using a Raspberry Pi + NEO 6M in C for our first semester university project at FAST NUCES Karachi.*

- Compares long and lat from GPS with cpu time against hardcoded values for the class location and schedule.
- Writes the attendance log in a file shared on the network. 
- Opens browser with current long lat on google maps (invoking browser with vars passed into url) & a short audio recording using the Raspberry Pi's microphone at press of a button.
