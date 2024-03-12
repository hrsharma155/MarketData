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
        /// @brief Calculate the Average Directional Index(ADX). Quantifies strength of a trend in a price series, regardless of direction. Default intervalAmount to 14.
        ///        ADX = EMA(DX, 14)
        /// @param symbol Company symbol for query
        /// @param intervalLength length of each period, 1min,5min,1day....    intervalAmount default to 14 
        /// @return vector containing adx value for each interval in the form <date,ADX....date,ADX>
        std::vector<std::string> ADX(std::string symbol, std::string intervalLength);
        /// @brief Calculate Average Direcitonal Index. Custom version of default ADX. intervalAmounts are mutable here.
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
        /// @brief Absolute Price Oscillator(APO). Shows difference between two moving averages of a price. Measures the close price 
        ///        APO = EMA of short period - EMA of long period
        /// @param symbol company symbol to query
        /// @param intervalLength length of each individual interval
        /// @param maType type of moving average. Constrained to: {EMA,SMA,WMA,MA}
        /// @param shortPeriodMA moving average of the short period. Default 12
        /// @param longPeriodMA  moving average of the longer period. Default 26
        /// @param typeOfData what do you want to measure specifically? High, low, open, close prices? Commonly measured for APO are closed prices Constrained to: {high,low,open,close}
        /// IMPORTANT: for querying the raw data, request for (2*longPeriodMA), to ensure no out of bounds errors
        /// @return vector containing APO value for each interval in the form <date,APO....date,APO>
        std::vector<std::string> APO(std::string symbol, std::string intervalLength, std::string maType, std::string shortPeriodMA, std::string longPeriodMA, std::string typeOfData);
        /// @brief Absolute Price Oscillator(APO). Shows difference between two moving averages of a price. Measures the close price 
        ///        APO = EMA of short period - EMA of long period
        /// @param symbol company symbol to query
        /// @param intervalLength length of each individual interval
        /// @param maType type of moving average. Constrained to: {EMA,SMA,WMA,MA}
        /// @param typeOfData what do you want to measure specifically? High, low, open, close prices? Commonly measured for APO are closed prices Constrained to: {high,low,open,close}
        /// IMPORTANT: Default shortEMA to 12, and default longEMA to 26
        /// IMPORTANT: for querying the raw data, request for 52 intervals, to ensure no out of bounds errors
        /// @return vector containing APO value for each interval in the form <date,APO....date,APO>
        std::vector<std::string> APO(std::string symbol, std::string intervalLength, std::string maType, std::string typeOfData);
        /// @brief Aroon Indicator identifies trends in the price of a security and likelihood trends will reverse. 
        ///        AROON UP   = ( ((numPeriodsToExamine) - (periods since 'numPeriodsToExamine' period High)) / numPeriodsToExamine  ) x 100
        ///        AROON DOWN = ( ((numPeriodsToExamine) - (periods since 'numPeriodsToExamine' period Low)) / numPeriodsToExamine  ) x 100
        /// @param symbol Company symbol for query
        /// @param intervalLength Length of each interval
        /// @param numPeriodsToExamine num of periods to look at 
        /// IMPORTANT: Also calculate AROON oscillator value by doing aroonUP - aroonDOWN
        /// @return vector containing AROON values for each interval in the form <date,AroonUP,AroonDOWN,AroonOSC......date,AroonUP,AroonDOWN,AroonOSC>
        std::vector<std::string> AROON(std::string symbol, std::string intervalLength, std::string numPeriodsToExamine);
        /// @brief Aroon Indicator identifies trends in the price of a security and likelihood trends will reverse. DEFAULT number of periods to examine is 14!!!
        ///        AROON UP   = ( ((14) - (periods since '14' period High)) / 14  ) x 100
        ///        AROON DOWN = ( ((14) - (periods since '14' period Low)) / 14  ) x 100
        /// @param symbol company symbol to query
        /// @param intervalLength length of each interval
        /// IMPORTANT: Also calculate AROON oscillator value by doing aroonUP - aroonDOWN
        /// @return vector containing AROON values for each interval in the form <date,AroonUP,AroonDOWN,AroonOSC......date,AroonUP,AroonDOWN,AroonOSC>
        std::vector<std::string> AROON(std::string symbol, std::string intervalLength);
        /// @brief Calculate the average true range over a specified number of periods (intervalAmount)
        /// @param symbol company symbol
        /// @param intervalLength length of each interval
        /// @param intervalAmount num of periods to examine and calc ATR for
        /// IMPORTANT: when requesting raw data, request for (intervalAmount + 1) intervals because need previous data to calculate current data.
        /// @return vector in the form <date,ATR.....date,ATR>
        std::vector<std::string> AverageTrueRange(std::string symbol, std::string intervalLength, std::string intervalAmount);
        /// @brief Calculate the average true range over a specified number of periods (14)
        /// @param symbol company symbol
        /// @param intervalLength length of each interval
        /// IMPORTANT: interval amount defaulted to 14
        /// IMPORTANT: when requesting raw data, request for (15) intervals because need previous data to calculate current data.
        /// @return vector in the form <date,ATR.....date,ATR>
        std::vector<std::string> AverageTrueRange(std::string symbol, std::string intervalLength);
        /// @brief Calculate the average value of a series in a given time period.
        /// @param symbol company symbol
        /// @param intervalLength length of each interval
        /// @param intervalAmount amount of intervals. 
        /// IMPORTANT: When querying raw data, request for (intervalAmount + intervalAmount)
        /// @param typeOfData constrained to one of: {high,low,open,close}
        /// @return vector:  <date,avg.....date,avg> 
        std::vector<std::string> AVG(std::string symbol, std::string intervalLength, std::string intervalAmount, std::string typeOfData);
        /// @brief calculate average price. (high + low + close + open) / 4
        /// @param symbol company symbol
        /// @param intervalLength length of each interval
        /// @param intervalAmount amount of intervals to calculate for
        /// @return vector: <date,AVGPRICE.....date,AVGPRICE>
        std::vector<std::string> AVGPRICE(std::string symbol, std::string intervalLength, std::string intervalAmount);
        /// @brief Bollinger Bands measures volatility located above and below a moving average. Creates upper, middle and lower band. 
        ///        Middle Band: moving average of data type. MB = SimpleMovingAverage(closePrices, 20 intervals). Use helper function
        ///        Upper Band: calculated by adding (stdDeviationMultiplier * standard deviation) 
        ///        Lower Band: calculated by subtracting (stdDeviationMultiplier * standard deviation)
        /// @param symbol company symbol
        /// @param intervalLength length of each interval
        /// @param intervalAmount amount of intervals
        /// @param maType moving average type. constrain to one of: {EMA, SMA, MA}
        /// @param stdDeviatioMultiplier stdDeviation multiplier K. multiply K with true stdDeviation to obtain the value to add or subtract from middle band.
        /// @param typeOfData type of data being one of: {high, low, open, close}
        /// @return vector: <date,upper,middle,lower.......date,upper,middle,lower>
        std::vector<std::string> BBANDS(std::string symbol, std::string intervalLength, std::string intervalAmount, std::string maType, std::string stdDeviationMultiplier, std::string typeOfData);




        
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