#pragma once

#include "Graphic_Device.h"
#include "Level_Manager.h"
#include "Object_Manager.h"
#include "Component_Manager.h"
#include "Camera_Manager.h"
/* 1. ���ӳ��� �ʿ��� ��ü(�Ŵ�����)���� ��Ƽ� �����Ѵ�. */
/* 2. Ŭ���̾�Ʈ �����ڰ� �����ϱ����� ��Ʈ�� �������ش�. ��. */
/* 3. ��¥ �ʿ��� �Լ��� Ŭ���׾�Ʈ�����ڿ��� ���������ֳ�. */

BEGIN(Engine)

class ENGINE_DLL CGameInstance final : public CBase
{
	DECLARE_SINGLETON(CGameInstance)
public:
	CGameInstance();
	virtual ~CGameInstance() = default;

public: /* ���� ���̺귲�� ����Ҷ� �ʿ��� �ʱ�ȭ �������� ��ĥ�ž�. */
	HRESULT Initialize_Engine(_uint iNumLevels, const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut);
	HRESULT Tick_Engine(_float fTimeDelta);
	HRESULT Render_Engine();
	HRESULT Clear(_uint iLevelID);

public: /* For.Graphic_Device */	
	void		Render_Begin(void);
	void		Render_End(HWND hWnd = NULL);

public: /* For.Level_Manager */
	HRESULT Open_Level(_uint iLevelID, class CLevel* pLevel);

public: /* For.Object_Manager */
	HRESULT Add_Prototype(const _tchar* pPrototypeTag, class CGameObject* pPrototype);
	HRESULT Add_GameObject(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pPrototypeTag, void* pArg = nullptr);

public: /* For.Component_Mananger */
	HRESULT Add_Prototype(_uint iLevelIndex, const _tchar* pPrototypeTag, class CComponent* pPrototype);
	class CComponent* Clone_Component(_uint iLevelIndex, const _tchar* pPrototypeTag, void* pArg = nullptr);
public: /* For. Camera_Manager */
	HRESULT Add_Prototype(const _tchar * pPrototypeTag, class CCamera* pPrototype);
	class CCamera* Clone_Camera(const _tchar * pPrototypeTag, void* pArg = nullptr);
	class CCamera* Get_MainCamera();
	HRESULT			Set_MainCamera(class CCamera* _pCamera);


private:
	CGraphic_Device*				m_pGraphic_Device = nullptr;
	CLevel_Manager*					m_pLevel_Manager = nullptr;
	CObject_Manager*				m_pObject_Manager = nullptr;
	CComponent_Manager*				m_pComponent_Manager = nullptr;
	CCamera_Manager*				m_pCamera_Manager = nullptr;

public:
	static void Release_Engine();
	virtual void Free() override;
};

END