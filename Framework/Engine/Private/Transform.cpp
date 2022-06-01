#include "Transform.h"

CTransform::CTransform(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent(pGraphic_Device)
{

}

HRESULT CTransform::Initialize_Prototype()
{
	m_vPosition = { 0,0,0 };
	m_vAngle = { 0,0,0 };
	m_vScale = { 1,1,1 };

	return S_OK;
}

HRESULT CTransform::Initialize(void* pArg)
{

	return S_OK;
}

void CTransform::Set_Position(_float3 _vecPos)
{
	m_vPosition = _vecPos;
}

void CTransform::Set_Angle(_float3 _vecAngle)
{
	m_vAngle = _vecAngle;
}

void CTransform::Set_Scale(_float3 _vecScale)
{
	m_vScale = _vecScale;
}

CTransform* CTransform::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CTransform* pInstance = new CTransform(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CTransform");
		Safe_Release(pInstance);
	}
 	return pInstance;
}

CComponent* CTransform::Clone(void* pArg)
{
	CComponent* pInstance = new CTransform(*this);
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Created : CTransform");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTransform::Free()
{
	__super::Free();
}

void CTransform::Calc_World()
{
	_float4x4 matScale, matTranslation, matRotation;
	
	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationYawPitchRoll(&matRotation, m_vAngle.y, m_vAngle.x, m_vAngle.z);
	D3DXMatrixTranslation(&matTranslation, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = matScale * matRotation * matTranslation;
}

const _float4x4& CTransform::Get_Wolrd()
{
	return m_matWorld;
}

const _float3& CTransform::Get_Position()
{
	// // O: 여기에 return 문을 삽입합니다.
	return m_vPosition;
}

const _float3& CTransform::Get_Angle()
{
	// // O: 여기에 return 문을 삽입합니다.
	return m_vAngle;
}

const _float3& CTransform::Get_Scale()
{
	// // O: 여기에 return 문을 삽입합니다.
	return m_vScale;
}

void CTransform::Move(_float3 _speed)
{
	m_vPosition += _speed;
}

void CTransform::Rotate(_float3 _speed)
{
	m_vAngle += _speed;
}
