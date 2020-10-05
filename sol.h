#ifndef _SOL_H_
#define _SOL_H_

//#include "DEV_Config.h"
//#include "GUI_Paint.h"
//#include "GUI_BMPfile.h"
//#include "Debug.h"
#include <stdlib.h> // malloc() free()

struct DataChunk
{
	char* data;
	size_t size;
};

// enthaelt die anzuzeigenden Daten: 3 Tage morgens/mittags/abends und Tageswerte fuer eine Woche
struct CloudsData
{
	int daily[7];
	int average[3][3];
};

struct DataChunk callOpenWeatherMap(void);
struct CloudsData parseJson(struct DataChunk oneCall);
void refreshPanel(struct CloudsData Clouds);


#endif
