#include "..\Public\ThirdPersonCamera.h"
#include "GameObject.h"


CThirdPersonCamera::CThirdPersonCamera(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CCamera(pGraphic_Device)
{
}

CThirdPersonCamera::CThirdPersonCamera(const CThirdPersonCamera& Prototype)
	: CCamera(Prototype)
{
}


HRESULT CThirdPersonCamera::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CThirdPersonCamera::Initialize(void * pArg)
{
	return S_OK;
}

HRESULT CThirdPersonCamera::Render(float fWinCX, float fWinCY)
{
	_float3 m_vEye = _float3(0, 0, -15.f);
	_float3 m_vLook = _float3(0, 0, 0);
	_float3 m_vUp = { 0.f, 1.0f, 0.f };
	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vLook, &m_vUp);
	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &m_matView);
	D3DXMatrixPerspectiveFovLH(&m_matProj, 45, fWinCX / (float)fWinCY, 1.0f, 1000.f);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_matProj);

	return S_OK;
}

HRESULT CThirdPersonCamera::Tick_Camera(D3DXMATRIX& _mat)
{
	return S_OK;
}


CThirdPersonCamera* CThirdPersonCamera::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CThirdPersonCamera* pInstance = new CThirdPersonCamera(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CThirdPersonCamera");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent* CThirdPersonCamera::Clone(void* pArg)
{
	CThirdPersonCamera* pInstance = new CThirdPersonCamera(*this);

	if (FAILED(pInstance->Initialize(nullptr)))
	{
		MSG_BOX("Failed to Clone : CThirdPersonCamera");
		Safe_Release(pInstance);
	}
	return pInstance;
}


void CThirdPersonCamera::Free()
{
	__super::Free();
}

