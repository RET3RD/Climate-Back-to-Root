void averageTemperature(double temperature[][366], int numberOfYears, double treshold, double averageTemperatureArray[])
{
	int daysConsidered=366;
	for(int year=0;year<numberOfYears;year++)
	{
		averageTemperatureArray[year] = 0;
		for(int day=0;day<366;day++)
		{
			if(temperature[year][day]<-200)
			{
				daysConsidered--;
				continue;
			}			
			averageTemperatureArray[year]+=temperature[year][day];
		}
		if(daysConsidered==0)
		{
			averageTemperatureArray[year]=-275;
		}
		else
		{
			averageTemperatureArray[year]/=daysConsidered;
		}
	}
	return;
}

double averageValue(double array[], int effectiveLength)
{
	double average=0;
	int n=effectiveLength;
	for(int i=0;i<effectiveLength;i++)
	{
		if(array[i]<-274)
		{
			n--;
		}
		else
		{
			average+=array[i];
		}
	}
	average/=n;
	return average;
}

float overallAverageValue( float array[], int effArrSpan )
{
	float average=0;
	int n=effArrSpan;
	for(int i=0; i<effArrSpan; i++)
	{
		if(array[i]<-274)
		{
			n--;
		}
		else
		{
			average+=array[i];
		}
	}
	average/=n;
	return average;
}

void deviation(double array[], int effectiveLength, double average, double deviationArray[])
{
	for(int i=0;i<effectiveLength;i++)
	{
		deviationArray[i]=array[i]-average;
	}
	return;
}
