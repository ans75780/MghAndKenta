#include "stdafx.h"
#include "..\Public\Human.h"
#include "GameInstance.h"
#include "Cube.h"

CHuman::CHuman(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{

}

CHuman::CHuman(const CHuman & Prototype)
	: CGameObject(Prototype)
{
}

HRESULT CHuman::Initialize_Prototype()
{
	/* 백엔드로부터 값ㅇ를 어덩오낟. */

	return S_OK;
}

HRESULT CHuman::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;
	if (FAILED(SetUp_Parts()))
		return E_FAIL;
	
	return S_OK;
}

void CHuman::Tick(_float fTimeDelta)
{
	int a = 10;
	//m_pVIBufferHumanCom->Update_Vertex();

	if (GetKeyState(VK_CONTROL) & 0x8000)
		CCamera::Set_MainCamera(m_pFirstPersonCameraCom);
	if (GetKeyState(VK_SHIFT) & 0x8000)
		CCamera::Set_MainCamera(m_pThirdPersonCameraCom);


	CCube* LeftShoulder = Find_Parts(TEXT("LeftShoulder"));
	CCube* RightShoulder = Find_Parts(TEXT("RightShoulder"));
	CCube* Head = Find_Parts(TEXT("Head"));

	if (LeftShoulder)
	{
		LeftShoulder->Get_Transform()->Rotate(_float3(0.01f, 0, 0));
	}

	if (RightShoulder)
	{
		RightShoulder->Get_Transform()->Rotate(_float3(-0.01f, 0, 0));
	}

	if (Head)
	{
		Head->Get_Transform()->Rotate(_float3(0, 0.01f, 0));
	}

	for (auto& Pair : m_Parts)
	{
		Pair.second->Tick(fTimeDelta);
	}




}

void CHuman::LateTick(_float fTimeDelta)
{
	if (nullptr == m_pRendererCom)
		return;

	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_PRIORITY, this);
}

HRESULT CHuman::Render()
{
	if (m_pRoot)
		m_pRoot->Render();
	return S_OK;
}

void CHuman::Set_Parent_Child(CCube* _pParent, CCube* _pChild)
{
	_pParent->Add_Child(_pChild);
	_pChild->Set_Parent(_pParent);
}


HRESULT CHuman::SetUp_Components()
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
	m_pFirstPersonCameraCom = (CFirstPersonCamera*)pGameInstance->Clone_Component(LEVEL_STATIC, TEXT("Prototype_Component_FirstPersonCamera"));
	if (nullptr == m_pFirstPersonCameraCom)
		return E_FAIL;
	m_pThirdPersonCameraCom = (CThirdPersonCamera*)pGameInstance->Clone_Component(LEVEL_STATIC, TEXT("Prototype_Component_ThirdPersonCamera"));
	if (nullptr == m_pFirstPersonCameraCom)
		return E_FAIL;

	CCamera::Set_MainCamera(m_pThirdPersonCameraCom);
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CHuman::SetUp_Parts()
{
	CCube* body = CCube::Create(m_pGraphic_Device);
	if (FAILED(body->Initialize(nullptr)))
		return E_FAIL;
	CCube* head = CCube::Create(m_pGraphic_Device);
	if (FAILED(head->Initialize(nullptr)))
		return E_FAIL;
	head->Get_Transform()->Set_Position(_float3(0, 2, 0));
	head->Get_Transform()->Set_Scale(_float3(0.7f,0.7f,0.7f));
	Set_Parent_Child(body, head);

	CCube* LeftShoulder = CCube::Create(m_pGraphic_Device);
	if (FAILED(LeftShoulder->Initialize(nullptr)))
		return E_FAIL;
	LeftShoulder->Get_Transform()->Set_Position(_float3(-2, 0, 0));
	LeftShoulder->Get_Transform()->Set_Scale(_float3(0.7f, 0.7f, 0.7f));
	Set_Parent_Child(body, LeftShoulder);

	CCube* RightShoulder = CCube::Create(m_pGraphic_Device);
	if (FAILED(RightShoulder->Initialize(nullptr)))
		return E_FAIL;
	RightShoulder->Get_Transform()->Set_Position(_float3(2, 0, 0));
	RightShoulder->Get_Transform()->Set_Scale(_float3(0.7f, 0.7f, 0.7f));
	Set_Parent_Child(body, RightShoulder);

	CCube* LeftArm = CCube::Create(m_pGraphic_Device);
	if (FAILED(LeftArm->Initialize(nullptr)))
		return E_FAIL;
	LeftArm->Get_Transform()->Set_Position(_float3(0, -3, 0));
	LeftArm->Get_Transform()->Set_Scale(_float3(0.7f, 1.3f, 0.7f));
	Set_Parent_Child(LeftShoulder, LeftArm);

	CCube* RightArm = CCube::Create(m_pGraphic_Device);
	if (FAILED(RightArm->Initialize(nullptr)))
		return E_FAIL;
	RightArm->Get_Transform()->Set_Position(_float3(0, -3, 0));
	RightArm->Get_Transform()->Set_Scale(_float3(0.7f, 1.3f, 0.7f));
	Set_Parent_Child(RightShoulder, RightArm);



	CCube* LeftLeg = CCube::Create(m_pGraphic_Device);
	if (FAILED(LeftLeg->Initialize(nullptr)))
		return E_FAIL;
	LeftLeg->Get_Transform()->Set_Position(_float3(-1.5, -2.5f, 0));
	LeftLeg->Get_Transform()->Set_Scale(_float3(0.7f, 1.1f, 0.7f));
	Set_Parent_Child(body, LeftLeg);

	CCube* RightLeg = CCube::Create(m_pGraphic_Device);
	if (FAILED(RightLeg->Initialize(nullptr)))
		return E_FAIL;
	RightLeg->Get_Transform()->Set_Position(_float3(1.5, -2.5f, 0));
	RightLeg->Get_Transform()->Set_Scale(_float3(0.7f, 1.1f, 0.7f));
	Set_Parent_Child(body, RightLeg);



	m_pRoot = body;
	m_Parts.emplace(TEXT("Body"), body);
	m_Parts.emplace(TEXT("Head"), head);
	m_Parts.emplace(TEXT("LeftShoulder"), LeftShoulder);
	m_Parts.emplace(TEXT("RightShoulder"), RightShoulder);
	m_Parts.emplace(TEXT("LeftArm"), LeftArm);
	m_Parts.emplace(TEXT("RightArm"), RightArm);
	m_Parts.emplace(TEXT("LeftLeg"), LeftLeg);
	m_Parts.emplace(TEXT("RightLeg"), RightLeg);





	return S_OK;
}

CCube* CHuman::Find_Parts(const _tchar* partsName)
{
	auto	iter = find_if(m_Parts.begin(), m_Parts.end(), CTag_Finder(partsName));

	if (iter == m_Parts.end())
		return nullptr;

	return iter->second;
}

CHuman * CHuman::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CHuman*		pInstance = new CHuman(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CHuman");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CHuman::Clone(void* pArg)
{
	CHuman*		pInstance = new CHuman(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Created : CHuman");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CHuman::Free()
{
	__super::Free();
	Safe_Release(m_pFirstPersonCameraCom);
	Safe_Release(m_pThirdPersonCameraCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pTransformCom);
	for(auto & Pair : m_Parts)
	{
		Safe_Release(Pair.second);
	}
	m_Parts.clear();
	m_pRoot = nullptr;
}
