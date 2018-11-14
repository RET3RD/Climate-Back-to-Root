To properly run the program, you first need to specify the absolute path of the directory that you downloaded the folder into. The chage has to be made at lines 20-37.
To analyse a specific weather station, you need to replace the object names at line 48, 52 and 54. The objects are created at lines 20-37 with the names seen there.
So, for instance, if you want to run the program for the Falsterbo station, change the lines 48, 52 and 54 from "boras." to "falsterbo.".
If you want to calculate and plot the yearly deviation of the overall average temperature, you have to replace "getAverageTemperatureEachYear" with "getAverageTemperatureDeviation" in line 56.
To make a plot of the hottest and coldest days for each year, you have to call the hotCold() function of one of the objects, for instance lund.hotCold().

The program can then be executed by loading it into ROOT and then running project() in the ROOT command line.
