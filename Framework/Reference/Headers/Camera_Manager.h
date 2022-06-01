#pragma once

/* 컴포넌트들의 원형을 가지고 있는다. */
#include "Camera.h"
#include "Engine_Defines.h"
BEGIN(Engine)

class CCamera_Manager final : public CBase
{
	DECLARE_SINGLETON(CCamera_Manager)
public:
	CCamera_Manager();
	virtual ~CCamera_Manager() = default;

public:
	HRESULT Add_Prototype(const _tchar * pPrototypeTag, class CCamera* pPrototype);
	class CCamera* Clone_Camera(const _tchar * pPrototypeTag, void* pArg);
	HRESULT			Set_MainCamera(class CCamera* camera);
	CCamera*		Get_MainCamera();
private:
	map<const _tchar*, class CCamera*> m_pPrototypes;
	typedef map<const _tchar*, class CCamera*>		CAMERAS;
	class CCamera* m_pMainCamera = nullptr;

private:
	class CCamera* Find_Camera(const _tchar * pPrototypeTag);
public:
	virtual void Free() override;
};

END

