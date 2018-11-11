#include "randDegGen.cpp"
#include <fstream>
#include <iostream>
#include <TCanvas.h>
#include <TH1.h>
#include <TMath.h>

//void findHotCold(float[][366],int);
int findCold(float (&degs)[][], int yearIndex);


void hotCold()
{
	int totYears=300;
	float degMatr[totYears][366];
	randDegGen(degMatr,totYears); //will be replaced by function filling the matrix with the actual data
	int hottest[totYears]; int coldest[totYears];
	
	for(int yearIndex=0;yearIndex<totYears;yearIndex++)
	{
		//findHotCold(DegMatr, yearIndex);
		*(hottest+yearIndex)=1+distance(&degMatr[yearIndex][0] , max_element( &degMatr[yearIndex][0], &degMatr[yearIndex][365] ));
		coldest[yearIndex]=findCold(degMatr, yearIndex);
		
		cout<<"Coldest day of year "<<yearIndex<<": "<<coldest[yearIndex]<<endl;
	}
		
	
	//TODO: Modify findHotCold() so that it stores the days in hottest[] and coldest[]
	
	TH1I* histHottest=new TH1I("", "Counts of the hottest and coldest days of the year; DayNumber; Counts", 366, 1, 366);
	//TH1I* histColdest=new TH1I("hPhi", "ROOT func generated v2 distribution; x; Counts", 366, 1, 366);
	
	for(int yearIndex=0;yearIndex<totYears;yearIndex++)
	{
		histHottest->Fill(hottest[yearIndex]);
		//histColdest->Fill(coldest[yearIndex]);
	}
	TCanvas* hotColdCanv = new TCanvas("HotColdDays", "Frequency of hottest and coldest days of the year", 900, 600);
	histHottest->Draw();//histColdest->Draw();
	
}


int findCold(float (&degs)[][], int yearIndex)
{
	int coldestTillNow=0;
	for(int dayIndex=1; dayIndex<366; dayIndex++)
	{
		if(degs[yearIndex][dayIndex]<-274) continue; //discard day right away
		if(degs[yearIndex][dayIndex]<degs[yearIndex][dayIndex-1]) coldestTillNow=dayIndex;
	}
	return (coldestTillNow++);
}



/*
void findHotCold(float degMatr[][366],int yearIndex)
{
	int currHottest;
	currHottest=1+distance(max_element( &degMatr[yearIndex][0], &degMatr[yearIndex][365] ),&degMatr[yearIndex][0]);
	//(hottest+yearIndex)=currHottest;
	cout<<"Hottest day of year "<<yearIndex<<": "<<currHottest<<endl;
}
*/


/*
void increaseAgeByRef(int &Age){Age++; cout << "Adress by Ref: "<< &Age<<endl;}
increaseAgeByRef(myAge);
void increaseAgeByPtr(int* AgePtr){(*AgePtr)++; cout << "Adress by pointer: "<<AgePtr<<endl;}
increaseAgeByPtr(&Age);

*/
