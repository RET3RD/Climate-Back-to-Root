#ifndef TEMPTRENDER_H
#define TEMPTRENDER_H

#include <string.h>
#include "read.hpp"
#include "averages.hpp"
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <TGraph.h>
#include <TMath.h>
#include <algorithm>

//using namespace std;

class tempTrender{
	private:
	double data[100][366];
	double averageTemperatureEachYear[100];
	double averageTemperatureDeviation[100];
	
	protected:	
	int numberOfYears;
	int startYear;
	double averageTemperatureValue;
	double latitude;
	char* filename;
	double discFlag= -274.0;//for filtering: if(temperature<discTresh){discard}
	double discTresh = -275.0;//measures to discard are assigned with the temperature=discFlag.
	
	
	
	public:
	tempTrender(char* filePath)
	{
		filename = filePath;
		startYear=0;
		for(int i=0;i<100;i++)
		{
			for(int j=0;j<366;j++)
			{
				data[i][j]=0.0;
			}
		}
	
		readData(filename, data, numberOfYears, startYear, discFlag);
		latitude = readLatitude(filename);
		
		averageTemperature(data, numberOfYears, discTresh, averageTemperatureEachYear);
		averageTemperatureValue = averageValue(averageTemperatureEachYear, numberOfYears);
		deviation(averageTemperatureEachYear, numberOfYears, averageTemperatureValue, averageTemperatureDeviation);
	}; //Construct using the specified file
	~tempTrender() {} //Destructor
	
	
	double getDiscTresh(){return discTresh;}
	double getDiscFlag(){return discFlag;}
	double getAverageTemperature() { return averageTemperatureValue; }
	double getLatitude() { return latitude; }
	int getStartYear() { return startYear; }
	int getNumberOfYears() { return numberOfYears; }
	void getAverageTemperatureEachYear(double array[])
	{
		for(int i=0; i<numberOfYears;i++)
		{
			array[i]=averageTemperatureEachYear[i];
		}
		return;
	}
	void getAverageTemperatureDeviation(double array[])
	{
		for(int i=0; i<numberOfYears;i++)
		{
			array[i]=averageTemperatureDeviation[i];
		}
		return;
	}

	void hotCold()
	{
		int hottest[numberOfYears]; int coldest[numberOfYears];
		
		for(int yearIndex=0;yearIndex<numberOfYears;yearIndex++)
		{
			hottest[yearIndex]=findHot(data, yearIndex);
			coldest[yearIndex]=findCold(data,yearIndex);
			//OBS: after this point, we will use Jan01 = 1 (not 0 anymore)
		}
		
		plotHotCold(hottest, coldest, numberOfYears);
		
	}


	int findHot(double degs[][366],int yearIndex)
	{
		return 1+distance(&degs[yearIndex][0] , max_element( &degs[yearIndex][0], &degs[yearIndex][365] ));
		//distance(&firstAddress, &secondAddress) gives the distance between these addresses 
		//and max_element(&first_address,&second_address) gives the address of the highest value in the range,
		//so combined, they measure the distance from first array element to that of highest value
	}

	int findCold(double degs[][366], int yearIndex)
	{
		int coldestTillNow=0; //intermediate variable that saves the coldest day that was there till a certain times of iterations
		for(int dayIndex=1; dayIndex<366; dayIndex++)
		{
			if(degs[yearIndex][dayIndex]<discTresh) continue; //discard day right away
			if(degs[yearIndex][dayIndex]<degs[yearIndex][coldestTillNow]) coldestTillNow=dayIndex;
		}
		return (coldestTillNow++);
	}

	void plotHotCold( int hottest[], int coldest[], int numberOfYears )
	{
	TH1I* meanTempHistHot = new TH1I("hottest days", "frequentness of hottest days;number of day in year;counts", 366, 1, 367);
	TH1I* meanTempHistCold= new TH1I("coldest days", "frequentness of coldest days;number of day in year;counts", 366, 1, 367);
	TH1I* meanTempHistColdShift=new TH1I("coldest days", "frequentness of coldest days;number of day in year;counts", 366, 1+180, 367+180);
	TCanvas* hotColdCanv = new TCanvas("hottest-coldest", "frequency of hottest and coldest days", 1280, 720);
	hotColdCanv->SetGrid();
	for(int yearIndex=0; yearIndex<numberOfYears; yearIndex++)
	{
		meanTempHistHot->Fill(hottest[yearIndex]);
		meanTempHistCold->Fill(coldest[yearIndex]);
		
		if(coldest[yearIndex]<181) meanTempHistColdShift->Fill(coldest[yearIndex]+366);
		else meanTempHistColdShift->Fill(coldest[yearIndex]);
	}
	meanTempHistHot->SetFillColor(2); meanTempHistCold->SetFillColor(4);
	meanTempHistHot->Draw("BL"); meanTempHistCold->Draw("BC SAME");
	TF1* fitHot = new TF1("fitHot", "gaus",90,270);
	meanTempHistHot->Fit("fitHot","QR+","C");
	TF1 *funHot = meanTempHistHot->GetFunction("fitHot");
	funHot->SetLineColor(1); funHot->SetLineStyle(2); funHot->SetLineWidth(5);
	
	meanTempHistColdShift->Fit("gaus","Q0","");
	TF1* funCold = meanTempHistColdShift->GetFunction("gaus");
	TF1* funColdLeft = new TF1("fitColdLeft", "gaus",1,101);
	TF1* funColdRight= new TF1("fitColdRight","gaus",267,367);
	funColdLeft->SetParameters( funCold->GetParameter(0),funCold->GetParameter(1)-366,funCold->GetParameter(2) );
	funColdRight->SetParameters(funCold->GetParameter(0),funCold->GetParameter(1),funCold->GetParameter(2) );
	funColdLeft->SetLineColor(8); funColdLeft->SetLineStyle(9); funColdLeft->SetLineWidth(5);
	funColdRight->SetLineColor(8);funColdRight->SetLineStyle(9); funColdRight->SetLineWidth(5);
	funColdLeft->Draw("SAME"); funColdRight->Draw("SAME");
	}

};

class Uppsala : public tempTrender{
	private:
	double data[300][366];
	double averageTemperatureEachYear[300];
	double averageTemperatureDeviation[300];
	public:
	Uppsala(char* filePath):tempTrender(filePath)
	{
		filename = filePath;
		discTresh = -274.0;
		discFlag = -275.0;
		for(int i=0;i<300;i++)
		{
			for(int j=0;j<366;j++)
			{
				data[i][j]=0.0;
			}
		}
	
		readUppsala(filename, data, numberOfYears, startYear,discFlag);
		averageTemperature(data, numberOfYears, discTresh, averageTemperatureEachYear);
		averageTemperatureValue = averageValue(averageTemperatureEachYear, numberOfYears);
		deviation(averageTemperatureEachYear, numberOfYears, averageTemperatureValue, averageTemperatureDeviation);
	}; //Construct using the specified file
	
	
};
#endif
