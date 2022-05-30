#pragma once

#include "GameObject.h"
#include "Client_Defines.h"
BEGIN(Client)

class CCube : public CGameObject
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

public:
	static CCube* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END

