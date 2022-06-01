#include "stdafx.h"
#include "..\Public\MainApp.h"
#include "GameInstance.h"
#include "Level_Loading.h"
#include "../Default/FirstPersonCamera.h"

CMainApp::CMainApp()
	: m_pGameInstance(CGameInstance::Get_Instance())
{
	Safe_AddRef(m_pGameInstance);
}

HRESULT CMainApp::Initialize()
{
	GRAPHICDESC		GraphicDesc;
	ZeroMemory(&GraphicDesc, sizeof(GRAPHICDESC));

	GraphicDesc.hWnd = g_hWnd;
	GraphicDesc.iWinCX = g_iWinCX;
	GraphicDesc.iWinCY = g_iWinCY;
	GraphicDesc.isWindowMode = true;

	if (FAILED(m_pGameInstance->Initialize_Engine(LEVEL_END, GraphicDesc, &m_pGraphic_Device)))
		return E_FAIL;

	if (FAILED(Ready_Prototype_Component()))
		return E_FAIL;

	if (FAILED(Ready_Prototype_Camera()))
		return E_FAIL;
	if (FAILED(Open_Level(LEVEL_LOGO)))
		return E_FAIL;

	return S_OK;
}

void CMainApp::Tick(float fTimeDelta)
{
	if (nullptr == m_pGameInstance)
		return;

	m_pGameInstance->Tick_Engine(fTimeDelta);
}

HRESULT CMainApp::Render()
{
	if (nullptr == m_pGameInstance || 
		nullptr == m_pRenderer)
		return E_FAIL;

	m_pGameInstance->Render_Begin();
	
	if (m_pGameInstance->Get_MainCamera())
	{
		_float4x4 m_matView, m_matProj;
		_float3 m_vEye = m_pGameInstance->Get_MainCamera()->Get_Transform()->Get_Position();
		_float3 m_vLook = m_vEye;
		m_vLook.z += 10;
		_float3 m_vUp = { 0.f, 1.0f, 0.f };

		D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vLook, &m_vUp);
		m_pGraphic_Device->SetTransform(D3DTS_VIEW, &m_matView);
		D3DXMatrixPerspectiveFovLH(&m_matProj, 45, g_iWinCX / (float)g_iWinCY, 1.0f, 1000.f);
		m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_matProj);
	}
	m_pRenderer->Draw_RenderGroup();

	m_pGameInstance->Render_Engine();

	m_pGameInstance->Render_End(g_hWnd);

	return S_OK;
}

HRESULT CMainApp::Open_Level(LEVEL eLevelID)
{
	if (nullptr == m_pGameInstance)
		return E_FAIL;

	CLevel_Loading*		pLevel_Loading = CLevel_Loading::Create(m_pGraphic_Device, eLevelID);
	if (nullptr == pLevel_Loading)
		return E_FAIL;

	if (FAILED(m_pGameInstance->Open_Level(LEVEL_LOADING, pLevel_Loading)))
		return E_FAIL;

	return S_OK;
}

HRESULT CMainApp::Ready_Prototype_Component()
{
	if (nullptr == m_pGameInstance)
		return E_FAIL;

	/* For.Prototype_Component_Renderer */
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Renderer"),
		m_pRenderer = CRenderer::Create(m_pGraphic_Device))))
		return E_FAIL;
	Safe_AddRef(m_pRenderer);
	if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Transform"),
		CTransform::Create(m_pGraphic_Device))))
		return E_FAIL;
	return S_OK;
}

HRESULT CMainApp::Ready_Prototype_Camera()
{
	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_Camera_FirstPerson"),
		CFirstPersonCamera::Create(m_pGraphic_Device))))
		return E_FAIL;
	return S_OK;
}

CMainApp * CMainApp::Create()
{
	CMainApp*		pInstance = new CMainApp();

	if (FAILED(pInstance->Initialize()))
	{
		MessageBox(g_hWnd, TEXT("Failed to Created : CMainApp"), TEXT("System Error"), MB_OK);
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CMainApp::Free()
{
	Safe_Release(m_pRenderer);
	Safe_Release(m_pGraphic_Device);
	Safe_Release(m_pGameInstance);		

	CGameInstance::Release_Engine();	
}
