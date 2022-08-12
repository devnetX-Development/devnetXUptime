#include <Arduino.h>
#include <devnetXUptime.h>

UptimeClass::UptimeClass(void)
{
	this->MillisLast = 0;
	this->MillisOverflows = 0;
	
	this->UptimeTickInterval = 0;
	this->UptimeTickLast = 0;

	memset(this->Buffer, 0, sizeof(this->Buffer));
	
	this->CalculateUptime();
}

void UptimeClass::Process(void)
{
	// Run once per second
	if (UPTIME_MILLIS() - this->MillisLast >= 1000)
		this->CalculateUptime();

	if (this->UptimeTickInterval == 0)
		return;

	// Run once per UptimeTickInterval
	if (UPTIME_MILLIS() - this->UptimeTickLast >= this->UptimeTickInterval)
	{
		this->UptimeTickLast = UPTIME_MILLIS();
		
		// Trigger callback if defined
		if (this->UptimeTickFunction != NULL)
			(*this->UptimeTickFunction)();
	}
}

void UptimeClass::CalculateUptime(void)
{
	// Check if millis() overflow occured
	if (MillisLast > UPTIME_MILLIS())
	 	this->MillisOverflows++;

	// Save last millis
	MillisLast = UPTIME_MILLIS();

	// Increase every second
	uint32_t uptime = (uint32_t)((((uint64_t)(MillisOverflows) << 32) + MillisLast) / 1000);

	// Calculate Days, Hours, Minutes, Seconds
	this->UptimeDays = uptime / 86400;
	this->UptimeHours = uptime % 86400 / 3600;
	this->UptimeMinutes = uptime % 3600 / 60;
	this->UptimeSeconds = uptime % 60;
}

char *UptimeClass::ToString(void)
{
	snprintf(this->Buffer, sizeof(this->Buffer), "%u day%s %02u:%02u:%02u%c",
			 this->UptimeDays,
			 this->UptimeDays == 1 ? "" : "s",
			 this->UptimeHours,
			 this->UptimeMinutes,
			 this->UptimeSeconds,
			 0);

	return this->Buffer;
}

uint16_t UptimeClass::Days(void)
{
	return this->UptimeDays;
}

uint8_t UptimeClass::Hours(void)
{
	return this->UptimeHours;
}

uint8_t UptimeClass::Minutes(void)
{
	return this->UptimeMinutes;
}

uint8_t UptimeClass::Seconds(void)
{
	return this->UptimeSeconds;
}

void UptimeClass::SetUptimeTickInterval(uint32_t ms)
{
	this->UptimeTickInterval = ms;
	this->UptimeTickLast = UPTIME_MILLIS();
}

UptimeClass Uptime;