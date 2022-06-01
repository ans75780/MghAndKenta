#pragma once

#include "Component.h"
#include "Engine_Defines.h"

BEGIN(Engine)

class ENGINE_DLL CTransform final : public CComponent
{
	CTransform(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CTransform() = default;
public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
public:
	void		Set_Position(_float3 _vecPos);
	void		Set_Angle(_float3 _vecAngle);
	void		Set_Scale(_float3 _vecScale);
	void		Calc_World();
	const _float4x4&	Get_Wolrd();
public:
	const _float3& Get_Position();
	const _float3& Get_Angle();
	const _float3& Get_Scale();
public:
	void	Move(_float3 _speed);
	void	Rotate(_float3 _speed);
private:
	_float3 m_vPosition;
	_float3 m_vAngle;
	_float3	m_vScale;
private:
	_float4x4	m_matWorld;
public:
	static CTransform* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END

