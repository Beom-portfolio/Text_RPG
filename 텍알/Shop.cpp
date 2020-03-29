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
	//상점 아이템을 추가한다.
	if (!ItemList_Shop.empty())
		return;
	else
	{
		//Armor
		ItemBetterMake("구멍난 조끼", CItem::ITEM_ARMOR, 0, 50, 100);
		ItemBetterMake("평범한 갑옷", CItem::ITEM_ARMOR, 0, 150, 500);
		ItemBetterMake("황제가 입었던 견고한 황금갑옷", CItem::ITEM_ARMOR, 0, 500, 5000);

		//Weapon
		ItemBetterMake("반쯤 나간 곡검", CItem::ITEM_WEAPON, 100, 0, 500);
		ItemBetterMake("금간 글라디우스", CItem::ITEM_WEAPON, 250, 0, 1000);
		ItemBetterMake("금간 글라디우스", CItem::ITEM_WEAPON, 500, 0, 2500);
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

		cout << "---------------------상점----------------------" << endl
			<< endl;

		cout << "원하는 거래를 선택하세요! 돈 : " << player->GetInfo().Money << endl;
		cout << "1. 사기   2. 팔기   3.나가기 " << endl;
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
			cout << "상점을 나옵니다." << endl;
			SYS_PAUSE;
			return;
		default:
			cout << "잘못된 입력!" << endl;
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

		//사기
		cout << "원하는 아이템을 골라주세요~" << endl;

		int Input;
		int ItemNum = 0;

		for (auto iter : ItemList_Shop)
		{
			++ItemNum;
			cout << ItemNum << endl;
			cout << "가격 : " << iter->GetInfo().Money << endl;
			iter->RenderInfo();
		}

		cout << "돈 : " << player->GetInfo().Money << endl;
		cout << "아이템 번호 입력 : 사기  0. 나가기 " << endl;
		cin >> Input;

		if (0 == Input)
		{
			cout << "처음으로 돌아갑니다." << endl;
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
					cout << "돈 : " << player->GetInfo().Money << endl;
					cout << "구입 하시겠습니까? 1.예 2.아니오" << endl;
					cin >> Choice;

					switch (Choice)
					{
					case 1:
					{
						if (iter->GetInfo().Money > player->GetInfo().Money)
						{
							cout << "돈이 부족합니다!!" << endl;
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

							cout << "구입 완료!!" << endl;
							SYS_PAUSE;
							goto First;
						}
					}
					case 2:
						return;
					default:
						cout << "잘못된 입력!" << endl;
						SYS_PAUSE;
						continue;
					}
				}
			}
		}

		cout << "없는 아이템 번호입니다!" << endl;
		SYS_PAUSE;
	}
}

void CShop::Sell(CPlayer * player)
{
	while (1)
	{
		First:

		//팔기
		SYS_CLS;
		cout << "팔려하는 아이템을 골라주세요~" << endl;
		int Input;
		int ItemNum = 0;
		for (auto iter : *player->GetInventory())
		{
			++ItemNum;
			cout << ItemNum << endl;
			iter->RenderInfo();
		}
		cout << "돈 : " << player->GetInfo().Money << endl;
		cout << "아이템 선택 : 팔기  0. 나가기" << endl;
		cin >> Input;

		if (0 == Input)
		{
			cout << "처음으로 돌아갑니다." << endl;
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
					cout << "돈 : " << player->GetInfo().Money << endl;
					cout << "판매 하시겠습니까? 1.예 2.아니오" << endl;
					cin >> Choice;

					switch (Choice)
					{
					case 1:
					{
						player->GetRefInfo()->Money += iter->GetInfo().Money;
						player->GetInventory()->remove(iter);

						cout << "판매 완료!!" << endl;
						SYS_PAUSE;
						goto First;
					}
					case 2:
						return;
					default:
						cout << "잘못된 입력!" << endl;
						SYS_PAUSE;
						continue;
					}
				}
			}
		}
	}
}
