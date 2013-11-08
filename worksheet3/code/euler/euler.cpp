/**
*	Name: 		Samuel Delacruz
*	Email:		sjd054@bham.ac.uk
*	Assignment:	Question 3b of Worksheet 3 - Computational Modelling
*	
*	This program uses Euler's method to find an approximation of y(pi/4) in the
*	differential equation dy/dt = 1 + (y^2)
*
*	Usage:	Compile using g++, run as follows: > ./euler.o [n] [filename]
*		Where [n] is the maximum number of applications of Euler's method to apply
*		and [filename] is the file name to output data to. 
**/

#include<iostream>
#include<iomanip>
#include<cmath>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

void printResults(vector< vector<double> > &);
void saveResults(vector< vector<double> > &);
double f(double);
double euler(int,double);
vector<double> euler_multi(double,int);
vector<double> get_errors(double,vector<double>&);


//Constants
const double PI_4 = (double)0.25*acos(-1.0);//pi/4

int main(int argc, char* argv[]){

	//BEGIN COMMAND LINE ARGUMENT CHECKING
	if(argc < 3){
		//inform the user of correct usage
		cout << "Correct usage: " << argv[0] << " [n] [filename]" << endl;
		return -1;
	}
	
	//Parse user input as integer
	int n_max = atoi(argv[1]);
	//set filename
	string filename = argv[2];
	//check for positive N
	if(n_max < 0){
	
		cout << "Error: Positive n only" << endl;
		return -1;
	}
	//END COMMAND LINE ARGUMENT CHECKING	
	
	vector<double> euler_results = euler_multi(PI_4,n_max);
	vector<double> errors = get_errors(euler_results);
	
	vector<vector<double> > table(2);
	table.at(0) = euler_results;
	table.at(1) = errors;
	
	printResults(table);
	saveResults(table);
	
	return 0;
}


double f(double y){

	return (double)1.0 + pow(y,(double)2.0);

}

double euler(int n, double h){

	if(n == 0){
		return (double)0.0;
	}
	
	double y_prev = euler(n-1,h);
	return y_prev + h*f(y_prev);
}
