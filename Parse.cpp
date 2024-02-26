#ifndef PARSE_CPP
#define PARSE_CPP
#include "Parse.h"

#include <curl/curl.h>
#include <json-c/json.h>
#include <string>
#include <iostream>

size_t Parse::WriteCallBack(void *contents, size_t size, size_t nmemb, void *userp){
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


void Parse::WriteToJSON(std::string readBuffer){
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

void Parse::WriteToCSV(void *contents, std::string readBuffer){}

//Time series only. Data parsing. DELETE THESE TWO?
void Parse::ParseTSMetaToArr(std::string readBuffer){}
void Parse::ParseTSValuesToVec(std::string readBuffer){}




#endif