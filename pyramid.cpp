#include<bits/stdc++.h>
using namespace std;
int main(){
	
	int n;
	cout <<"enter the number of stars and then the no fo linies you want\n";
	cin>>n;
	for (int i=0;i<=n;i++){
		for(int j=0;j<=n-i-1;j++){
			cout<<" ";
		};
		
		for(int k=0;k<=2*i+1;k++){
			cout<<"*";
		};
		
		for(int p=0;p<=n-i-1;p++){
			cout<<" ";	
		};
	cout <<endl;
	
	};
	
	return 0;
}
