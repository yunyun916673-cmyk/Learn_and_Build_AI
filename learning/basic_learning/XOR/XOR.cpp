#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <random>
#include <algorithm>
using namespace std;
double S(double x) {return 1.0/(1.0+exp(-x));}
double dS(double s) {return s*(1.0-s);}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	random_device rd;
    default_random_engine gen(rd());
    uniform_real_distribution<double> dist(-1.0, 1.0);
    double h1_w1=dist(gen);
    double h1_w2=dist(gen);
    double h1_b=dist(gen);
    double h2_w1=dist(gen);
    double h2_w2=dist(gen);
    double h2_b=dist(gen);
    double o_w1=dist(gen);
    double o_w2=dist(gen);
    double o_b=dist(gen);
    double learn_rate=0.5;
    vector<array<int,3>> vec={{0,0,0},{0,1,1},{1,0,1},{1,1,0}};
    for (int i=0;i<10;i++) cout<<'=';
    cout<<'\n';
    cout<<"start training"<<'\n';
    for (int i=0;i<1000000;i++)
    {
    	double total_loss=0.0;
    	shuffle(vec.begin(),vec.end(),gen);
    	for (auto &[x1,x2,tag]:vec)
    	{
    		double h1_a=S(h1_w1*x1+h1_w2*x2+h1_b);
    		double h2_a=S(h2_w1*x1+h2_w2*x2+h2_b);
    		double o_a=S(o_w1*h1_a+o_w2*h2_a+o_b);
    		double error=o_a-tag;
    		total_loss+=0.5*error*error;
    		double o_t=error*dS(o_a);
    		double h1_t=o_t*o_w1*dS(h1_a);
    		double h2_t=o_t*o_w2*dS(h2_a);
    		o_w1-=learn_rate*o_t*h1_a;
    		o_w2-=learn_rate*o_t*h2_a;
    		o_b-=learn_rate*o_t;
    		h1_w1-=learn_rate*h1_t*x1;
    		h1_w2-=learn_rate*h1_t*x2;
    		h1_b-=learn_rate*h1_t;
    		h2_w1-=learn_rate*h2_t*x1;
    		h2_w2-=learn_rate*h2_t*x2;
    		h2_b-=learn_rate*h2_t;
    	}
    	if (!(i%10000))
    	{
    		cout<<"epoch: "<<i<<'\n'<<"total_loss: "<<total_loss<<'\n';
    	}
    }
    for (auto &[x1,x2,tag]:vec)
    {
    	double h1_a=S(h1_w1*x1+h1_w2*x2+h1_b);
    	double h2_a=S(h2_w1*x1+h2_w2*x2+h2_b);
    	double o_a=S(o_w1*h1_a+o_w2*h2_a+o_b);
    	cout<<"x1: "<<x1<<' '<<"x2: "<<x2<<'\n';
    	cout<<(o_a>0.5?"YES":"NO")<<'\n';
    }
    return 0;
}
