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