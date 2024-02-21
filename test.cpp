#include <curl/curl.h>
#include <iostream>
#include <string>
#include <json-c/json.h>



// Callback function for writing received data
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}



int main() {
   
    
    CURL *hnd = curl_easy_init();
    CURLcode ret;
    std::string readBuffer; // String to store the response data

    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(hnd, CURLOPT_URL, "https://api.twelvedata.com/time_series?symbol=AAPL&interval=15min&apikey=41a5696d75774b8eb6929a1dc1af50d6");
    curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, WriteCallback); // Set callback function
    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &readBuffer); // Set data structure to store response

    ret = curl_easy_perform(hnd); // Perform the CURL request

    if (ret == CURLE_OK) {
        json_object *parsed_json = json_tokener_parse(readBuffer.c_str()); // Parse the response data as JSON

        // Write parsed JSON to file
        FILE *fp = fopen("response.json", "w");
        if (fp != NULL) {
            fputs(json_object_to_json_string(parsed_json), fp);
            fclose(fp);
        }

        // Clean up JSON object
        json_object_put(parsed_json);
    }

    // Clean up CURL
    curl_easy_cleanup(hnd);

    return 0;
}