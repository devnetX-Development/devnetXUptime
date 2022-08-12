# devnetXUptime
A simple Arduino Uptime Library. This library is roll-over proof for 34 years.


## Library Functions
### Initialization
```c++
#include <devnetXUptime.h>
```
The library instantiates and initializes itself. Just include the header file where you need access to the uptime.

### Inside the loop()
It is **required** to call the ```Uptime.Process()``` method inside your ```loop()``` function.
This method will calculate the current uptime and trigger the ```Uptime.OnUptimeTick(...)``` callback, if you defined it. See examples.

### Uptime Methods
- ```Uptime.Days()```
	Returns the number of days passed since power-on.
- ```Uptime.Hours()```
	Returns the number of hours passed since power-on (relative to the days).
- ```Uptime.Minutes()```
	Returns the number of hours passed since power-on (relative to the hours).
- ```Uptime.Seconds()```
	Returns the number of hours passed since power-on (relative to the minutes).
- ```Uptime.ToString()```
	Creates a formatted char array buffer that contains the current uptime and returns a pointer to it.
- ```Uptime.SetUptimeTickInterval(ms)```
	If you wish to display the uptime periodically, You can use the ```Uptime.OnUptimeTick(...)``` callback.
	The interval can be defined in milliseconds by calling the above method with the interval as the ```ms``` parameter.
	*Note:* The value ```5000``` will trigger the callback every 5 seconds.
	*Note:* The value ```0``` will deactivate the callback. This is also the default behaviour.

### OnUptimeTick Callback
```c++
Uptime.OnUptimeTick([]() {
	Serial.print("The uptime is: ");
	Serial.println(Uptime.ToString());
});
```
Use this callback to display the uptime periodically.
The interval can be set by calling the ```Uptime.SetUptimeTickInterval(ms)``` method. See the notes above.

---
Have fun! :)
