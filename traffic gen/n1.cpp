
#include<iostream>

#include<stdlib.h>
using namespace std;


void main(int argc,char* argv[])
{
	long long int i,n;
	int max,maxcom,s,d;
	char oname[20];
	cout<<"Enter max: ";
	cin>>max;
	cout<<"Enter maxcom: ";
	cin>>maxcom;
	cout<<"Enter file name: ";
	cin>>oname;
	cout<<"Enter n: ";
	cin>>n;
	srand(rand()*rand());
	freopen(oname, "w", stdout);
	cout<<n<<"\n";
	for(i=0;i<n;i++){
		s=rand()%max;
		d=rand()%max;
		if(s==d){
			i--;
			continue;
		}
		cout<<s<<" ";
		cout<<d<<" ";
		cout<<rand()%maxcom<<" ";
		cout<<rand()%maxcom<<" ";
		cout<<rand()%maxcom<<"\n";
	}

	
}
	
   