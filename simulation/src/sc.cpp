#include "sc.h"
#include<windows.h>


using namespace std;
using namespace simulation;
namespace simulation
{
	EventList agenda;

	double sim_clock = 0.;

}


int main()
{
	int M;
	double Lmin;
	double Lmax;
	double Lstep;
	int choice;
	cout <<endl<< "**********SYMULACJA CYFROWA**********" << endl;
	cout << "           Zuzanna Kaptur" << endl;
	cout << "*************************************" << endl<<endl;
	cout << "Parametry symulacji: 0 - domyslne, 1 - wprowadzenie wlasnych" << endl;
	cin >> choice;
	if(choice==0)
	{
		M = 30;
		Lmin = 0.075;
		Lmax = 0.095;
		Lstep = 0.0025;
	}
	else
	{
		cout << "Podaj minimalna wartosc intensywnosci (Lmin): ";
		cin >> Lmin;
		cout << "Podaj maksymalna wartosc intensywnosci (Lmax): ";
		cin >> Lmax;
		cout << "Podaj krok (Lstep): ";
		cin >> Lstep;
		cout << "Podaj liczbe symulacji dla kazdego parametru (M): ";
		cin >> M;
	}
	
	//-------------------------------------------
	// Set statistics file(s):
	//-------------------------------------------

	ofstream model_stats;
	ofstream model_stats2;
	ofstream type_generator;
	ofstream model_stats_max;
	ofstream cargo_stats;
	ofstream roro_stats;
	ofstream container_stats;
	ofstream yacht_stats;
	ofstream lane0_stats;
	ofstream lane1_stats;
	ofstream lane2_stats;
	ofstream ramp_stats;
	ofstream crane_stats;
	ofstream yacht_site_stats;
	

	model_stats.open("./output/model_stats.csv", std::ios_base::out | std::ios_base::trunc);
	model_stats_max.open("./output/model_stats_max.csv", std::ios_base::out | std::ios_base::trunc);

	cargo_stats.open("./output/cargo_stats.csv", std::ios_base::out | std::ios_base::trunc);
	roro_stats.open("./output/roro_stats.csv", std::ios_base::out | std::ios_base::trunc);
	container_stats.open("./output/container_stats.csv", std::ios_base::out | std::ios_base::trunc);
	yacht_stats.open("./output/yacht_stats.csv", std::ios_base::out | std::ios_base::trunc);

	lane0_stats.open("./output/lane0_stats.csv", std::ios_base::out | std::ios_base::trunc);
	lane1_stats.open("./output/lane1_stats.csv", std::ios_base::out | std::ios_base::trunc);
	lane2_stats.open("./output/lane2_stats.csv", std::ios_base::out | std::ios_base::trunc);

	ramp_stats.open("./output/ramp_stats.csv", std::ios_base::out | std::ios_base::trunc);
	crane_stats.open("./output/crame_stats.csv", std::ios_base::out | std::ios_base::trunc);
	yacht_site_stats.open("./output/yacht_site_stats.csv", std::ios_base::out | std::ios_base::trunc);

	model_stats2.open("./output/model_stats2.csv", std::ios_base::out | std::ios_base::trunc);
	type_generator.open("./output/type_generator.csv", std::ios_base::out | std::ios_base::trunc);
	Watercraft::weight_stats.open("./output/weight_stats.csv", std::ios_base::out | std::ios_base::trunc);
	

	model_stats << "lambda_1" << ';' << "est_mu_st" << ';' << "delta" << '\n';
	model_stats_max << "lambda_1" << ';' << "est_mu_st" << ';' << "delta" << '\n';
	lane0_stats << "lambda_1" << ';' << "est_mu_st" << ';' << "delta" << '\n';
	lane1_stats << "lambda_1" << ';' << "est_mu_st" << ';' << "delta" << '\n';
	lane2_stats << "lambda_1" << ';' << "est_mu_st" << ';' << "delta" << '\n';
	ramp_stats << "lambda_1" << ';' << "est_mu_st" << ';' << "delta" << '\n';
	crane_stats << "lambda_1" << ';' << "est_mu_st" << ';' << "delta" << '\n';
	yacht_site_stats << "lambda_1" << ';' << "est_mu_st" << ';' << "delta" << '\n';


	type_generator << "drobnicowce" << ';' << "ro-ro" << ';' << "kontenerowce" << ";"<< "jachty" << '\n';

	//-------------------------------------------

	ConfidenceIntervalEstimator service_time;
	ConfidenceIntervalEstimator max_service_time;
	ConfidenceIntervalEstimator cargo_st;
	ConfidenceIntervalEstimator roro_st;
	ConfidenceIntervalEstimator container_st;
	ConfidenceIntervalEstimator yacht_st;
	ConfidenceIntervalEstimator lane0_st;
	ConfidenceIntervalEstimator lane1_st;
	ConfidenceIntervalEstimator lane2_st;
	ConfidenceIntervalEstimator ramp_st;
	ConfidenceIntervalEstimator crane_st;
	ConfidenceIntervalEstimator yacht_site_st;


	for (double L = Lmin; L < Lmax; L += Lstep)
	{
		service_time.reset();
		Watercraft::setLambda(L);
		Watercraft::generator.open(("./output/generator_" + to_string(static_cast<int>(L * 10000)) +".csv").c_str(), std::ios_base::out | std::ios_base::trunc);
		

		for (int m = 0; m < M; m++)
		{
			sim_clock = 0.0;
			Process* current = NULL;
			(new Watercraft)->activate(0);

			Watercraft::watercraft_stats.open(("./output/watercraft_stats_" + to_string(static_cast<int>(L*10000)) + '_' + to_string(m) + ".csv").c_str(), std::ios_base::out | std::ios_base::trunc);

			Watercraft::watercraft_stats << "time" << ';' << "service_duration" << std::endl;

			while (Watercraft::serviced < 10000.)
			{
				current = agenda.first()->proc;

				sim_clock = agenda.first()->event_time;

				agenda.remove_first();

				current->execute();
				if (current->terminated) delete current;

			}
			Watercraft::reset_statistics();

			while (Watercraft::serviced < 50000.)
			{
				
				current = agenda.first()->proc;

				sim_clock = agenda.first()->event_time;

				agenda.remove_first();

				current->execute();
				if (current->terminated) delete current;

			}
			service_time.add_realization(Watercraft::get_mu_st());
			max_service_time.add_realization(Watercraft::max_wait_time);
			cargo_st.add_realization(Watercraft::waiting_time_type[0]/Watercraft::serviced_type[0]);
			roro_st.add_realization(Watercraft::waiting_time_type[1] / Watercraft::serviced_type[1]);
			container_st.add_realization(Watercraft::waiting_time_type[2] / Watercraft::serviced_type[2]);
			yacht_st.add_realization(Watercraft::waiting_time_type[3] / Watercraft::serviced_type[3]);
			lane0_st.add_realization(Watercraft::get_lane_stats(0));
			lane1_st.add_realization(Watercraft::get_lane_stats(1));
			lane2_st.add_realization(Watercraft::get_lane_stats(2));
			ramp_st.add_realization(Watercraft::get_resource_stats(ramp));
			crane_st.add_realization(Watercraft::get_resource_stats(crane));
			yacht_site_st.add_realization(Watercraft::get_resource_stats(yacht_site));

			type_generator << Watercraft::number_type[0] << ";" << Watercraft::number_type[1] << ";" << Watercraft::number_type[2] << ";" << Watercraft::number_type[3] << '\n';
			//-----------------------------------

			Watercraft::reset_simulation();

			Watercraft::watercraft_stats.close();
			
			
			
		}

		model_stats << L << ';' << service_time.get_mu() << ';' << service_time.get_delta(ConfidenceIntervalEstimator::alpha0_005) << '\n';
		model_stats_max << L << ';' << max_service_time.get_mu() << ';' << max_service_time.get_delta(ConfidenceIntervalEstimator::alpha0_005) << '\n';
		cargo_stats << L << ';' << cargo_st.get_mu() << ';' << cargo_st.get_delta(ConfidenceIntervalEstimator::alpha0_005) << '\n';
		roro_stats << L << ';' << roro_st.get_mu() << ';' << roro_st.get_delta(ConfidenceIntervalEstimator::alpha0_005) << '\n';
		container_stats << L << ';' << container_st.get_mu() << ';' << container_st.get_delta(ConfidenceIntervalEstimator::alpha0_005) << '\n';
		yacht_stats << L << ';' << yacht_st.get_mu() << ';' << yacht_st.get_delta(ConfidenceIntervalEstimator::alpha0_005) << '\n';
		lane0_stats << L << ';' << lane0_st.get_mu() << ';' << lane0_st.get_delta(ConfidenceIntervalEstimator::alpha0_005) << '\n';
		lane1_stats << L << ';' << lane1_st.get_mu() << ';' << lane1_st.get_delta(ConfidenceIntervalEstimator::alpha0_005) << '\n';
		lane2_stats << L << ';' << lane2_st.get_mu() << ';' << lane2_st.get_delta(ConfidenceIntervalEstimator::alpha0_005) << '\n';
		ramp_stats << L << ';' << ramp_st.get_mu() << ';' << ramp_st.get_delta(ConfidenceIntervalEstimator::alpha0_005) << '\n';
		crane_stats << L << ';' << crane_st.get_mu() << ';' << crane_st.get_delta(ConfidenceIntervalEstimator::alpha0_005) << '\n';
		yacht_site_stats << L << ';' << yacht_site_st.get_mu() << ';' << yacht_site_st.get_delta(ConfidenceIntervalEstimator::alpha0_005) << '\n';

		Watercraft::generator.close();
		std::cout << "Mean service time:" << service_time.get_mu() << " +/- " << service_time.get_delta(ConfidenceIntervalEstimator::alpha0_005) << endl;
	}
	model_stats2.close();
	model_stats.close();
	model_stats_max.close();

	cargo_stats.close();
	roro_stats.close();
	container_stats.close();
	yacht_stats.close();

	lane0_stats.close();
	lane1_stats.close();
	lane2_stats.close();

	ramp_stats.close();
	crane_stats.close();
	yacht_site_stats.close();
	Watercraft::generator.close();
	type_generator.close();
	
	Watercraft::weight_stats.close();
	getchar();
	getchar();

	return 0;
}