#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> //for atoi() and atof()
#include <stdio.h>

using namespace std;

void readData(char* filename, double dataArray[][366], int& numberOfYears, int& startYear, double discFlag)
{
	ifstream fileIn;
	fileIn.open(filename);
	
	char ch;
	char datum[4];
	string trash;
	
	while(fileIn>>ch)
	{
		if(ch=='D')
		{
			fileIn>>datum[0]>>datum[1]>>datum[2]>>datum[3];
			if(datum[0]=='a'&&datum[1]=='t'&&datum[2]=='u'&&datum[3]=='m')
			{
				getline(fileIn, trash);
				break;
			}
		}
	}
	
	bool startWriting=false, isGood=true;
	int year, year_index=0,day_index=0;
	string date="", new_date;
	double temperature;
	char quality;
	while(fileIn>>year)
	{
		getline(fileIn, new_date, ';');
		if(new_date=="-01-01"&&date=="")
		{
			startWriting=true;
			date=new_date;
			startYear=year;
		}
		if(date=="-12-31"&&new_date=="-01-01")
		{
			for(;day_index<366;day_index++)
			{
				dataArray[year_index][day_index]=discFlag;
			}
			day_index=0;
			year_index++;
		}
		getline(fileIn, trash, ';');
		fileIn>>temperature>>ch>>quality;
		getline(fileIn, trash);
		if(date!=new_date)
		{
			if(isGood)
			{
				dataArray[year_index][day_index]=temperature/3;
			}
			else
			{
				dataArray[year_index][day_index]=discFlag;
			}
			day_index++;
			isGood=true;
			date=new_date;
		}
		if(startWriting)
		{
			dataArray[year_index][day_index]+=temperature;
			if(quality!='G')
			{
				isGood=false;
			}
		}
	}
	numberOfYears=year_index;
	fileIn.close();
	return;
}

void readUppsala(char* filename, double dataArray[][366], int& numberOfYears, int& startYear, double discFlag)
{
	ifstream fileIn;
	fileIn.open(filename);
	
	bool startWriting=false;
	int year,year_index=0,day_index=0,month,day,dataId;
	double temperature, other;
	
	while(fileIn>>year>>month>>day>>temperature>>other>>dataId)
	{
		if(month==1 && day==1 && !startWriting)
		{
			startWriting=true;
			startYear=year;
		}
		if(startWriting)
		{
			if(dataId==1)
			{
				dataArray[year_index][day_index]=temperature;
			}
			else
			{
				dataArray[year_index][day_index]=discFlag;
			}
			day_index++;
			if(month==12&&day==31)
			{
				for(;day_index<366;day_index++)
				{
					dataArray[year_index][day_index]=discFlag;
				}
				day_index=0;
				year_index++;
				numberOfYears=year_index;
			}
		}
	}
	fileIn.close();
	return;
}

double readLatitude(char* filename)
{
	ifstream readFile(filename);
		
	char extrSnippet[250]; //temporary char array with large size to prevent overflow
	char* nullOrNot=NULL; //initialize a test pointer to 0
	while( !readFile.eof() )
	{
		readFile.getline(extrSnippet, 250,';'); //reads everything before ';' into extrSnippet
		nullOrNot=strstr(extrSnippet,"Latitud"); //gives the pointer where it found the string "Latitud". returns NULL pointer if nothing found
		if(nullOrNot) break; //if nullOrNot is not a NULL pointer
	}
	if ( !nullOrNot ) cout<<"Something went wrong retrieving the latitude.";
	readFile.getline(extrSnippet, 250); //effectively to switch to the next line because default delim is \n
	for(int pos=1; pos<5; pos++) //read out at 4th position which corresponds to latitude
	{
		readFile.getline(extrSnippet, 250, ';');
	}
	return atof(extrSnippet);
}
