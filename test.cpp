#include <curl/curl.h>
#include <iostream>
#include <string>
#include <json-c/json.h>
#include "Parse.h"
#include "GeneralInfo.h"


int main() {

   
    GeneralInfo dataReport;
    std::string l = "AAPL";
    dataReport.setValuesTS(l, 2);
    
    



    return 0;
}