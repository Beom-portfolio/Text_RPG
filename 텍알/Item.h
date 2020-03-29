#pragma once
#include "GameObject.h"
class CItem :
	public CGameObject
{
public:
	enum ItemType{ITEM_ARMOR, ITEM_WEAPON, ITEM_END};
public:
	CItem();
	CItem(INFO& Info, NAME& Name);
	virtual ~CItem();
public:
	void SetItemType(const ItemType& type) { Type = type; }
	void SetEquipCheck(const bool& check) { EquipCheck = check; }
public:
	const bool& GetEquipCheck() { return EquipCheck; }
	const ItemType& GetItemType() { return Type; }
public:
	virtual void Initialize();
	virtual void RenderInfo();
public:
	void Equip(INFO* Info);
	void UnEquip(INFO* Info);
private:
	bool			EquipCheck = false;
	ItemType Type = ITEM_END;
};

