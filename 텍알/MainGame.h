#pragma once

class CGameObject;
class CStage;
class CShop;
class CMainGame
{
public:
	CMainGame();
	~CMainGame();
public:
	void start();
	void selectClass(INFO& Info);
	void process();
	//menu
	void dungeon();
	void shop();
	void Inventory();
	void save();
	void load();
	void tempsave();
	void tempload();

	void Free();
private:
	CGameObject* m_pPlayer = nullptr;
	CStage*		 m_pStage = nullptr;
	CShop*		 m_pShop = nullptr;
};

