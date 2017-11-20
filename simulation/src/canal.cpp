/********************************************//**
 * \file   canal.cpp
 * \brief  Canal and lane implementation.
 * \author Zuzanna Kaptur
 * \date   2015
 ***********************************************/
 
#include "sc.h"
#include <cmath>
using namespace simulation;

//===============================================
double Canal::canal_using_time = 0.;
//===============================================
Lane::Lane(double i_depth)
{
	depth = i_depth;
	free = true;
	last_use_direction = 1;
	last_use_time = -Tt;	//ustawiamy tak, aby przy obliczaniu stanu toru dla zerowej chwili otrzymac wartosc 0
	lane_using_time = 0.;
}
//----------------------------------------------
Lane::Lane()
{
	depth = 0.;
	free = true;
	last_use_direction = 1;
	last_use_time = -Tt;	//ustawiamy tak, aby przy obliczaniu stanu toru dla zerowej chwili otrzymac wartosc 0
	lane_using_time = 0.;
}
//----------------------------------------------
int Lane::getState(Watercraft* pwc)
{
	if ((sim_clock - last_use_time) >= Tt) return 0;
	if (pwc->direction == last_use_direction) return -1;
	return 1;
}
//----------------------------------------------
double Lane::SailTime(Watercraft* pwc)
{
	return (9.5 + pwc->weight / 1000 + log(pwc->weight / 100) / log(5) + 5 * getState(pwc));
}

//===============================================

Canal::Canal(int n)
{
	lane_table = new Lane[n];
	number_of_lanes = n;
	lane_table[0].depth = 2;
	lane_table[1].depth = 6;
	lane_table[2].depth = 12;
}
//----------------------------------------------
void Canal::setDepth(int n, double i_depth)
{
	lane_table[n].depth = i_depth;
}
//----------------------------------------------
bool Lane::isAvailable(Watercraft* candidate)
{
	if (!this->free) return false;
	if (candidate->weight / 1000 > this->depth) return false;
	return true;
}
//----------------------------------------------
bool Canal::isFree(int lane_number)
{
	return lane_table[lane_number].free;
}
//----------------------------------------------
void Canal::disp()
{
	for (int i = 0; i < 3; i++)
	{
		cout << "Tor nr" << i << ": ";
		if (lane_table[i].free) cout << "wolny";
		else cout << "zajety";
		cout << endl;
	}
}
//----------------------------------------------
double Canal::getDepth(int n)
{
	return lane_table[n].depth;
}
/////////////////////////////////////////////////
//***********************************************
