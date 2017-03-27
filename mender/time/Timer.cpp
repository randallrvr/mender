//*****************************************************************************
//render/time/Timer.cpp********************************************************
//*****************************************************************************

//Header Include
#include "Timer.h"

//Namespaces
using namespace render;
using namespace std::chrono;

//-----------------------------------------------------------------------------
//TimerBase--------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TimerBase::start()
{
	auto now = Clock::now();
	start_time = duration_cast<nanoseconds>(now.time_since_epoch()).count();
}
//-----------------------------------------------------------------------------
void TimerBase::stop()
{
	auto now = Clock::now();
	stop_time = duration_cast<nanoseconds>(now.time_since_epoch()).count();
}


//-----------------------------------------------------------------------------
//Timer------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Timer::Timer() : TimerBase()
{

}
//-----------------------------------------------------------------------------
uint64_t Timer::getTime()
{
}
//-----------------------------------------------------------------------------
double Timer::time()
{
}
//-----------------------------------------------------------------------------
double Timer::ns()
{
	return double(stop_time - start_time) * 1000000000.0 / double(frequency);
}
//-----------------------------------------------------------------------------
double Timer::us()
{
	return double(stop_time - start_time) * 1000000.0 / double(frequency);
}
//-----------------------------------------------------------------------------
double Timer::ms()
{
	return double(stop_time - start_time) * 1000.0 / double(frequency);
	//	return(time() / 1000.0);
}
//-----------------------------------------------------------------------------
double Timer::seconds()
{
	return double(stop_time - start_time) / double(frequency);
}


//-----------------------------------------------------------------------------
//glTimerSynch-----------------------------------------------------------------
//-----------------------------------------------------------------------------
uint64_t glTimerSynch::getTime()
{
	GLint64 time;
	glGetInteger64v(GL_TIMESTAMP, &time);
	return (uint64_t)time;
}
//-----------------------------------------------------------------------------
void glTimerSynch::start()
{
	GLint64 start;
	glGetInteger64v(GL_TIMESTAMP, &start);
	start_time = (uint64_t)start;
}
//-----------------------------------------------------------------------------
void glTimerSynch::stop()
{
	GLint64 stop;
	glGetInteger64v(GL_TIMESTAMP, &stop);
	stop_time = (uint64_t)stop;
}
//-----------------------------------------------------------------------------
double glTimerSynch::ns()
{
	return double(stop_time - start_time);
}
//-----------------------------------------------------------------------------
double glTimerSynch::us()
{
	return double(stop_time - start_time) / 1000.0;
}
//-----------------------------------------------------------------------------
double glTimerSynch::ms()
{
	return double(stop_time - start_time) / 1000000.0;
}
//-----------------------------------------------------------------------------
double glTimerSynch::seconds()
{
	return double(stop_time - start_time) / 1000000000.0;
}

//-----------------------------------------------------------------------------
//glTimerAsynch-----------------------------------------------------------------
//-----------------------------------------------------------------------------
glTimerAsynch::glTimerAsynch() : TimerBase()
{
	glGenQueries(1, &start_query_id);
	glGenQueries(1,  &stop_query_id);
}
//-----------------------------------------------------------------------------
void glTimerAsynch::start()
{
	glQueryCounter(start_query_id, GL_TIMESTAMP);
}
//-----------------------------------------------------------------------------
void glTimerAsynch::stop()
{
	glQueryCounter(stop_query_id, GL_TIMESTAMP);
}
//-----------------------------------------------------------------------------
uint64_t glTimerAsynch::getTime()
{
	GLint done;

	done = 0;
	while(!done)	glGetQueryObjectiv(start_query_id, GL_QUERY_RESULT_AVAILABLE, &done);
	done = 0;
	while(!done)	glGetQueryObjectiv( stop_query_id, GL_QUERY_RESULT_AVAILABLE, &done);

	glGetQueryObjectui64v(start_query_id, GL_QUERY_RESULT, &start_time);
	glGetQueryObjectui64v( stop_query_id, GL_QUERY_RESULT,  &stop_time);

	return stop_time;
}
//-----------------------------------------------------------------------------
double glTimerAsynch::ns()
{
	this->getTime();
	return double(stop_time - start_time);
}
//-----------------------------------------------------------------------------
double glTimerAsynch::us()
{
	this->getTime();
	return double(stop_time - start_time) / 1000.0;
}
//-----------------------------------------------------------------------------
double glTimerAsynch::ms()
{
	this->getTime();
	return double(stop_time - start_time) / 1000000.0;
}
//-----------------------------------------------------------------------------
double glTimerAsynch::seconds()
{
	this->getTime();
	return double(stop_time - start_time) / 1000000000.0;
}