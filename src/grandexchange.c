#include "grandexchange.h"
#include "download.h"

void getTopRunescapeCraftingMatPrices(){
	getData("../runescapedata/runite_ore/Runite_Ore", ".json", "http://services.runescape.com/m=itemdb_rs/api/catalogue/detail.json?item=451");
	getData("../runescapedata/elder_log/Elder_Log", ".json", "http://services.runescape.com/m=itemdb_rs/api/catalogue/detail.json?item=29556");
	getData("../runescapedata/royal_dragonhide/Royal_Dragonhide", ".json", "http://services.runescape.com/m=itemdb_rs/api/catalogue/detail.json?item=24372");
	getData("../runescapedata/coal/Coal", ".json", "http://services.runescape.com/m=itemdb_rs/api/catalogue/detail.json?item=453");
	getData("../runescapedata/nature_rune/Nature_Rune", ".json", "http://services.runescape.com/m=itemdb_rs/api/catalogue/detail.json?item=561");
	getData("../runescapedata/pure_essence/Pure_Essence", ".json", "http://services.runescape.com/m=itemdb_rs/api/catalogue/detail.json?item=7936");

}

void getHistoricalCraftingMatPrices(){
	getData("../runescapedata/Runite_Ore_Hist", ".json", "http://services.runescape.com/m=itemdb_rs/api/graph/451.json");
	getData("../runescapedata/Elder_Log_Hist", ".json", "http://services.runescape.com/m=itemdb_rs/api/graph/29556.json");
	getData("../runescapedata/Royal_Dragonhide_Hist", ".json", "http://services.runescape.com/m=itemdb_rs/api/graph/24372.json");
	getData("../runescapedata/Coal_Hist", ".json", "http://services.runescape.com/m=itemdb_rs/api/graph/453.json");
	getData("../runescapedata/Nature_Rune_Hist", ".json", "http://services.runescape.com/m=itemdb_rs/api/graph/561.json");
	getData("../runescapedata/Pure_Essence_Hist", ".json", "http://services.runescape.com/m=itemdb_rs/api/graph/7936.json");
}

void getBondPrice(){
	getData("../runescapedata/bond/Bond", ".json", "http://services.runescape.com/m=itemdb_rs/api/catalogue/detail.json?item=29492");
}

void getHistoricalBondPrices(){
	getData("../runescapedata/Bond_Hist", ".json", "http://services.runescape.com/m=itemdb_rs/api/graph/29492.json");
}

