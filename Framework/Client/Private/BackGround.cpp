#include "stdafx.h"
#include "..\Public\BackGround.h"

CBackGround::CBackGround(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{

}

CBackGround::CBackGround(const CBackGround & Prototype)
	: CGameObject(Prototype)
{
}

HRESULT CBackGround::Initialize_Prototype()
{
	/* �鿣��κ��� ������ �����. */

	return S_OK;
}

HRESULT CBackGround::Initialize(void* pArg)
{

	
	return S_OK;
}

void CBackGround::Tick(_float fTimeDelta)
{
	int a = 10;
}

void CBackGround::LateTick(_float fTimeDelta)
{
	int a = 10;
}

HRESULT CBackGround::Render()
{
	return S_OK;
}

CBackGround * CBackGround::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CBackGround*		pInstance = new CBackGround(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CBackGround");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBackGround::Clone(void* pArg)
{
	CBackGround*		pInstance = new CBackGround(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Created : CBackGround");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBackGround::Free()
{
	__super::Free();
}
