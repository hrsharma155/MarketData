#ifndef GENERALINFO_CPP
#define GENERALINFO_CPP
#include "GeneralInfo.h"
#include "Parse.h"
#include <curl/curl.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <json-c/json.h>


//Time series functions
void GeneralInfo::setValuesTS(std::string symbol, std::string intervalLength){
    CURL *hnd = curl_easy_init();

    std::string URL = "https://api.twelvedata.com/time_series?symbol=" + symbol + "&interval=" + intervalLength + "&outputsize=1&apikey=41a5696d75774b8eb6929a1dc1af50d6";

    if (hnd) {
        std::string readBuffer; // String to store the response data
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

 


    //parse the .json file and sort into vector
    GeneralInfo::valuesTS.push_back(1.0);
    GeneralInfo::valuesTS.push_back(1.0);


}
void GeneralInfo::setValuesTS(std::string symbol, int intervalLength, int intervalAmount){}

//Exchagne rate functions
void GeneralInfo::setValuesER(std::string symbol1, std::string symbol2, std::string dateTimeString){}
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
std::string GeneralInfo::ConvertFromUnixTime(int unixTime){}

#endif 