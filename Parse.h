#ifndef PARSE_H
#define PARSE_H

#include <string>



class Parse{    

    size_t WriteCallBack(void *contents, size_t size, size_t nmemb, void *userp){}

    void WriteToJSON (void *contents, std::string readBuffer){}

    void WriteToCSV (void *contents, std::string readBuffer){}

    //TIME SERIES DATA PARSING

    void ParseTSMetaToArr(std::string readBuffer){}

    void ParseTSValuesToVec(std::string readBuffer){}

};

#endif