#pragma once

#include "Client_Defines.h"
#include "Base.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CVIBuffer_Cube;
class CGameInstance;
class CFirstPersonCamera;
class CThirdPersonCamera;

END

BEGIN(Client)
//class CGameInstance;
class CMainApp final : public CBase
{
private:
	CMainApp();
	virtual ~CMainApp() = default;
public:
	HRESULT Initialize();	
	void Tick(float fTimeDelta);
	HRESULT Render();

private:
	CGameInstance*			m_pGameInstance = nullptr;
	LPDIRECT3DDEVICE9		m_pGraphic_Device = nullptr;
	CRenderer*				m_pRenderer = nullptr;
private:
	HRESULT Open_Level(LEVEL eLevelID);
	HRESULT Ready_Prototype_Component();

public:
	static CMainApp* Create();
	virtual void Free();

};

END