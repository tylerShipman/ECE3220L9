#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <vector>
#include <string>

using namespace std;



class LabFunction {	//stores information about file

private:

	int maximumValue;	//max possible value in file
	double average;		//average of file
	//double *data;		//data from file

public:
	vector<double> data;
	int length;			//number of values in file
	LabFunction();
	LabFunction(int);	//takes a number and opens the corresponding file
	//LabFunction(char[20]);	//takes a filename and opens the file
	LabFunction(string);
	~LabFunction();		//frees data

	void offset(int);	//replaces data with offset data
	void scale(int);		//replaces data with scale data
	void normalize();	//replaces data with normalize data
	void center();		//replaces data with center data

	void Sig_info();		//prints info to terminal
	void Save_file();	//saves info to file
	void setAvg();
	void setMax();


	void operator+(double offset){
		for (int i = 0; i < length; i++)
			data[i] += offset;
	}
	void operator*(double scale){
		for (int i = 0; i < length; i++)
			data[i] *= scale;
	}


};

LabFunction::LabFunction(){

	length = 0;
	maximumValue = 0;
	average = 0;



}

LabFunction::LabFunction(int userChoice) {

	//char inputFileName[20];
	string inputFileName;
	FILE* inputFp;
	int sizeOfFile, maxOfFile, i;
	double dataOfFile;
	if (userChoice < 10) {
		//sprintf(inputFileName, "Raw_data_0%d.txt", userChoice);
		inputFileName = "Raw_data_0" + to_string(userChoice) + ".txt";
	} else {
		//sprintf(inputFileName, "Raw_data_%d.txt", userChoice);
		inputFileName = "Raw_data_"+ to_string(userChoice) + ".txt";
	}
	cout<<inputFileName<<endl;
	inputFp = fopen(inputFileName.c_str(), "r");
	if (!inputFp) {
		printf("Error opening input file.");
	}

	fscanf(inputFp, "%d %d", &sizeOfFile, &maxOfFile);
	length = sizeOfFile;
	cout << sizeOfFile << " ";
	maximumValue = maxOfFile;
	cout << maxOfFile << endl;
	//data = new double[length];
	for (i = 0; i < sizeOfFile; i++) {

		fscanf(inputFp, "%lf", &dataOfFile);
		data[i] = dataOfFile;
	}

//	for (i = 0; i < sizeOfFile; i++) {
//
//		cout << data[i] << endl;
//	}

	//average = findAverage(getData(), length);
	fclose(inputFp);

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


	for (i = 0; i < sizeOfFile; i++) {

		fscanf(inputFp, "%lf", &dataOfFile);

		data.push_back(dataOfFile);
	}

	for (i = 0; i < sizeOfFile; i++) {

		cout << data[i] << endl;

	}



	fclose(inputFp);




}

LabFunction::~LabFunction() {
	//free(data);
}

void LabFunction::scale(int scale) {
	*this*scale;
	maximumValue *= scale;
	setAvg();
}

void LabFunction::offset(int offset) {

	*this+offset;
	maximumValue += offset;
	setAvg();

}

void LabFunction::center() {

	int i;
	for (i = 0; i < length; i++) {

		data[i] -= average;

	}
	setAvg();
	maximumValue-= average;

}

void LabFunction::normalize() {

	int i;
	for (i = 0; i < length; i++) {

		data[i] = (data[i] / (double) maximumValue);

	}
	setAvg();
	maximumValue = 1;

}

void LabFunction::Sig_info() {
	int i;
	cout << "Length: " << length << endl << "Max Value: " << maximumValue
			<< endl<< "Average: " << average << endl;
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

void LabFunction::setAvg() {

	double sum = 0;

	for (int i = 0; i < data.size(); i++) {

		sum += data[i];

	}

	average = sum / (double) data.size();



}

void LabFunction::setMax(){
	maximumValue = data[0];

		for(int i=0; i<length; i++)
		{
			if( data[i] > maximumValue )
			{
				maximumValue = data[i];
			}
		}

}

void menu() {	//Displays the following options and takes the userSeletion

	cout << "Select one of the following:" << endl << "1. Scale" << endl
			<< "2. Offset" << endl << "3. Center" << endl << "4. Normalize"
			<< endl;

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

LabFunction operator+(const LabFunction &lhs, const LabFunction &rhs){
	if(lhs.length != rhs.length)
		{
			cout << "Error: objects are not of same length" << endl;
			exit(-1);
		}
		else
		{
			LabFunction sum;
			sum.length = lhs.length;
			for(int i=0; i<sum.length; i++)
			{
				// use push_back to grow vector
				sum.data.push_back(lhs.data[i]);
				sum.data[i] += rhs.data[i];
			}
			sum.setAvg();
			sum.setMax();
			return sum;
		}
}

int main(int argc, char** argv) {

	int counter = 1;			//Keeps track of args
	int userChoice;			//takes user input
	//char inputFileName[30];	//name of file
	string inputFileName;
	int selection;
	int factor;


	if (argc == 3) {

		if (strcmp(argv[counter], "-n") == 0) {
			LabFunction test(atoi(argv[counter+1]));
			menu();
			cin>>selection;
			menu2(test);



		} else if (strcmp(argv[counter], "-f") == 0) {

			LabFunction test(argv[counter + 1]);
			menu();
			cin>>selection;
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
			//sprintf(inputFileName, "Raw_data_0%d.txt", userChoice);
			inputFileName = "Raw_data_0" + to_string(userChoice) + ".txt";

		} else {
			//sprintf(inputFileName, "Raw_data_%d.txt", userChoice);
			inputFileName = "Raw_data_" + to_string(userChoice) + ".txt";
		}


		LabFunction test(inputFileName);

		menu();
		cin>>selection;
		if (selection == 1) {
					cout << "Enter a number to scale by:" << endl;
					cin >> factor;
					test.scale(factor);

				}
				if (selection == 2) {
					cout << "Enter a number to offset by: " << endl;
					cin >> factor;
					test.offset(factor);
				}
				if (selection == 3) {
					test.center();
				}
				if (selection == 4) {
					test.normalize();
				}

		menu2(test);


	}

	LabFunction function3("Raw_data_01.txt");
	cout<<"----------------------------------------------------------------"<<endl;
	LabFunction function2("Raw_data_01.txt");
	LabFunction function4 = operator+(function2,function3);
	function4.Sig_info();



	return 0;
}
