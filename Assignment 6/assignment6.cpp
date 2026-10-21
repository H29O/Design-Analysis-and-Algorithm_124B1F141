#include<iostream>
#include<vector>
using namespace std;

int main(){
	int n , W;
	cout<<"Enter no. of items: ";
	cin>>n;

	cout<<"Enter truck capacity: ";
	cin>>W;
	
	vector<int> weight(n),utility(n);

	cout<<"Enter weight and utility of each item:\n";
	
	for(int i = 0 ; i<n ; i++){
		cout<<"Item "<<i+1<<" : ";
		cin>>weight[i]>>utility[i];
	}

	vector<vector<int>>dp(n+1,vector<int>(W+1,0));
	for (int i = 1 ; i<=n ;i++){
		for (int w = 1 ; w<=W ; w++){
			dp[i][w] = dp[i-1][w];
			if(weight[i-1]<=w){
				dp[i][w] = max(
					dp[i][w],
					utility[i-1] + dp[i-1][w - weight[i-1]]
				);
			}
		}
	}
	cout<<"\nMaximum utility = " <<dp[n][W]<<endl;
	int w = W;
	cout<<"Selected Items: ";

	for(int i = n ; i>0 ; i--){
		if(dp[i][w] != dp[i-1][w]){
			cout<<i<<" ";
			w -= weight[i-1];
		}
	}

	cout<<endl;
	return 0 ;
}
