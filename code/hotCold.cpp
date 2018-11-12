#include "randDegGen.cpp"
#include "tempTrender.hpp"
#include <fstream>
#include <iostream>
#include <TCanvas.h>
#include <TH1.h>
#include <TMath.h>
#include <algorithm>

int findHot(double degs[][366],int yearIndex);
int findCold(double degs[][366], int yearIndex);
void plotHotCold(int hottestArr[], int coldestArr[], int numberOfYears);


void hotCold()
{
	int numberOfYears=300;
	double degMatr[numberOfYears][366];
	randDegGen(degMatr,numberOfYears);
	//readData(filename, degMatr[][366], numberOfYears, startYear, discFlag)
	int hottest[numberOfYears]; int coldest[numberOfYears];
	
	for(int yearIndex=0;yearIndex<numberOfYears;yearIndex++)
	{
		hottest[yearIndex]=findHot(degMatr, yearIndex);
		coldest[yearIndex]=findCold(degMatr,yearIndex);
		//OBS: after this point, we will use Jan01 = 1 (not 0 anymore)
	}
	
	plotHotCold(hottest, coldest, numberOfYears);
	
}


int findHot(double degs[][366],int yearIndex)
{
	return 1+distance(&degs[yearIndex][0] , max_element( &degs[yearIndex][0], &degs[yearIndex][365] ));
}

int findCold(double degs[][366], int yearIndex)
{
	int coldestTillNow=0;
	for(int dayIndex=1; dayIndex<366; dayIndex++)
	{
		if(degs[yearIndex][dayIndex]<-274) continue; //discard day right away
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
