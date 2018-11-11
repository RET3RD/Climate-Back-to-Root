#include <iostream>
#include <fstream>
#include <string>


void readInTemp(string station, float& degMatrix[][366])
{
	ifstream timeDegFile;
	timeDegFile.open(station+".csv"); // open input file
	
	int dummyInt; float dummyFloat; //dummy vars to dump unnecessary data form the file
	int currDay; int currYear; //year and day considered at the current point of the while loop
	float currTemp; //avg temp considered at current while loop pos. The actual thing we are interested in.
	int currCity; //city code: 1 for recordings of Uppsala, !=1 for other cities
	int lastYear; //stores the year of the previous run through the while loop; used to determine when there is a new year
	int yearIndex=0; int dayIndex=0; //used to fill the tempMatrix[yearIndex][dayIndex] accordingly
	
	int yearCount; int dayCount;
	
	while( timeDegFile >> currYear >> dummyInt >> currDay >> currTemp >> dummyFloat >> currCity )
	{ //the structure will stay uniform like this through the whole document
		if(currCity!=1) //if there is not a 1 at the end, the recording does not come from Uppsala and should be discarded
		{
			currTemp=getDiscFlag(); //flags currTemp to remove it later
		}
		degMatrix[yearIndex][dayIndex]=currTemp; //actual temperature assignment done
		//Now check if the year changed
		if(lastYear=!currYear)
		{
			if(dayIndex==364) //meaning it is not a leap year
			{
				degMatrix[currYear][365]=getDiscFlag(); //flag so the missing last point will also be kicked out at analysis
			}
			dayIndex=-1; //reset to -1 since it will be incremented to 0 at end of loop
			yearIndex++;
		}
		lastYear=currYear;
		dayIndex++;
		
	}
	
	
	
	
	return;
}



vector< float[366] > degYVector; //one element is a vector of all days

for (int i = 0; i < 10; i++) {
    vector<int> row; // Create an empty row
    for (int j = 0; j < 20; j++) {
        row.push_back(i * j); // Add an element (column) to the row
    }
    vec.push_back(row); // Add the row to the main vector
}

