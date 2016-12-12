/* 
 * Qlearning test
 * 2016.06.06
 * author:soma62jp
 *                  */


#include "test.h"

//using namespace std;


Qlearning::Qlearning(const double &qmax,const double &rew,const double &alpha,const double &gamma,const int &epsilon,const int &trial):
		Q_max(qmax),
		reward(rew),
		alpha(alpha),
		gamma(gamma),
		epsilon(epsilon),
		trial_max(trial)
{

	//
	num_a=2;
	num_s=2;

	Qtable.resize(num_s);				// ()内の数字が要素数になる
	for( int i=0; i<num_s; i++ ){
		Qtable[i].resize(num_a);
		std::fill(Qtable[i].begin(), Qtable[i].end(), 0);
	}

	srand((unsigned int)time(NULL));


}

Qlearning::~Qlearning()
{

}


void Qlearning::train()
{
	int a=0;
	int s=0;
	int sd=0;

	for(int i=0;i<trial_max;i++){
	
		//行動の選択
		a=epsilon_greedy(epsilon,s,num_a,Qtable);
		//行動の実行
		reward=state_machine(s,a,sd);
		//sdにおけるＱ値の最大値を求める
		Q_max=max_Qval(sd,num_a,Qtable);
		//Ｑ値の更新
		Qtable[s][a]=(1 - alpha) * Qtable[s][a] + alpha * (reward + gamma * Q_max);
		s=sd;

		std::cout << "i=" << i << std::endl;
		if(reward>0){
			std::cout << "成功" << std::endl;
		}
	
	}

	for(int i=0;i<num_s;i++){
		for(int j=0;j<num_a;j++){
			std::cout << " " << Qtable[i][j];
		}
		std::cout << std::endl;
	}


}

double Qlearning::state_machine(int s,int a,int &sd)
{
	double rew;

	if(a==0){
		sd=!s;
		rew=0;
	}else{
		if(s==1){
			sd=s;
			rew=10;
		}else{
			sd=s;
			rew=0;
		}
	}

	return rew;

}

double Qlearning::max_Qval(int s,int num_a,std::vector< std::vector<double> > &Qtable)
{
	double max;
	int i=0;
	
	max=Qtable[s][0];
	for(i=1;i<num_a;i++){
		if (Qtable[s][i]>max){
			max=Qtable[s][i];
		}
	}
	return max;

}

int Qlearning::select_action(int s,int num_a,std::vector< std::vector<double> > &Qtable)
{
	double max;
	int i=0;
	std::vector<int> i_max(num_a,0);
	int num_i_max=1;
	int a;

	i_max[0]=0;
	max=Qtable[s][0];

	for(i=1;i<num_a;i++){
		if (Qtable[s][i]>max){
			max=Qtable[s][i];
			num_i_max=1;
			i_max[0]=i;
		}
		else if(Qtable[s][i]==max){
			num_i_max++;
			i_max[num_i_max-1]=i;
		}
	}

	for(i=0;i<num_i_max;i++){
		std::cout << "i_max[" <<  i << "]=" << i_max[i] << std::endl;
	}

	a=i_max[rand()%num_i_max];
	
	return a;

}

int Qlearning::epsilon_greedy(int epsilon,int s,int num_a,std::vector< std::vector<double> > &Qtable)
{
	int a;
	if(epsilon > rand()%100){
		//無作為に行動を選択
		a=rand()%num_a;
		//printf("無作為に選択\n");
	}
	else{
		//最大のＱ値を持つ行動を選択
		a=select_action(s,num_a,Qtable);
		//printf("最大値をとる行動を選択\n");
	}
	return a;

}


void Qlearning::outlog(double value)
{
	//Form1->Memo1->Lines->Add(FloatToStr(value));
	std::cout << value << std::endl;
}

void Qlearning::outlog(std::string str)
{
	//Form1->Memo1->Lines->Add(str.c_str());
	std::cout << str << std::endl;
}



int main()
{

  //Qlearning ql(0,0,0.5,0.9,10,1000);

  //ql.train();

  std::cout << "まだできていません。。" << std::endl;

  return 0;

}
