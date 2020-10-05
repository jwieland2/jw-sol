#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sol.h"
#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "GUI_BMPfile.h"
#include "EPD_4in2.h"

void refreshPanel(struct CloudsData Clouds)
{
    char out[10];
    time_t now;
    time_t rawtime;
    struct tm* ts;

    time(&now);

    printf("e-Paper Init and Clear...\r\n");
    EPD_4IN2_Init();
    EPD_4IN2_Clear();
    DEV_Delay_ms(500);

    //Create a new image cache
    UBYTE* Image;
    // you have to edit the startup_stm32fxxx.s file and set a big enough heap size
    UWORD Imagesize = ((EPD_4IN2_WIDTH % 8 == 0) ? (EPD_4IN2_WIDTH / 8) : (EPD_4IN2_WIDTH / 8 + 1)) * EPD_4IN2_HEIGHT;	// normal

    //EPD_4IN2_Init_4Gray();
    //UWORD Imagesize = ((EPD_4IN2_WIDTH % 8 == 0)? (EPD_4IN2_WIDTH / 4 ): (EPD_4IN2_WIDTH / 4 + 1)) * EPD_4IN2_HEscaIGHT;	// gray


    if ((Image = (UBYTE*)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        return;
    }
    Paint_NewImage(Image, EPD_4IN2_WIDTH, EPD_4IN2_HEIGHT, 0, WHITE);
    //Paint_SetScale(4);
    Paint_Clear(WHITE);

    // Gitter zeichnen
    printf("draw vertical\n");
    Paint_DrawLine(100, 1, 100, 299, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(200, 1, 200, 299, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(300, 1, 300, 299, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

    printf("draw horizontal\n");
    Paint_DrawLine(1, 75, 400, 75, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(1, 150, 400, 150, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(2, 225, 398, 225, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

    // Beschriftungen - Wochentage
    printf("draw string\n");
    Paint_DrawString_EN(10, 10, "Heute", &Font16, WHITE, BLACK);
    rawtime = now;
    ts = localtime(&rawtime);
    strftime(out, sizeof(out), "%a", ts);
    Paint_DrawString_EN(10, 40, out, &Font16, WHITE, BLACK);

    rawtime = now + 86400;   // 86400s = 1d
    ts = localtime(&rawtime);
    strftime(out, sizeof(out), "%a", ts);
    Paint_DrawString_EN(10, 85, "Morgen", &Font16, WHITE, BLACK);
    Paint_DrawString_EN(10, 115, out, &Font16, WHITE, BLACK);

    rawtime = now + 86400 * 2;
    ts = localtime(&rawtime);
    strftime(out, sizeof(out), "%a", ts);
    Paint_DrawString_EN(10, 160, "2 Tage", &Font16, WHITE, BLACK);
    Paint_DrawString_EN(10, 190, out, &Font16, WHITE, BLACK);

    rawtime = now + 86400 * 3;
    ts = localtime(&rawtime);
    strftime(out, sizeof(out), "%a", ts);
    Paint_DrawString_EN(10, 235, out, &Font16, WHITE, BLACK);
    //Paint_DrawString_EN(10, 115, out, &Font16, WHITE, BLACK);

    rawtime = now + 86400 * 4;
    ts = localtime(&rawtime);
    strftime(out, sizeof(out), "%a", ts);
    //Paint_DrawString_EN(10, 85, "Morgen", &Font16, WHITE, BLACK);
    Paint_DrawString_EN(110, 235, out, &Font16, WHITE, BLACK);

    rawtime = now + 86400 * 5;
    ts = localtime(&rawtime);
    strftime(out, sizeof(out), "%a", ts);
    //Paint_DrawString_EN(10, 85, "Morgen", &Font16, WHITE, BLACK);
    Paint_DrawString_EN(210, 235, out, &Font16, WHITE, BLACK);

    rawtime = now + 86400 * 6;
    ts = localtime(&rawtime);
    strftime(out, sizeof(out), "%a", ts);
    //Paint_DrawString_EN(10, 85, "Morgen", &Font16, WHITE, BLACK);
    Paint_DrawString_EN(310, 235, out, &Font16, WHITE, BLACK);

    // Werte eintragen - Tageszeiten
    int i, j, k;
    int spacingX = 100;
    int spacingY = 75;
    for (j = 0; j < 3; j++)
    {
        for (k = 0; k < 3; k++)
        {
            if (Clouds.average[j][k] == 0)
                Paint_DrawString_EN(30 + spacingX * (j + 1), 30 + spacingY * k, "0", &Font24, WHITE, BLACK);
            else if (Clouds.average[j][k] == -1)
                Paint_DrawString_EN(30 + spacingX * (j + 1), 30 + spacingY * k, "X", &Font24, WHITE, BLACK);
            else
                Paint_DrawNum(30 + spacingX * (j + 1), 30 + spacingY * k, Clouds.average[j][k], &Font24, BLACK, WHITE);

            printf("[%d][%d]\t%d\n", j, k, Clouds.average[j][k]);
        }
    }

    // Werte eintragen - Tage
    for (i = 0; i < 4; i++)
    {
        if (Clouds.daily[3 + i] == 0)
            Paint_DrawString_EN(30 + i * 100, 255, "0", &Font24, WHITE, BLACK);
        else
            Paint_DrawNum(30 + i * 100, 255, Clouds.daily[3 + i], &Font24, BLACK, WHITE);
    }

    EPD_4IN2_Display(Image);
    //EPD_4IN2_4GrayDisplay(Image);

    DEV_Delay_ms(2000);

    printf("Goto Sleep...\r\n");
    EPD_4IN2_Sleep();
    //free(Image);
    //Image = NULL;

    // close 5V
    printf("close 5V, Module enters 0 power consumption ...\r\n");
    DEV_Module_Exit();

    return;
}
