#pragma once

/* ȭ�鿡 �׷������� ��ü���� �׸��� ������� ��Ƽ� �����ϳ�.  */
/* ������ �ִ� ��ü���� �����Լ��� ȣ�����ֳ�. */

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CRenderer final : public CComponent
{
public:
	enum RENDERGROUP { RENDER_PRIORITY, RENDER_NONALPHABLEND, RENDER_ALPHABLEND, RENDER_UI, RENDER_END };

private:
	CRenderer(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CRenderer() = default;
	 
public:
	HRESULT Add_RenderGroup(RENDERGROUP	eGroup, class CGameObject* pGameObject);

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	HRESULT Draw_RenderGroup();

private:
	list<class CGameObject*>				m_RenderObjects[RENDER_END];
	typedef list<class CGameObject*>		RENDEROBJECTS;

public:
	static CRenderer* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END