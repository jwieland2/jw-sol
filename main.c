#include <stdlib.h>     //exit()
#include <stdio.h>
#include <signal.h>     //signal()
#include <locale.h>
#include "sol.h"
#include "DEV_Config.h"
//#include "EPD_4in2.h"

void Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:exit\r\n");
    DEV_Module_Exit();

    exit(0);
}


/*
    1. openweathermap.org onecall abfragen mit curl
    2. bewoelkung daten aus json extrahieren mit json-parser
    3. ePaper panel refresh
*/
int main(void)
{
    // Exception handling:ctrl + c
    signal(SIGINT, Handler);

    if(DEV_Module_Init()!=0){
        return -1;
    }
    
    struct DataChunk CallReturn; // Rohdaten von openweathermap
    struct CloudsData Clouds; // Daten die angezeigt werden sollen

    setlocale(LC_ALL, "de_DE.UTF-8");

    CallReturn = callOpenWeatherMap();

    Clouds = parseJson(CallReturn);

    refreshPanel(Clouds);

    // cleanup
    free(CallReturn.data);
    
    return 0;
}
