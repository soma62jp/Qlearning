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
		trial_max(trial),
		x_size(10),
		y_size(9)
{

	//
	num_a=4;
	num_s=x_size*y_size;
	x_init=1;
	y_init=1;
	num_step=100;

	Qtable.resize(num_s);				// ()内の数字が要素数になる
	for( int i=0; i<num_s; i++ ){
		Qtable[i].resize(num_a);
		std::fill(Qtable[i].begin(), Qtable[i].end(), 0);
	}

	maze.resize(x_size);				// ()内の数字が要素数になる
	for( int i=0; i<x_size; i++ ){
		maze[i].resize(y_size);
		std::fill(maze[i].begin(), maze[i].end(), 0);
	}

	//壁の設定
	for(int i=0;i<x_size;i++){
		for(int j=0;j<y_size;j++){
			if(i==0 || j==0 || i==x_size-1 || j==y_size-1){
				maze[i][j]=-1;
			}
		}
	}

	maze[2][2]=-1;
	maze[3][2]=-1;
	maze[6][3]=-1;
	maze[7][3]=-1;
	maze[8][3]=-1;
	maze[2][6]=-1;
	maze[2][7]=-1;
	maze[3][6]=-1;
	maze[6][7]=-1;

	//報酬の設定
	maze[8][6]=10;

	srand((unsigned int)time(NULL));


}

Qlearning::~Qlearning()
{

}


void Qlearning::train()
{
	int x,y;
	int a=0;
	int s=0;
	int sd=0;

	for(int i=0;i<x_size;i++){
		for(int j=0;j<y_size;j++){
			std::cout << std::setw(3) << maze[i][j];
		}
		std::cout << std::endl;
	}

	x=x_init;
	y=y_init;
	s=xy2s(x,y,x_size);

	for(int i=0;i<trial_max;i++){

		std::cout << "trial=" << i << std::endl;

		for(int j=0;j<num_step;j++){
		
			//行動の選択
			a=epsilon_greedy(epsilon,s,num_a,Qtable);
			sd=move(a,x,y,x_size);
			reward=maze[x][y];
			//sdにおけるＱ値の最大値を求める
			Q_max=max_Qval(sd,num_a,Qtable);
			//Ｑ値の更新
			Qtable[s][a]=(1 - alpha) * Qtable[s][a] + alpha * (reward + gamma * Q_max);
			s=sd;

			
			if(reward<0){
				std::cout << "失敗" << std::endl;
				x=x_init;
				y=y_init;
				s=xy2s(x,y,x_size);
				break;
			}else if(reward>0){
				std::cout << "成功" << std::endl;
				x=x_init;
				y=y_init;
				s=xy2s(x,y,x_size);
				break;		
			}else{
				s=sd;
			}

		}
	}

	for(x=0;x<x_size;x++){
		for(y=0;y<y_size;y++){
			s=xy2s(x,y,x_size);
			Q_max=max_Qval(s,num_a,Qtable);
			if(Q_max==0){
				std::cout << std::setw(3) << maze[x][y];
			}else{
				a=select_action(s,num_a,Qtable);
				if(a==0){
					std::cout << "  →";
				}else if(a==1){
					std::cout << "  ↓";
				}else if(a==2){
					std::cout <<"  ←";
				}else{
					std::cout << "  ↑";
				}
			}
		}
		std::cout << std::endl;
	}
}

int Qlearning::move(int a,int &x,int &y,int x_size)
{
	int sd;

	if(a==0){
		y++;
	}else if(a==1){
		x++;
	}else if(a==2){
		y--;
	}else{
		x--;
	}

	sd=xy2s(x,y,x_size);

	return sd;

}

int Qlearning::xy2s(int x,int y,int x_size)
{
	int s;
	s=x+y*x_size;
	return s;

}

double Qlearning::state_machine(int s,int a,int &sd)
{
/*	
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
*/
	return 0;
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
		//std::cout << "i_max[" <<  i << "]=" << i_max[i] << std::endl;
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

  Qlearning ql(0,0,0.5,0.9,10,300);

  ql.train();

  return 0;

}
