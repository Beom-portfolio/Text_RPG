#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}

CMonster::CMonster(INFO & Info, NAME & Name)
	:CGameObject(Info, Name)
{
}


CMonster::~CMonster()
{
}

void CMonster::Initialize()
{

}

void CMonster::RenderInfo()
{
	cout << endl 
		 << endl;
	cout << "========================Monster Info==========================" << endl 
		 << endl;
	cout << "몬스터 : " << m_pObjName->pName << endl;
	cout << "체력 : " << m_pObjInfo->Hp << endl;
	cout << "공격력 : " << m_pObjInfo->Att << endl;
	cout << "방어력 : " << m_pObjInfo->Armor << endl;

}