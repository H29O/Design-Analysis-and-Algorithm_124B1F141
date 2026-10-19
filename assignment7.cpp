#include<iostream>
using namespace std;

int graph[10][10];
int color[10];
int n,m;

bool isSafe(int v,int c){
	for (int i = 0 ;i < n ; i++){
		if (graph[v][i] == 1 && color[i]==c) return false;
	}
	return true;
}

bool coloring(int v){
	if(v==n) return true;
	for (int c= 1 ; c<=m ; c++){
		if (isSafe(v,c)){
			color[v]=c;
			if(coloring(v+1)) return true;
			color[v]=0;
		}
	}
	return false;
}

int main(){
	cout<<"Enter no. of subjects : ";
	cin>>n;
	cout<<"Enter no. of time slots : ";
	cin>>m;

	cout<<"Enter the adjacency matric:\n";
	for(int i = 0 ; i<n ;i++){
		for(int j = 0 ; j<n ; j++){
			cin>>graph[i][j];
		} 
	}
	if(coloring(0)){
		cout<<"\nTimetabe:\n";
		for(int i = 0 ; i<n ;i++){
			cout<<"Subject "<<i+1
			    <<" -> TimeSlot " <<color[i] <<endl;
		}
	}
	else{
		cout<<"\nNo possible timetable with "
		    <<m<<" time slots.\n";
	}
	return 0 ;
}
