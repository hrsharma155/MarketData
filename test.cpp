#include <curl/curl.h>
#include <iostream>
#include <string>
#include <json-c/json.h>
#include "Parse.h"
#include "GeneralInfo.h"


int main() {

   
    GeneralInfo dataReport;
    std::string l = "AAPL";
    dataReport.setValuesTS("AAPL", "5min");

    for (const auto& value : dataReport.valuesTS) {
        std::cout << value << ' ';
    }

    std::cout << "\n";

    



    return 0;
}