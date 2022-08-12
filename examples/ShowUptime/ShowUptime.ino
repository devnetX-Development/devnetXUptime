#include <Arduino.h>
#include <devnetXUptime.h>

void setup()
{
	// Init Serial
	Serial.begin(115200);

	// Set the UptimeTick callback interval to 1 second
	Uptime.SetUptimeTickInterval(1000);

	// Define the callback functionality
	Uptime.OnUptimeTick([]() {
		Serial.print("The uptime is: ");
		Serial.println(Uptime.ToString());
	});

	Serial.println("Welcome!");
}

void loop()
{
	// Run the Uptime Process Loop
	Uptime.Process();
}