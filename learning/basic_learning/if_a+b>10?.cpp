#include <iostream>
#include <vector>
#include <random>
#include <tuple>
using ll=long long;
using namespace std;
int func(double w1,double w2,double b,int x1,int x2){return (w1*x1+w2*x2+b)>0;}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	random_device rd;
	default_random_engine gen(rd());
	uniform_real_distribution<double> dist(-1,1);
	uniform_int_distribution<int> intdist(0,15);
	double w1=dist(gen);
	double w2=dist(gen);
	double b=dist(gen);
	double learn_rate=0.05;
	vector<tuple<double,double,int>> vec={};
	for (int i=0;i<1000000;i++)
	{
		double a1=intdist(gen);
		double a2=intdist(gen);
		vec.push_back({a1,a2,(int)(a1+a2>10)});
	}
	for (int i=0;i<10;i++) cout<<'=';
	cout<<'\n';
	cout<<"start training:"<<'\n';
	int cnt=0;
	int total_error=0;
	for (auto &[x1,x2,tag]:vec)
	{
		double z=w1*x1+w2*x2+b;
		int cur=(z>0);
		int error=tag-cur;
		total_error+=error;
		w1+=learn_rate*error*x1;
        w2+=learn_rate*error*x2;
        b+=learn_rate*error; cnt++;
        if (!(cnt%10000))
        {
        	cout<<"the"<<' '<<cnt<<':'<<'\n';	cout<<"total_error:"<<total_error<<'\n';
        	cout<<"w1:"<<w1<<' '<<"w2:"<<w2<<' '<<"b:"<<b<<'\n';
        	total_error=0;
        }
	}
	cout<<"stop training:"<<'\n';
	cout<<"result:"<<' ';
	cout<<"w1:"<<w1<<' '<<"w2:"<<w2<<' '<<"b:"<<b<<'\n';
	for (int i=0;i<10;i++) cout<<'=';
	cout<<'\n';
	for (int i=0;i<10;i++) cout<<'=';
	cout<<'\n';
	cout<<"start testing:"<<'\n';
	for (int i=0;i<10;i++)
	{
		int x1=intdist(gen);
		int x2=intdist(gen);
		cout<<"x1:"<<' '<<x1<<' '<<"x2:"<<' '<<x2<<'\n';
		cout<<"Answer:"<<' ';
		cout<<(func(w1,w2,b,x1,x2)?"YES":"NO")<<'\n';
	}
	cout<<"stop testing:"<<'\n';
	for (int i=0;i<10;i++) cout<<'=';
	cout<<'\n';
}