//---------------------------------------------------------------------------

#ifndef testH
#define testH

#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include <ctime>        // time
#include <cstdlib>      // srand,rand
#include <fstream>
#include <string>
#include <sstream> //文字ストリーム

//---------------------------------------------------------------------------
//using namespace std;

class Qlearning
{

	public:
		Qlearning(const double &qmax,const double &rew,const double &alpha,const double &gamma,const int &epsilon,const int &trial);
		~Qlearning();
		void train();
		void outlog(std::string str);
		void outlog(double value);

	private:
		double state_machine(int s,int a,int &sd);
		double max_Qval(int s,int num_a,std::vector< std::vector<double> > &Qtable);
		int select_action(int s,int num_a,std::vector< std::vector<double> > &Qtable);
		int epsilon_greedy(int epsilon,int s,int num_a,std::vector< std::vector<double> > &Qtable);

		std::vector< std::vector<double> > Qtable;

		
		double Q_max;
		double reward;

		// const parameter		
		const double alpha;
		const double gamma;
		const int epsilon;
		const int trial_max;

		int num_a;
		int num_s;

		template <typename T> std::string tostr(const T& t)
		{
			std::ostringstream os; os<<t; return os.str();
		}
		
};

#endif
