#ifndef GENERALINFO_CPP
#define GENERALINFO_CPP
#include "GeneralInfo.h"
#include <iostream>


//Time series functions
void GeneralInfo::setValuesTS(std::string symbol, int IntervalLength){}
void GeneralInfo::setValuesTS(std::string symbol, int intervalLength, int intervalAmount){}

//Exchagne rate functions
void GeneralInfo::setValuesER(std::string symbol1, std::string symbol2, std::string dateTimeString){}
void GeneralInfo::setValuesER(std::string symbol1, std::string symbol2){}

//Currency exchange functions
void GeneralInfo::setValuesCC(std::string symbool1, std::string symbol2, double amount){}
void GeneralInfo::setValuesCC(std::string symbol1, std::string symbol2, double amount, std::string dateTimeString){}



//Time series single interval getters
int GeneralInfo::getOpenTS(){}
int GeneralInfo::getHighTS(){}
int GeneralInfo::getLowTS(){}
int GeneralInfo::getCloseTS(){}
int GeneralInfo::getVolumeTS(){}
//Time series all intervals getters
std::vector<std::string> GeneralInfo::getTimeStampTS(){}
std::vector<double> GeneralInfo::getAllHighTS(){}
std::vector<double> GeneralInfo::getAllLowTS(){}
std::vector<double> GeneralInfo::getAllCloseTS(){}
std::vector<double> GeneralInfo::getAllVolumeTS(){}

//Exchange rate getters
double GeneralInfo::getStockExchangeRateER(){}
std::string GeneralInfo::getTimeStampER(int seconds){}

//Currency conversion getters
double GeneralInfo::getCurrencyExchangeRateCC(){}
double GeneralInfo::getCurrencyExchangeAmountCC(){}
std::string getTimeStampCC(int seconds){}

//Real time price getter
double GeneralInfo::getRealTimePriceRTP(std::string symbol){}

//HELPER FUNCTIONS
bool GeneralInfo::ValidateDateTime(const std::string& dateTimeString){}
std::string GeneralInfo::ConvertFromUnixTime(int unixTime){}

#endif 