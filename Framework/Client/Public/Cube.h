#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CCamera;
END
struct Vertex
{
	_float x, y, z;

	Vertex(_float _x, _float _y, _float _z)
		:x(_x),y(_y),z(_z)
	{

	}

};
BEGIN(Client)



class CCube final : public CGameObject
{
private:
	CCube(LPDIRECT3DDEVICE9 pGraphic_Device);
	CCube(const CCube& Prototype);
	virtual ~CCube() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg)override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	CRenderer* m_pRendererCom = nullptr;
	CTransform* m_pTransformCom = nullptr;
	CCamera*	m_pCamera = nullptr;
	LPDIRECT3DVERTEXBUFFER9		m_pVertexBuffer = nullptr;
	LPDIRECT3DINDEXBUFFER9		m_pIndexBuffer = nullptr;

private: /* 현재 객체에게 필요한 컴포넌트를 복제해온다. */
	HRESULT SetUp_Components();
	HRESULT	SetUp_DrawData();
public:
	static CCube* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};
END