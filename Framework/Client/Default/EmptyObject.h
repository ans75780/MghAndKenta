#pragma once


#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CCamera;
END


BEGIN(Client)

class CEmptyObject final : public CGameObject
{
private:
	CEmptyObject(LPDIRECT3DDEVICE9 pGraphic_Device);
	CEmptyObject(const CEmptyObject& Prototype);
	virtual ~CEmptyObject() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg)override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;
	CTransform* GetTransform();
	CGameObject* Get_Parent();
	CGameObject* Get_Child();

private:
	CGameObject* m_pParent = nullptr;
	CGameObject* m_pChild = nullptr;

	CRenderer* m_pRendererCom = nullptr;
	CTransform* m_pTransformCom = nullptr;
	CCamera* m_pCamera = nullptr;
	LPDIRECT3DVERTEXBUFFER9		m_pVertexBuffer = nullptr;
	LPDIRECT3DINDEXBUFFER9		m_pIndexBuffer = nullptr;

private: /* 현재 객체에게 필요한 컴포넌트를 복제해온다. */
	HRESULT SetUp_Components();
	HRESULT	SetUp_DrawData();
public:
	static CEmptyObject* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CEmptyObject* Clone(void* pArg) override;
	virtual void Free() override;
};
END

