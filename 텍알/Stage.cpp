#include "stdafx.h"
#include "Stage.h"
#include "GameObject.h"
#include "Monster.h"
#include "Player.h"

CStage::CStage()
{
}

CStage::CStage(const DungeonType & type)
	:Type(type)
{
}

CStage::~CStage()
{
}

void CStage::process(CGameObject* player)
{
	while (1)
	{
		Free();
		SpawnMonster();

		int check = Battle(player);

		if (1 == check)
			continue;
		else
			break;
	}
}

int CStage::Battle(CGameObject* player)
{
	SYS_CLS;

	cout << "����� ";

	switch (Type)
	{
	case Field:
		cout << "���ǿ��� ";
		break;
	case Cemetry:
		cout << "�������� ";
		break;
	case Hell:
		cout << "�������� ";
		break;
	default:
		cout << "���� !" << endl;
		SYS_PAUSE;
		return -1;
	}

	cout << m_pMonster->GetName().pName << " (��)�� ������! �����غ�!!" << endl;
	SYS_PAUSE;

	while (1)
	{
		if (0 >= player->GetInfo().Hp)
		{
			SYS_CLS;
			cout << "����� �׾����ϴ�. �޴��� ���ư��ϴ�." << endl;
			SYS_PAUSE;
			player->Initialize();
			return 0;
		}
		else if (0 >= m_pMonster->GetInfo().Hp)
		{
			SYS_CLS;
			cout << "����� " << m_pMonster->GetName().pName << "(��)�� ��ҽ��ϴ�!" << endl;
			cout << "����ġ : " << m_pMonster->GetInfo().Exp << "Exp ȹ��!" << endl;
			cout << "��� : " << m_pMonster->GetInfo().Money << "Gold ȹ��!" << endl;

			SYS_PAUSE;

			//������ üũ
			dynamic_cast<CPlayer*>(player)->BattleEnd(m_pMonster->GetInfo().Exp, m_pMonster->GetInfo().Money);
			player->Initialize();

			SYS_CLS;
			while (1)
			{
				rewind(stdin);

				char chInput;
				cout << endl << "����� ����Ͻðڽ��ϱ�? (y/n)" << endl;
				chInput = fgetc(stdin);

				if (chInput == 'y' || chInput == 'Y')
				{
					cout << "����� ����մϴ�!." << endl;
					SYS_PAUSE;
					return 1;
				}
				else if (chInput == 'n' || chInput == 'N')
				{
					cout << "�޴��� ���ư��ϴ�." << endl;
					SYS_PAUSE;
					return 0;
				}
				else
				{
					cout << "�߸��� �Է�!" << endl;
					SYS_PAUSE;
					continue;
				}
			}
		}
		SYS_CLS;

		int input;
		
		player->RenderInfo();
		m_pMonster->RenderInfo();

		cout << endl
			 << endl;

		cout << "������ �����ϼ���." << endl;
		cout << "1. ���� 2. ȸ�� 3. ���� ";
		cin >> input;

		switch (input)
		{
		case 1:
			//����
			//�÷��̾� ����
			cout << "����� " << m_pMonster->GetName().pName << "�� �����Ͽ���!!" << endl;
			
			if (m_pMonster->GetInfo().Armor >= player->GetInfo().Att)
			{
				cout << "������ ��������!! "  << m_pMonster->GetName().pName << "(��)�� �ƹ��� �������� ���� �ʾҴ�!!" << endl;
			}
			else
			{
				*player -= *m_pMonster;
				cout << m_pMonster->GetName().pName << "(��)�� " << player->GetInfo().Att << "�� �������� �Ծ���!" << endl
					<< endl;
			}
			//���� ����
			if (player->GetInfo().Armor >= m_pMonster->GetInfo().Att)
			{
				cout << "����� �ߵ��´�! "  << "����� �ƹ��� �������� ���� �ʾҴ�!!" << endl;
			}
			else
			{
				cout << m_pMonster->GetName().pName << "��(��) " << "����� �����Ͽ���!!" << endl;
				*m_pMonster -= *player;
				cout << "����� " << m_pMonster->GetInfo().Att << "�� �������� �Ծ���!" << endl;
			}
			SYS_PAUSE;
			break;
		case 2:
			//ȸ��
			//���� Ȯ���� ȸ��
			cout << "����� ȸ�Ǹ� �õ��ߴ�!!" << endl;
			int percentage;
			percentage = rand() % 101;
			
			if (percentage < 30)
			{
				cout << "ȸ�ǿ� �����Ͽ���!!" << endl;
				if (m_pMonster->GetInfo().Armor >= player->GetInfo().Att)
				{
					cout << "������ ��������!! " << m_pMonster->GetName().pName << "(��)�� �ƹ��� �������� ���� �ʾҴ�!!" << endl;
				}
				else
				{
					*player -= *m_pMonster;
					cout << m_pMonster->GetName().pName << "(��)�� " << player->GetInfo().Att << "�� �������� �Ծ���!" << endl
						<< endl;
				}
			}
			else
			{
				cout << "ȸ�ǿ� �����ߴ�!" << endl;
				//���� ����
				if (player->GetInfo().Armor >= m_pMonster->GetInfo().Att)
				{
					cout << "����� �ߵ��´�! " << "����� �ƹ��� �������� ���� �ʾҴ�!!" << endl;
				}
				else
				{
					cout << m_pMonster->GetName().pName << "��(��) " << "����� �����Ͽ���!!" << endl;
					*m_pMonster -= *player;
					cout << "����� " << m_pMonster->GetInfo().Att << "�� �������� �Ծ���!" << endl;
				}
			}
			SYS_PAUSE;
			break;
		case 3:
			//����
			cout << "�������ϴ�!!! ������ �̵��մϴ�." << endl;
			SYS_PAUSE;
			return 0;
		default:
			cout << "�߸��� �Է�!" << endl;
			SYS_PAUSE;
			continue;
		}
	}
}

void CStage::SpawnMonster()
{
	int randNum = 0;
	srand(unsigned(time(NULL)));
	randNum = rand() % 3;

	INFO MonInfo;
	NAME MonName;

	switch (Type)
	{
	case Field:
	{
		switch (randNum)
		{
		case Rat_Mon:
		{
			//Name
			char* monName = "����";
			MonName.pName = new char[strlen(monName) + 1];
			strcpy_s(MonName.pName, strlen(monName) + 1, monName);
			//Info
			MonInfo.MaxHp = 10;
			MonInfo.Exp = 5;
			MonInfo.Money = 10;
			MonInfo.Att = 7;
			MonInfo.Armor = 0;
			break;
		}
		case MushRoom_Mon:
		{
			//Name
			char* monName = "��������";
			MonName.pName = new char[strlen(monName) + 1];
			strcpy_s(MonName.pName, strlen(monName) + 1, monName);
			//Info
			MonInfo.MaxHp = 20;
			MonInfo.Exp = 7;
			MonInfo.Money = 15;
			MonInfo.Att = 13;
			MonInfo.Armor = 0;
			break;
		}
		case Tree_Mon:
		{
			//Name
			char* monName = "����������";
			MonName.pName = new char[strlen(monName) + 1];
			strcpy_s(MonName.pName, strlen(monName) + 1, monName);
			//Info
			MonInfo.MaxHp = 30;
			MonInfo.Exp = 10;
			MonInfo.Money = 20;
			MonInfo.Att = 16;
			MonInfo.Armor = 0;
			break;
		}
		default:
			cout << "���� �߻� !" << endl;
			SYS_PAUSE;
			return;
		}
		break;
	}
	case Cemetry:
	{
		switch (randNum)
		{
		case Skeleton_Mon:
		{
			//Name
			char* monName = "�ذ񺴻�";
			MonName.pName = new char[strlen(monName) + 1];
			strcpy_s(MonName.pName, strlen(monName) + 1, monName);
			//Info
			MonInfo.MaxHp = 35;
			MonInfo.Exp = 15;
			MonInfo.Money = 50;
			MonInfo.Att = 15;
			MonInfo.Armor = 10;
			break;
		}
		case Whitch_Mon:
		{
			//Name
			char* monName = "����";
			MonName.pName = new char[strlen(monName) + 1];
			strcpy_s(MonName.pName, strlen(monName) + 1, monName);
			//Info
			MonInfo.MaxHp = 45;
			MonInfo.Exp = 25;
			MonInfo.Money = 75;
			MonInfo.Att = 25;
			MonInfo.Armor = 30;
			break;
		}
		case Ghost_Mon:
		{
			//Name
			char* monName = "����";
			MonName.pName = new char[strlen(monName) + 1];
			strcpy_s(MonName.pName, strlen(monName) + 1, monName);
			//Info
			MonInfo.MaxHp = 55;
			MonInfo.Exp = 35;
			MonInfo.Money = 100;
			MonInfo.Att = 40;
			MonInfo.Armor = 50;
			break;
		}
		default:
			cout << "���� �߻�!" << endl;
			SYS_PAUSE;
			return;
		}
		break;
	}
	case Hell:
	{
		switch (randNum)
		{
		case Demon_Mon:
		{
			//Name
			char* monName = "Ÿ���� ����";
			MonName.pName = new char[strlen(monName) + 1];
			strcpy_s(MonName.pName, strlen(monName) + 1, monName);
			//Info
			MonInfo.MaxHp = 100;
			MonInfo.Exp = 150;
			MonInfo.Money = 1000;
			MonInfo.Att = 100;
			MonInfo.Armor = 60;
			break;
		}
		case Lucifer_Mon:
		{
			//Name
			char* monName = "Ÿ���� �ݺ��� õ�� �����";
			MonName.pName = new char[strlen(monName) + 1];
			strcpy_s(MonName.pName, strlen(monName) + 1, monName);
			//Info
			MonInfo.MaxHp = 200;
			MonInfo.Exp = 250;
			MonInfo.Money = 2000;
			MonInfo.Att = 250;
			MonInfo.Armor = 60;
			break;
		}
		case Hell_Hound_Mon:
		{
			//Name
			char* monName = "�Ƕ��� ������ ���Ͽ��";
			MonName.pName = new char[strlen(monName) + 1];
			strcpy_s(MonName.pName, strlen(monName) + 1, monName);
			//Info
			MonInfo.MaxHp = 300;
			MonInfo.Exp = 350;
			MonInfo.Money = 5000;
			MonInfo.Att = 350;
			MonInfo.Armor = 60;
			break;
		}
		default:
			cout << "���� �߻�!" << endl;
			SYS_PAUSE;
			return;
		}
		break;
	}
	}

	MonInfo.Hp = MonInfo.MaxHp;
	
	m_pMonster = new CMonster(MonInfo, MonName);

	if (nullptr != MonName.pName)
	{
		delete[] MonName.pName;
		MonName.pName = nullptr;
	}
}

void CStage::Free()
{
	if (nullptr != m_pMonster)
	{
		m_pMonster->Free();
		delete m_pMonster;
		m_pMonster = nullptr;
	}
}
