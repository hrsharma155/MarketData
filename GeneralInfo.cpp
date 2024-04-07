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
//date 0
//open 1
//close 4
//high 2
//low 3
//vol 5


//MAKE THE VECTORS POINTERS 
GeneralInfo::GeneralInfo() {
    // Allocate memory for the vectors on the heap
    valuesTS = new std::vector<StockValues>(); 
    valuesER = new std::vector<ExchangeRateValues>();
    valuesCC = new std::vector<CurrencyConversionValues>();
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

            
            StockValues stockValue;
            stockValue.dateTime = json_object_get_string(datetime);
            stockValue.open = json_object_get_string(open);
            stockValue.high = json_object_get_string(high);
            stockValue.low = json_object_get_string(low);
            stockValue.close = json_object_get_string(close);
            stockValue.volume = json_object_get_string(volume);

            valuesTS->push_back(stockValue);
         
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

        StockValues stockValue;
        stockValue.dateTime = json_object_get_string(datetime);
        stockValue.open = json_object_get_string(open);
        stockValue.high = json_object_get_string(high);
        stockValue.low = json_object_get_string(low);
        stockValue.close = json_object_get_string(close);
        stockValue.volume = json_object_get_string(volume);

        valuesTS->push_back(stockValue);
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
   
    ExchangeRateValues erVal;

    erVal.symbol = json_object_get_string(symbol);
    erVal.rate = json_object_get_string(rate);
    erVal.dateTime = formattedTime;

    valuesER->push_back(erVal);
    
  

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

    ExchangeRateValues erVal;

    erVal.symbol = json_object_get_string(symbol);
    erVal.rate = json_object_get_string(rate);
    erVal.dateTime = formattedTime;

    valuesER->push_back(erVal);

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
   

    CurrencyConversionValues ccValue;

    ccValue.symbol = json_object_get_string(symbol);
    ccValue.rate = json_object_get_string(rate);
    ccValue.amount = json_object_get_string(amount1);
    ccValue.dateTime = formattedTime;

    valuesCC->push_back(ccValue);

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
    
   CurrencyConversionValues ccValue;

    ccValue.symbol = json_object_get_string(symbol);
    ccValue.rate = json_object_get_string(rate);
    ccValue.amount = json_object_get_string(amount1);
    ccValue.dateTime = formattedTime;

    valuesCC->push_back(ccValue);

    // Cleanup JSON object
    json_object_put(parsed_json);
    fclose(fp);
}


std::string GeneralInfo::getOpenTSAt(int interval){
    //given interval, fetch open value at said interval
    //validate interval first w/ valuesTS->size() / 6
    if(interval < 0 || interval >= valuesTS->size()){
        return "GeneralInfo.cpp @ getOpenTSAt: interval passed is invalid. Try again";
    }
    std::string openValue = valuesTS->at(interval).open;
    return openValue;
}
std::string GeneralInfo::getHighTSAt(int interval){
    //given interval, fetch high value at said interval
    //validate interval first w/ valuesTS->size() / 6
    if(interval < 0 || interval >= valuesTS->size()){
        return "GeneralInfo.cpp @ getHighTSAt: interval passed is invalid. Try again";
    }
    std::string highValue = valuesTS->at(interval).high;
    return highValue;
}
std::string GeneralInfo::getLowTSAt(int interval){
    //given interval, fetch low value at said interval
    //validate interval first w/ valuesTS->size() / 6
    if(interval < 0 || interval >= valuesTS->size()){
        return "GeneralInfo.cpp @ getLowTSAt: interval passed is invalid. Try again";
    }
    std::string lowValue = valuesTS->at(interval).low;
    return lowValue;
}
std::string GeneralInfo::getCloseTSAt(int interval){
    //given interval, fetch close value at said interval
    //validate interval first w/ valuesTS->size() / 6
    if(interval < 0 || interval >= valuesTS->size()){
        return "GeneralInfo.cpp @ getCloseTSAt: interval passed is invalid. Try again";
    }
    std::string closeValue = valuesTS->at(interval).close;
    return closeValue;
}
std::string GeneralInfo::getVolumeTSAt(int interval){
    //given interval, fetch vollume value at said interval
    //validate interval first w/ valuesTS->size() / 6
    //Use: Volume = volVal + 6(interval)
    if(interval < 0 || interval >= valuesTS->size()){
        return "GeneralInfo.cpp @ getVolumeTSAt: interval passed is invalid. Try again";
    }
    std::string volumeValue = valuesTS->at(interval).volume; 
    return volumeValue;
}
std::string GeneralInfo::getTimeStampTSAt(int interval){
    //given interval, fetch time value at said interval
    //validate interval first w/ valuesTS->size() / 6
    //Use: Time = timeVal + 6(interval)
    if(interval < 0 || interval >= valuesTS->size()){
        return "GeneralInfo.cpp @ getTimeStampTSAt: interval passed is invalid. Try again";
    }
    std::string dateValue = valuesTS->at(interval).dateTime; 
    return dateValue;
}



//Time series all intervals getters
std::vector<std::string> GeneralInfo::getAllTimeStampTS(){
    //vector to return holding all values of type specified
    std::vector<std::string> temp;
    for (const auto& stockValue : *valuesTS) {
        // Push the value string into the temp vector
        temp.push_back(stockValue.dateTime);
    }
    return temp;
}
std::vector<std::string> GeneralInfo::getAllHighTS(){
    //vector to return holding all values of type specified
    std::vector<std::string> temp;
    for (const auto& stockValue : *valuesTS) {
        // Push the value string into the temp vector
        temp.push_back(stockValue.high);
    }
    return temp;
}
std::vector<std::string> GeneralInfo::getAllLowTS(){
    //vector to return holding all values of type specified
    std::vector<std::string> temp;
    for (const auto& stockValue : *valuesTS) {
        // Push the value string into the temp vector
        temp.push_back(stockValue.low);
    }
    return temp;
}
std::vector<std::string> GeneralInfo::getAllOpenTS(){
    //vector to return holding all values of type specified
    std::vector<std::string> temp;
    for (const auto& stockValue : *valuesTS) {
        // Push the value string into the temp vector
        temp.push_back(stockValue.open);
    }
    return temp;
}
std::vector<std::string> GeneralInfo::getAllCloseTS(){
    //vector to return holding all values of type specified
    std::vector<std::string> temp;
    for (const auto& stockValue : *valuesTS) {
        // Push the value string into the temp vector
        temp.push_back(stockValue.close);
    }
    return temp;
}
std::vector<std::string> GeneralInfo::getAllVolumeTS(){
    //vector to return holding all values of type specified
    std::vector<std::string> temp;
    for (const auto& stockValue : *valuesTS) {
        // Push the value string into the temp vector
        temp.push_back(stockValue.volume);
    }
    return temp;
}
//Exchange rate getters
std::string GeneralInfo::getStockExchangeRateER(){
    return valuesER->at(0).rate;
}
std::string GeneralInfo::getTimeStampER(){
    return valuesER->at(0).dateTime;
}
//Currency conversion getters
std::string GeneralInfo::getCurrencyExchangeRateCC(){
    return valuesCC->at(0).rate;
}
std::string GeneralInfo::getCurrencyExchangeAmountCC(){
    return valuesCC->at(0).amount;
}
std::string GeneralInfo::getTimeStampCC(){
    return valuesCC->at(0).dateTime;
}
//Real time price getter
double GeneralInfo::getRealTimePriceRTP(std::string symbol){return 0;}
//HELPER FUNCTIONS
std::string GeneralInfo::ConvertFromUnixTime(std::string unixTime){
    std::time_t result = std::stol(unixTime);
    std::tm *ptm = std::localtime(&result);

    char buffer[32];
    std::strftime(buffer, 32, "%Y-%m-%d %H:%M:%S", ptm);

    return std::string(buffer);

}
bool GeneralInfo::ValidateDateTime(const std::string& dateTimeString){return false;}
#endif 