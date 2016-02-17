#ifndef TRADINGPOST_H_INCLUDED
#define TRADINGPOST_H_INCLUDED

void getGW2ExchangeRates();
void getTopGW2CraftingMats();
void getTopGW2CraftingMatPrices();
void getGW2Item(int id, char *fileNamePrefix);
void getGW2ItemPrice(char *ids, char *fileNamePrefix);
void getAllGW2Items();

#endif
