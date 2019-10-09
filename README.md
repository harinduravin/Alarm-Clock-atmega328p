# Alarm-Clock-atmega328p
Alarm Clock with display and 4 control buttons

The alarm clock is capable of storing the time even at no external power condition
Display the date and time through an LCD display
Allows the user to select options through a menu
* Home - Date and time
* Change time
* Add alarm
* Delete and manage alarms

The device consist of an RTC module, and a Solid state relay that can trigger a powerful bell if necessary.
The buttons operate through the use of interrupts
Alarms are stored in the eeprom of the chip. This allows the device to keep track of previously set alarms
even after power is disconnected.
