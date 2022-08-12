/// \file      devnetXUptime.h
/// \brief     A simple Arduino Uptime Library.
/// \author    Alexej Goujine (dev@devnetx.at)
/// \copyright Copyright (c) 2020-2022 devnetX Development

#pragma once

#include <Arduino.h>

#if !defined(DEVNETXUPTIME_BUFFERSIZE)
	#define DEVNETXUPTIME_BUFFERSIZE 24U
#endif

#define UPTIME_MILLIS() (millis())
// #define UPTIME_MILLIS() (millis() + ((2^32) - 10000)) // For testing purposes only (millis overflow after 10 seconds)

class UptimeClass
{
	public:

		/// Construct a new Uptime object
		/// 
		UptimeClass(void);
		
		/// Uptime Process method. Must be called once per loop()
		/// 
		void Process(void);
		
		/// Returns the uptime as formatted c_str
		/// 
		/// @return char* Formatted Uptime c_str
		char *ToString(void);

		/// Returns the Uptime Days
		/// 
		/// @return uint16_t Uptime Days
		uint16_t Days(void);

		/// Returns the uptime Hours
		/// 
		/// @return uint8_t Uptime Hours
		uint8_t Hours(void);

		/// Returns the uptime Minutes
		/// 
		/// @return uint8_t Uptime Minutes
		uint8_t Minutes(void);

		/// Returns the uptime Seconds
		/// 
		/// @return uint8_t Uptime Seconds
		uint8_t Seconds(void);

		/// Set the Uptime Tick Interval
		/// 
		/// @param ms Interval in milliseconds
		void SetUptimeTickInterval(uint32_t ms);

		// Callback
		void OnUptimeTick(void (*func)()) { this->UptimeTickFunction = func; }

	private:

		char Buffer[DEVNETXUPTIME_BUFFERSIZE];

		uint8_t MillisOverflows;
		uint32_t MillisLast;
		
		uint16_t UptimeDays;
		uint8_t  UptimeHours;
		uint8_t  UptimeMinutes;
		uint8_t  UptimeSeconds;

		uint32_t UptimeTickInterval;
		uint32_t UptimeTickLast;

		void CalculateUptime(void);
		void (*UptimeTickFunction)();
};

extern UptimeClass Uptime;