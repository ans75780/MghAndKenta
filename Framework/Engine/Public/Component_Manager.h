#pragma once



/* 컴포넌트들의 원형을 가지고 있는다. */

#include "Base.h"

BEGIN(Engine)

class CComponent_Manager final : public CBase
{
	DECLARE_SINGLETON(CComponent_Manager)
public:
	CComponent_Manager();
	virtual ~CComponent_Manager() = default;

public:
	HRESULT Reserve_Container(_uint iNumLevels);
	HRESULT Add_Prototype(_uint iLevelIndex, const _tchar* pPrototypeTag, class CComponent* pPrototype);
	class CComponent* Find_Components(_uint iLevelIndex, const _tchar* pPrototypeTag);
private:
	_uint			m_iNumLevels = 0;

	map<const _tchar*, class CComponent*>*				m_pPrototypes = nullptr;
	typedef map<const _tchar*, class CComponent*>		PROTOTYPES;

private:




public:
	virtual void Free() override;
};

END