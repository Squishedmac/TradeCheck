#include <iostream>
#include <string>
#include <curl/curl.h>
#include<nlohmann/json.hpp>
#include<ctime>
#include"dpdcs.h"
using namespace std;
using namespace nlohmann;



void tickercheck(string name)
{
    string url2 = "https://api.polygon.io/v3/reference/tickers?ticker="+name+"&active=true&sort=ticker&order=asc&limit=10&apiKey=SKAtADU48sQOIXhIY0mb8KZ3dwIXA1yT";
    string result = recurl(url2);
    cout << result;
}

bool response(string name,float CurVal,string key)
{
    indicators indi;
    cout << "\n";
    string res2;
    string res= indi.SMA(name,key);
    float SMA= stof(res);
    if (CurVal < SMA)
        return false;
     res = indi.EMA(name, key);
    float EMA = stof(res);
    if (EMA < SMA)
        return false;
    
     res = indi.ADX(name, key);
    float ADX = stof(res);
    if (ADX < 20)
        return false;
     res,res2 = indi.AroO(name, key);
    float AroOU = stof(res);
    float AroOD = stof(res2);
    if (AroOD > AroOU)
        return false;
    res = indi.RSI(name, key);
    float RSI = stof(res);
    if (RSI < 50)
        return false;
    return true;
}

void main()
{

    
    string name="AAPL";
    tickercheck(name);
    //we use cURL to obtain the json file as a string
    auto curl = curl_easy_init();
    struct tm nowLocal;
    time_t now = time(0);
    localtime_s(&nowLocal,&now);
 
    int year = (nowLocal.tm_year + 1900);
    int month = (nowLocal.tm_mon + 1);
    int day = (nowLocal.tm_mday);
    int prev_day = (nowLocal.tm_mday - 1);
    string dtm = to_string(year) + '-' +'0'+ to_string(month) + '-' + '0' + to_string(day);
    string ydtm = to_string(year) + '-' + '0' + to_string(month) + '-' + '0' + to_string(prev_day);
    string url = "https://api.polygon.io/v2/aggs/ticker/"+name+"/range/1/minute/"+ "2022-01-07" + "/" + dtm + "?adjusted=true&sort=asc&limit=120&apiKey='polygon.io key'";
   
    string key = "your key";
    string readBuffer = recurl(url);
    float elem1;
    vector<float>Entries;
    json j=json::parse(readBuffer);
    for (auto it = j.begin(); it != j.end();it++)
        for (auto& elem : j["results"])
            Entries.push_back(elem["c"]);
        cout << "\n";
        elem1 = Entries[0];
    bool evaluate =response(name,elem1,key);
    cout << "\n"<<evaluate;


}
