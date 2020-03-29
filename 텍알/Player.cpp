#include "stdafx.h"
#include "Player.h"
#include "Item.h"


CPlayer::CPlayer()
{
}

CPlayer::CPlayer(INFO & Info, NAME & Name)
	:CGameObject(Info, Name)
{
}

CPlayer::~CPlayer()
{
}


void CPlayer::Initialize()
{
	//�ʱ�ȭ?
	m_pObjInfo->Hp = m_pObjInfo->MaxHp;
	//Att�� ��� ����
	switch (m_pObjInfo->eClass)
	{
	case Warior:
		m_pObjInfo->Armor = int(20 + (m_pObjInfo->Str * 3) + (m_pObjInfo->Dex * 2) + (m_pObjInfo->Int * 1.5));
		m_pObjInfo->Att = 10 + (m_pObjInfo->Str * 4) + (m_pObjInfo->Dex * 2) + (m_pObjInfo->Int * 0);
		break;
	case Thief:
		m_pObjInfo->Armor = int(15 + (m_pObjInfo->Str * 3) + (m_pObjInfo->Dex * 2.5) + (m_pObjInfo->Int * 1.5));
		m_pObjInfo->Att = 15 + (m_pObjInfo->Str * 2) + (m_pObjInfo->Dex * 2) + (m_pObjInfo->Int * 2);
		break;
	case Wizard:
		m_pObjInfo->Armor = int(10 + (m_pObjInfo->Str * 3) + (m_pObjInfo->Dex * 2.5) + (m_pObjInfo->Int * 1.5));
		m_pObjInfo->Att = 20 + (m_pObjInfo->Str * 0) + (m_pObjInfo->Dex * 2) + (m_pObjInfo->Int * 4);
		break;
	}

	//���� ���ο� ���� ItemAtt, ItemArmor ����
	m_pObjInfo->ItemArmor = 0;
	m_pObjInfo->ItemAtt = 0;

	//�˻�
	for (auto iter : Inventory)
	{
		if (true == iter->GetEquipCheck())
		{
			switch (iter->GetItemType())
			{
			case CItem::ITEM_ARMOR:
				m_pObjInfo->ItemArmor += iter->GetInfo().Armor;
				break;
			case CItem::ITEM_WEAPON:
				m_pObjInfo->ItemAtt += iter->GetInfo().Att;
				break;
			}
		}
	}

	m_pObjInfo->Armor += m_pObjInfo->ItemArmor;
	m_pObjInfo->Att += m_pObjInfo->ItemAtt;
}

void CPlayer::RenderInfo()
{
	Initialize();

	cout << "=====================Player Info=======================" << endl
		<< endl;


	cout << "�÷��̾� �̸� : " << m_pObjName->pName << endl;
	cout << "�÷��̾� ���� : " << m_pObjName->pClassName << endl;
	cout << "Level : " << m_pObjInfo->Level << endl;
	cout << "ü�� : " << m_pObjInfo->Hp << endl;
	cout << "�� : " << m_pObjInfo->Str << endl;
	cout << "��ø : " << m_pObjInfo->Dex << endl;
	cout << "���� : " << m_pObjInfo->Int << endl;
	cout << "Att : " << m_pObjInfo->Att << endl;
	cout << "Armor : " << m_pObjInfo->Armor << endl << endl;

}

void CPlayer::BattleEnd(const int & Exp, const int & Money)
{
	m_pObjInfo->Money += Money;
	m_pObjInfo->Exp += Exp;

	while(1)
	{ 
		if (m_pObjInfo->Exp >= m_pObjInfo->MaxExp)
		{
			cout << "�����!!!!" << endl
				<< endl;
			m_pObjInfo->Level += 1;
			
			cout << "������ �����ϴ�!" << endl
				<< endl;
			m_pObjInfo->MaxHp = int(m_pObjInfo->MaxHp * 1.5);

			switch (m_pObjInfo->eClass)
			{
			case Warior:
				if (0 == m_pObjInfo->Level % 2)
				{
					cout << "���� +1 �� �˴ϴ�!!" << endl;
					cout << "��ø�� +1 �� �˴ϴ�!!" << endl;

					m_pObjInfo->Str += 1;
					m_pObjInfo->Dex += 1;
				}
				else
				{
					cout << "���� +1 �� �˴ϴ�!!" << endl;
					m_pObjInfo->Str += 1;
				}
				break;
			case Thief:
				if (0 == m_pObjInfo->Level % 2)
				{
					cout << "���� +1 �� �˴ϴ�!!" << endl;
					cout << "��ø�� +1 �� �˴ϴ�!!" << endl;
					cout << "������ +1 �� �˴ϴ�!!" << endl;

					m_pObjInfo->Str += 1;
					m_pObjInfo->Dex += 1;
					m_pObjInfo->Int += 1;
				}
				else
				{
					cout << "��ø�� +1 �� �˴ϴ�!!" << endl;
					m_pObjInfo->Dex += 1;
				}
				break;
			case Wizard:
				if (0 == m_pObjInfo->Level % 2)
				{
					cout << "��ø�� +1 �� �˴ϴ�!!" << endl;
					cout << "������ +1�� �˴ϴ�!!" << endl;

					m_pObjInfo->Dex += 1;
					m_pObjInfo->Int += 1;
				}
				else
				{
					cout << "������ +1 �� �˴ϴ�!!" << endl;
					m_pObjInfo->Int += 1;
				}
				break;
			}

			m_pObjInfo->Exp -= m_pObjInfo->MaxExp;
			m_pObjInfo->MaxExp = int(m_pObjInfo->MaxExp * 1.25);
			
			SYS_PAUSE;
		}
		else
		{
			break;
		}
	}
}

void CPlayer::ItemToInventory(CItem * item)
{
	Inventory.push_back(item);
}

void CPlayer::ClearInventory()
{
	if (!Inventory.empty())
	{
		for (auto& iter : Inventory)
		{
			iter->Free();
			delete iter;
			iter = nullptr;
		}

		Inventory.clear();
	}
}
