#ifndef GENERALINFO_CPP
#define GENERALINFO_CPP
#include "GeneralInfo.h"
#include "Parse.h"
#include <curl/curl.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <ctime>
#include <json-c/json.h>



//Time series functions
void GeneralInfo::setValuesTS(std::string symbol, std::string intervalLength){
    CURL *hnd = curl_easy_init();

    std::string URL = "https://api.twelvedata.com/time_series?symbol=" + symbol + "&interval=" + intervalLength + "&outputsize=1&apikey=41a5696d75774b8eb6929a1dc1af50d6";
    std::string readBuffer; // String to store the response data
    if (hnd) {
        //std::string readBuffer; // String to store the response data
        curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(hnd, CURLOPT_URL, URL.c_str());
        curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, Parse::WriteCallBack); // Use the member function of Parse class
        curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &readBuffer); // Pass the instance of Parse class
        CURLcode ret = curl_easy_perform(hnd); // Perform the CURL request
        if (ret == CURLE_OK) {
            Parse::WriteToJSON(readBuffer); // Call WriteToJSON to process and save the data
        }
        curl_easy_cleanup(hnd); // Clean up CURL
    }

    //open file
    std::ifstream file("response.json");
    try{
        if(!file.is_open()){
            throw std::runtime_error("json file failed to open for vector parsing");
        }
    }
    catch(const std::runtime_error& e){
        std::cerr << e.what() <<std::endl;
    }
 
        // Assuming 'readBuffer' contains the JSON data as a string
        struct json_object *parsed_json = json_tokener_parse(readBuffer.c_str());
        struct json_object *values;
        
        // Get the 'values' array from the parsed JSON
        json_object_object_get_ex(parsed_json, "values", &values);

        size_t n_values = json_object_array_length(values);
        for (size_t i = 0; i < n_values; i++) {
            // Get the json object at the current index in the array
            struct json_object *value = json_object_array_get_idx(values, i);

            // Extract individual data from the object
            struct json_object *datetime, *open, *high, *low, *close, *volume;
            json_object_object_get_ex(value, "datetime", &datetime);
            json_object_object_get_ex(value, "open", &open);
            json_object_object_get_ex(value, "high", &high);
            json_object_object_get_ex(value, "low", &low);
            json_object_object_get_ex(value, "close", &close);
            json_object_object_get_ex(value, "volume", &volume);

            // Push back the values into the vector in the specified order
            valuesTS.push_back(json_object_get_string(datetime));
            valuesTS.push_back(json_object_get_string(open));
            valuesTS.push_back(json_object_get_string(high));
            valuesTS.push_back(json_object_get_string(low));
            valuesTS.push_back(json_object_get_string(close));
            valuesTS.push_back(json_object_get_string(volume));
        }

        // Cleanup JSON object
        json_object_put(parsed_json);

}
void GeneralInfo::setValuesTS(std::string symbol, std::string intervalLength, std::string intervalAmount){
   CURL *hnd = curl_easy_init();

    std::string URL = "https://api.twelvedata.com/time_series?symbol=" + symbol + "&interval=" + intervalLength + "&outputsize=" + intervalAmount + "&apikey=41a5696d75774b8eb6929a1dc1af50d6";
    std::string readBuffer; // String to store the response data
    if (hnd) {
        //std::string readBuffer; // String to store the response data
        curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(hnd, CURLOPT_URL, URL.c_str());
        curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, Parse::WriteCallBack); // Use the member function of Parse class
        curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &readBuffer); // Pass the instance of Parse class
        CURLcode ret = curl_easy_perform(hnd); // Perform the CURL request
        if (ret == CURLE_OK) {
            Parse::WriteToJSON(readBuffer); // Call WriteToJSON to process and save the data
        }
        curl_easy_cleanup(hnd); // Clean up CURL
    }

    std::ifstream file("response.json");
    try{
        if(!file.is_open()){
            //std::cerr << "json file failed to open for vector parsing";
            throw std::runtime_error("json file failed to open for vector parsing");
        }
    }
    catch(const std::runtime_error& e){
        std::cerr << e.what() <<std::endl;
    }
 
    // Assuming 'readBuffer' contains the JSON data as a string
    struct json_object *parsed_json = json_tokener_parse(readBuffer.c_str());
    struct json_object *values;
    
    // Get the 'values' array from the parsed JSON
    json_object_object_get_ex(parsed_json, "values", &values);

    size_t n_values = json_object_array_length(values);
    for (size_t i = 0; i < n_values; i++) {
        // Get the json object at the current index in the array
        struct json_object *value = json_object_array_get_idx(values, i);

        // Extract individual data from the object
        struct json_object *datetime, *open, *high, *low, *close, *volume;
        json_object_object_get_ex(value, "datetime", &datetime);
        json_object_object_get_ex(value, "open", &open);
        json_object_object_get_ex(value, "high", &high);
        json_object_object_get_ex(value, "low", &low);
        json_object_object_get_ex(value, "close", &close);
        json_object_object_get_ex(value, "volume", &volume);

        // Push back the values into the vector in the specified order
        valuesTS.push_back(json_object_get_string(datetime));
        valuesTS.push_back(json_object_get_string(open));
        valuesTS.push_back(json_object_get_string(high));
        valuesTS.push_back(json_object_get_string(low));
        valuesTS.push_back(json_object_get_string(close));
        valuesTS.push_back(json_object_get_string(volume));
    }
    // Cleanup JSON object
    json_object_put(parsed_json);
}

//Exchagne rate functions
void GeneralInfo::setValuesER(std::string symbol1, std::string symbol2, std::string dateTimeString){
   CURL *hnd = curl_easy_init();

    std::string URL = "https://api.twelvedata.com/exchange_rate?symbol=" + symbol1 + "/" + symbol2 + "&date=" + dateTimeString + "&apikey=41a5696d75774b8eb6929a1dc1af50d6";
    std::string readBuffer; // String to store the response data
    if (hnd) {
        //std::string readBuffer; // String to store the response data
        curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(hnd, CURLOPT_URL, URL.c_str());
        curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, Parse::WriteCallBack); // Use the member function of Parse class
        curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &readBuffer); // Pass the instance of Parse class
        CURLcode ret = curl_easy_perform(hnd); // Perform the CURL request
        if (ret == CURLE_OK) {
            Parse::WriteToJSON(readBuffer); // Call WriteToJSON to process and save the data
        }
        curl_easy_cleanup(hnd); // Clean up CURL
    }

    FILE *fp = fopen("response.json", "r");


  // Assuming 'readBuffer' contains the JSON data as a string
    struct json_object *parsed_json = json_object_from_file("response.json"); //ADD EXCEPTION FOR IF NOT PARSED
    if (!fp) {
            throw std::runtime_error("Failed to open response.json for parsing");
    }

    struct json_object *symbol, *rate, *timestamp;

    json_object_object_get_ex(parsed_json,"symbol", &symbol);
    json_object_object_get_ex(parsed_json, "rate", &rate);
    json_object_object_get_ex(parsed_json, "timestamp", &timestamp);
   
    valuesER.push_back(json_object_get_string(symbol));
    valuesER.push_back(json_object_get_string(rate));
    valuesER.push_back(json_object_get_string(timestamp));

    // Cleanup JSON object
    json_object_put(parsed_json);
    fclose(fp);

}
void GeneralInfo::setValuesER(std::string symbol1, std::string symbol2){}

//Currency exchange functions
void GeneralInfo::setValuesCC(std::string symbool1, std::string symbol2, double amount){}
void GeneralInfo::setValuesCC(std::string symbol1, std::string symbol2, double amount, std::string dateTimeString){}



//Time series single interval getters
int GeneralInfo::getOpenTS(){}
int GeneralInfo::getHighTS(){}
int GeneralInfo::getLowTS(){}
int GeneralInfo::getCloseTS(){}
int GeneralInfo::getVolumeTS(){}
//Time series all intervals getters
std::vector<std::string> GeneralInfo::getTimeStampTS(){}
std::vector<double> GeneralInfo::getAllHighTS(){}
std::vector<double> GeneralInfo::getAllLowTS(){}
std::vector<double> GeneralInfo::getAllCloseTS(){}
std::vector<double> GeneralInfo::getAllVolumeTS(){}

//Exchange rate getters
double GeneralInfo::getStockExchangeRateER(){}
std::string GeneralInfo::getTimeStampER(int seconds){}

//Currency conversion getters
double GeneralInfo::getCurrencyExchangeRateCC(){}
double GeneralInfo::getCurrencyExchangeAmountCC(){}
std::string getTimeStampCC(int seconds){}

//Real time price getter
double GeneralInfo::getRealTimePriceRTP(std::string symbol){}

//HELPER FUNCTIONS
bool GeneralInfo::ValidateDateTime(const std::string& dateTimeString){}
std::string GeneralInfo::ConvertFromUnixTime(std::string unixTime){
    std::time_t result = std::stol(unixTime);
    std::tm *ptm = std::localtime(&result);

    char buffer[32];
    std::strftime(buffer, 32, "%Y-%m-%d %H:%M:%S", ptm);

    return std::string(buffer);

}

#endif 