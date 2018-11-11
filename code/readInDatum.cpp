#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> //for atoi() and atof()
#include <stdio.h>
#include <string.h>

using namespace std;
/*
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
*/
//#include "dataTree.h"

int main()
{
	ifstream readFile("testData.dat");
	
	// First I read until I come to the line that starts with Datum
	/*
	string extrSnippet;
	while( !readFile.eof() )
	{
		getline(readFile, extrSnippet, ';'); //getline(charArray[], int buffsize) extracts to charArray till either more than buffsize chars are extracted or \n is encountered
		cout<<"new String: "<<extrSnippet<<endl;
		if (extrSnippet.find("Datum") != std::string::npos)
		{
			cout<<"Datum found"<<endl;
			break;
		}
	}
	*/
	
	char extrSnippet[250];
	char* nullOrNot=NULL;
	while( !readFile.eof() )
	//for(int i=0; i<10;i++)
	{
		readFile.getline(extrSnippet, 250,';');
		nullOrNot=strstr(extrSnippet,"Datum"); //gives the pointer where it found the string "Datum". returns NULL pointer if nothing found
		if(nullOrNot) //if nullOrNot is not a NULL pointer
		{
			cout<<"Datum found"<<endl;
			break;
		}
		cout<<"String: "<<extrSnippet<<endl;
	}
	
}
