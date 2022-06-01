#include "stdafx.h"
#include "Human.h"
#include "GameInstance.h"
CHuman::CHuman(LPDIRECT3DDEVICE9 pGraphic_Device)
    :CGameObject(pGraphic_Device)
{
    Safe_AddRef(m_pGraphic_Device);
}

CHuman::CHuman(const CHuman& Prototype)
    :CGameObject(Prototype.m_pGraphic_Device)
{
    Safe_AddRef(m_pGraphic_Device);
}

HRESULT CHuman::Initialize_Prototype()
{
    return E_NOTIMPL;
}

HRESULT CHuman::Initialize(void* pArg)
{
    return E_NOTIMPL;
}

void CHuman::Tick(_float fTimeDelta)
{
}

void CHuman::LateTick(_float fTimeDelta)
{
}

HRESULT CHuman::Render()
{
    return S_OK;
}

CGameObject* CHuman::Find_Parts(const _tchar* _tag)
{
    auto	iter = find_if(m_parts.begin(), m_parts.end(), CTag_Finder(_tag));

    if (iter == m_parts.end())
        return nullptr;

    return iter->second;
}

HRESULT CHuman::SetUp_Components()
{
    return E_NOTIMPL;
}

HRESULT CHuman::SetUp_Parts()
{
    CGameInstance* pGameInstance = CGameInstance::Get_Instance();
    Safe_AddRef(pGameInstance);

    m_parts.emplace("Body",
                    pGameInstance->
        
        );


    Safe_Release(pGameInstance);
    return S_OK;
}

CHuman* CHuman::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
    CHuman* pInstance = new CHuman(pGraphic_Device);

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed to Created : CHuman");
        Safe_Release(pInstance);
    }

    return pInstance;
}

CGameObject* CHuman::Clone(void* pArg)
{
    CHuman* pInstance = new CHuman(*this);

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Created : CHuamn");
        Safe_Release(pInstance);
    }
    return pInstance;
}

void CHuman::Free()
{
    __super::Free();
    for (auto& Pair : m_parts)
    {
        Safe_Release(Pair.second);
    }
    m_parts.clear();
    Safe_Release(m_pGraphic_Device);
}
