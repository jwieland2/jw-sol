# jw-sol
![LastCommit](https://img.shields.io/github/last-commit/jwieland2/jw-sol))
![Badge](https://img.shields.io/badge/made%20by-jwieland2-blue.svg)
![Photo](https://raw.githubusercontent.com/jwieland2/jw-sol/main/photo2.jpg)
1. Fetch weather data in json format from [https://www.openweathermap.org](openweathermap.org) One Call API using curl
* One Call API is free to use with 1000 calls / day.
* For regular use, please consider registering and replacing my token.
* Hourly forecast for 48 hours, daily forecast for 7 days.
2. Extract percentage of cloud cover for the next week using json-parser
* Hourly data is averaged over morning (7:00-10:00), noon (11:00-14:00) and afternoon (15:00-18:00)
3. Display results on a waveshare e-Paper Display (400x300 px)
* For further information, check the [Waveshare wiki](https://www.waveshare.com/wiki/Main_Page)