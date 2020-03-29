#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"
#include "Item.h"
#include "GameObject.h"
#include "Stage.h"
#include "Shop.h"

CMainGame::CMainGame()
{
}

CMainGame::~CMainGame()
{	
	Free();
}

void CMainGame::start()
{
	char input = 0;
	
	while (1)
	{
		start:
		SYS_CLS;

		cout << "새로운 캐릭터를 만드시겠습니까? (y/n)";
		input = fgetc(stdin);

		SYS_CLS;

		if (input == 'y' || input == 'Y')
		{
			if (nullptr != m_pPlayer)
			{
				m_pPlayer->Free();
				delete m_pPlayer;
				m_pPlayer = nullptr;
			}

			NAME NameInfo;
			char Name[32] = "";

			cout << "플레이어의 이름? ";
			cin >> Name;

			NameInfo.pName = new char[strlen(Name) + 1];
			strcpy_s(NameInfo.pName, strlen(Name) + 1, Name);
			
			INFO PlayerInfo;

			selectClass(PlayerInfo);

			cout << " " << endl;

			SYS_PAUSE;

			switch (PlayerInfo.eClass)
			{
			case Warior:
			{
				char* className = "전사";
				NameInfo.pClassName = new char[strlen(className) + 1];
				strcpy_s(NameInfo.pClassName, strlen(className) + 1, className);
				break;
			}
			case Thief:
			{
				char* className = "도적";
				NameInfo.pClassName = new char[strlen(className) + 1];
				strcpy_s(NameInfo.pClassName, strlen(className) + 1, className);
				break;
			}
			case Wizard:
			{
				char* className = "법사";
				NameInfo.pClassName = new char[strlen(className) + 1];
				strcpy_s(NameInfo.pClassName, strlen(className) + 1, className);
				break;
			}
			}

			//플레이어 생성
			m_pPlayer = new CPlayer(PlayerInfo, NameInfo);
			m_pPlayer->Initialize();

			delete[] NameInfo.pClassName;
			delete[] NameInfo.pName;

			SYS_CLS;

			m_pPlayer->RenderInfo();
			
			
			while (1)
			{
				cout << "이대로 시작합니다. 계속하시겠습니까? (y/n)";
				cin >> input;
				cout << endl
					<< endl;
				if (input == 'y' || input == 'Y')
				{
					cout << "텍알에 오신걸 진심으로 환영합니다." << endl;
					SYS_PAUSE;
					break;
				}
				else if (input == 'n' || input == 'N')
				{
					SYS_CLS;
					rewind(stdin);
					goto start;
					break;
				}
				else
				{
					cout << "잘못된 입력입니다." << endl;
					rewind(stdin);
					continue;
				}
			}

			break;
		}
		else if (input == 'n' || input == 'N')
		{
			load();
			break;
		}
		else
		{
			cout << "잘못된 입력입니다. 처음으로 되돌아갑니다." << endl;
			rewind(stdin);
			SYS_PAUSE;
			continue;
		}
	}
}

void CMainGame::selectClass(INFO& Info)
{
	int ClassType;
	cout << endl 
		<< "플레이어의 직업?" << endl
		<< endl
		<< endl
		<< "1.전사(강인하지만. 멍청하다.)" << endl
		<< endl
		<< "2.도적(날렵하지만. 이도저도 아니다)" << endl
		<< endl
		<< "3.법사(약골이지만. 똑똑하다.)";

	while (1)
	{
		cin >> ClassType;

		cout << endl;

		switch (ClassType)
		{
		case Warior:
			cout << "당신은 꼴통 전사를 선택하였다. 물론 힘은 졸라쎔 ㅋ" << endl;
			Info.MaxHp = 50;
			Info.Str = 10;
			Info.Dex = 7;
			Info.Int = 2;
			break;
		case Thief:
			cout << "당신은 팔방미인 도적을 선택하였다. 물론 이도저도아니라 븅신임 ㅋ" << endl;
			Info.MaxHp = 35;
			Info.Str = 8;
			Info.Dex = 8;
			Info.Int = 2;
			break;
		case Wizard:
			cout << "당신은 고지능 법사를 선택하였다. 물론 힘은 졸라약골 ㅋ" << endl;
			Info.MaxHp = 20;
			Info.Str = 2;
			Info.Dex = 7;
			Info.Int = 10;
			break;
		default:
			cout << "잘못된 입력입니다." << endl;
			continue;
		}

		Info.Level = 1;
		Info.MaxExp = 20;
		Info.Exp = 0;
		Info.Money = 0;
		Info.eClass = (CLASS)ClassType;
		Info.ItemAtt = 0;
		Info.ItemArmor = 0;

		break;
	}
}

void CMainGame::process()
{
	while (1)
	{
		SYS_CLS;
		
		m_pPlayer->RenderInfo();
		
		int inputMenu = 0;
		cout << "1.던전으로 가기 2.상점 3.인벤토리 4.저장 5.불러오기 6.종료";
		cin >> inputMenu;

		switch (inputMenu)
		{
		case 1:
			cout << "던전으로 들어갑니다." << endl;
			SYS_PAUSE;
			dungeon();
			break;
		case 2:
		{
			cout << "상점으로 들어갑니다." << endl;
			SYS_PAUSE;
			shop();
			break;
		}
		case 3:
			cout << "인벤토리 창으로 이동합니다." << endl;
			SYS_PAUSE;
			Inventory();
			break;
		case 4:
			save();
			break;
		case 5:
			cout << "기존에 있는 파일의 정보를 불러옵니다." << endl;
			SYS_PAUSE;
			load();
			break;
		case 6:
			cout << "게임을 종료합니다." << endl;
			return;
		default:
			cout << "잘못된 입력" << endl;
			SYS_PAUSE;
			continue;
		}
	}
}

void CMainGame::dungeon()
{
	while (1)
	{
		SYS_CLS;

		int		inputStage;
		m_pPlayer->RenderInfo();

		cout << "가려고자 하는 던전을 입력하세요!" << endl
			 << endl;
		cout << "1. 수풀(초급)   2. 묘지(중급)   3. 지옥(고급)  4.메뉴로 돌아가기";
		cin >> inputStage;

		SYS_CLS;

		switch (inputStage)
		{
		case 1:
			cout << "수풀로 향합니다. (ㅎㅎ)" << endl;
			SYS_PAUSE;
			m_pStage = new CStage(CStage::Field);
			break;
		case 2:
			cout << "묘지로 향합니다." << endl;
			SYS_PAUSE;
			m_pStage = new CStage(CStage::Cemetry);
			break;
		case 3:
			cout << "지옥으로 향합니다. 각오하십시오?" << endl;
			SYS_PAUSE;
			m_pStage = new CStage(CStage::Hell);
			break;
		case 4:
			cout << "메뉴로 돌아갑니다." << endl;
			SYS_PAUSE;
			return;
		default:
			cout << "잘못된 입력" << endl;
			SYS_PAUSE;
			continue;
		}
	
		m_pStage->process(m_pPlayer);

		delete m_pStage;
		m_pStage = nullptr;
		break;
	}
}

void CMainGame::shop()
{
	m_pPlayer->GetRefInfo()->Money += 10000;
	if (nullptr == m_pShop)
	{
		m_pShop = new CShop();
	}
	m_pShop->Process(dynamic_cast<CPlayer*>(m_pPlayer));
}

void CMainGame::Inventory()
{
	while (1)
	{
		First:
		SYS_CLS;

		int input;
		int Num = 0;

		list<CItem*>* InvenList = dynamic_cast<CPlayer*>(m_pPlayer)->GetInventory();

		for (auto iter : *InvenList)
		{
			++Num;
			cout << Num << endl;
			iter->RenderInfo();
		}

		cout << endl;
		cout << "골드 : " << m_pPlayer->GetInfo().Money << endl
			<< endl;
		cout << "아이템의 숫자 입력 : 착용, 착용해제, 0. 돌아가기";
		cin >> input;

		if (0 == input)
		{
			cout << "메뉴로 돌아갑니다." << endl;
			SYS_PAUSE;
			return;
		}
		else
		{
			int SearchNum = 0;
			bool SearchCheck = false;

			//Search 함수 활용?
			for (auto iter : *InvenList)
			{

				++SearchNum;

				if (input == SearchNum)
				{
					//착용해제
					if (true == iter->GetEquipCheck())
					{
						iter->UnEquip(m_pPlayer->GetRefInfo());
						goto First;
					}

					//중복착용 확인
					switch (iter->GetItemType())
					{
					case CItem::ITEM_ARMOR:
					{
						for (auto iter : *InvenList)
						{
							if (CItem::ITEM_ARMOR == iter->GetItemType()
								&& true == iter->GetEquipCheck())
							{
								cout << "갑옷은 이미 착용중입니다! 중복 착용은 허용 안됩니다." << endl;
								SYS_PAUSE;
								goto First;
							}
						}
						break;
					}
					case CItem::ITEM_WEAPON:
					{
						for (auto iter : *InvenList)
						{
							if (CItem::ITEM_WEAPON == iter->GetItemType()
								&& true == iter->GetEquipCheck())
							{
								cout << "무기는 이미 착용중입니다! 중복 착용은 허용 안됩니다." << endl;
								SYS_PAUSE;
								goto First;
							}
						}
						break;
					}
					default :
					{
						cout << "무기 타입 오류 발생" << endl;
						SYS_PAUSE;
						return;
					}
					}

					if (false == iter->GetEquipCheck())
					{
						iter->Equip(m_pPlayer->GetRefInfo());
					}
					
					m_pPlayer->Initialize();
					SearchCheck = true;
				}
			}

			if (false == SearchCheck)
			{
				SYS_CLS;
				cout << "착용할 아이템이 존재하지 않습니다." << endl;

				SYS_PAUSE;
			}
		}
	}
}

void CMainGame::save()
{
	SYS_CLS;

	//플레이어 정보
	FILE* file;
	
	fopen_s(&file, "savefile.txt", "w");
	
	if (NULL == file)
	{
		cout << "저장 하는데 문제가 생겼습니다." << endl;
		SYS_PAUSE;
		return;
	}

	//이름
	NAME  tempStruct_Name = m_pPlayer->GetName();

	fputs(tempStruct_Name.pName, file);
	fputc('\0', file);
	fputs(tempStruct_Name.pClassName, file);
	fputc('\0', file);
	
	//정보
	INFO tempStruct_Info = m_pPlayer->GetInfo();

	fwrite(&tempStruct_Info, sizeof(INFO), 1, file);

	//인벤토리 정보
	list<CItem*>* InvenList = dynamic_cast<CPlayer*>(m_pPlayer)->GetInventory();
	for (auto iter : *InvenList)
	{
		//이름
		NAME  tempItem_Name = iter->GetName();

		fputs(tempItem_Name.pName, file);
		fputc('\0', file);

		//정보
		INFO tempItem_Info = iter->GetInfo();
		fwrite(&tempItem_Info, sizeof(INFO), 1, file);

		//분류
		fwrite(&iter->GetItemType(), sizeof(CItem::ItemType), 1, file);

		//착용여부
		fwrite(&iter->GetEquipCheck(), sizeof(bool), 1, file);
	}

	fclose(file);

	cout << "저장 완료!!" << endl;
	SYS_PAUSE;
	return;
}

void CMainGame::load()
{
	SYS_CLS;
	//플레이어 정보
	FILE* file;

	fopen_s(&file, "savefile.txt", "rt");
	
	if (NULL == file)
	{
		cout << "파일이 존재하지 않습니다!" << endl;
		SYS_PAUSE;
		return;
	}

	NAME tempName;

	char pTempName[128] = "";
	char pTempClassName[128] = "";

	for (int i = 0;; ++i)
	{
		char tempChar;
		tempChar = fgetc(file);

		if ('\0' == tempChar)
			break;

		pTempName[i] = tempChar;
	}

	for (int i = 0;; ++i)
	{
		char tempChar;
		tempChar = fgetc(file);

		if ('\0' == tempChar)
			break;

		pTempClassName[i] = tempChar;
	}

	tempName.pName = new char[strlen(pTempName) + 1];
	strcpy_s(tempName.pName, strlen(pTempName) + 1, pTempName);
	tempName.pClassName = new char[strlen(pTempClassName) + 1];
	strcpy_s(tempName.pClassName, strlen(pTempClassName) + 1, pTempClassName);

	INFO tempInfo;

	fread(&tempInfo, sizeof(INFO), 1, file);

	if (nullptr != m_pPlayer)
	{
		dynamic_cast<CPlayer*>(m_pPlayer)->ClearInventory();
		Free();
	}

	m_pPlayer = new CPlayer(tempInfo, tempName);

	//인벤토리
	while (1)
	{
		NAME tempName;

		char tempItemName[128] = "";

		for (int i = 0;; ++i)
		{
			char tempChar;
			tempChar = fgetc(file);

			if (EOF == tempChar)
				goto Finish;

			if ('\0' == tempChar)
				break;

			tempItemName[i] = tempChar;
		}

		tempName.pName = new char[strlen(tempItemName) + 1];
		strcpy_s(tempName.pName, strlen(tempItemName) + 1, tempItemName);

		INFO tempItemInfo;
		fread(&tempItemInfo, sizeof(INFO), 1, file);

		CItem* pItem = new CItem(tempItemInfo, tempName);

		//분류
		CItem::ItemType type;
		fread(&type, sizeof(CItem::ItemType), 1, file);
		pItem->SetItemType(type);

		//착용여부
		bool	EquipCheck;
		fread(&EquipCheck, sizeof(bool), 1, file);
		pItem->SetEquipCheck(EquipCheck);

		dynamic_cast<CPlayer*>(m_pPlayer)->ItemToInventory(pItem);

		delete[] tempName.pName;
	}

Finish:
	m_pPlayer->Initialize();

	fclose(file);

	delete[] tempName.pName;
	delete[] tempName.pClassName;

	cout << "불러오기 완료!" << endl;
	SYS_PAUSE;
	return;
}

void CMainGame::tempsave()
{
	SYS_CLS;

	//플레이어 정보
	FILE* file;

	fopen_s(&file, "savefile.txt", "w");

	if (NULL == file)
	{
		cout << "저장 하는데 문제가 생겼습니다." << endl;
		SYS_PAUSE;
		return;
	}

	//이름
	NAME  tempStruct_Name = m_pPlayer->GetName();

	fwrite(&tempStruct_Name, sizeof(NAME), 1, file);
	
	//정보
	INFO tempStruct_Info = m_pPlayer->GetInfo();

	fwrite(&tempStruct_Info, sizeof(INFO), 1, file);

	//인벤토리 정보
	list<CItem*>* InvenList = dynamic_cast<CPlayer*>(m_pPlayer)->GetInventory();
	
	int InvenSize = InvenList->size();
	fwrite(&InvenSize, sizeof(int), 1, file);
	
	for (auto iter : *InvenList)
	{
		//이름
		NAME  tempItem_Name = iter->GetName();
		fwrite(&tempItem_Name, sizeof(NAME), 1, file);

		//정보
		INFO tempItem_Info = iter->GetInfo();
		fwrite(&tempItem_Info, sizeof(INFO), 1, file);

		//분류
		fwrite(&iter->GetItemType(), sizeof(CItem::ItemType), 1, file);

		//착용여부
		fwrite(&iter->GetEquipCheck(), sizeof(bool), 1, file);
	}

	fclose(file);

	cout << "저장 완료!!" << endl;
	SYS_PAUSE;
	return;
}

void CMainGame::tempload()
{
	SYS_CLS;
	//플레이어 정보
	FILE* file;

	fopen_s(&file, "savefile.txt", "rt");

	if (NULL == file)
	{
		cout << "파일이 존재하지 않습니다!" << endl;
		SYS_PAUSE;
		return;
	}

	NAME tempName;

	fread(&tempName, sizeof(NAME), 1, file);
	
	INFO tempInfo;

	fread(&tempInfo, sizeof(INFO), 1, file);

	if (nullptr != m_pPlayer)
	{
		dynamic_cast<CPlayer*>(m_pPlayer)->ClearInventory();
		Free();
	}

	m_pPlayer = new CPlayer(tempInfo, tempName);

	int InvenSize = 0;
	fread(&InvenSize, sizeof(int), 1, file);

	//인벤토리
	for (int i = 0; i < InvenSize; ++i)
	{
		NAME tempName;
		fread(&tempName, sizeof(NAME), 1, file);

		INFO tempItemInfo;
		fread(&tempItemInfo, sizeof(INFO), 1, file);

		CItem* pItem = new CItem(tempItemInfo, tempName);

		//분류
		CItem::ItemType type;
		fread(&type, sizeof(CItem::ItemType), 1, file);
		pItem->SetItemType(type);

		//착용여부
		bool	EquipCheck;
		fread(&EquipCheck, sizeof(bool), 1, file);
		pItem->SetEquipCheck(EquipCheck);

		dynamic_cast<CPlayer*>(m_pPlayer)->ItemToInventory(pItem);
	}
	m_pPlayer->Initialize();

	fclose(file);

	cout << "불러오기 완료!" << endl;
	SYS_PAUSE;
	return;
}

void CMainGame::Free()
{
	if (nullptr != m_pPlayer)
	{
		m_pPlayer->Free();
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}

	if (nullptr != m_pStage)
	{
		m_pStage->Free();
		delete m_pStage;
		m_pStage = nullptr;
	}

	if (nullptr != m_pShop)
	{
		m_pShop->Free();
		delete m_pShop;
		m_pShop = nullptr;
	}
}
