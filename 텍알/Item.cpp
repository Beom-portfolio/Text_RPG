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

	cout << "�����۸� : " << m_pObjName->pName << endl;

	cout << "�з� : ";

	if (ITEM_ARMOR == Type)
		cout << "����" << endl;
	else if (ITEM_WEAPON == Type)
		cout << "����" << endl;
	else
		cout << "unknown" << endl;
	
	cout << endl;
	
	if (true == EquipCheck)
		cout << "������" << endl;
	else
		cout << "������" << endl;

	cout << "���� ���� : " << m_pObjInfo->Armor << endl;
	cout << "���ݷ� ���� : " << m_pObjInfo->Att << endl;
	cout << endl;

	cout << "=============================================================================" << endl
		<< endl;
}

void CItem::Equip(INFO * Info)
{
	SYS_CLS;

	EquipCheck = true;

	cout << m_pObjName->pName << "(��)�� ���� �Ͽ����ϴ�!" << endl;

	switch (Type)
	{
	case ITEM_ARMOR:
		Info->ItemArmor += m_pObjInfo->Armor;
		break;
	case ITEM_WEAPON:
		Info->ItemAtt += m_pObjInfo->Att;
		break;
	}

	cout << "������ " << m_pObjInfo->Armor << "��ŭ �����Ͽ����ϴ�!" << endl;
	cout << "���ݷ��� " << m_pObjInfo->Att << "��ŭ �����Ͽ����ϴ�!" << endl;

	SYS_PAUSE;
}

void CItem::UnEquip(INFO * Info)
{
	SYS_CLS;

	EquipCheck = false;

	cout << m_pObjName->pName << "(��)�� ������ �����Ͽ����ϴ�!" << endl
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

	cout << "������ " << m_pObjInfo->Armor << "��ŭ �����Ͽ����ϴ�!" << endl;
	cout << "���ݷ��� " << m_pObjInfo->Att << "��ŭ �����Ͽ����ϴ�!" << endl;

	SYS_PAUSE;
}
