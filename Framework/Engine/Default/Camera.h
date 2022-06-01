#pragma once

#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CCamera abstract : public CBase
{
protected:
	CCamera(LPDIRECT3DDEVICE9 pGraphic_Device);
	CCamera(const CCamera& Prototype);
	virtual ~CCamera() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
public:
	void			SetMainCam();
private:
	LPDIRECT3DDEVICE9			m_pGraphic_Device = nullptr;
	class CTransform*					m_pTransform;
public:
	virtual CCamera* Clone(void* pArg) = 0;
	virtual void Free() override;
};
END
