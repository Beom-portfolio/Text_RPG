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
	cout << "���� : " << m_pObjName->pName << endl;
	cout << "ü�� : " << m_pObjInfo->Hp << endl;
	cout << "���ݷ� : " << m_pObjInfo->Att << endl;
	cout << "���� : " << m_pObjInfo->Armor << endl;

}