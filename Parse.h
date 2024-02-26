#ifndef PARSE_H
#define PARSE_H

#include <string>
#include <curl/curl.h>
#include <json-c/json.h>
#include <iostream>


class Parse{    
    public:
        //Writes the received data from the the http request to the readbuffer
        //static because it doesnt use any member vars of the Parse class
        static size_t WriteCallBack(void *contents, size_t size, size_t nmemb, void *userp);

        //Sends the written data from the read buffer to a .json file called "response.json"
        //static cuz it doesnt use any memeber vars of the Parse class
        static void WriteToJSON(std::string readBuffer);

        //Sends the written data from the read buffer to a .csv file called "response.csv"
        void WriteToCSV(void *contents, std::string readBuffer);





        //TIME SERIES ONLY. Data parsing 

        //take all the meta object data (general info about company) and put into an array 'metaData'
        void ParseTSMetaToArr(std::string readBuffer);

        //take all the values object data (high,low,volume,open,close) and put into a vector 'genValues'
        void ParseTSValuesToVec(std::string readBuffer);

};

#endif