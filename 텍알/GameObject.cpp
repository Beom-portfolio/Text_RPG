#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
{
}

CGameObject::CGameObject(INFO & Info, NAME& Name)
{
	//Set Info
	if (nullptr == m_pObjInfo)
		m_pObjInfo = new INFO;

	m_pObjInfo->eClass = Info.eClass;
	
	m_pObjInfo->Level = Info.Level;
	m_pObjInfo->MaxHp = Info.MaxHp;
	m_pObjInfo->Hp = m_pObjInfo->MaxHp;
	m_pObjInfo->Str = Info.Str;
	m_pObjInfo->Dex = Info.Dex;
	m_pObjInfo->Int = Info.Int;

	m_pObjInfo->Att = Info.Att;
	m_pObjInfo->Armor = Info.Armor;
	m_pObjInfo->ItemAtt = Info.ItemAtt;
	m_pObjInfo->ItemArmor = Info.ItemArmor;

	m_pObjInfo->MaxExp = Info.MaxExp;
	m_pObjInfo->Exp = Info.Exp;
	m_pObjInfo->Money = Info.Money;

	//Set Name
	if (nullptr == m_pObjName)
		m_pObjName = new NAME;

	if (nullptr != m_pObjName->pClassName)
	{
		delete[] m_pObjName->pClassName;
		m_pObjName->pClassName = nullptr;
	}
	if (nullptr != m_pObjName->pName)
	{
		delete[] m_pObjName->pName;
		m_pObjName->pName = nullptr;
	}

	if (nullptr != Name.pClassName)
	{
		m_pObjName->pClassName = new char[strlen(Name.pClassName) + 1];
		strcpy_s(m_pObjName->pClassName, strlen(Name.pClassName) + 1, Name.pClassName);
	}

	if (nullptr != Name.pName)
	{
		m_pObjName->pName = new char[strlen(Name.pName) + 1];
		strcpy_s(m_pObjName->pName, strlen(Name.pName) + 1, Name.pName);
	}
	
}


CGameObject::~CGameObject()
{
}

CGameObject & CGameObject::operator-=(CGameObject & obj)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	obj.m_pObjInfo->Hp -= m_pObjInfo->Att;

	return *this;
}

void CGameObject::Initialize()
{
}

void CGameObject::RenderInfo()
{
}

void CGameObject::Free()
{
	if (nullptr != m_pObjName)
	{
		if (nullptr != m_pObjName->pClassName)
		{
			delete[] m_pObjName->pClassName;
			m_pObjName->pClassName = nullptr;
		}
		if (nullptr != m_pObjName->pName)
		{
			delete[] m_pObjName->pName;
			m_pObjName->pName = nullptr;
		}

		delete m_pObjName;
	}

	if (nullptr == m_pObjInfo)
		delete m_pObjInfo;
}
