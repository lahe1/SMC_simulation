


#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include <algorithm>  


using namespace std;
class State
{
public:
	string state;
	State()
	{

	}
	State(string w)
	{
		state = w;
	}



};
class Event
{
public:
	string event;

	Event()
	{

	}
	Event(string e)
	{

		event = e;
	}
};
class Transition
{
public:
	State* st[2];
	Event* ev;
	void ses(State* u, Event* i, State* o)
	{

		st[0] = u;
		st[1] = o;
		ev = i;
	}
};
class Control_decision
{
public:
	string gamma_name;
	vector<Event*>enable;
	vector<Event*>force;
	int enable_1(Event* k)
	{
		int test = 0;
		for (int k_1 = 0; k_1 < enable.size(); k_1++)
		{
			if (k == enable[k_1])
			{

				test = 1;
			}

		}
		if (test == 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}

	}
	int force_1(Event* k)
	{
		int test = 0;
		for (int k_1 = 0; k_1 < force.size(); k_1++)
		{

			if (k == force[k_1])
			{

				test = 1;
			}

		}
		if (test == 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
};
class control_decision_time
{
public:
	Control_decision* j;
	int time;
	control_decision_time()
	{

	}
	control_decision_time(Control_decision* w, int i)
	{
		j = w;
		time = i;
	}

};
vector<Transition*>preserve_transition;
vector<Transition*>preserve_transition_under_control;
vector<Transition*>preserve_transition_active_withtout_control;
int Delata_withtout_control(State* u)
{

	vector<Transition*>possible_transition;


	//find possible transitions;
	for (int j = 0; j < preserve_transition.size(); j++)
	{

		if (u == preserve_transition[j]->st[0])
		{
			possible_transition.push_back(preserve_transition[j]);

		}
	}
	preserve_transition_active_withtout_control = possible_transition;

	if (preserve_transition_active_withtout_control.size() == 0)
	{
		return 0;
	}

	if (preserve_transition_active_withtout_control.size() > 0)
	{
		return 1;
	}


}
int Delata_control(State* u, Control_decision* i)//whetehr or not the trnsition is allowed under control
{

	vector<Transition*>preserve_transition_under_control1;
	vector<Transition*>possible_transition;


	//find possible transitions;
	for (int j = 0; j < preserve_transition.size(); j++)
	{

		if (u == preserve_transition[j]->st[0])
		{
			possible_transition.push_back(preserve_transition[j]);

		}
	}


	for (int j = 0; j < possible_transition.size(); j++)
	{
		//deal with tick
		if (possible_transition[j]->ev->event == "tick")
		{

			//for test
			int t_1 = 0;
			for (int c_1 = 0; c_1 < possible_transition.size(); c_1++)
			{

				if (i->enable_1(possible_transition[c_1]->ev) == 1 and i->force_1(possible_transition[c_1]->ev) == 1)
				{

					t_1 = 1;
				}
			}
			if (t_1 == 0)
			{
				preserve_transition_under_control1.push_back(possible_transition[j]);
			}

		}
		else//deal with non-tick event
		{

			if (i->enable_1(possible_transition[j]->ev) == 1)
			{
				preserve_transition_under_control1.push_back(possible_transition[j]);
			}

		}

	}

	preserve_transition_under_control = preserve_transition_under_control1;
	if (preserve_transition_under_control.size() == 0)
	{

		return 0;
	}

	if (preserve_transition_under_control.size() > 0)
	{

		return 1;
	}


}
vector<Transition*>preserve_transition_under_control_over_approximation;//storage the allowed trnaisiotions under over-approximation
int over_approxiamtion_control(State* u, vector<control_decision_time*>* w)//whetehr or not the trnsition is allowed under control
{


	vector<Transition*>preserve_transition_under_control_over_approximation1;
	vector<Transition*>possible_transition;
	vector<control_decision_time*>control_channel_configuration1 = *w;
	//find possible transitions;



	for (int j = 0; j < preserve_transition.size(); j++)
	{

		if (u == preserve_transition[j]->st[0])
		{
			possible_transition.push_back(preserve_transition[j]);

		}
	}



	for (int j = 0; j < possible_transition.size(); j++)
	{

		//deal with tick
		if (possible_transition[j]->ev->event == "tick")
		{

			for (int j_1 = 0; j_1 < control_channel_configuration1.size(); j_1++)//choose one decision from the current control channel configuration
			{

				int t_1 = 0;
				for (int c_1 = 0; c_1 < possible_transition.size(); c_1++)
				{
					if (control_channel_configuration1[j_1]->j->enable_1(possible_transition[c_1]->ev) == 1 and control_channel_configuration1[j_1]->j->force_1(possible_transition[c_1]->ev) == 1)
					{



						t_1 = 1;
					}
				}
				if (t_1 == 0)
				{

					preserve_transition_under_control_over_approximation1.push_back(possible_transition[j]);
					break;
				}
			}
		}
		else//deal with non-tick event
		{

			for (int j_1 = 0; j_1 < control_channel_configuration1.size(); j_1++)//choose one decision from the current control channel configuration
			{



				if (control_channel_configuration1[j_1]->j->enable_1(possible_transition[j]->ev) == 1)
				{
					preserve_transition_under_control_over_approximation1.push_back(possible_transition[j]);
					break;
				}

			}

		}

	}

	preserve_transition_under_control_over_approximation = preserve_transition_under_control_over_approximation1;

	if (preserve_transition_under_control_over_approximation.size() == 0)
	{

		return 0;
	}

	if (preserve_transition_under_control_over_approximation.size() > 0)
	{

		return 1;
	}


}
State* delata(State* u, Event* i)
{
	int j = 0;
	for (; j < preserve_transition.size();)
	{

		if (u == preserve_transition[j]->st[0])
		{
			if (i == preserve_transition[j]->ev)
			{
				return preserve_transition[j]->st[1];
			}
		}


		j = j + 1;


	}

	return 0;



}
vector<Event*>observable_event_set;
Control_decision* control_decision_in_use;
State* current_state;
vector<Control_decision*>control_decision_set;
int is_observable(Event* w)
{
	for (int i = 0; i < observable_event_set.size(); i++)
	{

		if (w == observable_event_set[i])
		{
			return 1;
		}

	}
	return 0;

}
vector<control_decision_time*>CDT_adress;
vector<control_decision_time*>CDT_adress_for_configuration;
vector<State*>current_state_estimate_open_loop;
void update_the_CSE_OL(Event* e)//update the state estimate under open-loop situation
{



	vector<State*>empty;
	vector<State*>state_has_been_processed;
	vector<State*>state_estimate_after_e;
	vector<State*>state_process;
	state_process = current_state_estimate_open_loop;


	if (e->event == "empty_string")
	{
		state_estimate_after_e.push_back(current_state_estimate_open_loop[0]);//inisiate state is added
		while (state_process.size() > 0)
		{

			Delata_withtout_control(state_process[0]);//find all possible transitions at state state_process[0]

			for (int i_1 = 0; i_1 < preserve_transition_active_withtout_control.size(); i_1++)
			{
				if (is_observable(preserve_transition_active_withtout_control[i_1]->ev) == 0)//check whether the chosen event is unobservable
				{
					//update the stste estimate
					int pp_1 = 1;//wheter or not the state is estiated before
					for (int pp_2 = 0; pp_2 < state_estimate_after_e.size(); pp_2++)
					{
						if (preserve_transition_active_withtout_control[i_1]->st[1] == state_estimate_after_e[pp_2])
						{
							pp_1 = 0;//the state has been estimated before
							break;
						}
					}
					if (pp_1 == 1)//the state has not been estimated
					{
						state_estimate_after_e.push_back(preserve_transition_active_withtout_control[i_1]->st[1]);
					}

					int test = 1;//check wheter or not the new encountered state is in vector
					int test_1 = 1;
					for (int i_2 = 0; i_2 < state_process.size(); i_2++)
					{
						if (preserve_transition_active_withtout_control[i_1]->st[1] == state_process[i_2])
						{
							test = 0;
							break;
						}
					}
					for (int i_2 = 0; i_2 < state_has_been_processed.size(); i_2++)
					{
						if (preserve_transition_active_withtout_control[i_1]->st[1] == state_has_been_processed[i_2])
						{
							test_1 = 0;
							break;
						}
					}
					if (test == 1 and test_1 == 1)
					{
						state_process.push_back(preserve_transition_active_withtout_control[i_1]->st[1]);

					}
				}
			}
			state_has_been_processed.push_back(state_process[0]);

			state_process.erase(state_process.begin());//the first element of vector has been processed

		}

		current_state_estimate_open_loop = state_estimate_after_e;

	}


	else
	{

		while (state_process.size() > 0)
		{

			//process the first element of the vector
			Delata_withtout_control(state_process[0]);//find all possible transitions at state state_process[0]

			for (int i_1 = 0; i_1 < preserve_transition_active_withtout_control.size(); i_1++)
			{
				if (preserve_transition_active_withtout_control[i_1]->ev == e)//check whether e==the chosen event
				{

					int pp_1 = 1;//wheter or not the state is estiated before
					for (int pp_2 = 0; pp_2 < state_estimate_after_e.size(); pp_2++)
					{
						if (preserve_transition_active_withtout_control[i_1]->st[1] == state_estimate_after_e[pp_2])
						{
							pp_1 = 0;//the state has been estimated before
							break;
						}
					}
					if (pp_1 == 1)//the state has not been estimated
					{
						state_estimate_after_e.push_back(preserve_transition_active_withtout_control[i_1]->st[1]);
					}
				}
			}
			state_process.erase(state_process.begin());//the first element of vector has been processed
		}

		state_process = state_estimate_after_e;//unobservable reach

		state_has_been_processed = empty;
		while (state_process.size() > 0)
		{

			Delata_withtout_control(state_process[0]);//find all possible transitions at state state_process[0]

			for (int i_1 = 0; i_1 < preserve_transition_active_withtout_control.size(); i_1++)
			{
				if (is_observable(preserve_transition_active_withtout_control[i_1]->ev) == 0)//check whether the chosen event is unobservable
				{
					//update the stste estimate
					int pp_1 = 1;//wheter or not the state is estiated before
					for (int pp_2 = 0; pp_2 < state_estimate_after_e.size(); pp_2++)
					{
						if (preserve_transition_active_withtout_control[i_1]->st[1] == state_estimate_after_e[pp_2])
						{
							pp_1 = 0;//the state has been estimated before
							break;
						}
					}
					if (pp_1 == 1)//the state has not been estimated
					{
						state_estimate_after_e.push_back(preserve_transition_active_withtout_control[i_1]->st[1]);
					}

					int test = 1;//check wheter or not the new encountered state is in vector
					int test_1 = 1;
					for (int i_2 = 0; i_2 < state_process.size(); i_2++)
					{
						if (preserve_transition_active_withtout_control[i_1]->st[1] == state_process[i_2])
						{
							test = 0;
							break;
						}
					}
					for (int i_2 = 0; i_2 < state_has_been_processed.size(); i_2++)
					{
						if (preserve_transition_active_withtout_control[i_1]->st[1] == state_has_been_processed[i_2])
						{
							test_1 = 0;
							break;
						}
					}
					if (test == 1 and test_1 == 1)
					{
						state_process.push_back(preserve_transition_active_withtout_control[i_1]->st[1]);

					}
				}
			}
			state_has_been_processed.push_back(state_process[0]);

			state_process.erase(state_process.begin());//the first element of vector has been processed

		}

		current_state_estimate_open_loop = state_estimate_after_e;
	}
}
vector<State*>current_over_approximation_state_estimate;//storage the state estimate
void update_the_COASE_unobservable_reach(vector<control_decision_time*>* control_channel_configuration)//update the over-approximation state estimate 

{
	vector<State*>empty;
	vector<State*>state_has_been_processed;
	vector<State*>state_estimate;
	vector<State*>state_process;
	state_process = current_over_approximation_state_estimate;

	state_estimate = current_over_approximation_state_estimate;//inisiate state is added
	while (state_process.size() > 0)
	{

		over_approxiamtion_control(state_process[0], control_channel_configuration);//find all possible transitions enabled at state state_process[0] under control channel configuration

		for (int i_1 = 0; i_1 < preserve_transition_under_control_over_approximation.size(); i_1++)
		{
			if (is_observable(preserve_transition_under_control_over_approximation[i_1]->ev) == 0)//check whether the chosen event is unobservable
			{
				//update the stste estimate
				int pp_1 = 1;//wheter or not the state is estiated before
				for (int pp_2 = 0; pp_2 < state_estimate.size(); pp_2++)
				{
					if (preserve_transition_under_control_over_approximation[i_1]->st[1] == state_estimate[pp_2])
					{
						pp_1 = 0;//the state has been estimated before
						break;
					}
				}
				if (pp_1 == 1)//the state has not been estimated
				{
					state_estimate.push_back(preserve_transition_under_control_over_approximation[i_1]->st[1]);
				}

				int test = 1;//check wheter or not the new encountered state is in vector
				int test_1 = 1;
				for (int i_2 = 0; i_2 < state_process.size(); i_2++)
				{
					if (preserve_transition_under_control_over_approximation[i_1]->st[1] == state_process[i_2])
					{
						test = 0;
						break;
					}
				}
				for (int i_2 = 0; i_2 < state_has_been_processed.size(); i_2++)
				{
					if (preserve_transition_under_control_over_approximation[i_1]->st[1] == state_has_been_processed[i_2])
					{
						test_1 = 0;
						break;
					}
				}
				if (test == 1 and test_1 == 1)
				{
					state_process.push_back(preserve_transition_under_control_over_approximation[i_1]->st[1]);

				}
			}
		}
		state_has_been_processed.push_back(state_process[0]);

		state_process.erase(state_process.begin());//the first element of vector has been processed

	}

	current_over_approximation_state_estimate = state_estimate;
}
void update_the_COASE_observable_reach(Event* e, vector<control_decision_time*>* control_channel_configuration)//update the over-approximation state estimate,observable reach

{
	vector<State*>empty;
	vector<State*>state_has_been_processed;
	vector<State*>state_estimate_after_e;
	vector<State*>state_process;
	state_process = current_over_approximation_state_estimate;

	//test
	/*int fuck1 = 0;
	for (int i = 0; i < state_process.size(); i++)
	{
		cout << state_process[i]->state << endl;
		over_approxiamtion_control(state_process[i], control_channel_configuration);

		for (int i_1 = 0; i_1 < preserve_transition_under_control_over_approximation.size(); i_1++)
		{
			cout << preserve_transition_under_control_over_approximation[i_1]->ev->event << endl;
			if (preserve_transition_under_control_over_approximation[i_1]->ev == e)
			{
				fuck1 = 1;
			}
		}
	}
	if (fuck1 == 0)
	{
		cout << (*control_channel_configuration).size() << endl;
		cout << (*control_channel_configuration)[0]->j->gamma_name << endl;
		cout << "fuck222" << endl;
		cout << e->event << endl;
		while (1);
	}*/
	//test

	while (state_process.size() > 0)
	{

		//process the first element of the vector
		over_approxiamtion_control(state_process[0], control_channel_configuration);//find all possible transitions at state state_process[0]



		for (int i_1 = 0; i_1 < preserve_transition_under_control_over_approximation.size(); i_1++)
		{


			if (preserve_transition_under_control_over_approximation[i_1]->ev == e)//check whether e==the chosen event
			{


				int pp_1 = 1;//wheter or not the state is estiated before
				for (int pp_2 = 0; pp_2 < state_estimate_after_e.size(); pp_2++)
				{
					if (preserve_transition_under_control_over_approximation
						[i_1]->st[1] == state_estimate_after_e[pp_2])
					{
						pp_1 = 0;//the state has been estimated before
						break;
					}
				}
				if (pp_1 == 1)//the state has not been estimated
				{
					state_estimate_after_e.push_back(preserve_transition_under_control_over_approximation
						[i_1]->st[1]);
				}
			}
		}

		state_process.erase(state_process.begin());//the first element of vector has been processed


	}
	current_over_approximation_state_estimate = state_estimate_after_e;
}
void Closed_loop_run_delays_losses_non_fifo(State* w, int i, Event* e_1)
{
	control_decision_time CDT[20000];
	control_decision_time CDT_for_channel_configuration[20000];

	for (int p = 0; p < 20000; p++)//assign the addresses of the objectives to vector
	{
		CDT_adress.push_back(&CDT[p]);
	}

	for (int p = 0; p < 20000; p++)//assign the addresses of the objectives to vector
	{
		CDT_adress_for_configuration.push_back(&CDT_for_channel_configuration[p]);
	}

	current_state_estimate_open_loop.push_back(w);//initiate the initial state
	update_the_CSE_OL(e_1);//the initial state estimate ES(empty_string)

	current_over_approximation_state_estimate.push_back(w);//initial the over-approximation state 

	current_state = w;//the initial state
	int delay_bound = i;
	vector<State*>actual_arrival_states;
	vector<State*>empty1;
	actual_arrival_states.push_back(w);



	//vector<Control_decision*>decision_issue_within_delay_bound;
	vector<control_decision_time*>control_channel;//storage issued control decisions

	vector<control_decision_time*>control_channel_configuration;
	//vector<Control_decision*>empty_function;//for clearing vector
	vector<control_decision_time*>all_decisions_with_time0;//storage control decisions with timing index 0

	vector<control_decision_time*>all_decisions_with_time0_configuration;//storage control decisions with timing index< 0
	vector<control_decision_time*>all_decisions_with_time_biger_than0;//storage control decisions with timing index >0
	vector<control_decision_time*>empty_function;//for clearing vector
	//cout << control_decision_set.size() << endl;
	int x, z, y, v, q;
	int q_1 = 0;//for finding objective later
	y = 0;//check whether or not 1000 of CDT space is used.
	int y_1 = 0;
	x = (rand() % (control_decision_set.size()));//randomly choose a control decision to be the initial contol decision without delays and losses
	//cout << "x: " << x << endl;

	cout << "the supervisor issues:" << control_decision_set[x]->gamma_name << ";" << endl;


	CDT_adress_for_configuration[y_1]->j = control_decision_set[x];//use the objective
	CDT_adress_for_configuration[y_1]->time = delay_bound;//assigning delay bound to control_decision_set[x]->gamma_name 
	control_channel_configuration.push_back(CDT_adress_for_configuration[y_1]);//adding control_decision_set[x]->gamma_name to control channel
	y_1 = y_1 + 1;





	//compute the unobservable reach
	update_the_COASE_unobservable_reach(&control_channel_configuration);

	control_decision_in_use = control_decision_set[x];//the initial control decision is control_decision_set[x];
	//cout << control_decision_in_use->gamma_name << endl;

	cout << "the control decision used by the plant is:" << control_decision_set[x]->gamma_name << ";" << endl;


	cout << "the initial open-loop state estimate is:" << endl;
	for (int es = 0; es < current_state_estimate_open_loop.size(); es++)
	{
		if (es == current_over_approximation_state_estimate.size() - 1)
		{
			cout << current_state_estimate_open_loop[es]->state << ".";
		}
		else
		{
			cout << current_state_estimate_open_loop[es]->state << ",";
		}
	}
	cout << endl;



	cout << "the initial over-apprxoximation state estimate is:" << endl;
	for (int es = 0; es < current_over_approximation_state_estimate.size(); es++)
	{
		if (es == current_over_approximation_state_estimate.size() - 1)
		{
			cout << current_over_approximation_state_estimate[es]->state << ".";
		}
		else
		{
			cout << current_over_approximation_state_estimate[es]->state << ",";
		}
	}
	cout << endl;



	while (Delata_control(current_state, control_decision_in_use) == 1)//there is an enabled transition at the current state
	{

		//cout << "y=\t" << y << endl;
		if (y_1 == 20000)//the maximum number of objectives that can be used, i.e., the maximum number of the control channel states
		{
			cout << "We stop the simulation since the data collected is enoupgh to illustrate the proposed method." << endl;
			while (1);
			break;

		}
		if (y == 20000)//the maximum number of objectives that can be used, i.e., the maximum number of the control channel states
		{
			cout << "We stop the simulation since the data collected is enoupgh to illustrate the proposed method." << endl;
			while (1);
			break;

		}




		z = (rand() % (preserve_transition_under_control.size()));//choose one enabled event randomly
		//cout << z << endl;
		//preserve_transition_under_control[z]->ev->event:The event to occur


		//if unobservabel;update states


		current_state = preserve_transition_under_control[z]->st[1];

		if (is_observable(preserve_transition_under_control[z]->ev) == 0)
		{
			int yy = 1;
			for (int yyy = 0; yyy < actual_arrival_states.size(); yyy++)
			{
				if (current_state == actual_arrival_states[yyy])
				{
					yy = 0;
				}
			}
			if (yy == 1)
			{
				actual_arrival_states.push_back(current_state);
			}
		}








		if (is_observable(preserve_transition_under_control[z]->ev) == 1)
		{
			cout << "the states that the plant has reached before a new observation event are:\t" << endl;
			for (int yyyy = 0; yyyy < actual_arrival_states.size(); yyyy++)
			{
				if (yyyy == actual_arrival_states.size() - 1)
				{
					cout << actual_arrival_states[yyyy]->state << ".";
				}
				else
				{
					cout << actual_arrival_states[yyyy]->state << ",";

				}

			}
			cout << endl;


			cout << "................................................" << endl;
			cout << preserve_transition_under_control[z]->ev->event << "\t is observabled" << endl;
			update_the_CSE_OL(preserve_transition_under_control[z]->ev);//update state estimate ES after preserve_transition_under_control[z]




			update_the_COASE_observable_reach(preserve_transition_under_control[z]->ev, &control_channel_configuration);//compute the observable reach under over_approximation



			actual_arrival_states = empty1;
			actual_arrival_states.push_back(current_state);//change??






			cout << "the current open-loop state estimate after\t" << preserve_transition_under_control[z]->ev->event << "\t is:" << endl;
			for (int es = 0; es < current_state_estimate_open_loop.size(); es++)
			{

				cout << current_state_estimate_open_loop[es]->state << ",";
			}
			cout << endl;
			//cout << "the current state after\t" << preserve_transition_under_control[z]->ev->event << "\t is\t:" << current_state->state <<endl;

			/*cout << "the current over approximation state estimate after\t" << preserve_transition_under_control[z]->ev->event << "\t is:" << endl;
			for (int es = 0; es < current_over_approximation_state_estimate.size(); es++)
			{

				cout << current_over_approximation_state_estimate[es]->state << ",";
			}
			cout << endl;*/


			if (preserve_transition_under_control[z]->ev->event == "tick")
			{

				for (int l = 0; l < control_channel.size(); l++)//decrease the timming indexs in control channel
				{

					control_channel[l]->time = control_channel[l]->time - 1;//update control channel

				}
				for (int l = 0; l < control_channel_configuration.size(); l++)//decrease the timming indexs in control channel configuration
				{

					control_channel_configuration[l]->time = control_channel_configuration[l]->time - 1;//update control channel configuration

				}

			}

			//delete all the dicisions whoese timing indices are zero.



			for (int j = 0; j < control_channel.size(); j++)//storage control decisions with timing index 0
			{
				if (control_channel[j]->time == 0)
				{
					all_decisions_with_time0.push_back(control_channel[j]);

				}

			}


			if (all_decisions_with_time0.size() == 0)
			{
				cout << "no new control decision is received by the plant immediately after event\t" << preserve_transition_under_control[z]->ev->event << ";" << endl;
				cout << "no control decisions are lost immediately after event\t" << preserve_transition_under_control[z]->ev->event << ";" << endl;
				//cout << "the current control decision used by the plant immediately after event" << control_decision_in_use->gamma_name << endl;

			}

			if (all_decisions_with_time0.size() > 0)//updating the current control decision by deleting all_decisions_with_time0
			{

				x = (rand() % (all_decisions_with_time0.size()));//choose one control decision to arrive at the plant
				control_decision_in_use = all_decisions_with_time0[x]->j;//update the current control decision;



				cout << "control decision\t" << control_decision_in_use->gamma_name << "\t reaches the plant immediately after event\t" << preserve_transition_under_control[z]->ev->event << ";" << endl;
				if (all_decisions_with_time0.size() == 1)
				{
					cout << "no control decisions are lost immediately after event\t" << preserve_transition_under_control[z]->ev->event << ";" << endl;

				}
				if (all_decisions_with_time0.size() > 1)
				{
					cout << "the lost control decisions immediately after event\t" << preserve_transition_under_control[z]->ev->event << "\t are:" << endl;

					for (int es = 0; es < all_decisions_with_time0.size(); es++)
					{

						if (es < x)
						{
							cout << all_decisions_with_time0[es]->j->gamma_name << ",";
						}
						if (es > x)
						{
							cout << all_decisions_with_time0[es]->j->gamma_name << ",";
						}

					}

					cout << endl;
				}



				all_decisions_with_time0 = empty_function;//clear vector all_decisions_with_time0
				//delete all the current control decisions with timing 0 from the control channel
				for (int j = 0; j < control_channel.size(); j++)//storage control decisions with timing index >0
				{
					if (control_channel[j]->time > 0)
					{
						all_decisions_with_time_biger_than0.push_back(control_channel[j]);

					}

				}
				control_channel = all_decisions_with_time_biger_than0;//update control channel by deleting decisions with timing 0
				all_decisions_with_time_biger_than0 = empty_function;//clear vector all_decisions_with_time>0
			}
			cout << "the control decision used by the plant immediately after event\t" << preserve_transition_under_control[z]->ev->event << "\t is:" << control_decision_in_use->gamma_name << ";" << endl;








			//update control channel configuration after event

			for (int j = 0; j < control_channel_configuration.size(); j++)//storage control decisions with timing index >=0
			{
				if (control_channel_configuration[j]->time >= 0)
				{
					all_decisions_with_time0_configuration.push_back(control_channel_configuration[j]);

				}

			}

			control_channel_configuration = all_decisions_with_time0_configuration;//update control channel configuration by deleting control decisions with timing index<0

			all_decisions_with_time0_configuration = empty_function;//initiate the vector

			if (control_channel_configuration.size() == 0)//saving computer space
			{
				y_1 = 0;
			}
			x = (rand() % (control_decision_set.size()));//choose one control decision to issue
			//the chosen decision: control_decision_set[x]->gamma_name
			cout << "the supervisor issues control decision:" << control_decision_set[x]->gamma_name << ";" << endl;
			v = (rand() % (delay_bound + 1));//assigning delay time to control_decision_set[x]->gamma_name 


			CDT_adress_for_configuration[y_1]->j = control_decision_set[x];//use the objective
			CDT_adress_for_configuration[y_1]->time = delay_bound;//assigning delay bound to control_decision_set[x]->gamma_name 
			control_channel_configuration.push_back(CDT_adress_for_configuration[y_1]);//adding control_decision_set[x]->gamma_name to control channel
			y_1 = y_1 + 1;

			update_the_COASE_unobservable_reach(&control_channel_configuration);//update the unobservable reach;


			if (v == 0)//do not need to update control channel
			{
				cout << "there is no control delays and losses for the issued control decision;" << endl;
				control_decision_in_use = control_decision_set[x];//update the current control decision
				cout << "the current control decision after the issued control deiciosn is:" << control_decision_in_use->gamma_name << ";" << endl;

			}
			if (v > 0)//update control channel
			{
				cout << "the issued control decision is delayed in the control channel;" << endl;
				cout << "the plant use a decision issued before:" << control_decision_in_use->gamma_name << ";" << endl;

				CDT_adress[y]->j = control_decision_set[x];//use the objective
				CDT_adress[y]->time = v;//assigning delay time to control_decision_set[x]->gamma_name 
				control_channel.push_back(CDT_adress[y]);//adding control_decision_set[x]->gamma_name to control channel
				y = y + 1;
			}

			cout << "the current over approximation state estimate after\t" << preserve_transition_under_control[z]->ev->event << "\t and the issued control deicision is:" << endl;
			for (int es = 0; es < current_over_approximation_state_estimate.size(); es++)
			{

				cout << current_over_approximation_state_estimate[es]->state << ",";
			}
			cout << endl;



			if (control_channel.size() == 0)
			{
				cout << "no control decisions are delayed in the control channel;" << endl;
				y = 0;
			}

			if (control_channel.size() > 0)
			{
				cout << "the control decisions delayed in the control channel are:";
				for (int es = 0; es < control_channel.size(); es++)
				{
					if (es == control_channel.size() - 1)
					{
						cout << "(" << control_channel[es]->j->gamma_name << "," << control_channel[es]->time << ").";
					}
					else
					{
						cout << "(" << control_channel[es]->j->gamma_name << "," << control_channel[es]->time << "),";
					}
				}
				cout << endl;
			}


		}


	}
	cout << "no transition is allowed at\t" << current_state->state << endl;





}
void Closed_loop_run_delays_losses_fifo(State* w, int i, Event* e_1)
{
	control_decision_time CDT[20000];
	control_decision_time CDT_for_channel_configuration[20000];

	for (int p = 0; p < 20000; p++)//assign the addresses of the objectives to vector
	{
		CDT_adress.push_back(&CDT[p]);
	}

	for (int p = 0; p < 20000; p++)//assign the addresses of the objectives to vector
	{
		CDT_adress_for_configuration.push_back(&CDT_for_channel_configuration[p]);
	}

	current_state_estimate_open_loop.push_back(w);//initiate the initial state
	update_the_CSE_OL(e_1);//the initial state estimate ES(empty_string)

	current_over_approximation_state_estimate.push_back(w);//initial the over-approximation state 

	current_state = w;//the initial state
	int delay_bound = i;
	vector<State*>actual_arrival_states;
	vector<State*>empty1;
	actual_arrival_states.push_back(w);



	//vector<Control_decision*>decision_issue_within_delay_bound;
	vector<control_decision_time*>control_channel;//storage issued control decisions

	vector<control_decision_time*>control_channel_configuration;
	//vector<Control_decision*>empty_function;//for clearing vector
	vector<control_decision_time*>all_decisions_with_time0;//storage control decisions with timing index 0

	vector<control_decision_time*>all_decisions_with_time0_configuration;//storage control decisions with timing index< 0
	vector<control_decision_time*>all_decisions_with_time_biger_than0;//storage control decisions with timing index >0
	vector<control_decision_time*>empty_function;//for clearing vector
	//cout << control_decision_set.size() << endl;
	int x, z, y, v, q;
	int q_1 = 0;//for finding objective later
	y = 0;//check whether or not 1000 of CDT space is used.
	int y_1 = 0;
	x = (rand() % (control_decision_set.size()));//randomly choose a control decision to be the initial contol decision without delays and losses
	//cout << "x: " << x << endl;

	cout << "the supervisor issues:" << control_decision_set[x]->gamma_name << ";" << endl;


	CDT_adress_for_configuration[y_1]->j = control_decision_set[x];//use the objective
	CDT_adress_for_configuration[y_1]->time = delay_bound;//assigning delay bound to control_decision_set[x]->gamma_name 
	control_channel_configuration.push_back(CDT_adress_for_configuration[y_1]);//adding control_decision_set[x]->gamma_name to control channel
	y_1 = y_1 + 1;





	//compute the unobservable reach
	update_the_COASE_unobservable_reach(&control_channel_configuration);

	control_decision_in_use = control_decision_set[x];//the initial control decision is control_decision_set[x];
	//cout << control_decision_in_use->gamma_name << endl;

	cout << "the control decision used by the plant is:" << control_decision_set[x]->gamma_name << ";" << endl;


	cout << "the initial open-loop state estimate is:" << endl;
	for (int es = 0; es < current_state_estimate_open_loop.size(); es++)
	{
		if (es == current_over_approximation_state_estimate.size() - 1)
		{
			cout << current_state_estimate_open_loop[es]->state << ".";
		}
		else
		{
			cout << current_state_estimate_open_loop[es]->state << ",";
		}
	}
	cout << endl;



	cout << "the initial over-apprxoximation state estimate is:" << endl;
	for (int es = 0; es < current_over_approximation_state_estimate.size(); es++)
	{
		if (es == current_over_approximation_state_estimate.size() - 1)
		{
			cout << current_over_approximation_state_estimate[es]->state << ".";
		}
		else
		{
			cout << current_over_approximation_state_estimate[es]->state << ",";
		}
	}
	cout << endl;



	while (Delata_control(current_state, control_decision_in_use) == 1)//there is an enabled transition at the current state
	{

		//cout << "y=\t" << y << endl;
		if (y_1 == 20000)//the maximum number of objectives that can be used, i.e., the maximum number of the control channel states
		{
			cout << "We stop the simulation since the data collected is enoupgh to illustrate the proposed method." << endl;
			while (1);
			break;

		}
		if (y == 20000)//the maximum number of objectives that can be used, i.e., the maximum number of the control channel states
		{
			cout << "We stop the simulation since the data collected is enoupgh to illustrate the proposed method." << endl;
			while (1);
			break;

		}




		z = (rand() % (preserve_transition_under_control.size()));//choose one enabled event randomly
		//cout << z << endl;
		//preserve_transition_under_control[z]->ev->event:The event to occur


		//if unobservabel;update states


		current_state = preserve_transition_under_control[z]->st[1];

		if (is_observable(preserve_transition_under_control[z]->ev) == 0)
		{
			int yy = 1;
			for (int yyy = 0; yyy < actual_arrival_states.size(); yyy++)
			{
				if (current_state == actual_arrival_states[yyy])
				{
					yy = 0;
				}
			}
			if (yy == 1)
			{
				actual_arrival_states.push_back(current_state);
			}
		}








		if (is_observable(preserve_transition_under_control[z]->ev) == 1)
		{

			//determine whether the proposed method is effective
			/*for (int t = 0; t < actual_arrival_states.size(); t++)
			{
				auto it = std::find(current_over_approximation_state_estimate.begin(), current_over_approximation_state_estimate.end(), actual_arrival_states[t]);
				if (it == current_over_approximation_state_estimate.end())
				{
					std::cout << "fail" << std::endl;
					while (1);
				}
			}*/




			cout << "the states that the plant has reached before a new observation event are:\t" << endl;
			for (int yyyy = 0; yyyy < actual_arrival_states.size(); yyyy++)
			{
				if (yyyy == actual_arrival_states.size() - 1)
				{
					cout << actual_arrival_states[yyyy]->state << ".";
				}
				else
				{
					cout << actual_arrival_states[yyyy]->state << ",";

				}

			}
			cout << endl;


			cout << "................................................" << endl;
			cout << preserve_transition_under_control[z]->ev->event << "\t is observabled" << endl;
			update_the_CSE_OL(preserve_transition_under_control[z]->ev);//update state estimate ES after preserve_transition_under_control[z]




			update_the_COASE_observable_reach(preserve_transition_under_control[z]->ev, &control_channel_configuration);//compute the observable reach under over_approximation



			actual_arrival_states = empty1;
			actual_arrival_states.push_back(current_state);//change??






			cout << "the current open-loop state estimate after\t" << preserve_transition_under_control[z]->ev->event << "\t is:" << endl;
			for (int es = 0; es < current_state_estimate_open_loop.size(); es++)
			{

				cout << current_state_estimate_open_loop[es]->state << ",";
			}
			cout << endl;
			//cout << "the current state after\t" << preserve_transition_under_control[z]->ev->event << "\t is\t:" << current_state->state <<endl;

			/*cout << "the current over approximation state estimate after\t" << preserve_transition_under_control[z]->ev->event << "\t is:" << endl;
			for (int es = 0; es < current_over_approximation_state_estimate.size(); es++)
			{

				cout << current_over_approximation_state_estimate[es]->state << ",";
			}
			cout << endl;*/


			if (preserve_transition_under_control[z]->ev->event == "tick")
			{

				for (int l = 0; l < control_channel.size(); l++)//decrease the timming indexs in control channel
				{

					control_channel[l]->time = control_channel[l]->time - 1;//update control channel

				}
				for (int l = 0; l < control_channel_configuration.size(); l++)//decrease the timming indexs in control channel configuration
				{

					control_channel_configuration[l]->time = control_channel_configuration[l]->time - 1;//update control channel configuration

				}

			}

			//delete all the dicisions whoese timing indices are zero.



			for (int j = 0; j < control_channel.size(); j++)//storage control decisions with timing index 0
			{
				if (control_channel[j]->time == 0)
				{
					all_decisions_with_time0.push_back(control_channel[j]);

				}

			}


			if (all_decisions_with_time0.size() == 0)
			{
				cout << "no new control decision is received by the plant immediately after event\t" << preserve_transition_under_control[z]->ev->event << ";" << endl;
				cout << "no control decisions are lost immediately after event\t" << preserve_transition_under_control[z]->ev->event << ";" << endl;
				//cout << "the current control decision used by the plant immediately after event" << control_decision_in_use->gamma_name << endl;

			}

			if (all_decisions_with_time0.size() > 0)//updating the current control decision by deleting all_decisions_with_time0
			{


				control_decision_in_use = all_decisions_with_time0[all_decisions_with_time0.size() - 1]->j;//update the current control decision;



				cout << "control decision\t" << control_decision_in_use->gamma_name << "\t reaches the plant immediately after event\t" << preserve_transition_under_control[z]->ev->event << ";" << endl;
				if (all_decisions_with_time0.size() == 1)
				{
					cout << "no control decisions are lost immediately after event\t" << preserve_transition_under_control[z]->ev->event << ";" << endl;

				}
				if (all_decisions_with_time0.size() > 1)
				{
					cout << "the lost control decisions immediately after event\t" << preserve_transition_under_control[z]->ev->event << "\t are:" << endl;

					for (int es = 0; es < all_decisions_with_time0.size() - 2; es++)
					{


						cout << all_decisions_with_time0[es]->j->gamma_name << ",";

					}

					cout << endl;
				}



				all_decisions_with_time0 = empty_function;//clear vector all_decisions_with_time0
				//delete all the current control decisions with timing 0 from the control channel
				for (int j = 0; j < control_channel.size(); j++)//storage control decisions with timing index >0
				{
					if (control_channel[j]->time > 0)
					{
						all_decisions_with_time_biger_than0.push_back(control_channel[j]);

					}

				}
				control_channel = all_decisions_with_time_biger_than0;//update control channel by deleting decisions with timing 0
				all_decisions_with_time_biger_than0 = empty_function;//clear vector all_decisions_with_time>0
			}
			cout << "the control decision used by the plant immediately after event\t" << preserve_transition_under_control[z]->ev->event << "\t is:" << control_decision_in_use->gamma_name << ";" << endl;








			//update control channel configuration after event

			for (int j = 0; j < control_channel_configuration.size(); j++)//storage control decisions with timing index >=0
			{
				if (control_channel_configuration[j]->time >= 0)
				{
					all_decisions_with_time0_configuration.push_back(control_channel_configuration[j]);

				}

			}

			control_channel_configuration = all_decisions_with_time0_configuration;//update control channel configuration by deleting control decisions with timing index<0

			all_decisions_with_time0_configuration = empty_function;//initiate the vector

			if (control_channel_configuration.size() == 0)//saving computer space
			{
				y_1 = 0;
			}
			x = (rand() % (control_decision_set.size()));//choose one control decision to issue
			//the chosen decision: control_decision_set[x]->gamma_name
			cout << "the supervisor issues control decision:" << control_decision_set[x]->gamma_name << ";" << endl;






			CDT_adress_for_configuration[y_1]->j = control_decision_set[x];//use the objective
			CDT_adress_for_configuration[y_1]->time = delay_bound;//assigning delay bound to control_decision_set[x]->gamma_name 
			control_channel_configuration.push_back(CDT_adress_for_configuration[y_1]);//adding control_decision_set[x]->gamma_name to control channel
			y_1 = y_1 + 1;

			update_the_COASE_unobservable_reach(&control_channel_configuration);//update the unobservable reach;

			//determine whether there is decison in the control channel
			if (control_channel.size() == 0)
			{
				v = (rand() % (delay_bound + 1));//assigning delay time to control_decision_set[x]->gamma_name 
				if (v == 0)//do not need to update control channel
				{
					cout << "there is no control delays and losses for the issued control decision;" << endl;
					control_decision_in_use = control_decision_set[x];//update the current control decision
					cout << "the current control decision after the issued control deiciosn is:" << control_decision_in_use->gamma_name << ";" << endl;

				}
				if (v > 0)//update control channel
				{
					cout << "the issued control decision is delayed in the control channel;" << endl;
					cout << "the plant use a decision issued before:" << control_decision_in_use->gamma_name << ";" << endl;

					CDT_adress[y]->j = control_decision_set[x];//use the objective
					CDT_adress[y]->time = v;//assigning delay time to control_decision_set[x]->gamma_name 
					control_channel.push_back(CDT_adress[y]);//adding control_decision_set[x]->gamma_name to control channel
					y = y + 1;
				}

			}

			if (control_channel.size() > 0)
			{

				//assigning delay time to control_decision_set[x]->gamma_name considering fifo
				v = control_channel[control_channel.size() - 1]->time + rand() % (delay_bound - control_channel[control_channel.size() - 1]->time + 1);

				cout << "the issued control decision is delayed in the control channel;" << endl;
				cout << "the plant use a decision issued before:" << control_decision_in_use->gamma_name << ";" << endl;

				CDT_adress[y]->j = control_decision_set[x];//use the objective
				CDT_adress[y]->time = v;//assigning delay time to control_decision_set[x]->gamma_name 
				control_channel.push_back(CDT_adress[y]);//adding control_decision_set[x]->gamma_name to control channel
				y = y + 1;


			}









			cout << "the current over approximation state estimate after\t" << preserve_transition_under_control[z]->ev->event << "\t and the issued control deicision is:" << endl;
			for (int es = 0; es < current_over_approximation_state_estimate.size(); es++)
			{

				cout << current_over_approximation_state_estimate[es]->state << ",";
			}
			cout << endl;



			if (control_channel.size() == 0)
			{
				cout << "no control decisions are delayed in the control channel;" << endl;
				y = 0;
			}

			if (control_channel.size() > 0)
			{
				cout << "the control decisions delayed in the control channel are:";
				for (int es = 0; es < control_channel.size(); es++)
				{
					if (es == control_channel.size() - 1)
					{
						cout << "(" << control_channel[es]->j->gamma_name << "," << control_channel[es]->time << ").";
					}
					else
					{
						cout << "(" << control_channel[es]->j->gamma_name << "," << control_channel[es]->time << "),";
					}
				}
				cout << endl;
			}


		}


	}
	cout << "no transition is allowed at\t" << current_state->state << endl;





}
int main()
{






	//State q_0("q_0");
	//State q_1("q_1");
	//State q_2("q_2");
	//State q_3("q_3");
	//State q_4("q_4");
	//State q_5("q_5");
	//State q_6("q_6");

	State q_0("q_0e");
	State q_1("q_e1");
	State q_2("q_e2");
	State q_3("q_e3");
	State q_4("q_e4");
	State q_5("q_e5");
	State q_6("q_e6");
	State q_7("q_e7");
	State q_8("q_e8");
	State q_9("q_e9");
	State q_10("q_e10");
	State q_11("q_e11");
	State q_12("q_e12");
	State q_13("q_e13");
	State q_14("q_e14");
	State q_15("q_e15");
	State q_16("q_e16");
	State q_17("q_e17");
	State q_18("q_e18");
	State q_19("q_e19");
	State q_20("q_e20");
	State q_21("q_e21");
	State q_22("q_e22");
	State q_23("q_e23");
	State q_24("q_e24");
	State q_25("q_e25");
	State q_26("q_e26");




	Event a("a");
	Event b("b");
	Event c("c");
	Event d("d");
	Event tick("tick");

	Event empty_string("empty_string");
	Event ao("a_o");
	Event bo("b_o");
	Event co("c_o");
	Event cl("c_l");

	observable_event_set.push_back(&tick);
	observable_event_set.push_back(&ao);
	observable_event_set.push_back(&bo);
	observable_event_set.push_back(&co);


	Transition t1;
	t1.ses(&q_0, &a, &q_1);
	preserve_transition.push_back(&t1);

	Transition t2;
	t2.ses(&q_1, &tick, &q_2);
	preserve_transition.push_back(&t2);

	Transition t3;
	t3.ses(&q_1, &ao, &q_3);
	preserve_transition.push_back(&t3);

	Transition t4;
	t4.ses(&q_2, &ao, &q_4);
	preserve_transition.push_back(&t4);

	Transition t5;
	t5.ses(&q_4, &tick, &q_0);
	preserve_transition.push_back(&t5);

	Transition t6;
	t6.ses(&q_3, &tick, &q_4);
	preserve_transition.push_back(&t6);

	Transition t7;
	t7.ses(&q_0, &c, &q_5);
	preserve_transition.push_back(&t7);

	Transition t8;
	t8.ses(&q_5, &tick, &q_6);
	preserve_transition.push_back(&t8);

	Transition t9;
	t9.ses(&q_6, &co, &q_7);
	preserve_transition.push_back(&t9);

	Transition t10;
	t10.ses(&q_6, &cl, &q_7);
	preserve_transition.push_back(&t10);

	Transition t11;
	t11.ses(&q_7, &tick, &q_4);
	preserve_transition.push_back(&t11);

	Transition t12;
	t12.ses(&q_5, &b, &q_8);
	preserve_transition.push_back(&t12);

	Transition t13;
	t13.ses(&q_8, &co, &q_9);
	preserve_transition.push_back(&t13);

	Transition t14;
	t14.ses(&q_8, &cl, &q_9);
	preserve_transition.push_back(&t14);

	Transition t15;
	t15.ses(&q_9, &bo, &q_10);
	preserve_transition.push_back(&t15);

	Transition t16;
	t16.ses(&q_9, &d, &q_11);
	preserve_transition.push_back(&t16);

	Transition t17;
	t17.ses(&q_10, &d, &q_12);
	preserve_transition.push_back(&t17);

	Transition t18;
	t18.ses(&q_12, &tick, &q_0);
	preserve_transition.push_back(&t18);

	Transition t19;
	t19.ses(&q_11, &bo, &q_12);
	preserve_transition.push_back(&t19);

	Transition t20;
	t20.ses(&q_11, &tick, &q_13);
	preserve_transition.push_back(&t20);

	Transition t21;
	t21.ses(&q_13, &bo, &q_0);
	preserve_transition.push_back(&t21);

	Transition t22;
	t22.ses(&q_13, &c, &q_14);
	preserve_transition.push_back(&t22);

	Transition t23;
	t23.ses(&q_14, &bo, &q_5);
	preserve_transition.push_back(&t23);

	Transition t24;
	t24.ses(&q_14, &b, &q_15);
	preserve_transition.push_back(&t24);

	Transition t25;
	t25.ses(&q_15, &d, &q_16);
	preserve_transition.push_back(&t25);

	Transition t26;
	t26.ses(&q_15, &bo, &q_8);
	preserve_transition.push_back(&t26);

	Transition t27;
	t27.ses(&q_16, &bo, &q_17);
	preserve_transition.push_back(&t27);

	Transition t28;
	t28.ses(&q_8, &d, &q_17);
	preserve_transition.push_back(&t28);

	Transition t29;
	t29.ses(&q_17, &tick, &q_18);
	preserve_transition.push_back(&t29);

	Transition t30;
	t30.ses(&q_17, &co, &q_11);
	preserve_transition.push_back(&t30);

	Transition t31;
	t31.ses(&q_17, &cl, &q_11);
	preserve_transition.push_back(&t31);

	Transition t32;
	t32.ses(&q_13, &a, &q_19);
	preserve_transition.push_back(&t32);

	Transition t33;
	t33.ses(&q_19, &bo, &q_1);
	preserve_transition.push_back(&t33);

	Transition t34;
	t34.ses(&q_19, &ao, &q_20);
	preserve_transition.push_back(&t34);



	Transition t35;
	t35.ses(&q_20, &bo, &q_3);
	preserve_transition.push_back(&t35);

	Transition t36;
	t36.ses(&q_21, &co, &q_19);
	preserve_transition.push_back(&t36);

	Transition t37;
	t37.ses(&q_21, &cl, &q_19);
	preserve_transition.push_back(&t37);

	Transition t38;
	t38.ses(&q_21, &ao, &q_22);
	preserve_transition.push_back(&t38);

	Transition t39;
	t39.ses(&q_18, &a, &q_21);
	preserve_transition.push_back(&t39);

	Transition t40;
	t40.ses(&q_22, &co, &q_20);
	preserve_transition.push_back(&t40);

	Transition t41;
	t41.ses(&q_22, &cl, &q_20);
	preserve_transition.push_back(&t41);

	Transition t42;
	t42.ses(&q_18, &c, &q_23);
	preserve_transition.push_back(&t42);

	Transition t43;
	t43.ses(&q_18, &co, &q_13);
	preserve_transition.push_back(&t43);

	Transition t44;
	t44.ses(&q_18, &cl, &q_13);
	preserve_transition.push_back(&t44);

	Transition t45;
	t45.ses(&q_23, &co, &q_14);
	preserve_transition.push_back(&t45);

	Transition t46;
	t46.ses(&q_23, &cl, &q_14);
	preserve_transition.push_back(&t46);

	Transition t47;
	t47.ses(&q_23, &b, &q_24);
	preserve_transition.push_back(&t47);

	Transition t48;
	t48.ses(&q_24, &co, &q_15);
	preserve_transition.push_back(&t48);

	Transition t49;
	t49.ses(&q_24, &cl, &q_15);
	preserve_transition.push_back(&t49);

	Transition t50;
	t50.ses(&q_24, &d, &q_25);
	preserve_transition.push_back(&t50);

	Transition t51;
	t51.ses(&q_25, &co, &q_16);
	preserve_transition.push_back(&t51);

	Transition t52;
	t52.ses(&q_25, &cl, &q_16);
	preserve_transition.push_back(&t52);


	Transition t53;
	t53.ses(&q_5, &co, &q_26);
	preserve_transition.push_back(&t53);

	Transition t54;
	t54.ses(&q_5, &cl, &q_26);
	preserve_transition.push_back(&t54);

	Transition t55;
	t55.ses(&q_26, &b, &q_9);
	preserve_transition.push_back(&t55);

	Transition t56;
	t56.ses(&q_26, &tick, &q_7);
	preserve_transition.push_back(&t56);

	Control_decision gamma1;
	gamma1.gamma_name = "gamma_1";
	gamma1.enable.push_back(&c);
	gamma1.enable.push_back(&d);
	gamma1.enable.push_back(&ao);
	gamma1.enable.push_back(&bo);
	gamma1.enable.push_back(&co);
	gamma1.enable.push_back(&cl);

	Control_decision gamma2;
	gamma2.gamma_name = "gamma_2";
	gamma2.enable.push_back(&c);
	gamma2.enable.push_back(&d);
	gamma2.enable.push_back(&ao);
	gamma2.enable.push_back(&bo);
	gamma2.enable.push_back(&co);
	gamma2.enable.push_back(&cl);
	gamma2.enable.push_back(&a);

	Control_decision gamma3;
	gamma3.gamma_name = "gamma_3";
	gamma3.enable.push_back(&c);
	gamma3.enable.push_back(&d);
	gamma3.enable.push_back(&ao);
	gamma3.enable.push_back(&bo);
	gamma3.enable.push_back(&co);
	gamma3.enable.push_back(&cl);
	gamma3.enable.push_back(&b);


	Control_decision gamma4;
	gamma4.gamma_name = "gamma_4";
	gamma4.enable.push_back(&c);
	gamma4.enable.push_back(&d);
	gamma4.enable.push_back(&ao);
	gamma4.enable.push_back(&bo);
	gamma4.enable.push_back(&co);
	gamma4.enable.push_back(&cl);
	gamma4.enable.push_back(&b);
	gamma4.force.push_back(&b);

	Control_decision gamma5;
	gamma5.gamma_name = "gamma_5";
	gamma5.enable.push_back(&c);
	gamma5.enable.push_back(&d);
	gamma5.enable.push_back(&ao);
	gamma5.enable.push_back(&bo);
	gamma5.enable.push_back(&co);
	gamma5.enable.push_back(&cl);
	gamma5.enable.push_back(&a);
	gamma5.enable.push_back(&b);

	Control_decision gamma6;
	gamma6.gamma_name = "gamma_6";
	gamma6.enable.push_back(&c);
	gamma6.enable.push_back(&d);
	gamma6.enable.push_back(&ao);
	gamma6.enable.push_back(&bo);
	gamma6.enable.push_back(&co);
	gamma6.enable.push_back(&cl);
	gamma6.enable.push_back(&a);
	gamma6.enable.push_back(&b);
	gamma6.force.push_back(&b);

	control_decision_set.push_back(&gamma1);
	control_decision_set.push_back(&gamma2);
	control_decision_set.push_back(&gamma3);
	control_decision_set.push_back(&gamma4);
	control_decision_set.push_back(&gamma5);
	control_decision_set.push_back(&gamma6);



	//test
		//vector<control_decision_time*>control_channel_configuration1;
		//control_decision_time te1;
		//te1.j = &gamma8;
		//te1.time = 1;
		//control_channel_configuration1.push_back(&te1);
		//over_approxiamtion_control(&q_1, &control_channel_configuration1);
		//for (int i_1 = 0; i_1 < preserve_transition_under_control_over_approximation.size(); i_1++)
		//{
			//cout << q_1.state << endl;
			//cout << preserve_transition_under_control_over_approximation[i_1]->ev->event << endl;

		//}

		//while (1);
		//test



	srand((unsigned)time(NULL));

	cout << "Please input the delay bound cc" << endl;
	int Delay_bound;
	cin >> Delay_bound;
	cout << "Thanks for your input." << endl;

	cout << "Please input an integer, 0 or 1, to choose the channel mode, where 0 represents FIFO mode and 1 represents Non-FIFO mode, respectively." << endl;
	int mode;
	cin >> mode;
	cout << "Thanks for your input." << endl;

	if (mode == 0)
	{
		Closed_loop_run_delays_losses_fifo(&q_0, Delay_bound, &empty_string);
	}
	if (mode == 1)
	{
		Closed_loop_run_delays_losses_non_fifo(&q_0, Delay_bound, &empty_string);
	}

}
