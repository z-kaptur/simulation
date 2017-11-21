/********************************************//**
 * \file   sc.h
 * \brief  Main header file
 * \author Zuzanna Kaptur
 * \date   2015
 ***********************************************/
#ifndef SC_H_
#define SC_H_
//***********************************************
/////////////////////////////////////////////////
//-----------------------------------------------
// STANDARD C/C++ LIBRARIES:
//-----------------------------------------------

#include <iostream>
#include <fstream>
#include <iomanip>
//#include <string>
#include <sstream>
#include <vector>
#include <cmath>
//#include <cstdlib>

//-----------------------------------------------
// USING DECLARATIONS:
//-----------------------------------------------
using namespace std;

//-----------------------------------------------
// ENUM TYPES:
//-----------------------------------------------

//! Typ wyliczeniowy reprezentujacy typy zasobow w porcie
enum Watercraft_type { cargo, roro, container_ship1, yacht };

//! Typ wyliczeniowy reprezentujacy typy zasobow w porcie
enum Resource { ramp, crane, yacht_site };

using namespace std;

//-----------------------------------------------
// PROJECT HEADER FILES:
//-----------------------------------------------

#include "rng.h"
#include "event_scheduling.h"
#include "process.h"
#include "watercraft.h"
#include "port.h"
#include "canal.h"
#include "queue.h"
#include "confidence_interval_estimation.h"


//-----------------------------------------------
// SIMULATION NAMESPACE:
//-----------------------------------------------

namespace simulation
{
	extern EventList agenda;
	extern double sim_clock;
}


#endif /* SC_H_ */
