#pragma once
#include "Item.h"
class CPlayer;
class CShop
{
public:
	CShop();
	virtual ~CShop();
private:
	void Initialize();
	void ItemBetterMake(const char* name, const CItem::ItemType& type, const int& att, const int& armor, const int& money);
public:
	void Process(CPlayer* player);
	void Free();
private:
	void Buy(CPlayer* player);
	void Sell(CPlayer* player);
private:
	list<CItem*> ItemList_Shop;
};

