#include "..\Public\Renderer.h"


CRenderer::CRenderer(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent(pGraphic_Device)
{
}

HRESULT CRenderer::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CRenderer::Initialize(void * pArg)
{
	return S_OK;
}

CComponent * CRenderer::Clone(void * pArg)
{
	return nullptr;
}

void CRenderer::Free()
{
	__super::Free();
}
