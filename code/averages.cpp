void averageTemprature(float temperature[][366], int numberOfYears, float treshold, float averageTemperatureArray[])
{
	int daysConsidered;
	for(int year=0;year<numberOfYears;year++)
	{
		daysConsidered = 366;
		averageTemperatureArray[year] = 0;
		for(int day=0;day<366;day++)
		{
			if(temperature[year][day]<treshold)
			{
				daysConsidered--;
				continue;
			}
			averageTemperatureArray[year]+=temperature[year][day];
		}
		averageTemperatureArray[year]/=daysConsidered;
	}
	return;
}

float averageValue(float array[], int effectiveLength)
{
	float average=0;
	for(int i=0;i<effectiveLength;i++)
	{
		average+=array[i];
	}
	average/=effectiveLength;
	return average;
}

void deviation(float array[], int effectiveLength, float average, float deviationArray[])
{
	for(int i=0;i<effectiveLength;i++)
	{
		deviationArray[i]=array[i]-average;
	}
	return;
}
