#include "..\Public\Camera.h"
#include "GameObject.h"

CCamera* CCamera::g_pMainCamera = nullptr;

CCamera::CCamera(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent(pGraphic_Device)
{
}

CCamera::CCamera(const CCamera& Prototype)
	:CComponent(Prototype)
{
}


HRESULT CCamera::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCamera::Initialize(void * pArg)
{
	return S_OK;
}

CCamera* CCamera::Get_MainCamera()
{
	return g_pMainCamera;
}

HRESULT CCamera::Set_MainCamera(CCamera* _pCamera)
{
	g_pMainCamera = _pCamera;

	return S_OK;
}

void CCamera::Free()
{
	__super::Free();
}
