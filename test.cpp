#include <curl/curl.h>
#include <iostream>
#include <string>
#include <json-c/json.h>
#include "Parse.h"
#include "GeneralInfo.h"


int main() {

    //    TIME SERIES TESTS

    //     GeneralInfo dataReport;
    //     std::string l = "AAPL";
    //     dataReport.setValuesTS("AAPL", "5min", "3");
    //     int i= 1;
    //     int j = 1;
    //     for (const auto& value : dataReport.valuesTS) {
    //         std::cout << value << ' ';
    //         std::cout << "\n";
    //         if(i == (6*j)){
    //             std::cout << "\n";
    //             j++;
    //         }
    //         i++;

    //     }

    //     std::cout << "\n";

    

    //EXCHANGE RATE TESTS


    // GeneralInfo dataReport;
    // std::string symb1 = "CAD";
    // std::string symb2 = "USD";
    // dataReport.setValuesER(symb1, symb2, "2024-03-01 12:05:00");
    // int i= 1;
    // int j = 1;
    // for (const auto& value : dataReport.valuesER) {
    //     std::cout << value << ' ';
    //     std::cout << "\n";
    

    // }

    // std::cout << "\n";




    GeneralInfo time;
    std::cout << time.ConvertFromUnixTime("1709254920");


    return 0;
}