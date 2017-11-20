/********************************************//**
 * \file   process.cpp
 * \brief  Process implementation.
 * \author Krzysztof Bakowski (krzysztof.bakowski@put.poznan.pl)
 * \date   2013-05-08
 ***********************************************/
#include "sc.h"

/////////////////////////////////////////////////
unsigned int Process::id_counter = 0;
//-----------------------------------------------
double Process::time()
{
	return my_event->event_time;
}
//----------------------------------------------
void Process::activate(double time)
{
	my_event->event_time = simulation::sim_clock + time;

	simulation::agenda.schedule(my_event);
}
//----------------------------------------------
Process::~Process()
{
	if(my_event) delete my_event;

	my_event = NULL;
}
/////////////////////////////////////////////////
//***********************************************
