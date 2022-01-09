#pragma once

#include<iostream>
#include<curl/curl.h>
#include<string>
#include<nlohmann/json.hpp>
#include<vector>




static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
std::string recurl(std::string url)
{
    std::string readBuffer;
    auto curl = curl_easy_init();
    if (curl) 
    {

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

class indicators
{
    std::string key = "65QTFITRMOI848RD";
public:

    std::string SMA(std::string name,std::string key)
    {
        std::string var;
        std::string url = "https://www.alphavantage.co/query?function=SMA&symbol="+name+"&interval=1min&time_period=10&series_type=open&apikey="+key;
        std::string response = recurl(url.c_str());
        std::cout << response<<"\n\n\n";
        nlohmann::json j = nlohmann::json::parse(response);
        
        for (auto it = j.begin(); it != j.end(); it++)
            for (auto& elem : j["Technical Analysis: SMA"])
            {
                var = elem["SMA"];
                
            }
                
        return var;
    }
    std::string OBV(std::string name, std::string key)
    {
        std::string var;
        std::string url="https://www.alphavantage.co/query?function=OBV&symbol=" + name + "&interval=1min&apikey="+key;
        std::string response = recurl(url.c_str());
        nlohmann::json j = nlohmann::json::parse(response);
        for (auto it = j.begin(); it != j.end(); it++)
            for (auto& elem : j["Technical Analysis: OBV"])
            {
                var = elem["OBV"];

            }

        return var;
    }
    std::string EMA(std::string name, std::string key)
    {
        std::string var;
        std::string url = "https://www.alphavantage.co/query?function=EMA&symbol=" + name + "&interval=1min&time_period=50&series_type=open&apikey="+key;
        std::string response = recurl(url.c_str());
        nlohmann::json j = nlohmann::json::parse(response);
        for (auto it = j.begin(); it != j.end(); it++)
            for (auto& elem : j["Technical Analysis: SMA"])
            {
                var = elem["SMA"];

            }

        return var;
    }
    std::string ADX(std::string name, std::string key)
    {
        std::string var;
        std::string url="https://www.alphavantage.co/query?function=ADX&symbol="+name+"&interval=1min&time_period=10&apikey="+key;
        std::string response = recurl(url.c_str());
        nlohmann::json j = nlohmann::json::parse(response);
        for (auto it = j.begin(); it != j.end(); it++)
            for (auto& elem : j["Technical Analysis: ADX"])
            {
                var = elem["ADX"];

            }

        return var;
    }
    std::string AroO(std::string name, std::string key)
    {
        std::string var, var2;
        std::string url="https://www.alphavantage.co/query?function=AROON&symbol="+name+"&interval=1min&time_period=14&apikey="+key;
        std::string response = recurl(url.c_str());
        nlohmann::json j = nlohmann::json::parse(response);
        for (auto it = j.begin(); it != j.end(); it++)
            for (auto& elem : j["Technical Analysis: AROON"])
            {
                var = elem["Aroon Up"];
                var2 = elem["Aroon Down"];

            }

        return var,var2;
        
    }
  
    std::string RSI(std::string name, std::string key)
    {
        std::string var;
        std::string url = "https://www.alphavantage.co/query?function=RSI&symbol=" + name + "&interval=1min&time_period=10&series_type=open&apikey="+key;
        std::string response = recurl(url.c_str());
        nlohmann::json j = nlohmann::json::parse(response);
        for(auto it = j.begin(); it != j.end(); it++)
            for (auto& elem : j["Technical Analysis: RSI"])
            {
                var = elem["RSI"];

            }

        return var;
    }
    std::string SO(std::string name, std::string key)
    {
        std::string var,var2;
        std::string url = "https://www.alphavantage.co/query?function=STOCH&symbol="+name+"&interval=1min&apikey="+key;
        std::string response = recurl(url.c_str());
        nlohmann::json j = nlohmann::json::parse(response);
        for (auto it = j.begin(); it != j.end(); it++)
            for (auto& elem : j["Technical Analysis: STOCH"])
            {
                var = elem["SlowD"];
                var2 = elem["SlowK"];
            }

        return var,var2;
    }
};