#include <curl/curl.h>
#include <iostream>
#include <string>
#include <json-c/json.h>
#include "Parse.h"
#include "GeneralInfo.h"
#include "Analytics.h"

double average (std::vector<double> pass){
    int sum = 0;
    for(double value : pass){
        sum += value;
    }
    return sum / pass.size();
}

int main() {
   

    // TIME SERIES TESTS

    // GeneralInfo dataReport;
    // dataReport.setValuesTS("AAPL", "5min", "3");
    // int i= 1;
    // int j = 1;

    // for (const auto& stockValue : *(dataReport.valuesTS)) {
    //     std::cout << "Datetime: " << stockValue.dateTime
    //               << ", Open: " << stockValue.open
    //               << ", High: " << stockValue.high
    //               << ", Low: " << stockValue.low
    //               << ", Close: " << stockValue.close
    //               << ", Volume: " << stockValue.volume
    //               << std::endl;
    // }
    // Analytics a;
    // // a.setValuesTS("AAPL", "5min", "3");
    // // std::cout << "Money Flow Multiplier: " << a.MoneyFlowMultiplier(0) << "\n";
    // // std::cout << "Money Flow Volume: " << a.MoneyFlowVolume(0) << " \n" ;


    // std::vector<std::pair<std::string, double>> result;
    // result = a.ChaikinAD("AAPL", "5min", 10);
    // std::cout << "Money Flow Multiplier: " << a.MoneyFlowMultiplier(0) << "\n";
    // std::cout << "Money Flow Volume: " << a.MoneyFlowVolume(9) << " \n" ;

    // for (const auto &entry : result) {
    //     std::cout << "Date: " << entry.first << ", ChaikinAD: " << entry.second << '\n';
    // }

    
    Analytics a;
    std::vector<double> pass = {0,1,2,3,4,5,6,7,8,9,10};
    int periods = 2; //added periods - 1 intervals
    a.setValuesTS("AAPL", "5min", "11");
    std::vector<double> highs = a.getHighs();
    std::vector<double> lows = a.getLows();
    std::vector<double> closes = a.getCloses();
    
    for(auto value : highs){
        std::cout << value << "\n";
    }
    std::cout  << "\n\n\n\n\n lows: \n";

      for(auto value : lows){
        std::cout << value << "\n";
    }
    std::cout  << "\n\n\n\n\n Closes: \n";

      for(auto value : closes){
        std::cout << value << "\n";
    }
    std::cout  << "\n\n\n\n\n\n";







    std::vector<double> res = a.TrueRange(10);
    

    for(auto value: res){
        std::cout << value << "\n";
    }

    
    // for (auto value : result){
    //     std::cout << value.first << "    " << value.second << "\n";
    // }



    





    return 0;
}