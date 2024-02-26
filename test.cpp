#include <curl/curl.h>
#include <iostream>
#include <string>
#include <json-c/json.h>
#include "Parse.h"


int main() {
    CURL *hnd = curl_easy_init();
    if (hnd) {
        std::string readBuffer; // String to store the response data
        curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(hnd, CURLOPT_URL, "https://api.twelvedata.com/currency_conversion?symbol=USD/JPY&amount=122&apikey=41a5696d75774b8eb6929a1dc1af50d6");
        curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, Parse::WriteCallBack); // Use the member function of Parse class
        curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &readBuffer); // Pass the instance of Parse class
        CURLcode ret = curl_easy_perform(hnd); // Perform the CURL request
        if (ret == CURLE_OK) {
            Parse::WriteToJSON(readBuffer); // Call WriteToJSON to process and save the data
        }
        curl_easy_cleanup(hnd); // Clean up CURL
    }
   
    


    return 0;
}