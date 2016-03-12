#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

char delimiter = ',';

string extractFromLine(string sourceLine, int seriesSize, int posSeries[]);

int main(){
	string name; int colArrSize = 0;

	//user interface
	cout << "What data are you extracting? (oneWord): ";
	cin >> name;
	name = name + ".txt";
	cout << "How many columns?: ";
	cin >> colArrSize;
	int colArray[colArrSize];
	string data[colArrSize];
	cout << "Enter each position number \n(starting from 0) \nfollowed by the enter key: \n";
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
	while(!inputFile.eof()){
		getline(inputFile, line);
		string processedLine;
		processedLine = extractFromLine(line, colArrSize, colArray);
		outputFile << processedLine;
		line.clear();
	}

	inputFile.close();
	outputFile.close();
	cout << endl;
}





string extractFromLine(string sourceLine, int seriesSize, int posSeries[]){
	string outPutString = "";
	//perform extraction on line
	int position = 0;
	for(int linePos = 0; linePos < sourceLine.size(); linePos++){
		if(sourceLine[linePos] == ',') {
			position++;
		}
		else{
			for (int colToExtract = 0; colToExtract < seriesSize; colToExtract++) {
				//if this position matches a position to extract
				if(position == posSeries[colToExtract]){
					//print the current line character
					outPutString += sourceLine[linePos];
					//if we're about to change position, add delimiter
					if(sourceLine[linePos + 1] == ',') outPutString += delimiter;
				}
			}
		}
	}
	// int test = ;
	// cout << outPutString[outPutString.length() - 1];
	// outPutString.replace((outPutString.length() - 1), 1, "\n");
	// outPutString[outPutString.length() - 1] = "\n";

	// cout << outPutString.substr(0, (outPutString.length() - 1)) << endl;
	// // replace the last comma with a newline
	// outPutString += "\n";
	return outPutString.substr(0, (outPutString.length() - 1)) + "\n";
}

/*

eg3. $GPRMC,220516,A,5133.82,N,00042.24,W,173.8,231.8,130694,004.2,W*70
			 1    2    3    4    5     6    7    8      9     10  11 12

	 1   220516     Time Stamp
	 2   A          validity - A-ok, V-invalid
	 3   5133.82    current Latitude
	 4   N          North/South
	 5   00042.24   current Longitude
	 6   W          East/West
	 7   173.8      Speed in knots
	 8   231.8      True course
	 9   130694     Date Stamp
	 10  004.2      Variation
	 11  W          East/West
	 12  *70        checksum



	 In this sketch, we call GPS.read() within a once-a-millisecond timer (this is the same timer that runs the millis() command). Then in the main loop we can ask if a new chunk of data has been received by calling GPS.newNMEAreceived(), if this returns true then we can ask the library to parse that data with GPS.parse(GPS.lastNMEA()).

	We do have to keep querying and parsing in the main loop - its not possible to do this in an interrupt because then we'd be dropping GPS data by accident.
	Once data is parsed, we can just ask for data from the library like GPS.day, GPS.month and GPS.year for the current date. GPS.fix will be 1 if there is a fix, 0 if there is none. If we have a fix then we can ask for GPS.latitude, GPS.longitude, GPS.speed (in knots, not mph or k/hr!), GPS.angle, GPS.altitude (in centimeters) and GPS.satellites (number of satellites)

*/
