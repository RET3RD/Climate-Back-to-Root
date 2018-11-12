#include "tempTrender.hpp"
#include <string>
#include <iostream>

#include <TF1.h> 
#include <TH1.h> 
#include <TGraph.h> 
#include <TStyle.h> 
#include <TMath.h> 
#include <TFrame.h> 
#include <TCanvas.h>

using namespace std;

void sortArray(double array[], int arraySize);


void project()
{ //it may be necessary to change the paths because relative paths seem to not work
	string path="/home/courseuser/root/datasets/Boras.csv";
	tempTrender boras(strdup(path.c_str()));
	path="/home/courseuser/root/datasets/Falsterbo.csv";
	tempTrender falsterbo(strdup(path.c_str()));
	path="/home/courseuser/root/datasets/Falun.csv";
	tempTrender falun(strdup(path.c_str()));
	path="/home/courseuser/root/datasets/Karlstad.csv";
	tempTrender karlstad(strdup(path.c_str()));
	path="/home/courseuser/root/datasets/Lulea.csv";
	tempTrender lulea(strdup(path.c_str()));
	path="/home/courseuser/root/datasets/Lund.csv";
	tempTrender lund(strdup(path.c_str()));
	path="/home/courseuser/root/datasets/Soderarm.csv";
	tempTrender soderarm(strdup(path.c_str()));
	path="/home/courseuser/root/datasets/Umea.csv";
	tempTrender umea(strdup(path.c_str()));	
	path="/home/courseuser/root/datasets/Visby.csv";
	tempTrender visby(strdup(path.c_str()));
	
	
		
	int yearsConsidered=100;
	double year[100];
	double avgTemperature[100];
	
	
	//section about determining the mean temperature over the observation time
	//in order to switch to another weather station, the following three lines marked with // must be interchanged from boras to the desired other weather station. 
	yearsConsidered=boras.getNumberOfYears(); //
	
	
	int i=0;
	for(i=0;i<yearsConsidered;i++)
	{
		year[i]=double(boras.getStartYear()+i); //
	}
	boras.getAverageTemperatureEachYear(avgTemperature); //
	
	for(i=0;i<yearsConsidered;)
	{
		if(avgTemperature[i]<-274.) //
		{
			yearsConsidered--;
			for(int j=i;j<yearsConsidered;j++)
			{
				year[j]=year[j+1];
				avgTemperature[j]=avgTemperature[j+1];
			}
		}
		else i++;
	}
	
	TCanvas *avgTemp = new TCanvas("avgTemp","Yearly average temperature",200,10,1280,720);
    avgTemp->SetFillColor(42);
    avgTemp->SetGrid();
	avgTemp->Update();
	avgTemp->GetFrame()->SetFillColor(21);
	avgTemp->GetFrame()->SetBorderSize(12);
	
    TGraph* avgTempPlot = new TGraph(yearsConsidered,year,avgTemperature);
	avgTempPlot->SetLineColor(2);
	avgTempPlot->SetLineWidth(3);
	avgTempPlot->SetMarkerColor(4);
	avgTempPlot->SetMarkerStyle(21);
	avgTempPlot->SetTitle("Average temperature");
	avgTempPlot->GetXaxis()->SetTitle("year");
	avgTempPlot->GetYaxis()->SetTitle("average temperature, deg. C");
	avgTempPlot->Draw("ACP");

	
	
	
	int arrSize=8;
	double averageTemperatureValues[8] = {boras.getAverageTemperature(), falsterbo.getAverageTemperature(), karlstad.getAverageTemperature(), lulea.getAverageTemperature(), lund.getAverageTemperature(), soderarm.getAverageTemperature(), umea.getAverageTemperature(), visby.getAverageTemperature()};
	double latitudes[8] = {boras.getLatitude(), falsterbo.getLatitude(), karlstad.getLatitude(), lulea.getLatitude(), lund.getLatitude(), soderarm.getLatitude(), umea.getLatitude(), visby.getLatitude()};
	sortArray(latitudes,arrSize);

	
	TCanvas* latCanv  = new TCanvas("latCanv", "latitude of measure vs. avg temp",200,10, 1280,720); latCanv->cd();
	latCanv->SetFillColor(42);
    latCanv->SetGrid();
	latCanv->Update();
	latCanv->GetFrame()->SetFillColor(21);
	latCanv->GetFrame()->SetBorderSize(12);
	
	TGraph* tempVsLat = new TGraph(arrSize,latitudes, averageTemperatureValues);
	tempVsLat->SetLineColor(2);
	tempVsLat->SetLineWidth(3);
	tempVsLat->SetMarkerColor(4);
	tempVsLat->SetMarkerStyle(21);
	tempVsLat->SetTitle("Average temperature");
	tempVsLat->GetXaxis()->SetTitle("deg. of latitude");
	tempVsLat->GetYaxis()->SetTitle("average temperature, deg. C");
	tempVsLat->Draw("ACP");
	
}



void sortArray(double array[], int arraySize)
{
	double tempVar; int i; int j;
	for(i=0;i<arraySize;i++)
	{
		for(j=0;j<arraySize-i-1;j++)
		{
			if(array[j]>array[j+1])
			{
				tempVar=array[j];
				array[j]=array[j+1];
				array[j+1]=tempVar;
			}
		}
	}
}
