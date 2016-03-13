#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

char delimiter = ',';

//function prototype to settle scope access.
string extractFromLine(string sourceLine, int seriesSize, int posSeries[]);

int main(){
	string name;
	int colArrSize = 0;

	//user interface
	cout << "What data are you extracting? (oneWord): ";
	cin >> name;
	name = name + ".txt";
	cout << "How many columns?: ";
	cin >> colArrSize;
	int colArray[colArrSize];//makes the array of columns to extract arbitrarily sized
	cout << "Enter each position number \n(starting from 0) \nfollowed by the enter key: \n";
	//collect positions to extract
	for (int i = 0; i < colArrSize; i++) {
		cin >> colArray[i];
	}


	//open and check input/output files
	ifstream inputFile("rawData");
	if(!inputFile) {
		cout << "Unable to open the data source file\n";
		exit(-1);
	}
	ofstream outputFile(name.c_str());
	if(!outputFile){
		cout << "unable to open outputFile\n";
		exit(-1);
	}


	//process file line by line
	string line;
	string processedLine;
	while(!inputFile.eof()){
		getline(inputFile, line);
		processedLine = extractFromLine(line, colArrSize, colArray);
		outputFile << processedLine; // write to output file
		line.clear();//empty line to clean up for next run
	}

	//cleanup files and terminal
	inputFile.close();
	outputFile.close();
	cout << endl;
	return 0;
}


/*
	sourceLine = the line to be sorted
	seriesSize = the number of columns to extract
	posSeries = the array of ints collected from the user. Represents the actual positions to extract.
*/
string extractFromLine(string sourceLine, int seriesSize, int posSeries[]){
	string outPutString = "";
	//perform extraction on line
	int position = 0;
	for(int linePos = 0; linePos < sourceLine.size(); linePos++){
		if(sourceLine[linePos] == ',') {
			position++;
		}else{
			for (int colToExtract = 0; colToExtract < seriesSize; colToExtract++) {
				//if this position matches a position to extract
				if(position == posSeries[colToExtract]){
					//print the current line character
					outPutString += sourceLine[linePos];
					//if we're about to change position, add delimiter. This will leave a comma at the end!
					if(sourceLine[linePos + 1] == ',') outPutString += delimiter;
				}
			}
		}
	}
	// return the string but with last comma replace with newline char
	return outPutString.substr(0, (outPutString.length() - 1)) + "\n";
}
