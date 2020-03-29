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

	cout << "당신은 ";

	switch (Type)
	{
	case Field:
		cout << "들판에서 ";
		break;
	case Cemetry:
		cout << "묘지에서 ";
		break;
	case Hell:
		cout << "지옥에서 ";
		break;
	default:
		cout << "오류 !" << endl;
		SYS_PAUSE;
		return -1;
	}

	cout << m_pMonster->GetName().pName << " (을)를 만났다! 전투준비!!" << endl;
	SYS_PAUSE;

	while (1)
	{
		if (0 >= player->GetInfo().Hp)
		{
			SYS_CLS;
			cout << "당신은 죽었습니다. 메뉴로 돌아갑니다." << endl;
			SYS_PAUSE;
			player->Initialize();
			return 0;
		}
		else if (0 >= m_pMonster->GetInfo().Hp)
		{
			SYS_CLS;
			cout << "당신은 " << m_pMonster->GetName().pName << "(을)를 잡았습니다!" << endl;
			cout << "경험치 : " << m_pMonster->GetInfo().Exp << "Exp 획득!" << endl;
			cout << "골드 : " << m_pMonster->GetInfo().Money << "Gold 획득!" << endl;

			SYS_PAUSE;

			//레벨업 체크
			dynamic_cast<CPlayer*>(player)->BattleEnd(m_pMonster->GetInfo().Exp, m_pMonster->GetInfo().Money);
			player->Initialize();

			SYS_CLS;
			while (1)
			{
				rewind(stdin);

				char chInput;
				cout << endl << "사냥을 계속하시겠습니까? (y/n)" << endl;
				chInput = fgetc(stdin);

				if (chInput == 'y' || chInput == 'Y')
				{
					cout << "사냥을 계속합니다!." << endl;
					SYS_PAUSE;
					return 1;
				}
				else if (chInput == 'n' || chInput == 'N')
				{
					cout << "메뉴로 돌아갑니다." << endl;
					SYS_PAUSE;
					return 0;
				}
				else
				{
					cout << "잘못된 입력!" << endl;
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

		cout << "동작을 선택하세요." << endl;
		cout << "1. 공격 2. 회피 3. 도망 ";
		cin >> input;

		switch (input)
		{
		case 1:
			//공격
			//플레이어 공격
			cout << "당신은 " << m_pMonster->GetName().pName << "를 공격하였다!!" << endl;
			
			if (m_pMonster->GetInfo().Armor >= player->GetInfo().Att)
			{
				cout << "공격이 빚나갔다!! "  << m_pMonster->GetName().pName << "(은)는 아무런 데미지도 입지 않았다!!" << endl;
			}
			else
			{
				*player -= *m_pMonster;
				cout << m_pMonster->GetName().pName << "(은)는 " << player->GetInfo().Att << "의 데미지를 입었다!" << endl
					<< endl;
			}
			//몬스터 공격
			if (player->GetInfo().Armor >= m_pMonster->GetInfo().Att)
			{
				cout << "당신은 견뎌냈다! "  << "당신은 아무런 데미지도 입지 않았다!!" << endl;
			}
			else
			{
				cout << m_pMonster->GetName().pName << "은(는) " << "당신을 공격하였다!!" << endl;
				*m_pMonster -= *player;
				cout << "당신은 " << m_pMonster->GetInfo().Att << "의 데미지를 입었다!" << endl;
			}
			SYS_PAUSE;
			break;
		case 2:
			//회피
			//일정 확률로 회피
			cout << "당신은 회피를 시도했다!!" << endl;
			int percentage;
			percentage = rand() % 101;
			
			if (percentage < 30)
			{
				cout << "회피에 성공하였다!!" << endl;
				if (m_pMonster->GetInfo().Armor >= player->GetInfo().Att)
				{
					cout << "공격이 빚나갔다!! " << m_pMonster->GetName().pName << "(은)는 아무런 데미지도 입지 않았다!!" << endl;
				}
				else
				{
					*player -= *m_pMonster;
					cout << m_pMonster->GetName().pName << "(은)는 " << player->GetInfo().Att << "의 데미지를 입었다!" << endl
						<< endl;
				}
			}
			else
			{
				cout << "회피에 실패했다!" << endl;
				//몬스터 공격
				if (player->GetInfo().Armor >= m_pMonster->GetInfo().Att)
				{
					cout << "당신은 견뎌냈다! " << "당신은 아무런 데미지도 입지 않았다!!" << endl;
				}
				else
				{
					cout << m_pMonster->GetName().pName << "은(는) " << "당신을 공격하였다!!" << endl;
					*m_pMonster -= *player;
					cout << "당신은 " << m_pMonster->GetInfo().Att << "의 데미지를 입었다!" << endl;
				}
			}
			SYS_PAUSE;
			break;
		case 3:
			//도망
			cout << "도망갑니다!!! 마을로 이동합니다." << endl;
			SYS_PAUSE;
			return 0;
		default:
			cout << "잘못된 입력!" << endl;
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
			char* monName = "들쥐";
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
			char* monName = "버섯돌이";
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
			char* monName = "엑스스텀프";
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
			cout << "오류 발생 !" << endl;
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
			char* monName = "해골병사";
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
			char* monName = "마녀";
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
			char* monName = "유령";
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
			cout << "오류 발생!" << endl;
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
			char* monName = "타락한 데몬";
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
			char* monName = "타락을 반복한 천사 루시퍼";
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
			char* monName = "악랄한 지옥견 헬하운드";
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
			cout << "오류 발생!" << endl;
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
