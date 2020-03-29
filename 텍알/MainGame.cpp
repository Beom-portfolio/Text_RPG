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

		cout << "���ο� ĳ���͸� ����ðڽ��ϱ�? (y/n)";
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

			cout << "�÷��̾��� �̸�? ";
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
				char* className = "����";
				NameInfo.pClassName = new char[strlen(className) + 1];
				strcpy_s(NameInfo.pClassName, strlen(className) + 1, className);
				break;
			}
			case Thief:
			{
				char* className = "����";
				NameInfo.pClassName = new char[strlen(className) + 1];
				strcpy_s(NameInfo.pClassName, strlen(className) + 1, className);
				break;
			}
			case Wizard:
			{
				char* className = "����";
				NameInfo.pClassName = new char[strlen(className) + 1];
				strcpy_s(NameInfo.pClassName, strlen(className) + 1, className);
				break;
			}
			}

			//�÷��̾� ����
			m_pPlayer = new CPlayer(PlayerInfo, NameInfo);
			m_pPlayer->Initialize();

			delete[] NameInfo.pClassName;
			delete[] NameInfo.pName;

			SYS_CLS;

			m_pPlayer->RenderInfo();
			
			
			while (1)
			{
				cout << "�̴�� �����մϴ�. ����Ͻðڽ��ϱ�? (y/n)";
				cin >> input;
				cout << endl
					<< endl;
				if (input == 'y' || input == 'Y')
				{
					cout << "�ؾ˿� ���Ű� �������� ȯ���մϴ�." << endl;
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
					cout << "�߸��� �Է��Դϴ�." << endl;
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
			cout << "�߸��� �Է��Դϴ�. ó������ �ǵ��ư��ϴ�." << endl;
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
		<< "�÷��̾��� ����?" << endl
		<< endl
		<< endl
		<< "1.����(����������. ��û�ϴ�.)" << endl
		<< endl
		<< "2.����(����������. �̵����� �ƴϴ�)" << endl
		<< endl
		<< "3.����(���������. �ȶ��ϴ�.)";

	while (1)
	{
		cin >> ClassType;

		cout << endl;

		switch (ClassType)
		{
		case Warior:
			cout << "����� ���� ���縦 �����Ͽ���. ���� ���� ���� ��" << endl;
			Info.MaxHp = 50;
			Info.Str = 10;
			Info.Dex = 7;
			Info.Int = 2;
			break;
		case Thief:
			cout << "����� �ȹ���� ������ �����Ͽ���. ���� �̵������ƴ϶� ����� ��" << endl;
			Info.MaxHp = 35;
			Info.Str = 8;
			Info.Dex = 8;
			Info.Int = 2;
			break;
		case Wizard:
			cout << "����� ������ ���縦 �����Ͽ���. ���� ���� ������ ��" << endl;
			Info.MaxHp = 20;
			Info.Str = 2;
			Info.Dex = 7;
			Info.Int = 10;
			break;
		default:
			cout << "�߸��� �Է��Դϴ�." << endl;
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
		cout << "1.�������� ���� 2.���� 3.�κ��丮 4.���� 5.�ҷ����� 6.����";
		cin >> inputMenu;

		switch (inputMenu)
		{
		case 1:
			cout << "�������� ���ϴ�." << endl;
			SYS_PAUSE;
			dungeon();
			break;
		case 2:
		{
			cout << "�������� ���ϴ�." << endl;
			SYS_PAUSE;
			shop();
			break;
		}
		case 3:
			cout << "�κ��丮 â���� �̵��մϴ�." << endl;
			SYS_PAUSE;
			Inventory();
			break;
		case 4:
			save();
			break;
		case 5:
			cout << "������ �ִ� ������ ������ �ҷ��ɴϴ�." << endl;
			SYS_PAUSE;
			load();
			break;
		case 6:
			cout << "������ �����մϴ�." << endl;
			return;
		default:
			cout << "�߸��� �Է�" << endl;
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

		cout << "�������� �ϴ� ������ �Է��ϼ���!" << endl
			 << endl;
		cout << "1. ��Ǯ(�ʱ�)   2. ����(�߱�)   3. ����(���)  4.�޴��� ���ư���";
		cin >> inputStage;

		SYS_CLS;

		switch (inputStage)
		{
		case 1:
			cout << "��Ǯ�� ���մϴ�. (����)" << endl;
			SYS_PAUSE;
			m_pStage = new CStage(CStage::Field);
			break;
		case 2:
			cout << "������ ���մϴ�." << endl;
			SYS_PAUSE;
			m_pStage = new CStage(CStage::Cemetry);
			break;
		case 3:
			cout << "�������� ���մϴ�. �����Ͻʽÿ�?" << endl;
			SYS_PAUSE;
			m_pStage = new CStage(CStage::Hell);
			break;
		case 4:
			cout << "�޴��� ���ư��ϴ�." << endl;
			SYS_PAUSE;
			return;
		default:
			cout << "�߸��� �Է�" << endl;
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
		cout << "��� : " << m_pPlayer->GetInfo().Money << endl
			<< endl;
		cout << "�������� ���� �Է� : ����, ��������, 0. ���ư���";
		cin >> input;

		if (0 == input)
		{
			cout << "�޴��� ���ư��ϴ�." << endl;
			SYS_PAUSE;
			return;
		}
		else
		{
			int SearchNum = 0;
			bool SearchCheck = false;

			//Search �Լ� Ȱ��?
			for (auto iter : *InvenList)
			{

				++SearchNum;

				if (input == SearchNum)
				{
					//��������
					if (true == iter->GetEquipCheck())
					{
						iter->UnEquip(m_pPlayer->GetRefInfo());
						goto First;
					}

					//�ߺ����� Ȯ��
					switch (iter->GetItemType())
					{
					case CItem::ITEM_ARMOR:
					{
						for (auto iter : *InvenList)
						{
							if (CItem::ITEM_ARMOR == iter->GetItemType()
								&& true == iter->GetEquipCheck())
							{
								cout << "������ �̹� �������Դϴ�! �ߺ� ������ ��� �ȵ˴ϴ�." << endl;
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
								cout << "����� �̹� �������Դϴ�! �ߺ� ������ ��� �ȵ˴ϴ�." << endl;
								SYS_PAUSE;
								goto First;
							}
						}
						break;
					}
					default :
					{
						cout << "���� Ÿ�� ���� �߻�" << endl;
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
				cout << "������ �������� �������� �ʽ��ϴ�." << endl;

				SYS_PAUSE;
			}
		}
	}
}

void CMainGame::save()
{
	SYS_CLS;

	//�÷��̾� ����
	FILE* file;
	
	fopen_s(&file, "savefile.txt", "w");
	
	if (NULL == file)
	{
		cout << "���� �ϴµ� ������ ������ϴ�." << endl;
		SYS_PAUSE;
		return;
	}

	//�̸�
	NAME  tempStruct_Name = m_pPlayer->GetName();

	fputs(tempStruct_Name.pName, file);
	fputc('\0', file);
	fputs(tempStruct_Name.pClassName, file);
	fputc('\0', file);
	
	//����
	INFO tempStruct_Info = m_pPlayer->GetInfo();

	fwrite(&tempStruct_Info, sizeof(INFO), 1, file);

	//�κ��丮 ����
	list<CItem*>* InvenList = dynamic_cast<CPlayer*>(m_pPlayer)->GetInventory();
	for (auto iter : *InvenList)
	{
		//�̸�
		NAME  tempItem_Name = iter->GetName();

		fputs(tempItem_Name.pName, file);
		fputc('\0', file);

		//����
		INFO tempItem_Info = iter->GetInfo();
		fwrite(&tempItem_Info, sizeof(INFO), 1, file);

		//�з�
		fwrite(&iter->GetItemType(), sizeof(CItem::ItemType), 1, file);

		//���뿩��
		fwrite(&iter->GetEquipCheck(), sizeof(bool), 1, file);
	}

	fclose(file);

	cout << "���� �Ϸ�!!" << endl;
	SYS_PAUSE;
	return;
}

void CMainGame::load()
{
	SYS_CLS;
	//�÷��̾� ����
	FILE* file;

	fopen_s(&file, "savefile.txt", "rt");
	
	if (NULL == file)
	{
		cout << "������ �������� �ʽ��ϴ�!" << endl;
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

	//�κ��丮
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

		//�з�
		CItem::ItemType type;
		fread(&type, sizeof(CItem::ItemType), 1, file);
		pItem->SetItemType(type);

		//���뿩��
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

	cout << "�ҷ����� �Ϸ�!" << endl;
	SYS_PAUSE;
	return;
}

void CMainGame::tempsave()
{
	SYS_CLS;

	//�÷��̾� ����
	FILE* file;

	fopen_s(&file, "savefile.txt", "w");

	if (NULL == file)
	{
		cout << "���� �ϴµ� ������ ������ϴ�." << endl;
		SYS_PAUSE;
		return;
	}

	//�̸�
	NAME  tempStruct_Name = m_pPlayer->GetName();

	fwrite(&tempStruct_Name, sizeof(NAME), 1, file);
	
	//����
	INFO tempStruct_Info = m_pPlayer->GetInfo();

	fwrite(&tempStruct_Info, sizeof(INFO), 1, file);

	//�κ��丮 ����
	list<CItem*>* InvenList = dynamic_cast<CPlayer*>(m_pPlayer)->GetInventory();
	
	int InvenSize = InvenList->size();
	fwrite(&InvenSize, sizeof(int), 1, file);
	
	for (auto iter : *InvenList)
	{
		//�̸�
		NAME  tempItem_Name = iter->GetName();
		fwrite(&tempItem_Name, sizeof(NAME), 1, file);

		//����
		INFO tempItem_Info = iter->GetInfo();
		fwrite(&tempItem_Info, sizeof(INFO), 1, file);

		//�з�
		fwrite(&iter->GetItemType(), sizeof(CItem::ItemType), 1, file);

		//���뿩��
		fwrite(&iter->GetEquipCheck(), sizeof(bool), 1, file);
	}

	fclose(file);

	cout << "���� �Ϸ�!!" << endl;
	SYS_PAUSE;
	return;
}

void CMainGame::tempload()
{
	SYS_CLS;
	//�÷��̾� ����
	FILE* file;

	fopen_s(&file, "savefile.txt", "rt");

	if (NULL == file)
	{
		cout << "������ �������� �ʽ��ϴ�!" << endl;
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

	//�κ��丮
	for (int i = 0; i < InvenSize; ++i)
	{
		NAME tempName;
		fread(&tempName, sizeof(NAME), 1, file);

		INFO tempItemInfo;
		fread(&tempItemInfo, sizeof(INFO), 1, file);

		CItem* pItem = new CItem(tempItemInfo, tempName);

		//�з�
		CItem::ItemType type;
		fread(&type, sizeof(CItem::ItemType), 1, file);
		pItem->SetItemType(type);

		//���뿩��
		bool	EquipCheck;
		fread(&EquipCheck, sizeof(bool), 1, file);
		pItem->SetEquipCheck(EquipCheck);

		dynamic_cast<CPlayer*>(m_pPlayer)->ItemToInventory(pItem);
	}
	m_pPlayer->Initialize();

	fclose(file);

	cout << "�ҷ����� �Ϸ�!" << endl;
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
