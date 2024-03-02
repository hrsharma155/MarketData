#include <curl/curl.h>
#include <iostream>
#include <string>
#include <json-c/json.h>
#include "Parse.h"
#include "GeneralInfo.h"


int main() {

    // TIME SERIES TESTS

    // setValuesTS(3 paramaters)
    // GeneralInfo dataReport;
    // std::string l = "AAPL";
    // dataReport.setValuesTS("AAPL", "5min", "3");
    // int i= 1;
    // int j = 1;
    // for (const auto& value : dataReport.valuesTS) {
    // std::cout << value << ' ';
    // std::cout << "\n";
    // if(i == (6*j)){
    // std::cout << "\n";
    // j++;
    // }
    // i++;

    // }

    // std::cout << "\n";

    

    //EXCHANGE RATE TESTS

    //setvaluesER(2 paramaters)

    // GeneralInfo dataReport;
    // std::string symb1 = "CAD";
    // std::string symb2 = "USD";
    // dataReport.setValuesER(symb1, symb2);
    // int i= 1;
    // int j = 1;
    // for (const auto& value : dataReport.valuesER) {
    //     std::cout << value << ' ';
    //     std::cout << "\n";
    

    // }

    // std::cout << "\n";






    //Currency Conversion tests
    //setvaluesCC(4 paramaters)

    GeneralInfo dataReport;
    std::string symb1 = "CAD";
    std::string symb2 = "USD";
    std::string amount = "400";
    std::string dateTimeString = "1995-01-02";
    dataReport.setValuesCC(symb1, symb2, amount, dateTimeString);
    int i= 1;
    int j = 1;
    for (const auto& value : dataReport.valuesCC) {
        std::cout << value << ' ';
        std::cout << "\n";
    

    }

    std::cout << "\n";





    return 0;
}