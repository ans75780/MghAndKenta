#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Client)

class CBackGround final : public CGameObject
{
private:
	CBackGround(LPDIRECT3DDEVICE9 pGraphic_Device);
	CBackGround(const CBackGround& Prototype);
	virtual ~CBackGround() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg)override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	static CBackGround* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END