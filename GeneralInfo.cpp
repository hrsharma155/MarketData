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



//MAKE THE VECTORS POINTERS 
GeneralInfo::GeneralInfo() {
    // Allocate memory for the vectors on the heap
    valuesTS = new std::vector<std::string>(); 
    valuesER = new std::vector<std::string>();
    valuesCC = new std::vector<std::string>();

}

GeneralInfo::~GeneralInfo() {
    // Free the allocated memory
    delete valuesTS; 
    delete valuesER;
    delete valuesCC;
}



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

            GeneralInfo();

            // Push back the values into the vector in the specified order
            valuesTS->push_back(json_object_get_string(datetime));
            valuesTS->push_back(json_object_get_string(open));
            valuesTS->push_back(json_object_get_string(high));
            valuesTS->push_back(json_object_get_string(low));
            valuesTS->push_back(json_object_get_string(close));
            valuesTS->push_back(json_object_get_string(volume));
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

        GeneralInfo();
        // Push back the values into the vector in the specified order
        valuesTS->push_back(json_object_get_string(datetime));
        valuesTS->push_back(json_object_get_string(open));
        valuesTS->push_back(json_object_get_string(high));
        valuesTS->push_back(json_object_get_string(low));
        valuesTS->push_back(json_object_get_string(close));
        valuesTS->push_back(json_object_get_string(volume));
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
    
    std::string timestampStr = std::to_string(json_object_get_int64(timestamp));
    std::string formattedTime = ConvertFromUnixTime(timestampStr);
   
    GeneralInfo();

    valuesER->push_back(json_object_get_string(symbol));
    valuesER->push_back(json_object_get_string(rate));
    valuesER->push_back(formattedTime);

    // Cleanup JSON object
    json_object_put(parsed_json);
    fclose(fp);

}
void GeneralInfo::setValuesER(std::string symbol1, std::string symbol2){
    CURL *hnd = curl_easy_init();

    std::string URL = "https://api.twelvedata.com/exchange_rate?symbol=" + symbol1 + "/" + symbol2 + "&apikey=41a5696d75774b8eb6929a1dc1af50d6";
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

    std::string timestampStr = std::to_string(json_object_get_int64(timestamp));
    std::string formattedTime = ConvertFromUnixTime(timestampStr);

    GeneralInfo();
   
    valuesER->push_back(json_object_get_string(symbol));
    valuesER->push_back(json_object_get_string(rate));
    valuesER->push_back(formattedTime);

    // Cleanup JSON object
    json_object_put(parsed_json);
    fclose(fp);




}

//Currency exchange functions
void GeneralInfo::setValuesCC(std::string symbol1, std::string symbol2, std::string amount){
    CURL *hnd = curl_easy_init();
   

    std::string URL = "https://api.twelvedata.com/currency_conversion?symbol=" + symbol1 + "/" + symbol2 + "&amount=" + amount + "&apikey=41a5696d75774b8eb6929a1dc1af50d6";
    std::string readBuffer; // String to store the response data
    if (hnd) {
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

    struct json_object *symbol, *rate, *timestamp, *amount1;

    json_object_object_get_ex(parsed_json,"symbol", &symbol);
    json_object_object_get_ex(parsed_json, "rate", &rate);
    json_object_object_get_ex(parsed_json, "amount", &amount1);
    json_object_object_get_ex(parsed_json, "timestamp", &timestamp);
    //convert to correct time format 
    std::string timestampStr = std::to_string(json_object_get_int64(timestamp));
    std::string formattedTime = ConvertFromUnixTime(timestampStr);
   

    GeneralInfo();

    valuesCC->push_back(json_object_get_string(symbol));
    valuesCC->push_back(json_object_get_string(rate));
    valuesCC->push_back(json_object_get_string(amount1));
    valuesCC->push_back(formattedTime);

    // Cleanup JSON object
    json_object_put(parsed_json);
    fclose(fp);


}
void GeneralInfo::setValuesCC(std::string symbol1, std::string symbol2, std::string amount, std::string dateTimeString){

    CURL *hnd = curl_easy_init();
   

    std::string URL = "https://api.twelvedata.com/currency_conversion?symbol=" + symbol1 + "/" + symbol2 + "&amount=" + amount + "&date=" + dateTimeString + "&apikey=41a5696d75774b8eb6929a1dc1af50d6";
    std::string readBuffer; // String to store the response data
    if (hnd) {
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

    struct json_object *symbol, *rate, *timestamp, *amount1;

    json_object_object_get_ex(parsed_json,"symbol", &symbol);
    json_object_object_get_ex(parsed_json, "rate", &rate);
    json_object_object_get_ex(parsed_json, "amount", &amount1);
    json_object_object_get_ex(parsed_json, "timestamp", &timestamp);
    //convert to correct time format 
    std::string timestampStr = std::to_string(json_object_get_int64(timestamp));
    std::string formattedTime = ConvertFromUnixTime(timestampStr);
    
    GeneralInfo();
    valuesCC->push_back(json_object_get_string(symbol));
    valuesCC->push_back(json_object_get_string(rate));
    valuesCC->push_back(json_object_get_string(amount1));
    valuesCC->push_back(formattedTime);

    // Cleanup JSON object
    json_object_put(parsed_json);
    fclose(fp);
}

//Time series single interval getters
std::string GeneralInfo::getOpenTS(){
    return valuesTS->at(1);
}
std::string GeneralInfo::getHighTS(){
    return valuesTS->at(2);
}
std::string GeneralInfo::getLowTS(){
    return valuesTS->at(3);
}
std::string GeneralInfo::getCloseTS(){
    return valuesTS->at(4);
}
std::string GeneralInfo::getVolumeTS(){
    return valuesTS->at(5);
}
//Time series all intervals getters
std::vector<std::string> GeneralInfo::getAllTimeStampTS(){
    //vector to return holding all the high values
    std::vector<std::string> temp;

    int intervalAm = (valuesTS->size() / 6);
    int index = 0;
    //use equation: val + 6(interval).... for timestamp, val = 0
    for(int i = 0; i < intervalAm; i++){
        index = 0 + 6*(i);
        temp.push_back(valuesTS->at(index));
    }

    return temp;

}
std::vector<std::string> GeneralInfo::getAllHighTS(){
    //vector to return holding all the high values
    std::vector<std::string> temp;

    int intervalAm = (valuesTS->size() / 6);
    int index = 0;
    //use equation: val + 6(interval).... for high, val = 2
    for(int i = 0; i < intervalAm; i++){
        index = 2 + 6*(i);
        temp.push_back(valuesTS->at(index));
    }

    return temp;

}
std::vector<std::string> GeneralInfo::getAllLowTS(){
    //vector to return holding all the high values
    std::vector<std::string> temp;

    int intervalAm = (valuesTS->size() / 6);
    int index = 0;
    //use equation: val + 6(interval).... for low, val = 3
    for(int i = 0; i < intervalAm; i++){
        index = 3 + 6*(i);
        temp.push_back(valuesTS->at(index));
    }

    return temp;

}
std::vector<std::string> GeneralInfo::getAllOpenTS(){
    //vector to return holding all the high values
    std::vector<std::string> temp;

    int intervalAm = (valuesTS->size() / 6);
    int index = 0;
    //use equation: val + 6(interval).... for open, val = 1
    for(int i = 0; i < intervalAm; i++){
        index = 1 + 6*(i);
        temp.push_back(valuesTS->at(index));
    }

    return temp;

}
std::vector<std::string> GeneralInfo::getAllCloseTS(){

    //vector to return holding all the high values
    std::vector<std::string> temp;

    int intervalAm = (valuesTS->size() / 6);
    int index = 0;
    //use equation: val + 6(interval).... for close, val = 4
    for(int i = 0; i < intervalAm; i++){
        index = 4 + 6*(i);
        temp.push_back(valuesTS->at(index));
    }

    return temp;
}
std::vector<std::string> GeneralInfo::getAllVolumeTS(){

    //vector to return holding all the high values
    std::vector<std::string> temp;

    int intervalAm = (valuesTS->size() / 6);
    int index = 0;
    //use equation: val + 6(interval).... for volume, val = 5
    for(int i = 0; i < intervalAm; i++){
        index = 5 + 6*(i);
        temp.push_back(valuesTS->at(index));
    }

    return temp;
}

//Exchange rate getters
std::string GeneralInfo::getStockExchangeRateER(){
    return valuesER->at(1);
}
std::string GeneralInfo::getTimeStampER(){
    return valuesER->at(2);
}

//Currency conversion getters
std::string GeneralInfo::getCurrencyExchangeRateCC(){
    return valuesCC->at(1);
}
std::string GeneralInfo::getCurrencyExchangeAmountCC(){
    return valuesCC->at(2);
}
std::string GeneralInfo::getTimeStampCC(){
    return valuesCC->at(3);
}

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