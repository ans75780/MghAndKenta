#include "stdafx.h"
#include "Cube.h"

CCube::CCube(LPDIRECT3DDEVICE9 pGraphic_Device)
    :CGameObject(pGraphic_Device)
{

}

CCube::CCube(const CCube& Prototype)
    :CGameObject(Prototype)
{

}

HRESULT CCube::Initialize_Prototype()
{
    return E_NOTIMPL;
}

HRESULT CCube::Initialize(void* pArg)
{
    return E_NOTIMPL;
}

void CCube::Tick(_float fTimeDelta)
{
}

void CCube::LateTick(_float fTimeDelta)
{
}

HRESULT CCube::Render()
{
    return E_NOTIMPL;
}

CCube* CCube::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
    return nullptr;
}

CGameObject* CCube::Clone(void* pArg)
{
    return nullptr;
}

void CCube::Free()
{
}
