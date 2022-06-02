#include "stdafx.h"
#include "..\Public\Cube.h"
#include "GameInstance.h"


CCube::CCube(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{

}

CCube::CCube(const CCube & Prototype)
	: CGameObject(Prototype)
{
}

HRESULT CCube::Initialize_Prototype()
{
	/* 백엔드로부터 값ㅇ를 어덩오낟. */

	return S_OK;
}

HRESULT CCube::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	
	return S_OK;
}

void CCube::Tick(_float fTimeDelta)
{
	int a = 10;
	//m_pVIBufferCubeCom->Update_Vertex();
}

void CCube::LateTick(_float fTimeDelta)
{
	if (nullptr == m_pRendererCom)
		return;

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_PRIORITY, this);
}

HRESULT CCube::Render()
{
	_float4x4 world;
	m_pTransformCom->Calc_World();
	world = m_pTransformCom->Get_Wolrd();
	if (m_pParent)
	{
		world *= m_pParent->Get_Transform()->Get_Wolrd();
	}
	//D3DXMatrixIdentity(&world);
	m_pGraphic_Device->SetTransform(D3DTS_WORLD, &world);
	m_pVIBufferCubeCom->Render();
	for (auto& iter : m_ChildList)
	{
		iter->Render();
	}
	return S_OK;
}

void CCube::Set_Parent(CCube* _pParent)
{
	m_pParent = _pParent;
}

CCube* CCube::Get_Parent()
{
	return m_pParent;
}

void CCube::Add_Child(CCube* _pChild)
{
	m_ChildList.push_back(_pChild);
}

CTransform* CCube::Get_Transform()
{
	return m_pTransformCom;
}

HRESULT CCube::SetUp_Components()
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	/* For.Com_Renderer */ 
	m_pRendererCom = (CRenderer*)pGameInstance->Clone_Component(LEVEL_STATIC, TEXT("Prototype_Component_Renderer"));
	if (nullptr == m_pRendererCom)
		return E_FAIL;

	m_pTransformCom = (CTransform*)pGameInstance->Clone_Component(LEVEL_STATIC, TEXT("Prototype_Component_Transform"));
	if (nullptr == m_pTransformCom)
		return E_FAIL;
	m_pVIBufferCubeCom = (CVIBuffer_Cube*)pGameInstance->Clone_Component(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Cube"));
	if (nullptr == m_pVIBufferCubeCom)
		return E_FAIL;


	Safe_Release(pGameInstance);
	return S_OK;
}

CCube * CCube::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CCube*		pInstance = new CCube(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CCube");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CCube::Clone(void* pArg)
{
	CCube*		pInstance = new CCube(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Created : CCube");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CCube::Free()
{
	__super::Free();

	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pVIBufferCubeCom);


}
