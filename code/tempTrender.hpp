#ifndef TEMPTRENDER_H
#define TEMPTRENDER_H

#include <string.h>
#include "read.hpp"
#include "averages.hpp"

//using namespace std;

class tempTrender{
	private:
	float data[100][366];
	int numberOfYears;
	int startYear;
	char* filename;
	float discTresh;
	float discFlag;
	float averageTemperatureEachYear[100];
	float averageTemperatureDeviation[100];
	float averageTemperatureValue;
	//measures to discard are assigned with the temperature=discFlag.
	//for filtering: if(temperature<discTresh){discard}
	
	public:
	tempTrender(char* filePath)
	{
		filename = filePath;
		startYear=0;
		discTresh = -274.0;
		discFlag = -275.0;
		for(int i=0;i<100;i++)
		{
			for(int j=0;j<366;j++)
			{
				data[i][j]=0.0;
			}
		}
	
		readData(filename, data, numberOfYears, startYear, discFlag);
		
		averageTemperature(data, numberOfYears, discTresh, averageTemperatureEachYear);
		averageTemperatureValue = averageValue(averageTemperatureEachYear, numberOfYears);
		deviation(averageTemperatureEachYear, numberOfYears, averageTemperatureValue, averageTemperatureDeviation);
	}; //Construct using the specified file
	~tempTrender() {} //Destructor
	
	//void tempOnDay(int monthToCalculate, int dayToCalculate); //Make a histogram of the temperature on this day
	//void tempOnDay(int dateToCalculate); //Make a histogram of the temperature on this date
	//void tempPerDay(); //Make a histogram of the average temperature of each day of the year
	//void hotCold(); //Make a histogram of the hottest and coldest day of the year
	//void tempPerYear(int yearToExtrapolate); //Make a histogram of average temperature per year, then fit and extrapolate to the given year
	float getDiscTresh(){return discTresh;}
	float getDiscFlag(){return discFlag;}
	float getAverageTemperature()
	{
		return averageTemperatureValue;
	}
	int getStarYear()
	{
		return startYear;
	}
	int getNumberOfYears()
	{
		return numberOfYears;
	}
	void getAverageTemperatureEachYear(float array[])
	{
		for(int i; i<numberOfYears;i++)
		{
			array[i]=averageTemperatureEachYear[i];
		}
		return;
	}
	void getAverageTemperatureDeviation(float array[])
	{
		for(int i; i<numberOfYears;i++)
		{
			array[i]=averageTemperatureDeviation[i];
		}
		return;
	}
};

class Uppsala : public tempTrender{
	private:
	float data[300][366];
	int numberOfYears;
	int startYear;
	char* filename;
	float discTresh;
	float discFlag;
	float averageTemperatureEachYear[300];
	float averageTemperatureDeviation[300];
	float averageTemperatureValue;
	public:
	Uppsala(char* filePath):tempTrender(filePath)
	{
		filename = filePath;
		startYear=0;
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
