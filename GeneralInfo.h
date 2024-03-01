#ifndef GENERALINFO_H
#define GENERALINFO_H

#include <string>
#include <vector>


class GeneralInfo{
    
    public:
        std::vector<std::string> valuesTS;
        std::vector<std::string> valuesER;
        //TIME SERIES GETTERS

        //TIME SRIES --> setting info into vector for 1 big interval starting from current time and backwards  

        //fetch and return open price that was set in the array 'genTSValues' via setter function. 
        //(openPrice = fetched open price from very last interval)
        //clear array after done
        int getOpenTS();
        //fetch and return high price that was set in the array 'genTSValues' via setter function
        //compare every single high in each interval. Take and return highest value.
        //clear array after done
        int getHighTS();
        //fetch and return low price that was set in the array 'genTSValues' via setter function
        //compare every single low in each interval. Take and return the lowest value
        //clear array after done
        int getLowTS();
        //fetch and return close price that was set in the array 'genTSValues' via setter function
        //closePrice = close price of the second interval. Why second? --> Edge case issue. Better accuracy 
        //clear array after done
        int getCloseTS();
        //fetch and return volume price that was set in the array 'genTSValues' via setter function
        //sum of all volumes across all intervals
        //clear array after done
        int getVolumeTS();


        //TIME SERIES --> getting info for MULTIPLE intervals requested

        //iterate through array and fetch timeStamp for each interval. Ordering from current time --> before current time
        //cout or put in an array
        std::vector<std::string> getTimeStampTS();
        //iterate through array and fetch every single highPrice value. Ordering from current time --> before current time
        //return as a vector. Clear 'genTSValues'
        std::vector<double> getAllHighTS();
        //iterate through array and fetch every single lowPrice value. Ordering from current time --> before current time
        //cout or put in an array. Clear 'genTSValues'
        std::vector<double> getAllLowTS();
        //iterate through array and fetch every single closePrice value. Ordering from current time --> before current time
        //cout or put in an array. Clear 'genTSValues'
        std::vector<double> getAllCloseTS();
        //iterate through array and fetch every single volume value. Ordering from current time --> before current time
        //cout or put in an array. Clear 'genTSValues'
        std::vector<double> getAllVolumeTS();


        //EXCHANGE RATE GETTERS (DONT NEED?)

        //fetch exchange rate from vector 'valuesER' ..... 2nd element
        //clear 'valuesER'
        double getStockExchangeRateER();
        //fetch time stamp in readable form. 
        //Param: Unix timestamp in seconds. 
        //Time stamp should be 3rd element in 'valuesER'
        //clear 'valuesER'
        std::string getTimeStampER(int seconds);



        //CURRENCY CONVERSION GETTERS   (OVERWRITES EXCHANGE RATE?)
        
        //get exchange rate of two currencies. 2nd element in vector 'valuesCC'
        double getCurrencyExchangeRateCC();
        //get currency exchange amount from two currencies. How much is 5 USD in CAD? 3rd element in 'valuesCC' vector
        double getCurrencyExchangeAmountCC();
        //get time as a string given unix time in seconds
        std::string getTimeStampCC(int seconds);



        //REAL TIME PRICE
        double getRealTimePriceRTP(std::string symbol);

    

        //TIME SERIES SETTERS

        /*  Given company symbol and interval length. Interval observed will be: current time --> (current time - interval).
            Run the http request, use WriteCallBack() and WriteToJson() to read and write to .json file
            Use Parse function to read the .json file and put TSValues all in the array 'genTSValues'
        */
        void setValuesTS(std::string symbol, std::string intervalLength); 
        /*  Given company symbol, interval length, and number of intervals. all the values of each interval will be placed in array consecutively
            Run the http request, use WriteCallBack() and WriteToJson() to read and write to .json file
            Use Parse function to read the .json file and put TSValues all in the array 'genTSValues'
        */
        void setValuesTS(std::string symbol, std::string intervalLength, std::string intervalAmount);


        //EXCHANGE RATE SETTERS (DONT NEED?)

        /*  Given company symbol1 and another company symbol2, and a specific dateTimeString. 
            Run http request, use WriteCallback() and WriteToJson() to read and write to .json file
            Put all values in array vector 'valuesER'..... <symbol1/symbol2, exchange rate, unix timestamp>
        */
        void setValuesER(std::string symbol1, std::string symbol2, std::string dateTimeString);
        /*  Given company symbol1 and another company symbol2. (http request will return local exchange time) 
            Run http request, use WriteCallback() and WriteToJson() to read and write to .json file
            Put all values in array vector 'valuesER'..... <symbol1/symbol2, exchange rate, unix timestamp>
        */
        void setValuesER(std::string symbol1, std::string symbol2);



        //CURRENCY CONVERSION SETTERS (OVERWRITES EXCHANGE RATE?)

        /*  Given company symbol1 and another company symbol2, and amount. (http request will return local exchange time) 
            Run http request, use WriteCallback() and WriteToJson() to read and write to .json file
            Put all values in array vector 'valuesCC'..... <symbol1/symbol2, exchange rate, amount,  unix timestamp>
        */
        void setValuesCC(std::string symbol1, std::string symbol2, double amount);
        /*  Given company symbol1 and another company symbol2, amount, and dateTimeString. (http request will return rate & amount at specified time) 
            Run http request, use WriteCallback() and WriteToJson() to read and write to .json file
            Put all values in array vector 'valuesCC'..... <symbol1/symbol2, exchange rate, amount, unix timestamp>
        */
        void setValuesCC(std::string symbol1, std::string symbol2, double amount, std::string dateTimeString);

        //HELPER FUNCTIONS
        std::string ConvertFromUnixTime(std::string unixTime);
    private:
        bool ValidateDateTime(const std::string& dateTimeString);

        // std::string ConvertFromUnixTime(std::string unixTime);
};


#endif