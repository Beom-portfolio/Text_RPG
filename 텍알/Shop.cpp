#include "stdafx.h"
#include "Shop.h"
#include "Player.h"


CShop::CShop()
{
	Initialize();
}

CShop::~CShop()
{
}

void CShop::Initialize()
{
	//���� �������� �߰��Ѵ�.
	if (!ItemList_Shop.empty())
		return;
	else
	{
		//Armor
		ItemBetterMake("���۳� ����", CItem::ITEM_ARMOR, 0, 50, 100);
		ItemBetterMake("����� ����", CItem::ITEM_ARMOR, 0, 150, 500);
		ItemBetterMake("Ȳ���� �Ծ��� �߰��� Ȳ�ݰ���", CItem::ITEM_ARMOR, 0, 500, 5000);

		//Weapon
		ItemBetterMake("���� ���� ���", CItem::ITEM_WEAPON, 100, 0, 500);
		ItemBetterMake("�ݰ� �۶��콺", CItem::ITEM_WEAPON, 250, 0, 1000);
		ItemBetterMake("�ݰ� �۶��콺", CItem::ITEM_WEAPON, 500, 0, 2500);
	}
}

void CShop::ItemBetterMake(const char * name, const CItem::ItemType& type, const int & att, const int & armor, const int & money)
{
	NAME tempName;
	INFO tempInfo;

	tempName.pName = new char[strlen(name) + 1];
	strcpy_s(tempName.pName, strlen(name) + 1, name);

	tempInfo.Att = att;
	tempInfo.Armor = armor;
	tempInfo.Money = money;

	CItem* pItem = new CItem(tempInfo, tempName);
	pItem->SetItemType(type);
	ItemList_Shop.push_back(pItem);

	delete[] tempName.pName;
}

void CShop::Process(CPlayer* player)
{
	while (1)
	{
		SYS_CLS;

		int Input;

		cout << "---------------------����----------------------" << endl
			<< endl;

		cout << "���ϴ� �ŷ��� �����ϼ���! �� : " << player->GetInfo().Money << endl;
		cout << "1. ���   2. �ȱ�   3.������ " << endl;
		cin >> Input;

		switch (Input)
		{
		case 1:
			Buy(player);
			break;
		case 2:
			Sell(player);
			break;
		case 3:
			cout << "������ ���ɴϴ�." << endl;
			SYS_PAUSE;
			return;
		default:
			cout << "�߸��� �Է�!" << endl;
			SYS_PAUSE;
			continue;
		}
	}

	

}

void CShop::Free()
{
	if (!ItemList_Shop.empty())
	{
		for (auto& iter : ItemList_Shop)
		{
			iter->Free();
			delete iter;
			iter = nullptr;
		}

		ItemList_Shop.clear();
	}
}

void CShop::Buy(CPlayer * player)
{
	while (1)
	{
		First:
		SYS_CLS;

		//���
		cout << "���ϴ� �������� ����ּ���~" << endl;

		int Input;
		int ItemNum = 0;

		for (auto iter : ItemList_Shop)
		{
			++ItemNum;
			cout << ItemNum << endl;
			cout << "���� : " << iter->GetInfo().Money << endl;
			iter->RenderInfo();
		}

		cout << "�� : " << player->GetInfo().Money << endl;
		cout << "������ ��ȣ �Է� : ���  0. ������ " << endl;
		cin >> Input;

		if (0 == Input)
		{
			cout << "ó������ ���ư��ϴ�." << endl;
			SYS_PAUSE;
			return;
		}
		 
		
		ItemNum = 0;

		SYS_CLS;
		for (auto iter : ItemList_Shop)
		{
			++ItemNum;
			if (Input == ItemNum)
			{
				while (1)
				{
					int Choice;

					iter->RenderInfo();
					cout << "�� : " << player->GetInfo().Money << endl;
					cout << "���� �Ͻðڽ��ϱ�? 1.�� 2.�ƴϿ�" << endl;
					cin >> Choice;

					switch (Choice)
					{
					case 1:
					{
						if (iter->GetInfo().Money > player->GetInfo().Money)
						{
							cout << "���� �����մϴ�!!" << endl;
							SYS_PAUSE;
							return;
						}
						else
						{
							player->GetRefInfo()->Money -= iter->GetInfo().Money;
							NAME tempName;
							INFO tempInfo;

							tempName.pName = new char[strlen(iter->GetName().pName) + 1];
							strcpy_s(tempName.pName, strlen(iter->GetName().pName) + 1, iter->GetName().pName);

							tempInfo.Armor = iter->GetInfo().Armor;
							tempInfo.Att = iter->GetInfo().Att;
							tempInfo.Money = iter->GetInfo().Money;
							CItem* pItem = new CItem(tempInfo, tempName);
							pItem->SetItemType(iter->GetItemType());

							player->ItemToInventory(pItem);

							delete[] tempName.pName;

							cout << "���� �Ϸ�!!" << endl;
							SYS_PAUSE;
							goto First;
						}
					}
					case 2:
						return;
					default:
						cout << "�߸��� �Է�!" << endl;
						SYS_PAUSE;
						continue;
					}
				}
			}
		}

		cout << "���� ������ ��ȣ�Դϴ�!" << endl;
		SYS_PAUSE;
	}
}

void CShop::Sell(CPlayer * player)
{
	while (1)
	{
		First:

		//�ȱ�
		SYS_CLS;
		cout << "�ȷ��ϴ� �������� ����ּ���~" << endl;
		int Input;
		int ItemNum = 0;
		for (auto iter : *player->GetInventory())
		{
			++ItemNum;
			cout << ItemNum << endl;
			iter->RenderInfo();
		}
		cout << "�� : " << player->GetInfo().Money << endl;
		cout << "������ ���� : �ȱ�  0. ������" << endl;
		cin >> Input;

		if (0 == Input)
		{
			cout << "ó������ ���ư��ϴ�." << endl;
			SYS_PAUSE;
			return;
		}

		ItemNum = 0;

		SYS_CLS;
		for (auto& iter : *player->GetInventory())
		{
			++ItemNum;
			if (Input == ItemNum)
			{
				while (1)
				{
					int Choice;

					iter->RenderInfo();
					cout << "�� : " << player->GetInfo().Money << endl;
					cout << "�Ǹ� �Ͻðڽ��ϱ�? 1.�� 2.�ƴϿ�" << endl;
					cin >> Choice;

					switch (Choice)
					{
					case 1:
					{
						player->GetRefInfo()->Money += iter->GetInfo().Money;
						player->GetInventory()->remove(iter);

						cout << "�Ǹ� �Ϸ�!!" << endl;
						SYS_PAUSE;
						goto First;
					}
					case 2:
						return;
					default:
						cout << "�߸��� �Է�!" << endl;
						SYS_PAUSE;
						continue;
					}
				}
			}
		}
	}
}
