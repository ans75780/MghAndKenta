#include "..\Public\FirstPersonCamera.h"
#include "GameObject.h"


CFirstPersonCamera::CFirstPersonCamera(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CCamera(pGraphic_Device)
{
}

CFirstPersonCamera::CFirstPersonCamera(const CFirstPersonCamera& Prototype)
	: CCamera(Prototype)
{
}


HRESULT CFirstPersonCamera::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CFirstPersonCamera::Initialize(void * pArg)
{
	m_vOffset = { 0,0,-5 };

	return S_OK;
}

HRESULT CFirstPersonCamera::Render(float fWinCX, float fWinCY)
{
	_float3 m_vEye = _float3(0, 0, -2.f);
	_float3 m_vLook = _float3(0, 0, 0);
	_float3 m_vUp = { 0.f, 1.0f, 0.f };
	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vLook, &m_vUp);
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &m_matView);
	D3DXMatrixPerspectiveFovLH(&m_matProj, 45, fWinCX / (float)fWinCY, 1.0f, 1000.f);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_matProj);

	return S_OK;
}



HRESULT CFirstPersonCamera::Tick_Camera(D3DXMATRIX& _mat)
{


	return S_OK;
}

CFirstPersonCamera* CFirstPersonCamera::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CFirstPersonCamera* pInstance = new CFirstPersonCamera(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : FirstPersonCamera");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent* CFirstPersonCamera::Clone(void* pArg)
{
	CFirstPersonCamera* pInstance = new CFirstPersonCamera(*this);

	if (FAILED(pInstance->Initialize(nullptr)))
	{
		MSG_BOX("Failed to Clone : FirstPersonCamera");
		Safe_Release(pInstance);
	}
	return pInstance;
}


void CFirstPersonCamera::Free()
{
	__super::Free();
}

