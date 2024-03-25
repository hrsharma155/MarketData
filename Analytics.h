#ifndef ANALYTICS_H
#define ANALYTICS_H
#include "GeneralInfo.h"
#include <vector>
#include <array>
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
        /// @brief Balance of Power (BOP) measures buying/selling pressure of an asset. 1 to -1 where 1 indicates high
        ///        BOP = (close - open) / (high - low)
        /// @param symbol company symbol
        /// @param intervalLength length of each interval
        /// @param intervalAmount # of intervals
        /// @return vector: <date,BOP.....date,BOP>
        std::vector<std::string> BOP(std::string symbol, std::string intervalLength, std::string intervalAmount);
        /// @brief Commodity Channel Index (CCI). 
        ///        1. Calc typical price... TP = (high+low+close) / 3
        ///        2. SMA of TP..... (summation of TP over N periods) / N
        ///        3. Mean Deviation = (Summation of |TP - SMAofTP|) / N
        ///        4. CCI = (TP - SMAofTP) / (0.015 * Mean Deviation)
        /// @param symbol company symbol
        /// @param intervalLength length of each interval
        /// @param intervalAmount # of intervals. Reconmmended 20.
        /// @return vector: <date,CCI.....date,CCI>
        std::vector<std::string> CCI(std::string symbol, std::string intervalLength, std::string intervalAmount);
        /// @brief find the ceiling of a data in a series
        /// @param symbol company
        /// @param intervalLength length of each interval
        /// @param intervalAmount  # of intervals.
        /// @param typeOfData one of : {high, low, close, open} DEFAULT to: close
        /// @return vector: <date,CEIL......date,CEIL>
        std::vector<std::string> CEIL(std::string symbol, std::string intervalLength, std::string intervalAmount, std::string typeOfData);
        /// @brief Chande Momentum Oscillator (CMO). between 100 and -100. +50 means overbought conditions, suggesting a reverasal. -50 means oversold, suggesting upward reversal
        ///        1. Determine number of intervals calculating for
        ///        2. Calculate price changes for each period. current period price change = (currentPerData - prevPerData)
        ///        3. Separate Gains and Losses. For each period, categorize as gain (+value) or loss (-value)
        ///        4. Sum all of the gains, and Sum all of the losses
        ///        5. Calculate CMO. CMO = ((sum of gains - sum of losses) / (sum of gains + sum of losses)) * 100
        /// @param symbol company symbol
        /// @param intervalLength length of each interval
        /// @param intervalAmount # of intervals.
        /// @param typeOfData one of: {high, low, open, close} DEFAULT to: close
        /// IMPORTANT: for raw data request, request for (intervalAmount +1) intervals. (need previous data for current)
        /// @return vector: <date,CMO......date,CMO>
        std::vector<std::string> CMO(std::string symbol, std::string intervalLength, std::string intervalAmount, std::string typeOfData);
        /// @brief Choppock Curve (COPPOCK). 
        ///        1. Calc rate of change. ROC(long n) =( (currentValue - value n periods ago) / (value n periods ago) ) * 100    DO for each interval in 'maIntervals'
        ///        2. Calc rate of change. ROC(short n) = ( (currentValue - value n periods ago) / (value n periods ago) ) * 100  DO for each interval in 'maIntervals'
        ///        3. Add ROC(long n) and ROC (short n). Do this for each period going forward
        ///        4. For each interval for 'maIntervals' , calculate the sum of ROC(long) and ROC(short)
        ///        5. Take a WMA of the last 'maIntervals' values. DO this for each period going forward until you hit most recent interval. WMA(value, maIntervals)
        /// @param  
        /// @param intervalLength length of each interval
        /// @param intervalAmount # of intervals.
        /// @param typeOfData One of {high, low, open, close}. Reconmmended: close
        /// @param maType type of moving average. Reconmmended: WMA
        /// @param maIntervals how many intervals for the moving average to go over. Reconmended: 10
        /// @param longROCPeriod Long number of periods ago. Reconmmended 14 month
        /// @param shortROCPeriod Short number of periods ago. Reconmnended 11 month
        /// IMPORTANT: request raw data amount of (intervalAmount + longROCPeriod)
        /// @return vector: <date,COPPOCK.....date,COPPOCK>
        std::vector<std::string> COPPOCK(std::string symbol, std::string intervalLength, std::string intervalAmount, std::string typeOfData, std::string maType, std::string maIntervals, std::string longROCPeriod, std::string shortROCPeriod);
        /// @brief Calculates the Pearson Correlation Coefficient (CORREL) between two time series.
        ///        CORREL measures the linear correlation between two time series, with values ranging from -1 to 1.
        ///        -1 indicates total negative correlation, 0 indicates no correlation, and 1 indicates total positive correlation.
        ///        CORREL = [n*(∑xy) - (∑x)*(∑y)] / sqrt([n*∑x^2 - (∑x)^2] * [n*∑y^2 - (∑y)^2])
        /// @param symbol1 The symbol for the first company or asset you are inquiring about.
        /// @param symbol2 The symbol for the second company or asset you are inquiring about.
        /// @param intervalLength The length of a single period, such as 1min, 5min, 15min, etc.
        /// @param timePeriod The number of periods to average over, with a default of 9 if not specified.
        /// @param seriesType1 The price type used for the first part of the technical indicator, defaulting to 'open'.
        /// @param seriesType2 The price type used for the second part of the technical indicator, defaulting to 'close'.
        /// @return A vector consisting of pairs of datetime and CORREL values in the form <datetime, CORREL, datetime, CORREL, ... etc.>
        std::vector<std::string> CORREL(std::string symbol1, std::string symbol2, std::string intervalLength, std::string intervalAmount, std::string seriesType1, std::string seriesType2);
        /// @brief Calculates ConnorsRSI (CRSI), an indicator combining three components: a short-term RSI,
        ///        the streak of consecutive up or down closes, and the percent rank of the asset's price change,
        ///        to indicate oversold or overbought levels. It's used to identify potential buy or sell opportunities.
        ///         ConnorsRSI (CRSI) is calculated as the average of three components: 
        /// 1. The Relative Strength Index (RSI) of the asset's price over a specified period (typically 3 days).
        /// 2. The RSI of the asset's up/down streak (the count of consecutive days the asset has closed higher or lower than the previous day), over a specified period (typically 2 days).
        /// 3. The Percent Rank of the asset's price change over a specified period (typically 100 days).
        /// The formula for ConnorsRSI is given by:
        /// CRSI = (RSI[Price, N1] + RSI[Streak, N2] + PercentRank[Price Change, N3]) / 3
        /// Where:
        /// - RSI[Price, N1] is the RSI of the asset's price over N1 periods.
        /// - RSI[Streak, N2] is the RSI of the asset's up/down streak over N2 periods.
        /// - PercentRank[Price Change, N3] is the percent rank of the asset's price change over N3 periods.
        /// - N1, N2, and N3 are the periods for each component, typically set to 3, 2, and 100 respectively.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param rsiPeriod Number of periods to calculate the RSI component, defaults to 3.
        /// @param streakPeriod Number of periods to calculate the streak RSI component, defaults to 2.
        /// @param percentRankPeriod Number of periods to calculate the percent rank component, defaults to 100.
        /// @param seriesType Price type on which the CRSI is calculated, typically 'close'.
        /// @return A vector containing dateTime and CRSI value pairs in the form <dateTime, CRSI, ...>.
        std::vector<std::string> CRSI(std::string symbol, std::string intervalLength, int rsiPeriod, int streakPeriod, int percentRankPeriod, std::string seriesType);
        /// @brief Calculates the Double Exponential Moving Average (DEMA) for a given symbol and interval.
        ///        DEMA aims to reduce lag by applying a double smoothing to the Exponential Moving Average (EMA).
        ///        DEMA = 2 * EMA(N) - EMA(EMA(N))
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param timePeriod Number of periods over which the DEMA is calculated, defaults to 9.
        /// @param seriesType Price type on which the DEMA is calculated, typically 'close'.
        /// @return A vector containing dateTime and DEMA value pairs in the form <dateTime, DEMA, ...>.
        std::vector<std::string> DEMA(std::string symbol, std::string intervalLength, std::string intervalAmount, std::string seriesType);
        /// @brief Calculates the division of values between two specified time series, such as the division
        ///        of the opening price series by the closing price series for a given symbol and interval.
        ///        DIV = Value of SeriesType1 / Value of SeriesType2
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param seriesType1 The price type used as the numerator in the division (e.g., open).
        /// @param seriesType2 The price type used as the denominator in the division (e.g., close).
        /// @return A vector containing dateTime and DIV value pairs in the form <dateTime, DIV, ...>.
        std::vector<std::string> DIV(std::string symbol, std::string intervalLength, std::string seriesType1 = "open", std::string seriesType2 = "close");
        /// @brief Calculates the Detrended Price Oscillator (DPO) for a given symbol and interval.
        ///        The DPO is used to eliminate long-term trends in prices by using a displaced moving average,
        ///        helping to identify cycles and overbought/oversold conditions in shorter time frames.
        ///          The Detrended Price Oscillator (DPO) is calculated by first determining a displaced moving average (DMA) for the specified time period. The DPO is then found by subtracting this DMA from the price approximately halfway through the period:
        ///          DPO = Price - DMA(Price, Time Period, Displacement)
        ///          where Displacement is (Time Period / 2 + 1) periods ago. This calculation removes the longer-term trend, isolating the shorter-term price cycles.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param timePeriod Number of periods over which the DPO is calculated, defaults to 21.
        /// @param seriesType Price type on which the DPO is calculated, typically 'close'.
        /// @param centered Specifies if the DPO values should be shifted to align with current prices, default is false.
        /// @return A vector containing dateTime and DPO value pairs in the form <dateTime, DPO, ...>.
        std::vector<std::string> DPO(std::string symbol, std::string intervalLength, int timePeriod = 21, std::string seriesType = "close", bool centered = false);
        /// @brief Applies the exponential function to the specified time series data, transforming each data point using the mathematical exponent function e^x, where x is the input value.
        ///         EXP(x) = e^x ...... is the input value 'seriesType'
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param seriesType Price type on which the exponential transformation is applied, typically 'close'.
        /// @return A vector containing dateTime and exponential value pairs in the form <dateTime, EXP, ...>.
        std::vector<std::string> EXP(std::string symbol, std::string intervalLength, std::string seriesType = "close");
        /// @brief Applies the mathematical floor function to the input data, transforming each value to the largest
        ///        previous integer. This is particularly useful for rounding down price data or other financial metrics.
        ///             FLOOR(Value) = Largest integer less than or equal to Value
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param seriesType Price type on which the FLOOR function is applied, typically 'close'.
        /// @return A vector containing dateTime and FLOOR value pairs in the form <dateTime, FLOOR, ...>.
        std::vector<std::string> FLOOR(std::string symbol, std::string intervalLength, std::string seriesType = "close");
        /// @brief Generates Heikin-Ashi Candlesticks for the given symbol and interval.
        ///        Heikin-Ashi Candlesticks are used to identify market trends and potential price reversals by averaging
        ///        price values, thereby filtering out market noise and smoothing the price action.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @return A vector of objects containing dateTime, heikinopens, heikinhighs, heikinlows, and heikincloses values for each period.
        std::vector<std::string> HEIKINASHICANDLES(std::string symbol, std::string intervalLength);
        /// @brief Calculates the High, Low, Close Average (HLC3) for a given symbol and interval.
        ///        HLC3 provides an average value based on the high, low, and close prices for each period, 
        ///        offering a simplified view of price movements.
        ///             HLC3 = (High + Low + Close) / 3
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @return A vector containing dateTime and HLC3 value pairs in the form <dateTime, HLC3, ...>.
        std::vector<std::string> HLC3(std::string symbol, std::string intervalLength);
        /// @brief Calculates the Hilbert Transform Dominant Cycle Period (HT_DCPERIOD) for a given symbol and interval.
        ///        This indicator is part of the Hilbert Transform concept and is used to estimate the length of price cycles.
        ///        It is based on the premise that market cycles can be identified through the sine wave characteristics of price actions.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param seriesType Price type on which the HT_DCPERIOD is calculated, typically 'close'.
        /// @return A vector containing dateTime and HT_DCPERIOD value pairs in the form <dateTime, HT_DCPERIOD, ...>.
        std::vector<std::string> HT_DCPERIOD(std::string symbol, std::string intervalLength, std::string seriesType = "close");
        /// @brief Calculates the Hilbert Transform Dominant Cycle Phase (HT_DCPHASE) for a given symbol and interval.
        ///        This indicator measures the phase within the dominant market cycle, providing insights into cycle peaks and troughs.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param seriesType Price type on which the HT_DCPHASE is calculated, typically 'close'.
        /// @return A vector containing dateTime and HT_DCPHASE value pairs in the form <dateTime, HT_DCPHASE, ...>.
        std::vector<std::string> HT_DCPHASE(std::string symbol, std::string intervalLength, std::string seriesType = "close");
        /// @brief Calculates the Hilbert Transform Phasor Components (HT_PHASOR) for a given symbol and interval.
        ///        This indicator decomposes the price series into two orthogonal components (in-phase and quadrature)
        ///        which can help in identifying the characteristic mode of the price cycle.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param seriesType Price type on which the HT_PHASOR is calculated, typically 'close'.
        /// @return A vector containing dateTime, in_phase, and quadrature value triples in the form <dateTime, in_phase, quadrature, ...>.
        std::vector<std::string> HT_PHASOR(std::string symbol, std::string intervalLength, std::string seriesType = "close");
        /// @brief Calculates the Hilbert Transform SineWave (HT_SINE) for a given symbol and interval.
        ///        This indicator provides two sine wave plots, the Sine and the Lead Sine, to help identify the dominant cycle
        ///        and anticipate cycle turns.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param seriesType Price type on which the HT_SINE is calculated, typically 'close'.
        /// @return A vector containing dateTime, ht_sine, and ht_leadsine value triples in the form <dateTime, ht_sine, ht_leadsine, ...>.
        std::vector<std::string> HT_SINE(std::string symbol, std::string intervalLength, std::string seriesType = "close");
        /// @brief Calculates the Hilbert Transform Instantaneous Trendline (HT_TRENDLINE) for a given symbol and interval.
        ///        This indicator provides a smoothed trendline that helps to identify the underlying trend of the price action
        ///        by using digital signal processing techniques.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param seriesType Price type on which the HT_TRENDLINE is calculated, typically 'close'.
        /// @return A vector containing dateTime and HT_TRENDLINE value pairs in the form <dateTime, HT_TRENDLINE, ...>.
        std::vector<std::string> HT_TRENDLINE(std::string symbol, std::string intervalLength, std::string seriesType = "close");
        /// @brief Calculates the Hilbert Transform Trend vs. Cycle Mode (HT_TRENDMODE) for a given symbol and interval.
        ///        This indicator determines the mode of the market - whether it is trending or in a cycle - 
        ///        by analyzing the price series through digital signal processing techniques.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param seriesType Price type on which the HT_TRENDMODE is calculated, typically 'close'.
        /// @return A vector containing dateTime and HT_TRENDMODE value pairs in the form <dateTime, HT_TRENDMODE, ...>.
        std::vector<std::string> HT_TRENDMODE(std::string symbol, std::string intervalLength, std::string seriesType = "close");
        /// @brief Calculates the Ichimoku Kinko Hyo (ICHIMOKU) indicator for a given symbol and interval.
        ///        The Ichimoku Cloud consists of five main components that provide insight into trend direction, momentum, and support & resistance levels.
        /// Conversion Line (Tenkan-sen): The average of the highest high and the lowest low over the last conversionLinePeriod periods.
        ///     Equation: Tenkan-sen = (Highest High + Lowest Low) / 2
        /// Base Line (Kijun-sen): The average of the highest high and the lowest low over the last baseLinePeriod periods.
        ///     Equation: Kijun-sen = (Highest High + Lowest Low) / 2
        /// Leading Span A (Senkou Span A): The average of the Conversion Line and the Base Line, plotted baseLinePeriod periods ahead.
        ///     Equation: Senkou Span A = (Tenkan-sen + Kijun-sen) / 2
        /// Leading Span B (Senkou Span B): The average of the highest high and the lowest low over the last leadingSpanBPeriod periods, plotted baseLinePeriod periods ahead.
        ///     Equation: Senkou Span B = (Highest High + Lowest Low) / 2
        /// Lagging Span (Chikou Span): The closing price plotted baseLinePeriod periods back
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param conversionLinePeriod Period over which the Conversion Line is calculated, typically 9.
        /// @param baseLinePeriod Period over which the Base Line is calculated, typically 26.
        /// @param leadingSpanBPeriod Period over which the Leading Span B is calculated, typically 52.
        /// @param includeAheadSpanPeriod Specifies if the future values of the Leading Span should be included.
        /// @return A vector containing dateTime, tenkan_sen (Conversion Line), kijun_sen (Base Line), senkou_span_a (Leading Span A), senkou_span_b (Leading Span B), and chikou_span (Lagging Span) for each period.
        std::vector<std::string> ICHIMOKU(std::string symbol, std::string intervalLength, int conversionLinePeriod = 9, int baseLinePeriod = 26, int leadingSpanBPeriod = 52, bool includeAheadSpanPeriod = true);
        /// @brief Calculates Kaufman's Adaptive Moving Average (KAMA) for a given symbol and interval.
        ///        KAMA accounts for market noise and volatility, making it a more responsive moving average that can adapt to price changes.
        /// 1. Efficiency Ratio (ER) Calculation:
        ///     ER = |Close - Close_(timePeriod)| / Sum from i=1 to timePeriod of |Close_i - Close_(i-1)|
        /// 2. Smoothing Constant (SC) Calculation:
        ///     SC = [ER * (FastSC - SlowSC) + SlowSC]^2
        ///     Where FastSC = 2 / (2 + 1) and SlowSC = 2 / (30 + 1)
        /// 3. KAMA Calculation:
        ///     KAMA = KAMA_prev + SC * (Price - KAMA_prev)
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param timePeriod Number of periods over which the KAMA is calculated, defaults to 9.
        /// @param seriesType Price type on which the KAMA is calculated, typically 'close'.
        /// @return A vector containing dateTime and KAMA value pairs in the form <dateTime, KAMA, ...>.
        std::vector<std::string> KAMA(std::string symbol, std::string intervalLength, int timePeriod = 9, std::string seriesType = "close");
        /// @brief Calculates Keltner Channels for a given symbol and interval.
        ///        Keltner Channels are volatility-based envelopes set above and below an exponential moving average.
        ///        This indicator helps to identify trend direction and is often used to spot potential breakouts or reversals.
        /// 1. Middle Line: Calculated as a moving average (MA) of the closing prices over a specified period.
        ///     Middle Line = MA(Close, timePeriod)
        /// 2. Upper Line: Determined by adding the Average True Range (ATR) of the closing prices, multiplied by a chosen multiplier, to the middle line.
        ///     Upper Line = Middle Line + (Multiplier x ATR(Close, atrTimePeriod))
        /// 3. Lower Line: Obtained by subtracting the Average True Range (ATR) of the closing prices, multiplied by a chosen multiplier, from the middle line.
        ///     Lower Line = Middle Line - (Multiplier x ATR(Close, atrTimePeriod))
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param timePeriod Number of periods over which the moving average is calculated, defaults to 20.
        /// @param atrTimePeriod Number of periods over which the Average True Range (ATR) is calculated, defaults to 10.
        /// @param multiplier Multiplier applied to the ATR to set the width of the channels, defaults to 2.
        /// @param maType Type of Moving Average used for the middle line, typically 'SMA'.
        /// @param seriesType Price type on which the Keltner Channels are calculated, typically 'close'.
        /// @return A vector containing dateTime, upper_line, middle_line, and lower_line value quadruples in the form <dateTime, upper_line, middle_line, lower_line, ...>.
        std::vector<std::string> KELTNER(std::string symbol, std::string intervalLength, int timePeriod = 20, int atrTimePeriod = 10, int multiplier = 2, std::string maType = "SMA", std::string seriesType = "close");
        /// @brief Calculates the Know Sure Thing (KST) indicator for a given symbol and interval.
        ///        KST is a momentum oscillator based on the rate of change (ROC) of four different price cycles,
        ///        smoothed by simple moving averages.
        /// ROC Calculation for Each Period:
        ///     ROC_i = ((Close_today - Close_(today - ROC Period_i)) / Close_(today - ROC Period_i)) * 100
        /// SMA of Each ROC
        ///     SMA_i(ROC_i) = SMA(ROC_i, SMA Period_i)
        /// Sum of Smoothed ROCs (KST Calculation):
        ///     KST = SMA_1(ROC_1) + SMA_2(ROC_2) + SMA_3(ROC_3) + SMA_4(ROC_4)
        /// KST Signal Line Calculation:
        ///     KST Signal = SMA(KST, Signal Period)
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param rocPeriods Array containing the periods for each of the four ROC calculations.
        /// @param smaPeriods Array containing the periods for the smoothing of each ROC.
        /// @param signalPeriod Period over which the signal line (a moving average of KST) is calculated.
        /// @param seriesType Price type on which the KST is calculated, typically 'close'.
        /// @return A vector containing dateTime, KST, and KST signal value triples in the form <dateTime, KST, KST_signal, ...>.
        std::vector<std::string> KST(std::string symbol, std::string intervalLength, std::array<int, 4> rocPeriods, std::array<int, 4> smaPeriods, int signalPeriod = 9, std::string seriesType = "close");
        /// @brief Calculates Linear Regression for a given symbol and interval.
        ///        Linear Regression is used to determine the trend direction by fitting a straight line through the price data.
        ///Linear Regression Calculation:
        /// 1. Formula for Linear Regression Line: Y = a + bX
        /// Where:
        /// - Y is the dependent variable (price).
        /// - a is the y-intercept of the line.
        /// - b is the slope of the line.
        /// - X is the independent variable (time).
        /// 2. Slope (b) Calculation:
        ///     b = (N * Σ(XY) - ΣX * ΣY) / (N * Σ(X^2) - (ΣX)^2)
        /// 3. Y-Intercept (a) Calculation:
        ///     a = (ΣY - b * ΣX) / N
        /// N represents the number of periods, and Σ denotes summation over those periods.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param timePeriod Number of periods over which the linear regression is calculated, defaults to 9.
        /// @param seriesType Price type on which the LINEARREG is calculated, typically 'close'.
        /// @return A vector containing dateTime and LINEARREG value pairs in the form <dateTime, LINEARREG, ...>.
        std::vector<std::string> LINEARREG(std::string symbol, std::string intervalLength, int timePeriod = 9, std::string seriesType = "close");
        /// @brief Calculates the angle of the Linear Regression trendline for a given symbol and interval.
        ///        The angle is measured in degrees and indicates the steepness of the regression line, 
        ///        providing insight into the trend's strength and direction.
        /// Linear Regression Angle Calculation:
        /// 1. Slope Calculation:
        ///    b = (N * Sum(XY) - Sum(X) * Sum(Y)) / (N * Sum(X^2) - (Sum(X))^2)
        /// 2. Convert Slope to Angle:
        ///    Angle = atan(b) * (180 / Pi)
        /// This process computes the angle of the linear regression trendline, offering insights into the trend's direction and momentum based on the angle's steepness.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param timePeriod Number of periods over which the linear regression angle is calculated, defaults to 9.
        /// @param seriesType Price type on which the LINEARREGANGLE is calculated, typically 'close'.
        /// @return A vector containing dateTime and LINEARREGANGLE value pairs in the form <dateTime, LINEARREGANGLE, ...>.
        std::vector<std::string> LINEARREGANGLE(std::string symbol, std::string intervalLength, int timePeriod = 9, std::string seriesType = "close");
        /// @brief Calculates the intercept of the Linear Regression trendline for each data point for a given symbol and interval.
        ///        The intercept is the point where the regression line crosses the Y-axis, indicating the baseline level of the dependent variable when all independent variables are zero.
        ///         Linear Regression Intercept Calculation:
        /// 1. Y-Intercept (a) Calculation:
        ///    a = (Sum(Y) - b * Sum(X)) / N
        /// Where:
        /// - a is the y-intercept of the regression line.
        /// - Sum(Y) is the total sum of the dependent variable values (e.g., price).
        /// - b is the slope of the linear regression line.
        /// - Sum(X) is the total sum of the independent variable values (e.g., time).
        /// - N is the number of data points.
        // The intercept indicates the baseline level of the dependent variable when the independent variables are zero, marking the point where the regression line crosses the Y-axis.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param timePeriod Number of periods over which the linear regression intercept is calculated, defaults to 9.
        /// @param seriesType Price type on which the LINEARREGINTERCEPT is calculated, typically 'close'.
        /// @return A vector containing dateTime and LINEARREGINTERCEPT value pairs in the form <dateTime, LINEARREGINTERCEPT, ...>.
        std::vector<std::string> LINEARREGINTERCEPT(std::string symbol, std::string intervalLength, int timePeriod = 9, std::string seriesType = "close");
        /// @brief Calculates the slope of the Linear Regression trendline for each data point for a given symbol and interval.
        ///        The slope indicates the direction and strength of the trend: a positive slope suggests an upward trend, while a negative slope indicates a downward trend.
        /// Linear Regression Slope Calculation:
        /// Slope (b) Formula:
        /// b = (N * Sum(XY) - Sum(X) * Sum(Y)) / (N * Sum(X^2) - (Sum(X))^2)
        /// Where:
        /// - Sum(XY) is the sum of the product of each period's time value (X) and its price value (Y).
        /// - Sum(X) is the sum of the time values.
        /// - Sum(Y) is the sum of the price values.
        /// - Sum(X^2) is the sum of the squared time values.
        /// - N is the number of periods.
        /// The slope of the linear regression line indicates the direction and strength of the trend: positive for an upward trend, and negative for a downward trend.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param timePeriod Number of periods over which the linear regression slope is calculated, defaults to 9.
        /// @param seriesType Price type on which the LINEARREGSLOPE is calculated, typically 'close'.
        /// @return A vector containing dateTime and LINEARREGSLOPE value pairs in the form <dateTime, LINEARREGSLOPE, ...>.
        std::vector<std::string> LINEARREGSLOPE(std::string symbol, std::string intervalLength, int timePeriod = 9, std::string seriesType = "close");
        /// @brief Transforms all data points of the given symbol and interval using the natural logarithm to the base of constant e.
        ///        The natural logarithm (ln) is the logarithm to the base e, where e is an irrational constant approximately equal to 2.71828.
        /// Natural Logarithm (LN) Transformation:
        /// The LN function transforms each data point by applying the natural logarithm to the base of constant e. For any given value, the LN is calculated as:
        /// LN(value) = loge(value)
        /// Where:
        /// - loge denotes the logarithm to the base e (approximately 2.71828).
        /// - value is the data point to which the LN transformation is applied, typically the closing price.
        /// This transformation is useful for stabilizing the variance of financial time series and making patterns more apparent.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param seriesType Price type on which the LN transformation is applied, typically 'close'.
        /// @return A vector containing dateTime and LN value pairs in the form <dateTime, LN, ...>.
        std::vector<std::string> LN(std::string symbol, std::string intervalLength, std::string seriesType = "close");
        /// @brief Transforms all data points of a given symbol and interval using the logarithm to base 10.
        /// LOG10 is used to transform data to a scale that can make exponential trends appear linear, aiding in trend identification.
        /// LOG10 (Logarithm to Base 10) Calculation:
        /// The LOG10 function transforms each data point in the series using the logarithm to base 10:
        /// LOG10(x) = log10(x)
        /// This operation is applied to each data point, where 'x' represents the value of the data point (e.g., the closing price of a stock). The transformation is particularly useful for analyzing data that exhibits exponential growth or decay, as it linearizes multiplicative relationships.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param seriesType Price type on which the LOG10 is calculated, typically 'close'.
        /// @return A vector containing dateTime and LOG10 value pairs in the form <dateTime, LOG10, ...>.
        std::vector<std::string> LOG10(std::string symbol, std::string intervalLength, std::string seriesType = "close");
        /// @brief Calculates the Moving Average Convergence Divergence (MACD) for a given symbol and interval.
        ///        MACD is calculated by subtracting the long-term moving average from the short-term moving average, 
        ///        which reveals trend changes and momentum. It includes the MACD line, signal line, and histogram.
        /// MACD (Moving Average Convergence Divergence) Calculation:
        /// 1. MACD Line:
        ///    MACD = EMA(Close, fastPeriod) - EMA(Close, slowPeriod)
        /// 2. Signal Line:
        ///    Signal Line = EMA(MACD, signalPeriod)
        /// 3. MACD Histogram:
        ///    MACD Histogram = MACD - Signal Line
        /// The MACD indicator is a momentum and trend-following indicator that shows the relationship between two moving averages of a security's price. The MACD Line crossing above the Signal Line indicates a bullish signal, while crossing below suggests a bearish signal. The MACD Histogram provides insight into the strength of the price movement.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param fastPeriod Number of periods for the fast moving average, typically 12.
        /// @param slowPeriod Number of periods for the slow moving average, typically 26.
        /// @param signalPeriod Number of periods for the signal line moving average, typically 9.
        /// @param seriesType Price type on which the MACD is calculated, typically 'close'.
        /// @return A vector containing dateTime and MACD value pairs in the form <dateTime, MACD, MACD_signal, MACD_hist, ...>.
        std::vector<std::string> MACD(std::string symbol, std::string intervalLength, int fastPeriod = 12, int slowPeriod = 26, int signalPeriod = 9, std::string seriesType = "close");
        /// @brief Calculates the Moving Average Convergence Divergence Extended (MACDEXT) for each data point for a given symbol and interval.
        ///        This extended version of MACD provides greater control over the moving average types and periods used in the calculation.
        /// MACDEXT (Moving Average Convergence Divergence Extended) Calculation:
        /// 1. Fast Moving Average: Calculated with the specified period and MA type for the fast component.
        /// 2. Slow Moving Average: Calculated with the specified period and MA type for the slow component.
        /// 3. MACD Line: Difference between the Fast and Slow Moving Averages.
        /// 4. Signal Line: Calculated as the Moving Average (with specified type and period) of the MACD Line.
        /// 5. Histogram: Difference between the MACD Line and the Signal Line.
        /// This extended version of MACD allows for customizable moving average types and periods, providing a more flexible approach to analyzing trend momentum and direction.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param fastPeriod Number of periods for the fast moving average, defaults to 12.
        /// @param slowPeriod Number of periods for the slow moving average, defaults to 26.
        /// @param signalPeriod Number of periods for the signal line, defaults to 9.
        /// @param fastMAType Type of Moving Average for the fast period, typically 'SMA'.
        /// @param slowMAType Type of Moving Average for the slow period, typically 'SMA'.
        /// @param signalMAType Type of Moving Average for the signal period, typically 'SMA'.
        /// @param seriesType Price type on which the MACDEXT is calculated, typically 'close'.
        /// @return A vector containing dateTime, MACD, MACD signal, and MACD histogram value quartets in the form <dateTime, MACD, MACD signal, MACD histogram, ...>.
        std::vector<std::string> MACDEXT(std::string symbol, std::string intervalLength, int fastPeriod = 12, int slowPeriod = 26, int signalPeriod = 9, std::string fastMAType = "SMA", std::string slowMAType = "SMA", std::string signalMAType = "SMA", std::string seriesType = "close");
        /// @brief Calculates the MESA Adaptive Moving Average (MAMA) for each data point for a given symbol and interval.
        ///        MAMA adapts to price movement based on the rate of change of phase as measured by the Hilbert Transform Discriminator.
        ///         MESA Adaptive Moving Average (MAMA) Calculation:
        /// 1. Rate of Change: Calculate the rate of change of phase using the Hilbert Transform Discriminator.
        /// 2. Fast Limit: Set the upper threshold for adaptiveness, usually 0.5.
        /// 3. Slow Limit: Set the lower threshold for adaptiveness, usually 0.05.
        /// 4. MAMA: Calculate the main MAMA line, adapting based on the rate of change within the set limits.
        /// 5. FAMA: Generate the Following Adaptive Moving Average as a smoother version of MAMA.
        /// This method allows the moving average to adapt to price movement based on the rate of change of phase, providing a dynamic approach to understanding market trends.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param fastLimit Upper threshold for the rate of change, defaults to 0.5.
        /// @param slowLimit Lower threshold for the rate of change, defaults to 0.05.
        /// @param seriesType Price type on which the MAMA is calculated, typically 'close'.
        /// @return A vector containing dateTime, MAMA, and FAMA (Following Adaptive Moving Average) triplets in the form <dateTime, MAMA, FAMA, ...>.
        std::vector<std::string> MAMA(std::string symbol, std::string intervalLength, double fastLimit = 0.5, double slowLimit = 0.05, std::string seriesType = "close");
        /// @brief Identifies the index of the highest value over a specified period for a given symbol and interval.
        ///         Index of Highest Value over Period (MAXINDEX) Calculation:
        /// 1. Period Selection: Select a time frame, defaulting to 9 periods.
        /// 2. Highest Value Identification: Locate the highest value within the chosen period based on the specified series type (typically close price).
        /// 3. Index Output: Output the index of the highest value within the period for each point in the interval.
        /// This approach is used to understand the relative position of the peak value within a given period, offering insights into the timing of price highs within the specified range.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param timePeriod The number of periods over which to calculate the highest value index.
        /// @param seriesType Price type on which the MAXINDEX is calculated, typically 'close'.
        /// @return A vector containing dateTime and MAXINDEX pairs in the form <dateTime, MAXINDEX, ...>.
        std::vector<std::string> MAXINDEX(std::string symbol, std::string intervalLength, int timePeriod = 9, std::string seriesType = "close");
        /// @brief McGinley Dynamic indicator keeps all the benefits from the moving averages but adds an adjustment to market speed.
        /// McGinley Dynamic (MD) = MD_previous + (Price - MD_previous) / (k * (Price / MD_previous) ^ 4)
        /// where:
        /// - MD_previous is the previous McGinley Dynamic value
        /// - Price is the current price
        /// - k is a constant, typically set to 0.6 (though it can vary based on the data)
        /// - The term (Price / MD_previous) ^ 4 is used to adjust the indicator's sensitivity to market speed
        /// @param symbol Symbol for the company you are inquiring about
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param timePeriod Number of periods to average over, typically set to 14.
        /// @return A vector containing <dateTime, mcginley_dynamic> pairs for each interval.
        std::vector<std::string> MCGINLEY_DYNAMIC(std::string symbol, std::string intervalLength, int timePeriod = 14);
        /// @brief Median Price (MEDPRICE) calculates the median level of prices for a given symbol and interval.
        /// MEDPRICE = (High + Low) / 2 .... for the current interval
        /// @param symbol Symbol for the company you are inquiring about
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @return A vector containing <dateTime, medprice> pairs for each interval.
        std::vector<std::string> MEDPRICE(std::string symbol, std::string intervalLength, std::string intervalAmount);
        /// @brief Money Flow Index (MFI) calculates the flow of money into and out of a security over a specified period of time.
        ///        The MFI is an oscillator that uses both price and volume to measure buying and selling pressure.
        ///        It's a component of the typical price multiplied by volume, comparing the positive and negative money flows.
        ///        MFI = 100 - (100 / (1 + (Positive Money Flow / Negative Money Flow)))
        /// @param symbol Symbol for the company you are inquiring about
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param timePeriod The number of periods over which the MFI is calculated, typically 14.
        /// @return A vector containing <dateTime, MFI value> pairs for each interval.
        std::vector<std::string> MFI(std::string symbol, std::string intervalLength, int timePeriod = 14);
        /// @brief MidPoint over period calculates the midpoint of the highest and lowest values in a given period.
        ///        MIDPOINT = (Highest Value + Lowest Value) / 2
        /// @param symbol Symbol for the company you are inquiring about
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param timePeriod The number of periods over which the midpoint is calculated, typically 9.
        /// @param dataType close, high, open, low ???
        /// @return A vector containing <dateTime, midpoint value> pairs for each interval.
        std::vector<std::string> MIDPOINT(std::string symbol, std::string intervalLength, int timePeriod = 9, std::string dataType);
        /// @brief MidPoint Price over period (MIDPRICE) calculates the midpoint of the highest high and lowest low over a specified period.
        ///        MIDPRICE = (Highest High + Lowest Low) / 2
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param timePeriod The number of periods over which the MIDPRICE is calculated, typically 9.
        /// @param intervalAmount amount of intervals
        /// @return A vector containing <dateTime, MIDPRICE value> pairs for each interval.
        std::vector<std::string> MIDPRICE(std::string symbol, std::string intervalLength, int timePeriod = 9, std::string intervalAmount);
        /// @brief Calculates the lowest value over a specified period for a given symbol and interval.
        ///        MIN is calculated as the minimum value within the specified time period based on the series type.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param intervalAmount Number of data points to retrieve, represents the output size.
        /// @param seriesType Price type on which the MIN is calculated, typically 'close'.
        /// @param timePeriod Number of periods to average over, typically 9.
        /// @return A vector containing dateTime and MIN value pairs in the form <dateTime, MIN, ...>.
        std::vector<std::string> MIN(std::string symbol, std::string intervalLength, std::string intervalAmount, std::string seriesType = "close", int timePeriod = 9);
        /// @brief Calculates the index of the lowest value over a specified period for a given symbol and interval.
        ///        MININDEX returns the position (index) of the minimum value within the specified time period based on the series type.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param intervalAmount Number of data points to retrieve, represents the output size.
        /// @param seriesType Price type on which the MININDEX is calculated, typically 'close'.
        /// @param timePeriod Number of periods to average over, typically 9.
        /// @return A vector containing dateTime and MININDEX value pairs in the form <dateTime, MININDEX, ...>.
        std::vector<std::string> MININDEX(std::string symbol, std::string intervalLength, std::string intervalAmount, std::string seriesType = "close", int timePeriod = 9);
        /// @brief Calculates the lowest and highest values over a specified period (MINMAX).
        ///        MINMAX provides the minimum and maximum values within a given time frame, offering insights into the range of price movements.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param intervalAmount Number of data points to retrieve, reflecting how many intervals you want the data for.
        /// @param seriesType Price type on which technical indicator is calculated, typically 'close'.
        /// @param timePeriod Number of periods to average over. Takes values in the range from 1 to 800, defaulting to 9.
        /// @return A vector containing pairs of dateTime, min, and max values in the form <dateTime, min, max, ...>.
        std::vector<std::string> MINMAX(std::string symbol, std::string intervalLength, std::string intervalAmount, std::string seriesType = "close", int timePeriod = 9);
        /// @brief Calculates the indexes of the lowest and highest values over a specified period (MINMAXINDEX).
        ///        MINMAXINDEX provides the indexes where the minimum and maximum values occur within a given time frame, offering insights into the timing of peak and trough movements.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param intervalAmount Number of data points to retrieve, reflecting how many intervals you want the data for.
        /// @param seriesType Price type on which technical indicator is calculated, typically 'close'.
        /// @param timePeriod Number of periods to average over. Takes values in the range from 1 to 800, defaulting to 9.
        /// @return A vector containing pairs of dateTime, minIdx, and maxIdx values in the form <dateTime, minIdx, maxIdx, ...>.
        std::vector<std::string> MINMAXINDEX(std::string symbol, std::string intervalLength, std::string intervalAmount, std::string seriesType = "close", int timePeriod = 9);
        /// @brief Calculates the Momentum (MOM) of an asset by comparing its current price with the price from N periods ago.
        ///        MOM = CurrentPrice - Price(N periods ago)
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param intervalAmount Number of data points to retrieve, reflecting how many intervals you want the data for.
        /// @param seriesType Price type on which technical indicator is calculated, typically 'close'.
        /// @param timePeriod Number of periods to compare the current price against, defaulting to 9.
        /// @return A vector containing pairs of dateTime and MOM values in the form <dateTime, MOM, ...>.
        std::vector<std::string> MOM(std::string symbol, std::string intervalLength, std::string intervalAmount, std::string seriesType = "close", int timePeriod = 9);
        /// @brief Calculates the multiplication of values of two specified time series for an asset.
        ///        MULT = Value(series_type_1) * Value(series_type_2)
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param intervalAmount Number of data points to retrieve, reflecting how many intervals you want the data for.
        /// @param seriesType1 Price type used as the first part of the technical indicator, typically 'open'.
        /// @param seriesType2 Price type used as the second part of the technical indicator, typically 'close'.
        /// @return A vector containing pairs of dateTime and MULT values in the form <dateTime, MULT, ...>.
        std::vector<std::string> MULT(std::string symbol, std::string intervalLength, std::string intervalAmount, std::string seriesType1 = "open", std::string seriesType2 = "close");
        /// @brief Calculates the Normalized Average True Range (NATR) of an asset, offering a normalized measure of volatility.
        ///        NATR is useful for comparing volatility across different price levels. 
        ///        NATR = (ATR / Close) * 100
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param intervalAmount Number of data points to retrieve, reflecting how many intervals you want the data for.
        /// @param timePeriod Number of periods to average over for the ATR calculation, typically 14.
        /// @return A vector containing pairs of dateTime and NATR values in the form <dateTime, NATR, ...>.
        std::vector<std::string> NATR(std::string symbol, std::string intervalLength, std::string intervalAmount, std::string timePeriod = "14");
        /// @brief Calculates the On Balance Volume (OBV) of an asset, a momentum indicator that uses volume flow
        ///        to predict changes in stock price. The OBV is calculated by adding or subtracting each day's volume
        ///        to the cumulative total when the stock closes up or down, respectively.
        ///      OBV = Previous OBV + Current Volume if Close > Previous Close
        ///            Previous OBV - Current Volume if Close < Previous Close
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param intervalAmount Number of data points to retrieve, reflecting how many intervals you want the data for.
        /// @return A vector containing pairs of dateTime and OBV values in the form <dateTime, OBV, ...>.
        std::vector<std::string> OBV(std::string symbol, std::string intervalLength, std::string intervalAmount);
        /// @brief Calculates the %B Indicator (PERCENT_B), measuring the position of the asset price relative to the upper and lower Bollinger Bands.
        ///        %B = (Price - Lower Band) / (Upper Band - Lower Band)
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param intervalAmount Number of data points to retrieve, reflecting how many intervals you want the data for.
        /// @param timePeriod Number of periods over which the Bollinger Bands are calculated, typically 20.
        /// @param maType Type of Moving Average used in Bollinger Bands calculation, typically "SMA".
        /// @param sd Number of standard deviations for the width of the Bollinger Bands, typically 2.
        /// @return A vector containing pairs of dateTime and PERCENT_B values in the form <dateTime, PERCENT_B, ...>.
        std::vector<std::string> PERCENT_B(std::string symbol, std::string intervalLength, std::string intervalAmount, std::string timePeriod = "20", std::string maType = "SMA", std::string sd = "2");
        /// @brief Calculates Pivot Points (High/Low) (PIVOT_POINTS_HL), used to foresee potential price reversals.
        ///        Pivot Points are calculated as the average of the high, low, and closing prices from the previous trading session.
        ///     Pivot Point High (H) = (Highest High + Lowest Low + Close) / 3
        ///     Pivot Point Low (L) = (Highest High + Lowest Low + Close) / 3
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param intervalAmount Number of data points to retrieve, reflecting how many intervals you want the data for.
        /// @param timePeriod Number of periods to average over for calculating high and low pivot points, typically 10.
        /// @return A vector containing pairs of dateTime and Pivot Points values in the form <dateTime, pivot_point_h, pivot_point_l, ...>.
        std::vector<std::string> PIVOT_POINTS_HL(std::string symbol, std::string intervalLength, std::string intervalAmount, std::string timePeriod = "10");
        /// @brief Calculates Percentage Price Oscillator (PPO) which shows the relationship between two Moving Averages (MA) as a percentage.
        ///        PPO = ((Fast MA - Slow MA) / Slow MA) * 100
        /// @param symbol The ticker symbol for the financial instrument.
        /// @param intervalLength The time period between each data point (e.g., 1min, 5min, 15min, etc.).
        /// @param fastPeriod The number of periods to consider for the fast moving average, defaulting to 12.
        /// @param slowPeriod The number of periods to consider for the slow moving average, defaulting to 26.
        /// @param maType The type of Moving Average to be used, defaulting to "SMA".
        /// @param seriesType The price type on which the technical indicator is calculated, defaulting to "close".
        /// @param intervalAmount The number of data points to calculate the PPO over.
        /// @return A vector of pairs, each containing a datetime and the corresponding PPO value for that time.
        std::vector<std::pair<std::string, double>> PPO(std::string symbol, std::string intervalLength, int fastPeriod = 12, int slowPeriod = 26, std::string maType = "SMA", std::string seriesType = "close", int intervalAmount);
        /// @brief Calculates the Rate of Change (ROC) which measures the percentage change in price between the current price and the price a certain number of periods ago.
        ///     ROC = ((Current Price / Price 'n' Periods Ago) - 1) * 100
        /// @param symbol The ticker symbol for the financial instrument.
        /// @param intervalLength The time period between each data point (e.g., 1min, 5min, 15min, etc.).
        /// @param intervalAmount The number of data points to calculate the ROC over, defaults to 9.
        /// @return A vector of pairs, each containing a datetime and the corresponding ROC value for that time.
        std::vector<std::pair<std::string, double>> ROC(std::string symbol, std::string intervalLength, int intervalAmount = 9);
        /// @brief Calculates the Rate of Change Percentage (ROCP) which measures the percentage difference between the current price and the price a certain number of periods ago.
        ///     ROCP = (Current Price - Price 'n' Periods Ago) / Price 'n' Periods Ago
        /// @param symbol The ticker symbol for the financial instrument.
        /// @param intervalLength The time period between each data point (e.g., 1min, 5min, 15min, etc.).
        /// @param intervalAmount The number of data points to calculate the ROCP over, defaults to 9.
        /// @return A vector of pairs, each containing a datetime and the corresponding ROCP value for that time.
        std::vector<std::pair<std::string, double>> ROCP(std::string symbol, std::string intervalLength, int intervalAmount = 9);
        /// @brief Calculates the Rate of Change Ratio (ROCR) which measures the ratio of the current price to the price a certain number of periods ago.
        ///     ROCR = Current Price / Price 'n' Periods Ago
        /// @param symbol The ticker symbol for the financial instrument.
        /// @param intervalLength The time period between each data point (e.g., 1min, 5min, 15min, etc.).
        /// @param intervalAmount The number of data points to calculate the ROCR over, defaults to 9.
        /// @return A vector of pairs, each containing a datetime and the corresponding ROCR value for that time.
        std::vector<std::pair<std::string, double>> ROCR(std::string symbol, std::string intervalLength, int intervalAmount = 9, std::string dataType);
        /// @brief Calculates the Rate of Change Ratio 100 scale (ROCR100) which measures the ratio of the current price to the price a certain number of periods ago, scaled by 100.
        ///      ROCR100 = (Current Price / Price 'n' Periods Ago) * 100
        /// @param symbol The ticker symbol for the financial instrument.
        /// @param intervalLength The time period between each data point (e.g., 1min, 5min, 15min, etc.).
        /// @param intervalAmount The number of data points to calculate the ROCR100 over, defaults to 9.
        /// @return A vector of pairs, each containing a datetime and the corresponding ROCR100 value for that time.
        std::vector<std::pair<std::string, double>> ROCR100(std::string symbol, std::string intervalLength, int intervalAmount = 9, std::string dataType);
        /// @brief Calculates the Relative Strength Index (RSI), a momentum indicator that measures the magnitude of recent price changes to evaluate overbought or oversold conditions.
        ///        RSI = 100 - (100 / (1 + (average gain / average loss)))
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param timePeriod The number of periods over which the RSI is calculated, with a common default of 14 periods.
        /// @return A vector containing <dateTime, RSI value> pairs for each interval, indicating the RSI value at the corresponding datetime.
        std::vector<std::string> RSI(std::string symbol, std::string intervalLength, int timePeriod = 14, std::string dataType = "close");
        /// @brief Calculates the Relative Volume Indicator (RVOL) to compare current trading volume to past volume over a specified period.
        ///        RVOL = Current Volume / Average Volume over 'time_period'
        /// @param symbol The ticker symbol for the financial instrument (e.g., "AAPL").
        /// @param intervalLength The time interval between data points (e.g., "1min").
        /// @param timePeriod The number of time periods over which to average the volume, with a default of 14.
        /// @return A vector containing pairs of datetime and RVOL values in the form <dateTime, RVOL, dateTime, RVOL, ... etc.>
        std::vector<std::string> RVOL(std::string symbol, std::string intervalLength, int timePeriod = 14);
        /// @brief Calculates the Parabolic SAR (SAR) to identify potential momentum in asset price movements.
        ///        SAR = SARprevious + acceleration * (EP - SARprevious)
        ///        Where:
        ///        - SARprevious is the SAR value in the previous period.
        ///        - acceleration is the acceleration factor, which increases by the acceleration factor every time a new EP (extreme point) is recorded.
        ///        - EP is the highest high in the current uptrend or the lowest low in the current downtrend.
        /// @param symbol The ticker symbol for the asset you're interested in.
        /// @param intervalLength The length of each time interval (e.g., 1min, 5min, 15min).
        /// @param acceleration The acceleration factor used to calculate the SAR, typically starting at 0.02.
        /// @param maximum The maximum value the acceleration factor can reach, typically set to 0.2.
        /// @return A vector containing pairs of date-time and SAR values in the form <dateTime, SAR, ...>.
        std::vector<std::string> SAR(std::string symbol, std::string intervalLength, double acceleration, double maximum);
        /// @brief Calculates the Parabolic SAR Extended (SAREXT), an enhanced version of the classic SAR with more flexible parameters.
        ///        SAREXT is used to identify potential reversals in the market price direction of an asset.
        /// @param symbol Symbol ticker of the instrument, e.g. AAPL, EUR/USD, ETH/BTC, etc.
        /// @param intervalLength Interval between two consecutive points in the time series, supporting: 1min, 5min, 15min, 30min, 45min, 1h, 2h, 4h, 1day, 1week, 1month.
        /// @param accelerationLimitLong The acceleration factor limit for long positions, defaulting to 0.02.
        /// @param accelerationLimitShort The acceleration factor limit for short positions, defaulting to 0.02.
        /// @param accelerationLong The initial acceleration factor for long positions, defaulting to 0.02.
        /// @param accelerationMaxLong The maximum acceleration factor for long positions, defaulting to 0.2.
        /// @param accelerationMaxShort The maximum acceleration factor for short positions, defaulting to 0.2.
        /// @param accelerationShort The initial acceleration factor for short positions, defaulting to 0.02.
        /// @param offsetOnReverse The offset applied when the position is reversed, defaulting to 0.
        /// @param startValue The starting value for the SAR calculation, defaulting to 0.
        /// @return A vector containing <dateTime, SAREXT value> pairs for each interval, indicating the SAR values for the specified parameters.
        std::vector<std::string> SAREXT(std::string symbol, std::string intervalLength, double accelerationLimitLong, double accelerationLimitShort, double accelerationLong, double accelerationMaxLong, double accelerationMaxShort, double accelerationShort, double offsetOnReverse, double startValue);
        /// @brief Transforms input data with square root, providing a smoother and normalized view of price data.
        ///        SQRT transformation can be particularly useful for reducing the influence of outliers and making exponential growth appear linear.
        ///        SQRT(value) = sqrt(value) .... for the current interval
        /// @param symbol Symbol for the company or asset you are inquiring about
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param seriesType Price type on which the square root transformation is applied, typically 'close'.
        /// @return A vector containing <dateTime, sqrtValue> pairs for each interval.
        std::vector<std::string> SQRT(std::string symbol, std::string intervalLength, std::string seriesType = "close");
        /// @brief Calculates the Standard Deviation (STDDEV) of a given symbol and interval to measure volatility and assess risks.
        ///        Standard Deviation is a statistical measurement that sheds light on the amount of variation or dispersion from the average.
        ///        A high standard deviation indicates a high level of volatility and potential risk, whereas a low standard deviation indicates stability.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param timePeriod Number of periods over which the standard deviation is calculated, defaults to 9.
        /// @param seriesType Price type on which the standard deviation is calculated, typically 'close'.
        /// @param sd Number of standard deviations, defaults to 2, to scale the standard deviation if needed.
        /// @return A vector containing <dateTime, stddevValue> pairs for each interval, where stddevValue is the calculated standard deviation.
        std::vector<std::string> STDDEV(std::string symbol, std::string intervalLength, std::string seriesType = "close", int timePeriod = 9, int sd = 2);
        /// @brief Calculates the Stochastic Oscillator, indicating momentum by comparing a closing price to its price range over a given period.
        ///        The oscillator comprises two lines: %K (the fast line) and %D (the slow line, which is a moving average of %K).
        /// @param symbol Symbol for the company or asset you are inquiring about
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param fastKPeriod Number of periods used to calculate the %K line, typically set to 14.
        /// @param slowKPeriod Number of periods used to smooth the %K line, typically set to 1.
        /// @param slowDPeriod Number of periods used to calculate the %D line, typically set to 3.
        /// @param slowKMAType Type of Moving Average used to smooth the %K line, typically 'SMA'.
        /// @param slowDMAType Type of Moving Average used to calculate the %D line, typically 'SMA'.
        /// @return A vector containing <dateTime, slowK, slowD> triplets for each interval, where 'slowK' is the smoothed %K line and 'slowD' is the %D line.
        std::vector<std::string> STOCH(std::string symbol, std::string intervalLength, int fastKPeriod = 14, int slowKPeriod = 1, int slowDPeriod = 3, std::string slowKMAType = "SMA", std::string slowDMAType = "SMA");
        /// @brief Calculates the Stochastic Fast (STOCHF) indicator, which is sensitive to price changes and often changes direction quickly.
        ///        STOCHF compares the closing price of a security to its price range over a given time period and consists of two lines: fast_k and fast_d.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of each interval, such as 1min, 5min, 15min, etc.
        /// @param intervalAmount Number of data points to retrieve, corresponding to the 'outputsize' in the API. It affects how many intervals of data are returned.
        /// @param fastKPeriod Number of periods used to calculate the %K line, with a default of 14.
        /// @param fastDPeriod Number of periods used to calculate the %D line, with a default of 3. This is a moving average of the %K line.
        /// @param fastDMAType Type of Moving Average used on the Fast D Period, with 'SMA' as the default.
        /// @return A vector containing <dateTime, fastK, fastD> triplets for each interval, where 'fastK' and 'fastD' represent the fast %K and %D lines, respectively.
        std::vector<std::string> STOCHF(std::string symbol, std::string intervalLength, std::string intervalAmount, int fastKPeriod = 14, int fastDPeriod = 3, std::string fastDMAType = "SMA");
        /// @brief Calculates the Stochastic RSI (STOCHRSI) indicator, combining the features of Stochastic Oscillator and Relative Strength Index.
        ///        STOCHRSI is used to identify overbought and oversold conditions as well as the current market trend.
        ///        The calculation involves applying the Stochastic formula to the RSI values instead of price data.
        ///        The 'K' value in STOCHRSI is the current value of the Stochastic RSI, whereas the 'D' value is the moving average of the 'K' value.
        ///        STOCHRSI = (RSI - RSI Lowest Low) / (RSI Highest High - RSI Lowest Low)
        ///        Where RSI is calculated for a specified 'rsi_length' and STOCHRSI is calculated over 'stoch_length'.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param stochLength The number of periods used for the Stochastic calculation.
        /// @param kPeriod The number of periods used to calculate the %K line.
        /// @param dPeriod The number of periods used to calculate the %D line (the moving average of %K).
        /// @param seriesType The price type on which the RSI is calculated, typically 'close'.
        /// @param rsiLength The number of periods used to calculate the RSI.
        /// @param intervalAmount The number of data points to retrieve, representing the output size.
        /// @return A vector containing <dateTime, kValue, dValue> triplets for each interval, where 'kValue' is the current value of STOCHRSI and 'dValue' is the moving average of 'kValue'.
        std::vector<std::string> STOCHRSI(std::string symbol, std::string intervalLength, int stochLength = 14, int kPeriod = 3, int dPeriod = 3, std::string seriesType = "close", int rsiLength = 14, std::string intervalAmount = "30");
        /// @brief Performs arithmetic subtraction between two price series for a given symbol and interval.
        ///        The SUB indicator subtracts the values of one time series from another, typically using different price types such as 'open' and 'close'.
        ///        This can be used to analyze the difference between opening and closing prices or any other combination of price types.
        ///        SUB(value1, value2) = value1 - value2 .... for each interval
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param seriesType1 The price type used as the first part of the technical indicator, typically 'open'.
        /// @param seriesType2 The price type used as the second part of the technical indicator, typically 'close'.
        /// @param intervalAmount The number of data points to retrieve, representing the output size.
        /// @return A vector containing <dateTime, subValue> pairs for each interval, where 'subValue' is the result of the subtraction.
        std::vector<std::string> SUB(std::string symbol, std::string intervalLength, std::string seriesType1 = "open", std::string seriesType2 = "close", std::string intervalAmount = "30");
        /// @brief Calculates the Summation (SUM) of values for a given symbol and interval, summing up the values of a specified price type over a certain period.
        ///        The SUM indicator provides a total sum of the specified series_type over the given time_period, helping to identify trends or patterns in data accumulation or depletion over time.
        ///        SUM = Σ(Price) over 'time_period'
        ///        This represents the cumulative sum of the price type specified (e.g., 'close' prices) over the number of periods specified by 'time_period'.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param seriesType The price type on which the summation is calculated, typically 'close'.
        /// @param timePeriod The number of periods over which the summation is calculated, defaults to 9.
        /// @param intervalAmount The number of data points to retrieve, representing the output size.
        /// @return A vector containing <dateTime, sumValue> pairs for each interval, where 'sumValue' is the cumulative sum of the specified price type over the 'time_period'.
        std::vector<std::string> SUM(std::string symbol, std::string intervalLength, std::string seriesType = "close", int timePeriod = 9, std::string intervalAmount = "30");
        /// @brief Calculates the SuperTrend Indicator, a trend-following indicator that is used to identify the direction of the market.
        ///        The SuperTrend Indicator combines the Average True Range (ATR) with a multiplier to determine trend direction.
        ///        The indicator flips above or below the price depending on the trend direction, and is used to set stop-loss orders or determine entry points.
        ///        SUPERTREND = Previous SUPERTREND value if condition is met, else Current High or Low +/- (Multiplier * ATR)
        ///        The condition for the SUPERTREND to remain the same is based on the price being above or below the previous SUPERTREND value and the trend direction.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param multiplier The number by which the ATR is multiplied. Used to adjust the indicator sensitivity.
        /// @param period The number of periods used to calculate the ATR, influencing the SUPERTREND sensitivity.
        /// @param intervalAmount The number of data points to retrieve, representing the output size.
        /// @return A vector containing <dateTime, supertrendValue> pairs for each interval, where 'supertrendValue' is the calculated SuperTrend value at each point in time.
        std::vector<std::string> SUPERTREND(std::string symbol, std::string intervalLength, int multiplier = 3, int period = 10, std::string intervalAmount = "30");
        /// @brief Calculates the SuperTrend Heikin-Ashi Candles Indicator, which combines the SuperTrend indicator with Heikin-Ashi candlestick values.
        ///        The SuperTrend component is used to determine the trend's direction, and the Heikin-Ashi values smooth out the price data to better identify market trends.
        ///        The SuperTrend calculation uses the Average True Range (ATR) and a multiplier to define the trend. A flip in the direction of the SuperTrend line indicates a potential reversal.
        ///        SUPERTREND = (High + Low) / 2 ± Multiplier * ATR(Period)
        ///        Heikin-Ashi candles are calculated using the open, high, low, and close prices, providing a synthesized view of trends.
        ///        HEIKIN-ASHI OPEN = (Previous Open + Previous Close) / 2
        ///        HEIKIN-ASHI CLOSE = (Open + High + Low + Close) / 4
        ///        HEIKIN-ASHI HIGH = Max(High, Open, Close)
        ///        HEIKIN-ASHI LOW = Min(Low, Open, Close)
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param multiplier Multiplier applied to the ATR to determine the trend threshold.
        /// @param period Number of periods used to calculate the ATR for the SuperTrend component.
        /// @param intervalAmount The number of data points to retrieve, representing the output size.
        /// @return A vector containing <dateTime, supertrendValue, heikinOpen, heikinHigh, heikinLow, heikinClose> for each interval, where each component represents the respective value at the corresponding dateTime.
        std::vector<std::string> SUPERTREND_HEIKINASHICANDLES(std::string symbol, std::string intervalLength, int multiplier = 3, int period = 10, std::string intervalAmount = "30");
        /// @brief Calculates the Triple Exponential Moving Average (T3MA), an enhanced version of the TEMA indicator that offers smoother moving averages.
        ///        T3MA provides better smoothing by extending the lookback period and incorporating a volume factor to adjust the responsiveness of the moving averages.
        ///        The T3MA is calculated using a series of weighted EMA calculations to produce a triple smoothing of the moving average.
        ///        T3MA = EMA3(EMA3(EMA3(Series))) where each EMA3 includes a volume factor (v_factor) to control the degree of smoothing.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param timePeriod Number of periods over which the T3MA is calculated, typically 9.
        /// @param vFactor Volume factor between 0 and 1, default 0.7, that determines the responsiveness of the moving average.
        /// @param seriesType The price type on which the T3MA is calculated, typically 'close'.
        /// @param intervalAmount The number of data points to retrieve, representing the output size.
        /// @return A vector containing <dateTime, t3maValue> pairs for each interval, where 't3maValue' represents the T3MA at the corresponding dateTime.
        std::vector<std::string> T3MA(std::string symbol, std::string intervalLength, int timePeriod = 9, double vFactor = 0.7, std::string seriesType = "close", std::string intervalAmount = "30");
        /// @brief Calculates the Triple Exponential Moving Average (TEMA), which provides a smoother and more responsive moving average by applying triple exponential smoothing.
        ///        TEMA reduces lag and enhances trend detection, making it more suitable for identifying market directions in a timely manner.
        ///        The calculation of TEMA involves single, double, and triple exponential smoothing of the price data.
        ///        TEMA = 3 * EMA(Price) - 3 * EMA(EMA(Price)) + EMA(EMA(EMA(Price)))
        ///        This formula ensures that the TEMA reacts faster to price changes compared to traditional moving averages, thereby reducing the inherent lag.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param timePeriod Number of periods over which the TEMA is calculated, typically 9.
        /// @param seriesType The price type on which the TEMA is calculated, typically 'close'.
        /// @param intervalAmount The number of data points to retrieve, representing the output size.
        /// @return A vector containing <dateTime, temaValue> pairs for each interval, where 'temaValue' represents the TEMA at the corresponding dateTime.
        std::vector<std::string> TEMA(std::string symbol, std::string intervalLength, int timePeriod = 9, std::string seriesType = "close", std::string intervalAmount = "30");
        /// @brief Calculates the Triangular Moving Average (TRIMA), a smoother version of the simple moving average that places more weight on the middle portion of the time period.
        ///        TRIMA is calculated by taking the average of a simple moving average over a period and the simple moving average of that average.
        ///        This results in a weight distribution that is triangular in shape and emphasizes the central values of the time period.
        ///        TRIMA = SUM(SUM(Price, N), N) / ((N/2) * (N+1))
        ///        where N is the time period, and Price is typically the closing price.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param timePeriod Number of periods over which the TRIMA is calculated, typically 9.
        /// @param seriesType The price type on which the TRIMA is calculated, typically 'close'.
        /// @param intervalAmount The number of data points to retrieve, representing the output size.
        /// @return A vector containing <dateTime, trimaValue> pairs for each interval, where 'trimaValue' represents the TRIMA at the corresponding dateTime.
        std::vector<std::string> TRIMA(std::string symbol, std::string intervalLength, int timePeriod = 9, std::string seriesType = "close", std::string intervalAmount = "30");
        /// @brief Calculates the Time Series Forecast (TSF), which is based on linear regression of the closing prices and predicts future values.
        ///        TSF extends the concept of a linear regression line into the future, providing a forecast based on past price data.
        ///        The calculation involves fitting a linear regression trendline to the last N points and projecting it forward to forecast future values.
        ///        TSF = b0 + b1 * (Time Period) where b0 is the intercept and b1 is the slope of the regression line.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param timePeriod Number of periods used to calculate the TSF, typically 9.
        /// @param seriesType The price type on which the TSF is calculated, typically 'close'.
        /// @param intervalAmount The number of data points to retrieve, representing the output size.
        /// @return A vector containing <dateTime, tsfValue> pairs for each interval, where 'tsfValue' represents the forecasted value at the corresponding dateTime based on the TSF calculation.
        std::vector<std::string> TSF(std::string symbol, std::string intervalLength, int timePeriod = 9, std::string seriesType = "close", std::string intervalAmount = "30");
        /// @brief Calculates the Typical Price (TYPPRICE), which is the average of the high, low, and closing prices for each period.
        ///        The Typical Price provides a simplified view of a security's price movement and is often used as a component in other technical indicators.
        ///        TYPPRICE = (High + Low + Close) / 3
        ///        This simple average gives equal weight to the high, low, and closing prices, summarizing the price action of a single period into a single value.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param intervalAmount The number of data points to retrieve, representing the output size.
        /// @return A vector containing <dateTime, typpriceValue> pairs for each interval, where 'typpriceValue' represents the Typical Price at the corresponding dateTime.
        std::vector<std::string> TYPPRICE(std::string symbol, std::string intervalLength, std::string intervalAmount = "30");
        /// @brief Calculates the Ultimate Oscillator (ULTOSC), which incorporates three different time periods to improve the identification of overbought and oversold conditions.
        ///        The ULTOSC combines short, intermediate, and long-term market trends in one value, aiming to reduce false signals.
        ///        It is calculated by taking the weighted sum of three oscillators of different time periods, where each oscillator is the ratio of the true range over a given period.
        ///        ULTOSC = (4 * ULTOSC1 + 2 * ULTOSC2 + ULTOSC3) / (4 + 2 + 1)
        ///        where ULTOSC1, ULTOSC2, and ULTOSC3 are the oscillators for time periods 1, 2, and 3, respectively.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param timePeriod1 The first time period for the ULTOSC calculation, typically 7.
        /// @param timePeriod2 The second time period for the ULTOSC calculation, typically 14.
        /// @param timePeriod3 The third time period for the ULTOSC calculation, typically 28.
        /// @param intervalAmount The number of data points to retrieve, representing the output size.
        /// @return A vector containing <dateTime, ultoscValue> pairs for each interval, where 'ultoscValue' represents the Ultimate Oscillator value at the corresponding dateTime.
        std::vector<std::string> ULTOSC(std::string symbol, std::string intervalLength, int timePeriod1 = 7, int timePeriod2 = 14, int timePeriod3 = 28, std::string intervalAmount = "30");
        /// @brief Calculates the Variance (VAR), which measures the spread between data points in a dataset to determine how far each point is from the mean.
        ///        Variance is a statistical figure that represents the degree of spread in a dataset. A high variance indicates that the data points are spread out over a larger range of values, while a low variance indicates that the data points are closer to the mean.
        ///        VAR = (Σ(Xi - Xmean)²) / N
        ///        where Xi is each individual data point, Xmean is the mean of all data points, and N is the number of data points.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param timePeriod Number of periods over which the variance is calculated, typically 9.
        /// @param seriesType The price type on which the variance is calculated, typically 'close'.
        /// @param intervalAmount The number of data points to retrieve, representing the output size.
        /// @return A vector containing <dateTime, varianceValue> pairs for each interval, where 'varianceValue' represents the variance of the data points at the corresponding dateTime.
        std::vector<std::string> VAR(std::string symbol, std::string intervalLength, int timePeriod = 9, std::string seriesType = "close", std::string intervalAmount = "30");
        /// @brief Calculates the Volume Weighted Average Price (VWAP), a trading benchmark that gives the average price an instrument has traded at throughout the day, based on both volume and price.
        ///        VWAP is often used in trading and by algorithms to ensure trades are executed close to this average price to minimize market impact.
        ///        VWAP is calculated by adding up the dollar amount traded for every transaction (price multiplied by the number of shares traded) and then dividing by the total shares traded for the day.
        ///        VWAP = Σ(Price * Volume) / Σ(Volume)
        ///        where Price is the price of each trade, and Volume is the size of each trade.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param intervalAmount The number of data points to retrieve, representing the output size.
        /// @return A vector containing <dateTime, VWAP value> pairs for each interval, where 'VWAP value' represents the volume weighted average price at the corresponding dateTime.
        std::vector<std::string> VWAP(std::string symbol, std::string intervalLength, std::string intervalAmount = "30");
        /// @brief Calculates the Weighted Close Price (WCLPRICE), which smoothens the price data by taking into account the high, low, and close prices with a double weight on the closing price.
        ///        The formula for WCLPRICE is: (High + Low + 2 * Close) / 4. This indicator provides a more balanced view of the price movements throughout the interval, emphasizing the closing price.
        ///        WCLPRICE provides a single price point that accounts for the volatility within the interval by balancing the high, low, and closing prices, with an emphasis on the closing price.
        /// @param symbol Symbol for the company or asset you are inquiring about.
        /// @param intervalLength Length of a single period, such as 1min, 5min, 15min, etc.
        /// @param intervalAmount The number of data points to retrieve, representing the output size.
        /// @return A vector containing <dateTime, wclPrice> pairs for each interval, where 'wclPrice' is the calculated weighted close price at the corresponding dateTime.
        std::vector<std::string> WCLPRICE(std::string symbol, std::string intervalLength, std::string intervalAmount = "30");
        /// @brief Calculates the Williams %R, identifying overbought and oversold levels, and potentially signaling entry and exit points.
        ///        Williams %R oscillates between 0 and -100, where values above -20 are considered overbought and values below -80 are considered oversold.
        ///        WILLR = (Highest High - Close) / (Highest High - Lowest Low) * -100 .... for the last 'timePeriod' intervals
        /// @param symbol The ticker symbol for the asset.
        /// @param interval The time interval between data points (e.g., 1min, 5min, 15min, etc.).
        /// @param timePeriod The lookback period over which the highs and lows are considered, defaults to 9.
        /// @return A vector of <dateTime, WILLR value> pairs, indicating the Williams %R value at each time point.
        std::vector<std::string> WILLR(std::string symbol, std::string interval, int timePeriod = 9);
        
        
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
        double WeightedMovingAverage(double value, int timePeriod);
        double SimpleMovingAverage(double value, int timePeriod);




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