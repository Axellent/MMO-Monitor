#include <stdio.h>
#include "tradingpost.h"
#include "download.h"

void coinsToGems();
void gemsToCoins();

void getGW2ExchangeRates(){
	coinsToGems();
	gemsToCoins();
}

void getTopGW2CraftingMats(){
	getGW2Item(19725, "gw2data/ancient/Ancient_Wood_Log_Item");
	getGW2Item(19745, "gw2data/gossamer/Gossamer_Scrap_Item");
	getGW2Item(19732, "gw2data/hardened/Hardened_Leather_Section_Item");
	getGW2Item(19701, "gw2data/orichalcum/Orichalcum_Ore_Item");
}

void getTopGW2CraftingMatPrices(){
	getGW2ItemPrice("19725", "gw2data/ancient/Ancient_Wood_Log");
	getGW2ItemPrice("19745", "gw2data/gossamer/Gossamer_Scrap");
	getGW2ItemPrice("19732", "gw2data/hardened/Hardened_Leather_Section");
	getGW2ItemPrice("19701", "gw2data/orichalcum/Orichalcum_Ore");
}

void getGW2Item(int id, char *fileNamePrefix){
	char page[1000];
	sprintf(page, "https://api.guildwars2.com/v2/items/%d", id);

	getData(fileNamePrefix, ".json", page);	
}

void getGW2ItemPrice(char *ids, char *fileNamePrefix){
	char page[1000];
	sprintf(page, "https://api.guildwars2.com/v2/commerce/prices/%s", ids);

	getData(fileNamePrefix, ".json", page);
}

void getAllGW2Items(){
	getData("gw2data/items", ".json", "https://api.guildwars2.com/v2/items");
}

void coinsToGems(){
	getData("gw2data/coins/coins", ".json", "https://api.guildwars2.com/v2/commerce/exchange/coins?quantity=100000");
}

void gemsToCoins(){
	getData("gw2data/gems/gems", ".json", "https://api.guildwars2.com/v2/commerce/exchange/gems?quantity=100");
}

