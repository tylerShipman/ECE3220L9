/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: TylerShipman
 *
 * Created on October 13, 2016, 10:37 AM
 */

#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <string>
using namespace std;

//double findAverage(double* values, int size); //Finds average of data
double findAverage(vector<double> values);
class LabFunction {	//stores information about file

private:

	//average of file
	//double *data;		//data from file

public:
	int maximumValue;	//max possible value in file
	double average;
	int length;			//number of values in file
	vector<double> data;
	LabFunction();
	LabFunction(int);	//takes a number and opens the corresponding file
	LabFunction(string);	//takes a filename and opens the file
	~LabFunction();		//frees data

	void offset(double);	//replaces data with offset data
	void scale(int);		//replaces data with scale data
	void normalize();	//replaces data with normalize data
	void center();		//replaces data with center data

	void Sig_info();		//prints info to terminal
	void Save_file();	//saves info to file

	void operator+(double offset){
		for(int i = 0; i < length; i++)
			data[i] = data[i] + (double) offset;

	}

	void operator*(int factor){

		    for(int i=0;i<length;i++)
		    		data[i] *= (double)factor;


	}

	vector<double> getData() { //Getter that returns data
		return data;
	}

};

LabFunction operator+(const LabFunction &x , const LabFunction &y){
	if(x.length != y.length)
		{
			cout << "Error: objects need to be of the same length." << endl;
			exit(-1);
		}
		else
		{
			LabFunction sum;
			sum.length = x.length;
			for(int i=0; i<sum.length; i++)
			{
				// use push_back to grow vector
				sum.data.push_back(x.data[i]);
				sum.data[i] += y.data[i];
			}
			sum.average = findAverage(sum.data);

			return sum;
		}

}

LabFunction::LabFunction(){

	data.resize(0);
	maximumValue = 0;
	average = 0;
	length = 0;
}

LabFunction::LabFunction(int userChoice) {

	char inputFileName[20];
	FILE* inputFp;
	int sizeOfFile, maxOfFile, i;
	double dataOfFile;
	if (userChoice < 10) {
		sprintf(inputFileName, "Raw_data_0%d.txt", userChoice);

	} else {
		sprintf(inputFileName, "Raw_data_%d.txt", userChoice);
	}
	cout<<inputFileName<<endl;
	inputFp = fopen(inputFileName, "r");
	if (!inputFp) {
		printf("Error opening input file.");
	}

	fscanf(inputFp, "%d %d", &sizeOfFile, &maxOfFile);
	length = sizeOfFile;
	cout << sizeOfFile << " ";
	maximumValue = maxOfFile;
	cout << maxOfFile << endl;
	//data = new double[length];
	data.resize(length);

	for (i = 0; i < sizeOfFile; i++) {

		fscanf(inputFp, "%lf", &dataOfFile);
		data[i] = dataOfFile;
	}

	for (i = 0; i < sizeOfFile; i++) {

		cout << data[i] << endl;
	}

	//average = findAverage(getData(), length);
	average = findAverage(getData());

}

LabFunction::LabFunction(string fileName) {
	int sizeOfFile, maxOfFile, i;
	double dataOfFile;
	cout<<fileName<<endl;
	FILE* inputFp = fopen(fileName.c_str(), "r");
	if (!inputFp) {
		printf("Error opening input file.");
	}

	fscanf(inputFp, "%d %d", &sizeOfFile, &maxOfFile);
	length = sizeOfFile;

	maximumValue = maxOfFile;

	//data = new double[sizeOfFile];
	data.resize(length);

	for (i = 0; i < sizeOfFile; i++) {

		fscanf(inputFp, "%lf", &dataOfFile);

		data[i] = dataOfFile;
	}

	for (i = 0; i < sizeOfFile; i++) {

		cout << data[i] << endl;

	}

	//average = findAverage(data, length);
	average = findAverage(getData());

}

LabFunction::~LabFunction() {
	//free(data);
}

void LabFunction::scale(int scale) {
//	int i;
//	for (i = 0; i < length; i++) {
//
//		data[i] = data[i] * scale;
//
//	}

	*this*scale;
}

void LabFunction::offset(double offset) {
//	int i;
//	for (i = 0; i < length; i++) {
//
//		data[i] = data[i] + offset;
//
//	}

	*this+offset;

}

void LabFunction::center() {

	int i;
	for (i = 0; i < length; i++) {

		data[i] -= average;

	}

}

void LabFunction::normalize() {

	int i;
	for (i = 0; i < length; i++) {

		data[i] = (data[i] / (double) maximumValue);

	}

}

void LabFunction::Sig_info() {
	int i;
	cout << "Length: " << length << endl << "Max Value: " << maximumValue
			<< endl << "Average: " << average << endl;
	for (i = 0; i < length; i++) {
		cout << data[i] << endl;
	}

}

void LabFunction::Save_file() {
	int i;
	FILE* outputFp = fopen("output.txt", "ab+");
	fprintf(outputFp, "%d %d\n", length, maximumValue);
	for (i = 0; i < length; i++) {

		fprintf(outputFp, "%lf\n", data[i]);

	}

	fclose(outputFp);

}

double findAverage(vector<double> values) {

	int i = 0;
	double sum = 0;
	double average = 0;
	for (i = 0; i < values.size(); i++) {

		sum += values[i];

	}

	average = sum / (double) values.size();

	return average;

}



void functionEvaluater(LabFunction test, int choice) {	//Works with menu() and performs corresponding operation
	int factor;
	if (choice == 1) {
		cout << "Enter a number to scale by:" << endl;
		cin >> factor;
		test.scale(factor);

	}
	if (choice == 2) {
		cout << "Enter a number to offset by: " << endl;
		cin >> factor;
		test.offset(factor);
	}
	if (choice == 3) {
		test.center();
	}
	if (choice == 4) {
		test.normalize();
	}



}

void menu(LabFunction test) {	//Displays the following options and takes the userSeletion
	int userChoice;
	cout << "Select one of the following:" << endl << "1. Scale" << endl
			<< "2. Offset" << endl << "3. Center" << endl << "4. Normalize"
			<< endl;
	cin >> userChoice;
	functionEvaluater(test, userChoice);

}

void menu2(LabFunction test) { //Displays the following options and takes the userSeletion

	int userChoice3;
	cout << "Select one of the following:" << endl << "1. Print info" << endl
			<< "2. Print info to file" << endl << "3. Both" << endl;
	cin >> userChoice3;

	if (userChoice3 == 1) {
		test.Sig_info();
	} else if (userChoice3 == 2) {
		test.Save_file();
	} else if (userChoice3 == 3) {
		test.Sig_info();
		test.Save_file();
	} else {
		cout << "Invalid input..." << endl;
	}

}

int main(int argc, char** argv) {

	int counter = 1;			//Keeps track of args
	int userChoice;			//takes user input
	char inputFileName[30];	//name of file




	if (argc == 3) {

		if (strcmp(argv[counter], "-n") == 0) {
			LabFunction test(atoi(argv[counter+1]));
			menu(test);
			menu2(test);



		} else if (strcmp(argv[counter], "-f") == 0) {

			LabFunction test(argv[counter + 1]);
			menu(test);
			menu2(test);

		}
	} else {
		cout
				<< "Please Enter an integer from 1-14 to open the corresponding file:"
				<< endl;
		cin >> userChoice;

		if (userChoice > 14 || userChoice < 1) {
			cout << "Error: Your selection was out of range..." << endl;
			return 0;
		}

		if (userChoice < 10) {
			sprintf(inputFileName, "Raw_data_0%d.txt", userChoice);

		} else {
			sprintf(inputFileName, "Raw_data_%d.txt", userChoice);
		}


		LabFunction test(inputFileName);

		menu(test);
		menu2(test);


	}



	return 0;
}

