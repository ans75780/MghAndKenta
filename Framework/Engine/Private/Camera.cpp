#include "Camera.h"
#include "GameInstance.h"
CCamera::CCamera(LPDIRECT3DDEVICE9 pGraphic_Device)
	:m_pGraphic_Device(pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}

CCamera::CCamera(const CCamera& Prototype)
	: m_pGraphic_Device(Prototype.m_pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}

HRESULT CCamera::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCamera::Initialize(void* pArg)
{
	return S_OK;
}

void CCamera::Set_MainCamera()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	pGameInstance->Set_MainCamera(this);
	
	Safe_Release(pGameInstance);

}

CTransform* CCamera::Get_Transform()
{
	return m_pTransform;
}


void CCamera::Free()
{
	Safe_Release(m_pGraphic_Device);
}
