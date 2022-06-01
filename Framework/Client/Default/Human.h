#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
#include "Cube.h"
BEGIN(Engine)
class CRenderer;
class CTransform;
class CCamera;
END
BEGIN(Client)
class CHuman final : public CGameObject
{
private:
	CHuman(LPDIRECT3DDEVICE9 pGraphic_Device);
	CHuman(const CHuman& Prototype);
	virtual ~CHuman() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg)override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;
public:
	class CGameObject* Find_Parts(const _tchar* _tag);
private:
	map<const _tchar*,CCube* > m_parts;
	CTransform* m_pTransformCom = nullptr;
private: 
	HRESULT SetUp_Components();
	HRESULT SetUp_Parts();
public:
	static CHuman* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};
END
