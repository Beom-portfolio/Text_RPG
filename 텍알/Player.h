#pragma once
#include "GameObject.h"

class CItem;
class CPlayer
	:public CGameObject
{
public:
	CPlayer();
	CPlayer(INFO& Info, NAME& Name);
	~CPlayer();
public:
	list<CItem*>* GetInventory()
	{
		return &Inventory;
	}
public:
	virtual void Initialize();
	virtual void RenderInfo();
public:
	void BattleEnd(const int& Exp, const int& Money);
	void ItemToInventory(CItem* item);
	void ClearInventory();
private:
	list<CItem*> Inventory;
};

