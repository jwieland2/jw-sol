#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sol.h"
#include "json.h"

struct CloudsData parseJson(struct DataChunk oneCall)
{
	struct CloudsData Clouds;
	json_char* json;
	json_value* value;

	json = (json_char*)oneCall.data;
	value = json_parse(json, (int)oneCall.size);

	if (value == NULL)
	{
		fprintf(stderr, "Unable to parse data\n");
		return Clouds;
	}

    int i;
    int hourlyTimestamp[48];
    int hourlyClouds[48];
	

	// Stundenwerte mit "ungueltig" -1 füllen
	for (int j = 0; j < 3; j++)
		for (int k = 0; k < 3; k++)
			Clouds.average[j][k] = -1;

	// nicht elegant aber was solls - bewoelkung wird direkt ueber die position ausgelesen
	// 1. value: 5 ist hourly data, 6 ist daily data
	// 2. value: Zeit iterator (1 Tag oder 1 Stunde)
	// 3. value: 0 ist timestamp (unix), bewoelkung ist [7 in hourly data] und [11 in daily data]

						// 5hourly                iterator            0dt 7clouds
	//value->u.object.values[5].value -> u.array.values[0] -> u.object.values[0].value->u.integer;	// hourly, 0, dt

						// 6daily                  iterator            0dt 11clouds
	//value->u.object.values[6].value -> u.array.values[0] -> u.object.values[0].value->u.integer;	// daily, 0, dt

	for (i = 0; i < 48; i++)
	{
		hourlyTimestamp[i] = value->u.object.values[5].value->u.array.values[i]->u.object.values[0].value->u.integer;
		hourlyClouds[i] = value->u.object.values[5].value->u.array.values[i]->u.object.values[7].value->u.integer;
		printf("%d\n", hourlyClouds[i]);
}

	for (i = 0; i < 7; i++)
	{
		//dailyTimestamp[i] = value->u.object.values[6].value->u.array.values[i]->u.object.values[0].value->u.integer;
		//dailyClouds[i] = value->u.object.values[6].value->u.array.values[i]->u.object.values[11].value->u.integer;
		Clouds.daily[i] = value->u.object.values[6].value->u.array.values[i]->u.object.values[11].value->u.integer;
	}

	json_value_free(value);
	
	// Durchschnitt fuer morgens/mittags/abends bilden
    	time_t rawtime = hourlyTimestamp[0];
    	struct tm* ts = localtime(&rawtime);
	int curDay = ts->tm_yday;
	int hourlyIndex = 0;
	int datapoints = 0;
	double average = 0;
	int timeOfDay; // 0: nacht, 1:morgens, 2:mittags, 3:abends

	for (hourlyIndex = 0; hourlyIndex < 48; hourlyIndex++)
	{
		rawtime = hourlyTimestamp[hourlyIndex];
		ts = localtime(&rawtime);
		

		// Tageszeit einordnen
		if (ts->tm_hour >= 7 && ts->tm_hour <= 10)
			timeOfDay = 1;
		else if (ts->tm_hour >= 11 && ts->tm_hour <= 14)
			timeOfDay = 2;
		else if (ts->tm_hour >= 15 && ts->tm_hour <= 18)
			timeOfDay = 3;
		else
			timeOfDay = 0;

		// Werte aufsummieren
		if (timeOfDay != 0)
		{
			average += hourlyClouds[hourlyIndex];
			datapoints++;
		}

		// auswerten zu letzter Stunde eines Tagesabschnitts oder am Schluss
		if (ts->tm_hour == 10 || ts->tm_hour == 14 || ts->tm_hour == 18 || hourlyIndex == 47)
		{
			if (datapoints > 0)
				average = average / datapoints;

			switch (timeOfDay)
			{
			case 1:
				Clouds.average[0][ts->tm_yday - curDay] = average;
				break;
			case 2:
				Clouds.average[1][ts->tm_yday - curDay] = average;
				break;
			case 3:
				Clouds.average[2][ts->tm_yday - curDay] = average;
				break;
			}

			average = 0;
			datapoints = 0;
		}
	}
			
	return Clouds;
}
