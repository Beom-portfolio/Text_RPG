#include "stdafx.h"
#include "Item.h"

CItem::CItem()
{
}

CItem::CItem(INFO & Info, NAME & Name)
	:CGameObject(Info, Name)
{
}

CItem::~CItem()
{
}

void CItem::Initialize()
{
}

void CItem::RenderInfo()
{
	cout << "=============================================================================" << endl
		<< endl;

	cout << "아이템명 : " << m_pObjName->pName << endl;

	cout << "분류 : ";

	if (ITEM_ARMOR == Type)
		cout << "갑옷" << endl;
	else if (ITEM_WEAPON == Type)
		cout << "무기" << endl;
	else
		cout << "unknown" << endl;
	
	cout << endl;
	
	if (true == EquipCheck)
		cout << "착용중" << endl;
	else
		cout << "미착용" << endl;

	cout << "방어력 증가 : " << m_pObjInfo->Armor << endl;
	cout << "공격력 증가 : " << m_pObjInfo->Att << endl;
	cout << endl;

	cout << "=============================================================================" << endl
		<< endl;
}

void CItem::Equip(INFO * Info)
{
	SYS_CLS;

	EquipCheck = true;

	cout << m_pObjName->pName << "(을)를 착용 하였습니다!" << endl;

	switch (Type)
	{
	case ITEM_ARMOR:
		Info->ItemArmor += m_pObjInfo->Armor;
		break;
	case ITEM_WEAPON:
		Info->ItemAtt += m_pObjInfo->Att;
		break;
	}

	cout << "방어력이 " << m_pObjInfo->Armor << "만큼 증가하였습니다!" << endl;
	cout << "공격력이 " << m_pObjInfo->Att << "만큼 증가하였습니다!" << endl;

	SYS_PAUSE;
}

void CItem::UnEquip(INFO * Info)
{
	SYS_CLS;

	EquipCheck = false;

	cout << m_pObjName->pName << "(을)를 착용을 해제하였습니다!" << endl
		<< endl;

	switch (Type)
	{
	case ITEM_ARMOR:
		Info->ItemArmor -= m_pObjInfo->Armor;
		break;
	case ITEM_WEAPON:
		Info->ItemAtt -= m_pObjInfo->Att;
		break;
	}

	cout << "방어력이 " << m_pObjInfo->Armor << "만큼 감소하였습니다!" << endl;
	cout << "공격력이 " << m_pObjInfo->Att << "만큼 감소하였습니다!" << endl;

	SYS_PAUSE;
}
