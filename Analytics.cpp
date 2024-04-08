#ifndef ANALYTICS_CPP
#define ANALYTICS_CPP
#include "Analytics.h"
#include <iostream>
#include <algorithm>
#include <map>

//SMA & EMA... for intervalAmount paramater, call for intervalAmount = values.size() + (periods - 1)


std::vector<std::pair<std::string, double>> Analytics::ChaikinAD(std::string symbol, std::string intervalLength, int intervalAmount){ 
    //populate global data structure
    setValuesTS(symbol, intervalLength, std::to_string(intervalAmount));
    if(intervalAmount < 0 || intervalAmount > valuesTS->size()){
        throw std::invalid_argument("Analytics.cpp @ ChaikinAD: Invalid paramater argument 'intervalAmount'\n");
    }
    std::vector<std::pair<std::string, double>> result;
    //Chakincurrent = Chaikinprevious + MFVcurrent
    double currentMFV; //Money Flow Volume for current interval
    double chaikinVal = 0.0; // initial chaikinVal
    for(int i = (intervalAmount - 1); i > -1; i--){
        //get MFV for current interval
        currentMFV = MoneyFlowVolume(i);
        //calculate chaikinVal for next interval given perious chaikin
        chaikinVal = chaikinVal + currentMFV;
        //get timestamp for the current interval and chaikinVal and push into data struct
        result.push_back({getTimeStampTSAt(i), chaikinVal});
        
    }
    //return vector ordered from oldest to newest interval. 
    //Reverse to preserve original ordering: newest to oldest
    std::reverse(result.begin(), result.end());
    return result;
}

std::vector<std::pair<std::string,double>> Analytics::ADOSC(std::string symbol, std::string intervalLength, int intervalAmount, int shortEMA, int longEMA){
    std::vector<std::pair<std::string,double>> adoscValues;
    //validate EMA paramaters
    if(longEMA < shortEMA || intervalAmount < 0){
        return adoscValues;
    }
    //get Chaikin AD line values
    std::vector<std::pair<std::string, double>> adValues = ChaikinAD(symbol, intervalLength, intervalAmount + longEMA);
    //validate success of ChaikinAD function
    if(adValues.size() == 0){
        return adoscValues;
    }
    //cast from pair vector, to single type vector, and extract numeric data
    std::vector<double> extractedADValues;
    for (auto pair : adValues) {
        extractedADValues.push_back(pair.second);
    }
    //EMA for short and long periods
    std::vector<double> longEMAValues = ExponentialMovingAverage(extractedADValues, longEMA);
    std::vector<double> shortEMAValues = ExponentialMovingAverage(extractedADValues, shortEMA );
    //value pair variables for return vector
    double valADOSC; std::string time;
    //run through ADOSC equation and get 'intervalAmount' data points
    for(int i = 0; i < intervalAmount; i++){
        valADOSC = shortEMAValues.at(i) - longEMAValues.at(i);
        time = adValues.at(i).first;
        adoscValues.push_back({time, valADOSC});
    }
    return adoscValues;
}





//HELPER FUNCTIONS
double Analytics::MoneyFlowMultiplier(int interval){
    //assume data filled up in valuesTS already
    //validate interval
    //get high, low, close for specific interval
    //run through equation
    //validate interval is within vector 
   
    if(interval < 0 || interval >= valuesTS->size()){
        throw std::invalid_argument("Analytics.cpp @ MoneyFlowMultiplier: Invalid paramater argument 'interval'\n");
    }
    //pull data values close high and low from response
    double close = std::stod(valuesTS->at(interval).close);
    double high = std::stod(valuesTS->at(interval).high);
    double low = std::stod(valuesTS->at(interval).low);

    //check for division by 0
    if(high == low){
        throw std::runtime_error("Analytics.cpp @ MoneyFlowMultiplier: high and low values are equal resulting in division by 0\n");
    }
    //Money Flow Multiplier Value equation
    return ((close - low) - (high - close)) / ((high - low));

}

double Analytics::MoneyFlowVolume(int interval){
    //assume data is populated in valuesTS
    //get MFV for current interval
    //validate interval is within vector 
    if(interval < 0 || interval >= valuesTS->size()){
        throw std::invalid_argument("Analytics.cpp @ MoneyFlowVolume: Invalid paramater argument 'interval'\n");
    }
    double MFM = MoneyFlowMultiplier(interval);
    double volume = std::stod(valuesTS->at(interval).volume);
    //MFV = MFM(current) * volume(current)
    return MFM * volume;
}

std::vector<double> Analytics::ExponentialMovingAverage(std::vector<double> values, int periods){
    std::vector<double> emaValues;
    if(periods <= 0 || values.size() < periods){
        return emaValues;
    }
    double k = 2.0 / (static_cast<double>(periods) + 1.0); //smothing factor for EMA equation
    double sum = 0; //sum to calculate SMA value for initialEMA
    for (int i = values.size() - periods; i < values.size(); i++){
        sum += values.at(i);
    }
    //get SMA of the last element in 'values' 
    double smaValue = (sum / periods);
    //run SMA of last element through EMA equation to get initialEMA
    double initialEMA = smaValue; //((values.at(values.size()- periods) ) * k) + (smaValue * (1 - k));
    emaValues.push_back(initialEMA);

    double emaToday;
    double emaYesterday = initialEMA;
    for(int i = values.size() - periods -1; i > -1; i--){
        emaToday = (values.at(i) * k) + (emaYesterday * (1 - k));
        emaValues.push_back(emaToday);
        emaYesterday = emaToday;
    }
    std::reverse(emaValues.begin(), emaValues.end());
    return emaValues;
}

std::vector<double> Analytics::SimpleMovingAverage(std::vector<double> values, int periods){
    //assume values.size == 10, and periods = 5. That means take SMA of intervals 10-6. 10 being oldest in time, 6 being newer.
    //add up all the values from intervals 10 through 6 and divide by 5. Thats SMA for period 6
    //periods cannot be greater than values.size


    //call for setvalues (intervalAmount = values.size() + (periods -1) )
    //assuming 'values' is what we want
    //behind the scenes, we API call for 'values.size + periods' intervals, to initialize oldest value
    //needs those extra intervals provided by periods or else 'values' would get cut down by magnitude of 'periods'



    std::vector<double> smaValues;
    if(periods <= 0 || values.size() < periods){
        return smaValues;
    }

    double sum = 0;
    for (int i = values.size() - periods; i < values.size(); i++){
        sum += values.at(i);
    }

    //initial SMA value 
    smaValues.push_back((sum / periods));

    int shiftOffset = 1;
    for(int i = values.size() - periods -1; i > -1; i--){
        sum = sum - values.at(values.size() - shiftOffset) + values.at(values.size() - periods - shiftOffset);
        shiftOffset++;

        smaValues.push_back((sum / periods));
    }
    std::reverse(smaValues.begin() , smaValues.end());
    //reverse vector

    //size of return vector is values.size() - periods + 1
    return smaValues;
}





#endif