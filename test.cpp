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
    // dataReport.setValuesTS("AAPL", "5min", "3");
    // int i= 1;
    // int j = 1;

    // for(int k =0; k < dataReport.valuesTS->size(); k++){
    //     std::cout << dataReport.valuesTS->at(k) << ' ';
    //     std::cout << "\n";
    //     if(i == (6*j)){
    //         std::cout << "\n";
    //         j++;
    //     }
    //     i++;

    // }


    // std::cout << "\n";
    // std::cout << "\n";
    // std::cout << "\n";
    // dataReport.getAllTimeStampTS();
    // std::cout << "\n";
    // std::cout << "\n";
    // dataReport.getAllHighTS();
    // std::cout << "\n";
    // std::cout << "\n";
    // dataReport.getAllLowTS();
    // std::cout << "\n";
    // std::cout << "\n";
    // dataReport.getAllOpenTS();
    // std::cout << "\n";
    // std::cout << "\n";
    // dataReport.getAllCloseTS();
    // std::cout << "\n";
    // std::cout << "\n";
    // std::vector<std::string> temp1 = dataReport.getAllVolumeTS();
    // for(int j = 0; j<temp1.size(); j++){
    //     std::cout << temp1.at(j);
    //     std::cout << "\n";
    // }

    // std::cout << "\n";

    //dataReport.~GeneralInfo(); // free allocated memory













    //EXCHANGE RATE TESTS

    //setvaluesER(2 paramaters)

    // GeneralInfo dataReport;
    // std::string symb1 = "CAD";
    // std::string symb2 = "USD";
    // dataReport.setValuesER(symb1, symb2);
    // int i= 1;
    // int j = 1;
    // for(int k =0; k < dataReport.valuesER->size(); k++){
    //     std::cout << dataReport.valuesER->at(k) << ' ';
    //     std::cout << "\n";
    //     if(i == (6*j)){
    //         std::cout << "\n";
    //         j++;
    //     }
    //     i++;

    // }
    // std::cout << "\n";






    //Currency Conversion tests
    //setvaluesCC(4 paramaters)

    // GeneralInfo dataReport;
    // std::string symb1 = "CAD";
    // std::string symb2 = "USD";
    // std::string amount = "400";
    // std::string dateTimeString = "1995-01-02";
    // dataReport.setValuesCC(symb1, symb2, amount);
    // int i= 1;
    // int j = 1;


    //  for(int k =0; k < dataReport.valuesCC->size(); k++){
    //     std::cout << dataReport.valuesCC->at(k) << ' ';
    //     std::cout << "\n";
    //     if(i == (6*j)){
    //         std::cout << "\n";
    //         j++;
    //     }
    //     i++;

    // }
    

    // std::cout << "\n";





    return 0;
}