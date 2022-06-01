#include "stdafx.h"
#include "FirstPersonCamera.h"
#include "GameInstance.h"
CFirstPersonCamera::CFirstPersonCamera(LPDIRECT3DDEVICE9 pGraphic_Device)
    :CCamera(pGraphic_Device)
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

HRESULT CFirstPersonCamera::Initialize(void* pArg)
{
    if (FAILED(SetUp_Components()))
        return E_FAIL;

    return S_OK;
}

HRESULT CFirstPersonCamera::SetUp_Components()
{
    CGameInstance* pGameInstance = CGameInstance::Get_Instance();
    Safe_AddRef(pGameInstance);

    m_pTransform = (CTransform*)pGameInstance->Clone_Component(LEVEL_STATIC, TEXT("Prototype_Component_Transform"));
    if (nullptr == m_pTransform)
        return E_FAIL;

    Safe_Release(pGameInstance);
    return S_OK;

}

CFirstPersonCamera* CFirstPersonCamera::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
    CFirstPersonCamera* pInstance = new CFirstPersonCamera(pGraphic_Device);

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed to Created : CBackGround");
        Safe_Release(pInstance);
    }

    return pInstance;
}

CFirstPersonCamera* CFirstPersonCamera::Clone(void* pArg)
{
    CFirstPersonCamera* pInstance = new CFirstPersonCamera(*this);

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Created : CFirstPersonCamera");
        Safe_Release(pInstance);
    }
    return pInstance;
}

void CFirstPersonCamera::Free()
{
    __super::Free();
    Safe_Release(m_pTransform);
}
