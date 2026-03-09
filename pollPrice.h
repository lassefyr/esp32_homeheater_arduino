#ifndef POLLPRICE_H
#define POLLPRICE_H

class ReadPrice {
private:
  bool needRd = true;
  float curPr[96]; // 96 slots (15 min intervals for 24 hours)
  int clkDev = 0;
  float limP = 0.07;
  const char* url = "https://api.spot-hinta.fi/Today";

  // Helper to calculate array index from Hour and Minute
  int getQIndex(int hours, int mins);
  void calcLimitFromPrices();


public:
    ReadPrice();
    void setLim(float value);
    float getLim();
    float getCurrPrice(int myH);
    int getInd();
    int getCH();
    float getPriceNow();
    void forceUpd();
    void checkIfUpd(int hour = -1);

    // ... other data ...
};

#endif