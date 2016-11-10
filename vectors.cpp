// Lab9_vectors.cpp
// This program shows some simple vector examples, and asks for simple tasks.
// Reference: Lippman, section 3.3

// Author: Luis Rivera

// IMPORTANT NOTE: YOU MAY NEED TO COMPILE ADDING THE FOLLOWING FLAG: -std=c++11
// Example: g++ Lab9_vectors.cpp -o Lab9_vectors -std=c++11
// Some initialization methods and other things are not supported by the old standard.

#include <iostream>
#include <vector>

using namespace std;

// Main function. Shows a few examples. Complete the assignments stated in the comments.
int main()
{
	vector<int> ivec1(5), ivec2;
	vector<double> dvec1{5.1}, dvec2(5,1.5);
	vector<string> svec1 = {"hello", "world"};
	// vector<myClass> myCvec;	// you can have vectors of objects
	// in general: vector<Type> vec;	// vector is a template

	for(int i = 0; i < ivec1.size(); i++)
		cout << ivec1[i] << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:ivec1)	// This is equivalent to the above for loop
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:dvec1)
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:dvec2)
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:svec1)
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
		
	cout << "Original size: " << ivec2.size() << endl;
	ivec2.push_back(50);
	cout << "New size: " << ivec2.size() << "\nAdded element: " << ivec2[0] << endl;
	cout << "\n------------------------------------------------------------------" << endl;
		
// ***********************************************************************
// Try all the wasy to initializa a vector shown in Table 3.4. Use the
// vectors above and/or declare new vectors.
// Some of those operations have already been used, but write your
// own examples.

vector<int> emptyVector; // Empty Vector

//Vectors with elements
vector<int> vector1{0,1,2};
vector<int> vector2 = {3,4,5};

//initialize to be same as vector 2
vector<int> vector3(vector2);
vector<int> vector4 = vector2;


// Do exercises 3.14 and 3.15 from Lippman (page 102)


//3.14

cout<<"Enter 5 integers seperated by a space"<<endl;

for(int i = 0; i < 5; i++){

	int temp;
	cin>>temp;
	emptyVector.push_back(temp);
}

cout<<"The numbers you entered were:"<<endl;

for(auto i: emptyVector)
	cout<<i<<endl;



//3.15

vector<string> stringVector;

cout<<"Enter 5 words seperated by a space"<<endl;

for(int i = 0; i < 5; i++){

	string temp;
        cin>>temp;
        stringVector.push_back(temp);

}

cout<<"The words you entered were:"<<endl;

for(auto i: stringVector)
	cout<<i<<endl;



// Try all the vector operations shown in table 3.5. Use the vectors above
// or define new ones. Try different types.

if(stringVector.empty() || emptyVector.empty())
	cout<<"You have an empty vector"<<endl;

cout<<"The size of your string vector is "<<stringVector.size()<<"."<<endl;

stringVector.push_back("NEW");

cout<<"New value in string index 0 is "<< stringVector[0]<<endl;

vector<int> numbers1{1,2,3,4};
vector<int> numbers2(numbers1);

if(numbers1 == numbers2)
	cout<<"These vectors are equal"<<endl;

numbers1 = {11,12,10,9};

if(numbers1 != numbers2)
	cout<<"These vectors are not equal"<<endl;


if(numbers1 > numbers2)
	cout<<"numbers1 > numbers2"<<endl;

numbers2 = {20,30,30,20};

if(numbers1 < numbers2)
	cout<<"numbers2 > numbers1"<<endl;



// ***********************************************************************

	return 0;
}
