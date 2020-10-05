#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "sol.h"

// * Save the data from received from the server into a Buffer struct.
// * @see https://curl.haxx.se/libcurl/c/CURLOPT_WRITEDATA.html for the function signature.
static size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* pointer)
{
    size_t realsize = size * nmemb;

    // Cast the received pointer to the Buffer structured data.
    struct DataChunk* mem = (struct DataChunk*)pointer;

    // Reallocate the memory for the Buffer char pointer
    mem->data = realloc(mem->data, mem->size + realsize + 1);


    if (mem->data == NULL) {
        printf("Failed to allocate memory for the http get data");
        return 0;
    }

    // Copy the fetched data to the Buffer char pointer
    memcpy(&(mem->data[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->data[mem->size] = 0;

    return realsize;
};

// Abfrage der onecall API von openWeatherMap. Return-json als DataChunk struct (char* + size_t)
struct DataChunk callOpenWeatherMap(void)
{
	CURL* curl_handle;
	CURLcode res;

	struct DataChunk chunk;

	chunk.data = malloc(1);
	chunk.size = 0;

	curl_global_init(CURL_GLOBAL_ALL);
	curl_handle = curl_easy_init();
	//curl_easy_setopt(hnd, CURLOPT_BUFFERSIZE, 102400L);
	curl_easy_setopt(curl_handle, CURLOPT_URL, "http://api.openweathermap.org/data/2.5/onecall?appid=ccbea7f2a8d813c921fa8d4a75bf633f&units=metric&lat=47.87&lon=11.15&exclude=minutely");
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)&chunk);
	curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
	res = curl_easy_perform(curl_handle);

	if (res != CURLE_OK)
	{
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		curl_easy_cleanup(curl_handle);
		curl_global_cleanup();
		return chunk;
	}
	else
	{
		printf("%lu bytes retrieved\n", (long)chunk.size);
		curl_easy_cleanup(curl_handle);
		curl_global_cleanup();
		return chunk;
	}
}
