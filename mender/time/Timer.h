//*****************************************************************************
//render/time/Timer.h**********************************************************
//*****************************************************************************

#pragma once

//Render Library Includes
#include <render/gl.h>

//Standard Library Includes
#include <cstdint>
#include <chrono>

namespace render
{
//-----------------------------------------------------------------------------
//TimerBase--------------------------------------------------------------------
//-----------------------------------------------------------------------------
class TimerBase
{
private:
	typedef std::chrono::high_resolution_clock Clock;
protected:
//	std::chrono::time_point start_time;
//	std::chrono::time_point stop_time;
	uint64_t start_time;	//microseconds
	uint64_t stop_time;		//microseconds
public:

	TimerBase() : start_time(0), stop_time(0) {}

	virtual uint64_t getTime() = 0;

	void start();
	void stop();

	virtual double ns() = 0;		//nanoseconds
	virtual double us() = 0;		//microseconds
	virtual double ms() = 0;		//milliseconds
	virtual double seconds() = 0;	//seconds
};
// End class TimerBase

//-----------------------------------------------------------------------------
//Timer------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class Timer : public TimerBase
{
private:
	uint64_t frequency;
public:
	Timer();

	uint64_t getTime();
	double      time();

	double ns();		//nanoseconds
	double us();		//microseconds
	double ms();		//milliseconds
	double seconds();	//seconds
};
// End class Timer

//-----------------------------------------------------------------------------
//glTimerSynch-----------------------------------------------------------------
//-----------------------------------------------------------------------------
class glTimerSynch : public TimerBase
{
public:
	glTimerSynch() : TimerBase() {}

	uint64_t getTime();

	void start();
	void  stop();

	double ns();		//nanoseconds
	double us();		//microseconds
	double ms();		//milliseconds
	double seconds();	//seconds
};
// End class glTimerSynch

//-----------------------------------------------------------------------------
//glTimerAsynch----------------------------------------------------------------
//-----------------------------------------------------------------------------
class glTimerAsynch : public TimerBase
{
private:
	GLuint start_query_id;
	GLuint  stop_query_id;

public:
	glTimerAsynch();

	uint64_t getTime();

	void start();
	void stop();

	double ns();		//nanoseconds
	double us();		//microseconds
	double ms();		//milliseconds
	double seconds();	//seconds
};
// End class glTimerAsynch
};
// End namespace render
