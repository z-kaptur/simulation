/********************************************//**
 * \file   process.h
 * \brief  Process implementation.
 * \author Krzysztof Bakowski (krzysztof.bakowski@put.poznan.pl)
 * \date   2013-05-08
 ***********************************************/

#ifndef PROCESS_H
#define PROCESS_H
/////////////////////////////////////////////////
class Process
{
public:

	//! Process constructor.
	Process(): phase(0), terminated(false)
	{
		my_event = new Event(this);

		id = id_counter++;
	}

	//! Delete event when deleting process.
	virtual ~Process();

	//! Virtual method responsible for execution of actions related to a specific time event.
	void virtual execute()=0;
	
	//! Get activation time.
	double time();
	
	//! Schedule process activation.
	void activate(double time);

	//! Get process ID.
	unsigned int get_pid(){ return id;}

	int phase;					//!< Process phase.

	bool terminated;			//!< Process termination indicator.

private:

	Event* my_event;				//!< Event pointer.

	unsigned int id;				//!< Process ID - PID.

	static unsigned int id_counter;	//!< Counter for PID.
};
/////////////////////////////////////////////////
//***********************************************
#endif /*PROCESS_H*/
