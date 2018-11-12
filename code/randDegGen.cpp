#include <TF1.h> // 1d function class
#include <TMath.h>	 // math functions
#include <TRandom.h> // random number generator
#include <TGraph.h>
void randDegGen(double randDegArr[][366],int yearSpan)
{
	TF1* sinSqAve = new TF1("Avg Temperature according squared sin"," 15*sin( TMath::Pi()*x/366 )^2 +3",0,366); //so on the mean the highest Temp is 18 and the lowest is 3
	TF1* gaussDev = new TF1("Gaussian Temperature deviation","gaus(0)",-10,10); //range to fetch tempDeviation from (maxDev can not exceed 6deg)
	gaussDev->SetParameters(1/sqrt(2*TMath::Pi()*2),0,2); //normalisation, mean, standard deviation
	//float days[366];
	for(int yearIndex=0;yearIndex<yearSpan;yearIndex++)
	{
		for(int dayIndex=0;dayIndex<366;dayIndex++)
		{
			randDegArr[yearIndex][dayIndex] = sinSqAve->Eval(dayIndex) + gaussDev->GetRandom(); //so in total we have the perfect sin^2-behavior plus a random deviation by 2deg std
			//days[dayIndex]=dayIndex;
		}
	}
	//TGraph *gr = new TGraph(366,days,randDegMatr);
	//gr->Draw("ACP");
}
