#include "stdafx.h"
#include "EmptyObject.h"
#include "GameInstance.h"
#include "../Default/FirstPersonCamera.h"
CEmptyObject::CEmptyObject(LPDIRECT3DDEVICE9 pGraphic_Device)
    :CGameObject(pGraphic_Device)
{
}

CEmptyObject::CEmptyObject(const CEmptyObject& Prototype)
    : CGameObject(Prototype)
{
}

HRESULT CEmptyObject::Initialize_Prototype()
{
    return S_OK;
}

HRESULT CEmptyObject::Initialize(void* pArg)
{
    if (FAILED(SetUp_Components()))
        return E_FAIL;

    return S_OK;
}

void CEmptyObject::Tick(_float fTimeDelta)
{
    if (GetKeyState('W') & 0x8000)
    {
        m_pTransformCom->Move(_float3(0, 0, 0.01f));
    }
    if (GetKeyState('S') & 0x8000)
    {
        m_pTransformCom->Move(_float3(0, 0, -0.01f));
    }
    if (GetKeyState('A') & 0x8000)
    {
        m_pTransformCom->Move(_float3(-0.01f, 0, 0));
    }
    if (GetKeyState('D') & 0x8000)
    {
        m_pTransformCom->Move(_float3(0.01f, 0, 0));
    }

    _float3 pos = m_pTransformCom->Get_Position();
    pos.z -= 5;
    m_pCamera->Get_Transform()->Set_Position(pos);
    if (GetKeyState(VK_LCONTROL) & 0x8000)
    {
        m_pCamera->Set_MainCamera();
    }
}

void CEmptyObject::LateTick(_float fTimeDelta)
{
}

HRESULT CEmptyObject::Render()
{
    return E_NOTIMPL;
}

CTransform* CEmptyObject::GetTransform()
{
    if (!m_pTransformCom)
        return nullptr;
    return m_pTransformCom;
}

CGameObject* CEmptyObject::Get_Parent()
{
    if (!m_pParent)
        return nullptr;

    return m_pParent;
}

CGameObject* CEmptyObject::Get_Child()
{
    if (!m_pChild)
        return nullptr;
    return m_pChild;
}

HRESULT CEmptyObject::SetUp_Components()
{
    CGameInstance* pGameInstance = CGameInstance::Get_Instance();
    Safe_AddRef(pGameInstance);

    m_pTransformCom = (CTransform*)pGameInstance->Clone_Component(LEVEL_STATIC, TEXT("Prototype_Component_Transform"));
    if (nullptr == m_pTransformCom)
        return E_FAIL;
    m_pCamera = (CCamera*)pGameInstance->Clone_Camera(TEXT("Prototype_Camera_FirstPerson"));
    if (nullptr == m_pCamera)
        return E_FAIL;

    Safe_Release(pGameInstance);
    return S_OK;
}

CEmptyObject* CEmptyObject::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
    CEmptyObject* pInstance = new CEmptyObject(pGraphic_Device);

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed to Created : CBackGround");
        Safe_Release(pInstance);
    }

    return pInstance;
}

CEmptyObject* CEmptyObject::Clone(void* pArg)
{
    CEmptyObject* pInstance = new CEmptyObject(*this);

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Created : EmptyObject");
        Safe_Release(pInstance);
    }

    return pInstance;
}


void CEmptyObject::Free()
{
    __super::Free();

    Safe_Release(m_pTransformCom);
    Safe_Release(m_pCamera);
}
