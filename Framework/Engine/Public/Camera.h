#pragma once

#include "Base.h"
#include "Component_Manager.h"
#include "Object_Manager.h"

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
	void			Set_MainCamera();
	CTransform*		Get_Transform();
private:
	LPDIRECT3DDEVICE9			m_pGraphic_Device = nullptr;
protected:
	CTransform* m_pTransform;
public:
	virtual CCamera* Clone(void* pArg) = 0;
	virtual void Free() override;
};
END
