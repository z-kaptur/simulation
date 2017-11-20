/********************************************//**
 * \file   port.cpp
 * \brief  Port class implementation.
 * \author Zuzanna Kaptur
 * \date   2015
 ***********************************************/
#include "sc.h"
using namespace simulation;

//===============================================
double Port::using_time [3]= {0., 0., 0.};
double Port::unit_per_min[3] = { 50.0 / 6, 10.0, 0 };
//===============================================

Port::Port(int*num_res)
{
	for (int i = 0; i < 3; i++)
	{
		number_of_resources[i] = num_res[i];
		available_resources[i] = num_res[i];
	}
}
//----------------------------------------------
int Port::get_number_of_resources(Resource res)
{
	return number_of_resources[res];
}
//----------------------------------------------
int Port::get_available_resources(Resource res)
{
	return available_resources[res];
}
//----------------------------------------------
void Port::show_available_resources()
{
	cout << "***DOSTEPNE ZASOBY W PORCIE***" << endl;
	cout << "Rampy: " << available_resources[ramp] << endl;
	cout << "Dzwigi: " << available_resources[crane] << endl;
	cout << "Miejsca dla jachtow: " << available_resources[yacht_site] << endl;
}

/////////////////////////////////////////////////
//***********************************************
