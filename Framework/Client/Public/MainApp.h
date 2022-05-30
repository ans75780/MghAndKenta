#pragma once

#include "Client_Defines.h"
#include "Base.h"

BEGIN(Engine)
class CGameInstance;
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

private:
	HRESULT Open_Level(LEVEL eLevelID);

public:
	static CMainApp* Create();
	virtual void Free();

};

END