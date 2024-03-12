#ifndef ANALYTICS_H
#define ANALYTICS_H
#include "GeneralInfo.h"
#include <vector>
#include <string>


class Analytics{
    public:
        /// @brief Calculates the Chaikin A/D line distribution to determine advance or decline of an asset
        ///        =(  ((close-low)-(high-close)) / (high-low)   ) x Volume
        /// @param symbol symbol for the company u are inquring about
        /// @param intervalLength length of a single period, 1min,5min,15min....etc 
        /// @param intervalAmount how many periods.. will only stick to 10.
        /// @return a vector consisting of <dateTime,valAD,dateTime,valAD.... etc
        std::vector<std::string> ChaikinAD(std::string symbol, std::string intervalLength, std::string intervalAmount);
        /// @brief Calculates the Chaikin A/D Oscillator. Finds the relationship between increasing and decreasing volume with
        ///        price fluctuations. Measures momentum of ADL line using EMAs of varying length.
        /// @param symbol Company symbol name
        /// @param intervalLength The length of each interval
        /// @param intervalAmount The amount of intervals 
        /// @param shortEMA Lower bound exponential moving average 
        /// @param longEMA  Upper bound exponential moving average 
        /// @return vector containing the dateTime and respective ADOSC value for all intervals given in the form <date,ADOSC...date,ADOSC...etc>
        std::vector<std::string> ADOSC(std::string symbol, std::string intervalLength, std::string intervalAmount, std::string shortEMA, std::string longEMA);
        /// @brief Calculate the average Directional Index(ADX). Quantifies strength of a trend in a price series, regardless of direction. Default intervalAmount to 14.
        ///        ADX = EMA(DX, 14)
        /// @param symbol Company symbol for query
        /// @param intervalLength length of each period, 1min,5min,1day....    intervalAmount default to 14 
        /// @return vector containing adx value for each interval in the form <date,ADX....date,ADX>
        std::vector<std::string> ADX(std::string symbol, std::string intervalLength);
        /// @brief Calculate average Direcitonal Index. Custom version of default ADX. intervalAmounts are mutable here.
        ///        ADX = EMA(DX, intervalAmount)
        /// @param symbol Company symbol for query
        /// @param intervalLength length of each period, 1min,5min,1day....
        /// @param intervalAmount amount of time periods
        /// @return vector containing adx value for each interval in the form <date,ADX....date,ADX>
        std::vector<std::string> ADX(std::string symbol, std::string intervalLength, std::string intervalAmount);
        /// @brief Smoothed version of ADX indicator. Quantifies momentum change in the ADX. Interval Amount defaulted to 14
        ///        ADXR = (currentADX + ADX from 14 periods ago.) / 2
        /// @param symbol company symbol for query
        /// @param intervalLength how long each interval is. 
        /// @return vector containing adxr value for each interval in the form <date,ADXR....date,ADXR>
        std::vector<std::string> ADXR(std::string symbol, std::string intervalLength);
        /// @brief Smoothed version of ADX indicator. Quantifies momentum change in the ADX. Calculate ADXR for each period relative to 'periods' periods ago.
        ///        ADXR = (currentADX + ADX from 'periods' periods ago) / 2
        /// @param symbol company symbol for query
        /// @param intervalLength how long each interval is 
        /// @param periods amount of periods to average over. 
        /// IMPORTANT: The amount of intervals to fetch for the raw data must be 2 * periods. This is because
        ///            in order to find the ADXR for interval(0), it would need access to the ADX from 'periods' periods ago.
        ///            So, doubling the raw data query will ensure no out of bounds error. 
        /// @return vector containing adxr value for each interval in the form <date,ADXR....date,ADXR>
        std::vector<std::string> ADXR(std::string symbol, std::string intervalLength, std::string periods);


        
    private:
        //HELPER FUNCTIONS
        
        /// @brief Calculates the Accumulation/Distribution Line (ADL) for an Interval
        ///        Formula for ADL = previousADL + Current Money Flow Volume (MFV)
        /// @param previousADL ADL for previous period. If no previous period, set to 0.
        /// @param moneyFlowVolume Current moneyFlowVolume via the MoneyFlowVolume function 
        /// @param periodCounter in the event of recursion, use for base case.
        /// @return ADL value for said interval
        double AccumDistrLine(double previousADL, double moneyFlowVolume, int periodCounter);
        /// @brief Calculate the money flow multiplier for the current interval. 
        ///        MFM = ((close-low)-(high-close)) / (high-low)
        /// @param close clsoe price of the interval
        /// @param high  highest price of the interval
        /// @param low   lowest price of the interval
        /// @return 'double' value of the money flow multiplier for the current interval.
        double MoneyFlowMultiplier(double close, double high, double low); 
        /// @brief Calculate the money flow volume value for an interval
        ///        MFV = Money Flow Multiplier (MFM) * Volume
        /// @param moneyFlowMultiplier money flow multiplier for the given interval
        /// @param volume volume of the given interval
        /// @return return the money flow volume value for the given interval
        double MoneyFlowVolume(double moneyFlowMultiplier, double volume);


        /// @brief Calculate EMA of a given period. EMA(today) = (Value(today) * Alpha) + (EMA(yesterday) * (1-Alpha))
        ///        Alpha = 2 / (N+1) .... where N is the timePeriod
        ///        Value(today) = value of the current period.        ex. (if calculating EMA of period 2, then use value of period 2). doesnt have to be confined to value, can get EMA of DX, DI...etc of anything really
        ///        EMA(yesterday) = EMA of previous period.
        /// @param timePeriod Refers to the amount of intervals to calculate up to. Constraint on variable is dependent on how many periods present in 'valuesTS'
        /// @param value data attribute you want to measure the moving average of.
        /// @return return EMA calculated up to the specified period #
        double ExponentialMovingAverage(double value, int timePeriod);





        /// @brief calculate the true range. 
        ///        Take greatest of the following: 
        ///             1.currentHigh - currentLow   
        ///             2.|(currentHigh - previousClose)|    
        ///             3.|(currentLow - previousClose)|
        /// @param currentHigh high price of the current period 
        /// @param currentLow low price of the current period
        /// @param previousClose close price of the period previous to the current period
        /// @return True range value
        double TrueRange(double currentHigh, double currentLow, double previousClose);
        /// @brief +DM = currentHigh - previousHigh
        /// @param currentHigh 
        /// @param previousHigh 
        /// @return +DM value
        double PositiveDirectionalMovement(double currentHigh, double previousHigh);
        /// @brief -DM = previousLow - currentLow
        /// @param currentLow 
        /// @param previousLow 
        /// @return -DM value
        double NegativeDirectionalMovement(double currentLow, double previousLow);
        /// @brief +DI = ((posDM)/TrueRange) * 100
        /// @param positiveDM use PositiveDirectionalMovement();
        /// @param trueRange use TrueRange();
        /// @return +DI value
        double PositiveDirectionalIndicator(double positiveDM, double trueRange);
        /// @brief -DI = ((negDM)/TrueRange) * 100
        /// @param negativeDM use NegativeDireciontalMovement();
        /// @param trueRange use TrueRange();
        /// @return -DI value
        double NegativeDirectionalIndicator(double negativeDM, double trueRange);
        /// @brief DX =  ( (|posDI - negDI|) / (|posDI + negDI|) ) * 100
        /// @param positiveDI use PositiveDirectionalIndicator();
        /// @param negativeDI use NegativeDirectionalIndicator();
        /// @return DX value 
        double DirectionalMovementIndex(double positiveDI, double negativeDI);

        


};

#endif