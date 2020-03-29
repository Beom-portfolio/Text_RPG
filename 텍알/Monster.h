#pragma once

#include "GameObject.h"

class CMonster
	:public CGameObject
{
public:
	CMonster();
	CMonster(INFO& Info, NAME& Name);
	~CMonster();
//Setting, Operator, InfoSet
public:
	virtual void Initialize();
	virtual void RenderInfo();

};

