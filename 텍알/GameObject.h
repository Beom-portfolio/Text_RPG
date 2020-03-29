#pragma once
class CGameObject
{
public:
	CGameObject();
	CGameObject(INFO& Info, NAME& Name);
	virtual ~CGameObject();
public:
	CGameObject& operator-=(CGameObject& obj);
public:
	const INFO& GetInfo() { return *m_pObjInfo; }
	const NAME& GetName() { return *m_pObjName; }
	INFO*		GetRefInfo() { return m_pObjInfo; }
	NAME*		GetRefName() { return m_pObjName; }
public:
	virtual void Initialize() = PURE;
	virtual void RenderInfo() = PURE;
public:
	void Free();
protected:
	NAME* m_pObjName = nullptr;
	INFO* m_pObjInfo = nullptr;
};

