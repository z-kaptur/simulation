/********************************************//**
 * \file   watercraft.cpp
 * \brief  Watercraft class implementation.
 * \author Zuzanna Kaptur
 * \date   2015
 ***********************************************/
#include "sc.h"
#include<Windows.h>
using namespace simulation;

//===============================================
unsigned int Watercraft::number = 0;
unsigned int Watercraft::counter = 0;

unsigned int Watercraft::number_type[4] = { 0, 0, 0, 0 };
unsigned int Watercraft::serviced = 0;
unsigned int Watercraft::serviced_type[4] = { 0, 0, 0, 0 };

double Watercraft::waiting_time = 0.;
double Watercraft::waiting_time_type[4] = { 0.,0.,0.,0. };
double Watercraft::max_wait_time = 0.;

ofstream Watercraft::watercraft_stats;

ofstream Watercraft::generator;

ofstream Watercraft::weight_stats;

QueueContainer* Watercraft::in_queue=new QueueContainer(5);
QueueContainer* Watercraft::out_queue=new QueueContainer(2);
int tablica[3] = { 15, 6, 45 };
Port* Watercraft::port = new Port(tablica);
Canal* Watercraft::canal = new Canal(3);


double Watercraft::lambda=12.066;
int Watercraft::seed_lambda=55;
int Watercraft::seed_type=9623;
int Watercraft::seed_load[4] = { 842, 25, 3464, 5 };
int Watercraft::seed_yacht_time=2517;
int Watercraft::seed_yacht_weight=425;
int Watercraft::seed_cargo_weight=3545;
int Watercraft::seed_roro_weight=257537;
int Watercraft::seed_container_weight=17337;
//===============================================

void Watercraft::show_available_resources(){ port->show_available_resources(); cout << endl; canal->disp();  }

Watercraft::Watercraft()
{
	id = counter;
	arrival = sim_clock;
	departure = 0.;
	direction = 1;
	start_service = 0.;
	used_lane = -1;
	double random = Uniform(seed_type);
	type = (random<=0.3)?cargo:(random<=0.6)?roro:(random<=0.8)?container_ship1:yacht;

	for (int i = 0; i < 3; i++) required_resources[i]=0;

	switch (type)
	{
	case cargo:
		required_resources[(int)ramp] = 1;
		load_prob = 4;
		weight = Uniform(seed_cargo_weight) * 2250 + 750;
		weight_stats << weight << "\n";
		break;
	case roro:
		required_resources[(int)ramp] = 2;
		load_prob = 75;
		weight = Uniform(seed_roro_weight) * 2000 + 500;
		break;
	case container_ship1:
		required_resources[(int)crane] = 1;
		load_prob = 5;
		weight = Uniform(seed_container_weight) * 2500 + 500;
		break;
	case yacht:
		required_resources[(int)yacht_site] = 1;
		load_prob = 0;
		weight = Uniform(seed_yacht_weight) * 1900 + 100;
	}

	load = 0.7*weight;
	number++;
	counter++;
	number_type[(int)type]++;
	
}
//----------------------------------------------
Watercraft::~Watercraft()
{
}
//----------------------------------------------
void Watercraft::show_required_resources()
{
	cout << endl << "***ZASOBY POTRZEBNE DO OBSLUGI JEDNOSTKI***" << endl;
	cout << "Rampy: " << required_resources[0] << endl;
	cout << "Dzwigi: " << required_resources[1] << endl;
	cout << "Msc jachtowe: " << required_resources[2] << endl;

}
//----------------------------------------------
int Watercraft::checkLanes()
{
	if (direction && !checkResources()) return -1;
	int best_lane = -1;
	double min_depth = 9999;
	for (int i = 0; i < 3; i++)
	{
		if (canal->lane_table[i].isAvailable(this))
		{
			best_lane = i;
			min_depth = canal->lane_table[i].depth;
		}
	}
	if (best_lane == -1) return -1;

	return best_lane;
}
//----------------------------------------------
Watercraft* Watercraft::LaneRelease(int lane_number)
{
	//cout << "release lane" << endl;
	int queue_number = -1;
	int current_id = 999999999;
	Watercraft* pwc=NULL;
	Watercraft* current_pwc = NULL;
	for (int i = 0; i < in_queue->number; i++)
	{
		pwc = in_queue->queueTable[i].checkFirst();
		if (pwc)
		{
			if (canal->lane_table[lane_number].isAvailable(pwc) && pwc->checkResources() && current_id > pwc->id)
			{
				//cout << "a tu co?" << endl;
				queue_number = i;
				current_id = pwc->id;
				current_pwc = pwc;
			}
		}
	}

	if (current_pwc && queue_number >= 0 && current_pwc->checkResources())
	{
		pwc = in_queue->pop(queue_number);

		pwc->used_lane = lane_number;
		canal->lane_table[lane_number].free = false;

		pwc->activate(0);
		return pwc;
	}
	
	queue_number = -1;
	current_id = 999999999;
	current_pwc = NULL;
	for (int i = 0; i < out_queue->number; i++)
	{
		pwc = out_queue->queueTable[i].checkFirst();
		if (pwc)
		{
			if (canal->lane_table[lane_number].isAvailable(pwc) && current_id > pwc->id_afterservice)
			{
				queue_number = i;
				current_id = pwc->id_afterservice;
				current_pwc = pwc;
			}
		}
	}

	if (queue_number >= 0)
	{
		pwc = out_queue->pop(queue_number);
		pwc->activate(0);
		pwc->used_lane = lane_number;
		canal->lane_table[lane_number].free = false;
		return pwc;
	}
	
	//cout << "nie wysz³o" << endl;
	return NULL;
}
//----------------------------------------------
Watercraft* Watercraft::ResourceRelease(Resource res)
{
	//cout << "release resource" << endl;
	int queue_number = -1;
	int current_lane = -1;
	int lane_number = -1;
	int current_id = 9999999;
	Watercraft* pwc=NULL;
	Watercraft* current_pwc = NULL;
	
	for (int i = 2 * (int)res; i < 2 * (int)res + 2; i++)
	{
		if (i == 5) continue;
		pwc = in_queue->queueTable[i].checkFirst();
		if (pwc == NULL) continue;
		current_lane = checkLanes();
		if (pwc->id<current_id && current_lane!=-1)
		{
			queue_number = i;
			lane_number = current_lane;
			current_id = pwc->id;
			current_pwc = pwc;

		}
	}
	
	if (pwc && queue_number >= 0 && pwc->checkResources())
	{
		pwc = in_queue->pop(queue_number);
		pwc->activate(0);
		pwc->used_lane = lane_number;
		canal->lane_table[lane_number].free = false;
		
		return pwc;
	}
	//cout << "nie wysz³o" << endl;
	return NULL;
}
//----------------------------------------------
void Watercraft::execute()
{
	if (port->available_resources[yacht_site] > 45) cout << "UPS" << endl;
	double sail_time;
	double next;
	int id_counter = 0;
	bool active = true;
	double test;
	while (active)
	{
		switch (phase)
		{
		case 0: 
				next = Exponential(lambda, seed_lambda);
				(new Watercraft)->activate(next);
				generator << next << "\n";
				arrival = sim_clock;

				if (allocateLane() ) {
					active = true; 
				}
				else
				{
					active = false;
					in_queue->push(this);
				}
				phase = 1;
				break;

		case 1: 
				for (int i = 0; i < 3; i++)	port->available_resources[i] -= required_resources[i];
			
				sail_time = canal->lane_table[used_lane].SailTime(this);
				activate(sail_time);

				start_service = sim_clock;
				serviced++;
				serviced_type[(int)type]++;
				waiting_time += sim_clock - arrival;
				waiting_time_type[(int)type] += sim_clock - arrival;
				if (sim_clock - arrival>max_wait_time) max_wait_time = sim_clock - arrival;
				watercraft_stats << sim_clock << ';' << sim_clock - arrival << '\n';
		
				canal->lane_table[used_lane].current = this;
				canal->lane_table[used_lane].free = false;
				canal->lane_table[used_lane].last_use_direction = direction;
				canal->lane_table[used_lane].lane_using_time += sail_time;
				canal->canal_using_time += sail_time;
				
				phase = 2;
				active = false;
				break;

		case 2:
				direction = 0;
		
				canal->lane_table[used_lane].current = NULL;
				canal->lane_table[used_lane].free = true;
				canal->lane_table[used_lane].last_use_time = sim_clock;
				
				LaneRelease(used_lane);
				used_lane = -1;
				activate(Service());
				
				phase = 3;
				active = false;
				break;

		case 3:	
			id_afterservice = id_counter++;
				if (allocateLane()) active = true;
				else
				{
					active = false;
					out_queue->push(this);
				}
				phase = 4;
				break;

		case 4:
				for (int i = 0; i < 3; i++) port->available_resources[i] += required_resources[i];
				
				sail_time = canal->lane_table[used_lane].SailTime(this);
				activate(sail_time);

				canal->lane_table[used_lane].current = this;
				canal->lane_table[used_lane].free = false;
				canal->lane_table[used_lane].last_use_direction = direction;
				canal->lane_table[used_lane].lane_using_time += sail_time;
				canal->canal_using_time += sail_time;
				
				Resource res;
				for (int i = 0; i < 3; i++)	if (required_resources[i]) res = (Resource)i;
				ResourceRelease(res);

				phase = 5;
				active = false;
				break;

		case 5:
				canal->lane_table[used_lane].current = NULL;
				canal->lane_table[used_lane].free = true;
				canal->lane_table[used_lane].last_use_time = sim_clock;

				LaneRelease(used_lane);
				used_lane = -1;

				active = false;
				terminated = true;
		}
	}
	
}
//----------------------------------------------
bool Watercraft::checkResources()
{
	for (int i = 0; i < 3; i++)
	{
		if (port->available_resources[i]<required_resources[i]) return false;
	}
	return true;
}
//----------------------------------------------
bool Watercraft::allocateLane()
{
	used_lane = checkLanes();
	if (used_lane == -1) return false;
	canal->lane_table[used_lane].free = false;
	
	return true;

}
//----------------------------------------------
double Watercraft::Service()
{
	double service_time = 0.;
	double los = Uniform(seed_load[(int)type]);
	int mult = (los < load_prob) ? 2 : 1;

	for (int i = 0; i < 3; i++)
	{
		if (required_resources[i] != 0)
		{
			if (i == 2)
			{
				service_time = Uniform(seed_yacht_time)*3600+720;
				port->using_time[i] += service_time;
			}
			else
			{
				service_time = load / (required_resources[i]*mult*port->unit_per_min[i]);
				port->using_time[i] += service_time*required_resources[i];
			}

		}
	}
	if (mult == 1) weight = 0.3*weight;
	return service_time;
}
//----------------------------------------------
void Watercraft:: show_statistics()
{
	cout <<endl<< "Liczba wygenerowanych jednostek: " << number << endl;
	cout << "Liczba obsluzonych jednostek:" << serviced << endl<<endl;

	cout << "Liczba wygenerowanych drobnicowcow:" << number_type[0] << endl;
	cout << "Liczba obsluzonych drobnicowcow:" << serviced_type[0] << endl<<endl;

	cout << "Liczba wygenerowanych statkow ro-ro:" << number_type[1] << endl;
	cout << "Liczba obsluzonych statkow ro-ro:" << serviced_type[1] << endl<<endl;

	cout << "Liczba wygenerowanych kontenerowcow:" << number_type[2] << endl;
	cout << "Liczba obsluzonych kontenerowcow:" << serviced_type[2] << endl<<endl;

	cout << "Liczba wygenerowanych jachtow:" << number_type[3] << endl;
	cout << "Liczba obsluzonych jachtow:" << serviced_type[3] << endl<<endl;

	cout << "Sredni czas oczekiwania na obsluge: " << waiting_time/serviced << endl;
	cout << "Sredni czas oczekiwania na obsluge drobnicowcow: " << waiting_time_type[0] / serviced_type[0] << endl;
	cout << "Sredni czas oczekiwania na obsluge statkow ro-ro: " << waiting_time_type[1] / serviced_type[1] << endl;
	cout << "Sredni czas oczekiwania na obsluge kontenerowcow: " << waiting_time_type[2] / serviced_type[2] << endl;
	cout << "Sredni czas oczekiwania na obsluge jachtow: " << waiting_time_type[3] / serviced_type[3] << endl<<endl;

	cout << "Maksymalny czas oczekiwania na obluge: " << max_wait_time << endl << endl;

	cout << "Procent wykorzystania ramp: " <<(port->using_time[0] / (port->number_of_resources[0]*sim_clock))*100<<"%"<< endl;
	cout << "Procent wykorzystania dzwigow: " << (port->using_time[1] / (port->number_of_resources[1] * sim_clock)) * 100 << "%" << endl;
	cout << "Procent wykorzystania przystani dla jachtow: " << (port->using_time[2] / (port->number_of_resources[2] * sim_clock)) * 100 << "%" << endl<<endl;

	
	for (int i = 0; i < 3; i++)
		cout << "Procentowy czas wykorzystania toru " << i << ". o glebokosci " << canal->getDepth(i) << "m : " << canal->lane_table[i].lane_using_time / sim_clock * 100 << endl;
	cout << endl;
}
//----------------------------------------------
double Watercraft::get_lane_stats(int i)
{
	return  canal->lane_table[i].lane_using_time / sim_clock * 100;
}
//----------------------------------------------
double Watercraft::get_resource_stats(Resource res)
{
	return (port->using_time[res] / (port->number_of_resources[res] * sim_clock)) * 100;
}
//----------------------------------------------
void Watercraft::show_queues()
{
	cout << "WEJŒCIOWA:" << endl;
	in_queue->disp();
	cout << "WYJŒCIOWA:" << endl;
	out_queue->disp();

}
//----------------------------------------------
int Watercraft::in_queue_length()
{
	return in_queue->length();
}
//----------------------------------------------
int Watercraft::out_queue_length()
{
	return out_queue->length();
}
//----------------------------------------------
void Watercraft::setLambda(double in)
{
	if(in) lambda = in;
}
//----------------------------------------------
void Watercraft::reset_statistics()
{
	number = 0;
	serviced = 0;
	for (int i = 0; i < 4; i++)
	{
		number_type[i] = 0;
		serviced_type[i] = 0;
		waiting_time_type[i] = 0.;
	}
	waiting_time = 0.;
	max_wait_time = 0.;
	
}
//----------------------------------------------
void Watercraft::reset()
{
	in_queue->make_empty();
	out_queue->make_empty();
	for (int i = 0; i < 3; i++)
	{
		port->available_resources[i] = port->number_of_resources[i];
		port->using_time[i] = 0.;

	}
	for (int i = 0; i < 3; i++)
	{
		canal->lane_table[i].free = true;
		canal->lane_table[i].last_use_direction = 1;
		canal->lane_table[i].last_use_time = -Tt;	//ustawiamy tak, aby przy obliczaniu stanu toru dla zerowej chwili otrzymac wartosc 0
		canal->lane_table[i].lane_using_time = 0.;
		
	}
	agenda.make_empty();
	counter = 0;


}
void Watercraft::reset_simulation()
{
	reset_statistics();
	reset();

}
/////////////////////////////////////////////////
//***********************************************