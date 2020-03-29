#pragma once
class CGameObject;
class CStage
{
public:
	enum DungeonType{Field, Cemetry, Hell, DungeonType_End};
public:
	CStage();
	CStage(const DungeonType& type);
	~CStage();
public:
	void process(CGameObject* player);
	int  Battle(CGameObject* player);
	void SpawnMonster();
	void Free();
private:
	CGameObject *m_pMonster = nullptr;
	DungeonType Type = DungeonType_End;
};

