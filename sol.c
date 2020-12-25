//#include "sol.h"
//#include "EPD_4in2.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <curl/curl.h>
//#include "json.h"
//
//static void print_depth_shift(int depth)
//{
//    int j;
//    for (j=0; j < depth; j++) {
//	printf(" ");
//    }
//}
//
//static void process_value(json_value* value, int depth, int dt[], int clouds[], int arraySize);
///*
//// todo: implement extract functions
//static int extract_clouds_from_object(json_value* value)
//{
//    int length, x;
//    if (value == NULL) {
//	return;
//    }
//    length = value->u.object.length;
//    for (x = 0; x < length; x++) {
//	if (strcmp(value->u.object.values[x].name, "clouds") == 0)
//	    return u.object.values[x].value.integer;
//    
//    return -1;
//}
//
//static int extract_clouds_from_array(json_value* value, int array_index)
//{
//    return extract_clouds_from_object(value->u.object.values[array_index]);
//}*/
//
//static void process_object(json_value* value, int depth, int dt[], int clouds[], int arraySize)
//{
//    int length, x;
//    if (value == NULL) {
//	return;
//    }
//    length = value->u.object.length;
//    printf("object with length %d\n", length);
//    for (x = 0; x < length; x++) {
//
//	if (strcmp(value->u.object.values[x].name, "hourly") == 0 ||
//	    strcmp(value->u.object.values[x].name, "daily") == 0)
//	{
//	    print_depth_shift(depth);
//	    process_value(value->u.object.values[x].value, depth+1, dt, clouds, arraySize);
//	}
//	else if (strcmp(value->u.object.values[x].name, "dt") == 0 ||
//	    strcmp(value->u.object.values[x].name, "clouds") == 0)
//	{
//	    printf("object[%d].name = %s\n", x, value->u.object.values[x].name);
//	    printf("object[%d].value = %lld\n", x, value->u.object.values[x].value->u.integer);
//	}
//    }
//}
//
//static void process_array(json_value* value, int depth, int dt[], int clouds[], int arraySize)
//{
//    int length, x;
//    if (value == NULL) {
//	return;
//    }
//    length = value->u.array.length;
//    printf("array with length %d\n", length);
//    for (x = 0; x < length; x++) {
//	process_value(value->u.array.values[x], depth, dt, clouds, arraySize);
//    }
//}
//
//static void process_value(json_value* value, int depth, int dt[], int clouds[], int arraySize)
//{
//    int j;
//    if (value == NULL) {
//	return;
//    }
//    if (value->type != json_object) {
//	print_depth_shift(depth);
//    }
//    switch(value->type) {
//	case json_none:
//	printf("none\n");
//	break;
//	case json_object:
//	process_object(value, depth+1, dt, clouds, arraySize);
//	break;
//	case json_array:
//	process_array(value, depth+1, dt, clouds, arraySize);
//	break;
//	case json_integer:
//	printf("int: %10" PRId64 "\n", value->u.integer);
//	break;
//	case json_double:
//	printf("double: %f\n", value->u.dbl);
//	break;
//	case json_string:
//	printf("string: %s\n", value->u.string.ptr);
//	break;
//	case json_boolean:
//	printf("bool: %d\n", value->u.boolean);
//	break;
//    }
//}
//
//struct MemoryStruct
//{
//    char* memory;
//    size_t size;
//};
//
//
//// * Save the data from received from the server into a Buffer struct.
//// * @see https://curl.haxx.se/libcurl/c/CURLOPT_WRITEDATA.html for the function signature.
//
//static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *pointer)
//{
//    size_t realsize = size * nmemb;
//
//    // Cast the received pointer to the Buffer structured data.
//    struct MemoryStruct *mem = (struct MemoryStruct *) pointer;
//
//    // Reallocate the memory for the Buffer char pointer
//    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
//    
//
//    if (mem->memory == NULL) {
//        printf("Failed to allocate memory for the http get data");
//        return 0;
//    }
//
//    // Copy the fetched data to the Buffer char pointer
//    memcpy(&(mem->memory[mem->size]), contents, realsize);
//    mem->size += realsize;
//    mem->memory[mem->size] = 0;
//    
//    return realsize;
//};
//
//int refreshPanel(void)
//{
//    printf("drawtest Demo\r\n");
//    if(DEV_Module_Init()!=0){
//        return -1;
//    }
//    
//    int i;
//    int dailyTimestamp[7], hourlyTimestamp[48];
//    int dailyClouds[7], hourlyClouds[48];
//    
//    
//    json_char* json;
//    json_value* value;
//    
//    if (res != CURLE_OK)
//    {
//	    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
//    }
//    else
//    {
//	    printf("%lu bytes retrieved\n", (long)chunk.size);
//	
//	    json = (json_char*)chunk.memory;
//	    value = json_parse(json, (int)chunk.size);
//	
//	    if (value == NULL)
//	    {
//	        fprintf(stderr, "Unable to parse data\n");
//	        free(chunk.memory);
//	        exit(1);
//	    }
//	
//	//process_value(value, 0, dailyTimestamp, dailyClouds, 50);
//	
//			      // 5houly                iterator            0dt 6clouds
//	//value->u.object.values[5].value->u.array.values[0]->u.object.values[0].value->u.integer;	// hourly, 0, dt
//	
//			    // 6daily                  iterator            0dt 11clouds
//	//value->u.object.values[6].value->u.array.values[0]->u.object.values[0].value->u.integer;	// daily, 0, dt
//	
//	
//	    for (i = 0; i < 48; i++)
//	    {
//	        hourlyTimestamp[i] = value->u.object.values[5].value->u.array.values[i]->u.object.values[0].value->u.integer;
//	        hourlyClouds[i] = value->u.object.values[5].value->u.array.values[i]->u.object.values[6].value->u.integer;
//	    }
//	
//	    for (i = 0; i < 7; i++)
//	    {
//	        dailyTimestamp[i] = value->u.object.values[6].value->u.array.values[i]->u.object.values[0].value->u.integer;
//	        dailyClouds[i] = value->u.object.values[6].value->u.array.values[i]->u.object.values[11].value->u.integer;
//	    }
//	
//	
//	
//	    json_value_free(value);
//    }
//    curl_easy_cleanup(curl_handle);
//    free(chunk.memory);
//    curl_global_cleanup();
//    /*
//    for (i = 0; i < 48; i++)
//    {
//	printf("%d\tdt: %d\tclouds: %d\n", i, hourlyTimestamp[i], hourlyClouds[i]);
//    }
//    
//    for (i = 0; i < 7; i++)
//    {
//	printf("%d\tdt: %d\tclouds: %d\n", i, dailyTimestamp[i], dailyClouds[i]);
//    }*/
//    
//    
//    // calc chunks
//    time_t rawtime;
//    struct tm *ts;
//    char readable[10];
//    
//    int curHour, curDay;
//    int avgClouds[3][3];
//    
//    
//    rawtime = hourlyTimestamp[0];
//    ts = localtime(&rawtime);
//    
//    curHour = ts->tm_hour;
//    curDay = ts->tm_yday;
//    
//    if (curDay >= 363)
//	return;
//    
//    if (curHour < 7)	// kein übermorgen
//    {
//	avgClouds[0][2] = -1;
//	avgClouds[1][2] = -1;
//	avgClouds[2][2] = -1;
//    }
//    else if (curHour > 10) // kein heute, morgens
//    {
//	avgClouds[0][0] = -1;
//	if (curHour > 14)	//kein heute, mittags
//	{
//	    avgClouds[1][0] = -1;
//	}
//    }
//    
//    int hourlyIndex = 0;
//    int datapoints = 0;
//    double average = 0;
//    for (hourlyIndex = 0; hourlyIndex < 48; hourlyIndex++)
//    {
//	rawtime = hourlyTimestamp[hourlyIndex];
//	ts = localtime(&rawtime);
//	
//	if ((ts->tm_hour >= 7 && ts->tm_hour <= 10)
//	    || (ts->tm_hour >= 11 && ts->tm_hour <= 14)
//	    || (ts->tm_hour >= 15 && ts->tm_hour <= 18))
//	{
//	    average += hourlyClouds[hourlyIndex];
//	    datapoints++;
//	}
//    
//	if (ts->tm_hour == 10 || ts->tm_hour == 14 || ts->tm_hour == 18 || hourlyIndex == 47)
//	{
//	    average = average / datapoints;
//	    switch(ts->tm_hour)
//	    {
//		case 7:
//		case 8:
//		case 9:
//		case 10:
//		avgClouds[0][ts->tm_yday - curDay] = average;
//		break;
//		
//		case 11:
//		case 12:
//		case 13:
//		case 14:
//		avgClouds[1][ts->tm_yday - curDay] = average;
//		break;
//		
//		case 15:
//		case 16:
//		case 17:
//		case 18:
//		avgClouds[2][ts->tm_yday - curDay] = average;
//		break;
//	    }
//	    average = 0;
//	    datapoints = 0;
//	}
//    }
//    
//
//    printf("e-Paper Init and Clear...\r\n");
//    EPD_4IN2_Init();
//    EPD_4IN2_Clear();
//    DEV_Delay_ms(500);
//
//    
//    //Create a new image cache
//    UBYTE *Image;
//    // you have to edit the startup_stm32fxxx.s file and set a big enough heap size
//    UWORD Imagesize = ((EPD_4IN2_WIDTH % 8 == 0)? (EPD_4IN2_WIDTH / 8 ): (EPD_4IN2_WIDTH / 8 + 1)) * EPD_4IN2_HEIGHT;	// normal
//    
//    //EPD_4IN2_Init_4Gray();
//    //UWORD Imagesize = ((EPD_4IN2_WIDTH % 8 == 0)? (EPD_4IN2_WIDTH / 4 ): (EPD_4IN2_WIDTH / 4 + 1)) * EPD_4IN2_HEscaIGHT;	// gray
//    
//    
//    if((Image = (UBYTE *)malloc(Imagesize)) == NULL) {
//        printf("Failed to apply for black memory...\r\n");
//        return -1;
//    }
//    Paint_NewImage(Image, EPD_4IN2_WIDTH, EPD_4IN2_HEIGHT, 0, WHITE);
//    //Paint_SetScale(4);
//    Paint_Clear(WHITE);
//
//    printf("draw vertical\n");
//    Paint_DrawLine(100, 1, 100, 299, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
//    Paint_DrawLine(200, 1, 200, 299, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
//    Paint_DrawLine(300, 1, 300, 299, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
//    
//    printf("draw horizontal\n");
//    Paint_DrawLine(1, 75, 400, 75, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
//    Paint_DrawLine(1, 150, 400, 150, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
//    Paint_DrawLine(2, 225, 398, 225, BLACK, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
//    
//    printf("draw string\n");
//    Paint_DrawString_EN(10, 10, "Heute", &Font16, WHITE, BLACK);
//    rawtime = hourlyTimestamp[0];
//    ts = localtime(&rawtime);
//    strftime(readable, sizeof(readable), "%a", ts);
//    Paint_DrawString_EN(10, 40, readable, &Font16, WHITE, BLACK);
//    
//    rawtime = hourlyTimestamp[0] + 86400;
//    ts = localtime(&rawtime);
//    strftime(readable, sizeof(readable), "%a", ts);
//    Paint_DrawString_EN(10, 85, "Morgen", &Font16, WHITE, BLACK);
//    Paint_DrawString_EN(10, 115, readable, &Font16, WHITE, BLACK);
//    
//    rawtime = hourlyTimestamp[0] + 86400*2;
//    ts = localtime(&rawtime);
//    strftime(readable, sizeof(readable), "%a", ts);
//    Paint_DrawString_EN(10, 160, "2 Tage", &Font16, WHITE, BLACK);
//    Paint_DrawString_EN(10, 190, readable, &Font16, WHITE, BLACK);
//    
//    rawtime = hourlyTimestamp[0] + 86400*3;
//    ts = localtime(&rawtime);
//    strftime(readable, sizeof(readable), "%a", ts);
//    Paint_DrawString_EN(10, 235, readable, &Font16, WHITE, BLACK);
//    //Paint_DrawString_EN(10, 115, readable, &Font16, WHITE, BLACK);
//    
//    rawtime = hourlyTimestamp[0] + 86400*4;
//    ts = localtime(&rawtime);
//    strftime(readable, sizeof(readable), "%a", ts);
//    //Paint_DrawString_EN(10, 85, "Morgen", &Font16, WHITE, BLACK);
//    Paint_DrawString_EN(110, 235, readable, &Font16, WHITE, BLACK);
//    
//    rawtime = hourlyTimestamp[0] + 86400*5;
//    ts = localtime(&rawtime);
//    strftime(readable, sizeof(readable), "%a", ts);
//    //Paint_DrawString_EN(10, 85, "Morgen", &Font16, WHITE, BLACK);
//    Paint_DrawString_EN(210, 235, readable, &Font16, WHITE, BLACK);
//    
//    rawtime = hourlyTimestamp[0] + 86400*6;
//    ts = localtime(&rawtime);
//    strftime(readable, sizeof(readable), "%a", ts);
//    //Paint_DrawString_EN(10, 85, "Morgen", &Font16, WHITE, BLACK);
//    Paint_DrawString_EN(310, 235, readable, &Font16, WHITE, BLACK);
//    
//    int j, k;
//    int spacingX = 100;
//    int spacingY = 75;
//    
//    for (j = 0; j < 3; j++)
//    {
//	for (k = 0; k < 3; k++)
//	{
//	    Paint_DrawNum(30 + spacingX * (j+1), 30 + spacingY * k, avgClouds[j][k], &Font24, BLACK, WHITE);
//	    printf("[%d][%d]\t%d\n", j, k, avgClouds[j][k]);
//	}
//    }
//    
//    for (i = 0; i < 4; i++)
//    {
//	if (dailyClouds[3+i] == 0)
//	    Paint_DrawString_EN(30 + i*100, 255, "0", &Font24, WHITE, BLACK);
//	else
//	    Paint_DrawNum(30 + i*100, 255, dailyClouds[3+i], &Font24, BLACK, WHITE);
//    }
//
//    /*
//    Paint_DrawPoint(10, 80, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
//    Paint_DrawPoint(10, 90, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
//    Paint_DrawPoint(10, 100, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
//    Paint_DrawLine(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
//    Paint_DrawLine(70, 70, 20, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
//    Paint_DrawRectangle(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
//    Paint_DrawRectangle(80, 70, 130, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
//    Paint_DrawCircle(45, 95, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
//    Paint_DrawCircle(105, 95, 20, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
//    Paint_DrawLine(85, 95, 125, 95, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
//    Paint_DrawLine(105, 75, 105, 115, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
//    Paint_DrawString_EN(10, 0, "waveshare", &Font16, BLACK, WHITE);
//    Paint_DrawString_EN(10, 20, "hello world", &Font12, WHITE, BLACK);
//    Paint_DrawNum(10, 33, 123456789, &Font12, BLACK, WHITE);
//    Paint_DrawNum(10, 50, 987654321, &Font16, WHITE, BLACK);
//    Paint_DrawString_CN(140, 0, "ÄãºÃabc", &Font12CN, GRAY1, GRAY4);
//    Paint_DrawString_CN(140, 40, "ÄãºÃabc", &Font12CN, GRAY2, GRAY3);
//    Paint_DrawString_CN(140, 80, "ÄãºÃabc", &Font12CN, GRAY3, GRAY2);
//    Paint_DrawString_CN(140, 120, "ÄãºÃabc", &Font12CN, GRAY4, GRAY1);
//	
//    Paint_DrawString_CN(220, 0, "Î¢Ñ©µç×Ó", &Font24CN, GRAY1, GRAY4);
//    Paint_DrawString_CN(220, 40, "Î¢Ñ©µç×Ó", &Font24CN, GRAY2, GRAY3);
//    Paint_DrawString_CN(220, 80, "Î¢Ñ©µç×Ó", &Font24CN, GRAY3, GRAY2);
//    Paint_DrawString_CN(220, 120, "Î¢Ñ©µç×Ó", &Font24CN, GRAY4, GRAY1);
//    */
//    
//    EPD_4IN2_Display(Image);
//    //EPD_4IN2_4GrayDisplay(Image);
//	
//    DEV_Delay_ms(2000);
//	
//	
//    printf("Goto Sleep...\r\n");
//    EPD_4IN2_Sleep();
//    free(Image);
//    Image = NULL;
//	
//    // close 5V
//    printf("close 5V, Module enters 0 power consumption ...\r\n");
//    DEV_Module_Exit();
//    
//    return 0;
//}
//
