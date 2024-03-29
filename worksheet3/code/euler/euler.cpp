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
void saveResults(vector< vector<double> > &,string);
double f(double);
double euler(int,double);
vector<double> euler_multi(double,int);
vector<double> get_errors(double,vector<double>&);


//Constants
const double PI_4 = (double)0.25*acos(-1.0);//pi/4
const double EXPECTED = (double)1.0;//tan(pi/4)

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
	
	cout << "\n\n||Calculating results, please wait...||\n";
	//Get results and errors, for y(pi/4), and up to max n specified
	vector<double> euler_results = euler_multi(PI_4,n_max);
	vector<double> errors = get_errors(EXPECTED,euler_results);
	
	//Store them in a 'table'
	vector<vector<double> > table(2);
	table.at(0) = euler_results;
	table.at(1) = errors;
	

	printResults(table);
	cout << "\n||Operation successful, saving results to " + filename + "||";
	saveResults(table,filename);
	
	return 0;
}

//[ dy/dt = 1 + y^2 ]
double f(double y){

	return (double)1.0 + pow(y,(double)2.0);

}

//Recursive function for retrieving nth value using euler method
//
double euler(int n, double h){

	if(n == 0){
		return (double)0.0;
	}
	
	double y_prev = euler(n-1,h);
	return y_prev + h*f(y_prev);
}

//Perform multiple Euler method solutions for different number of n
vector<double> euler_multi(double x_max,int n_max){

	vector<double> results(n_max);
	
	for(int i = 0; i < results.size(); i++){
	
		double h = x_max / (double)(i+1);//i+1 due to index starting at 0
		results.at(i) = euler(i+1,h);
	
	}
	
	return results;

}

//Iterate over all results and compare to expected result
vector<double> get_errors(double expected, vector<double> &values){

	vector<double> errors(values.size());
	
	for(int i = 0; i < errors.size(); i++){
	
		errors.at(i) = (double)abs(expected - values.at(i));
	
	}
	
	return errors;

}

//Print results to screen
void printResults(vector< vector<double> >& results){

	//print headers
	cout << "\nn\ty(pi/4)\tError\n";
	
	//Iterate over each n value
	for(int n = 0; n < results.at(0).size(); n++){
		
		//print iteration number
		cout << n+1 << "\t";
		
		//Iterate over columns
		for(int j = 0; j < results.size(); j++){

			cout << setprecision(15) << scientific << results.at(j).at(n) << "\t";

		}

		//newline
		cout << endl;

	}
}

//Save results to file
void saveResults(vector< vector<double> >& results, string fname){

	ofstream dataFile(fname.c_str());

	if(dataFile.is_open()){

		//Iterate over each n value
		for(int n = 0; n < results.at(0).size(); n++){
			
			//print iteration number
			dataFile << n+1 << "\t";
			
			//Iterate over columns
			for(int j = 0; j < results.size(); j++){

				dataFile << setprecision(15) << scientific << results.at(j).at(n) << "\t";

			}

			//newline
			dataFile << endl;

		}
	}
	
	dataFile.close();
}
