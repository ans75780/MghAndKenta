#include "Graphic_Device.h"

IMPLEMENT_SINGLETON(CGraphic_Device)

CGraphic_Device::CGraphic_Device()
	: m_p3D(nullptr) , m_pDevice(nullptr), m_pSprite(nullptr), m_pFont(nullptr)
{

}

HRESULT CGraphic_Device::InitDevice(const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut)
{
	// HRESULT : �Լ��� ȣ�� ���� ������ ���� ����� ��� �������
	// ������ �ִ� ���·� ����� ��� �������� ��ȯ��Ű�� ���� �ڷ���

	// (�׸���)��ġ �ʱ�ȭ : ��ġ�� ������ ��ü ����(m_p3D) -> ��ġ ���� -> ��ġ ���� ��ü ����(m_pDevice)

	// Direct3DCreate9 : LPDIRECT3D9 ��ü�� SDK ������ �°� �����ϴ� �Լ�
	m_p3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9			DeviceCaps;
	// 3D�������� �ʿ��� �⺻���� ������ �����ϴ��� �����Ͽ� ���� ������ �����ϱ� ���� ����ü
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	// FAILED ��ũ�� :hresult ��ȯŸ���� ������ ��� true
	// GetDeviceCaps : ��ġ ������ ����
	// D3DADAPTER_DEFAULT :������ �������� �⺻ �׷��� ī�带 �ǹ�
	// D3DDEVTYPE_HAL : HAL(hardware abstraction layer)�� ����Ǿ� �ִ� ��ġ�� �ʼ� ������ ������ ���� �־��ִ� ���ڰ�
	if (FAILED(m_p3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		MSG_BOX("GetDeviceCaps Failed"); // mfc������ ��밡���� �޼��� �ڽ� �Լ�
		return E_FAIL;
	}

	DWORD	vp = 0;		// ���ؽ� ���μ��� : ���� ���� + ���� ó��

	// HAL �� ���� ������ ��ġ�� �ϵ���� ���ؽ� ���μ����� �����ϴ��� �Ǵ�
	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;		// �׷��� ī��

	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;		// ���� ����(CPU)

	D3DPRESENT_PARAMETERS		d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	SetParameters(GraphicDesc, d3dpp);

	if (FAILED(m_p3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GraphicDesc.hWnd, vp, &d3dpp, &m_pDevice)))
	{
		MSG_BOX("CreateDevice Failed"); // mfc������ ��밡���� �޼��� �ڽ� �Լ�
		return E_FAIL;
	}

	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		MSG_BOX("m_pSprite Failed");
		return E_FAIL;
	}

	D3DXFONT_DESCW	tFontInfo;
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESCW));

	tFontInfo.Height = 20;
	tFontInfo.Width = 10;
	tFontInfo.Weight = FW_HEAVY;
	tFontInfo.CharSet = HANGEUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, L"�ü�");
	
	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo, &m_pFont)))
	{
		MSG_BOX("m_pFont Failed");
		return E_FAIL;
	}

	*ppOut = m_pDevice;

	Safe_AddRef(m_pDevice);

	return S_OK;
}

void CGraphic_Device::SetParameters(const GRAPHICDESC& GraphicDesc, D3DPRESENT_PARAMETERS & d3dpp)
{
	d3dpp.BackBufferWidth = GraphicDesc.iWinCX;
	d3dpp.BackBufferHeight = GraphicDesc.iWinCY;

	// �ĸ� ������ �ȼ� ���� , 32��Ʈ ���� ���
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	
	// �ĸ� ������ ����
	d3dpp.BackBufferCount = 1;

	// �ȼ��� �� �߻��ϴ� ��������� ������ �ε巴�� �����ϴ� ���(��Ƽ �������)�� �����ϴ��� ���θ� ���� ���ڰ�
	// �ڿ������� ������ ������ �������ϰ� �߻��ϱ� ������ ������� ���� ����
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	// ���簡 �ƴ� ��ü ����� ���� �׸���� ����⸦ �ϰԲ� ������ش�.
	
	// D3DSWAPEFFECT_DISCARD : ���� ü�� ���
	// D3DSWAPEFFECT_FLIP : ���� �ϳ��� �������鼭 ����ϴ� ���
	// D3DSWAPEFFECT_COPY : ���� ���۸��� �����ϰ� �����Ͽ� ����ϴ� ���

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = GraphicDesc.hWnd;	// ��ġ�� ����� ������ �ڵ� ����
	
	d3dpp.Windowed = GraphicDesc.isWindowMode; // TRUE�� ��� â���, FALSE ��ü ȭ�� ���

	// ���ٽ� ���� : �ݻ�� ���� ��ü�� ǥ���ϴ� ����
	// ���� ����(Z����) : ��ü�� ���� ���� �����Ͽ� ���ٰ��� ǥ���ϱ� ���� ����
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	// ��üȭ�� �ÿ� ����ϴ� ���ڰ�
	// â ��� �� ��� ��ġ�� �ƴ� �ü���� ������� ������
	// ��ü ȭ������ ���� �� ����� ������� ���� ����
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	
	// ������� �ÿ��� ���� ����
	// D3DPRESENT_INTERVAL_IMMEDIATE : ��� �ÿ�
	// D3DPRESENT_INTERVAL_DEFAULT : ������ ������ DIRECTX �˾Ƽ� ����, ���� ����� ������� ����
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}

void CGraphic_Device::Render_Begin(void)
{
	// ������ ���� : �ĸ� ���۸� ���� ����(�����)-> �ĸ� ���ۿ� �׸���-> �ĸ���ۿ� ����� ���ǽ��� ������ۿ� ����� ���ǽ��� ��ü�Ͽ� ����Ѵ�.

	// 1���� : ������� �ϴ� ��Ʈ�� ����
	// 2���� : ������� �ϴ� ��Ʈ �迭�� �̸�(nullptr�� ��� ��ü ȭ�� ������ �ش��ϴ� ���Ͷ�� �ǹ�)

	m_pDevice->Clear(0,
		nullptr,
		D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB(255, 124, 124, 124),	// ����� ����
		1.f, // z������ �ʱ�ȭ ��
		0);	 // ���ٽ� ������ �ʱ�ȭ ��

	//���⼭���� �ĸ���ۿ� �׸��� ������ �˸���.
	m_pDevice->BeginScene();

	// 2D �̹����� �׸� �� �ֵ��� ��ġ���� �˸�, ���� ������ �ɼ��� �Ű������� �־���
	// �����׽�Ʈ�� ��ȿ�� ���¿��� ���ĺ������� ����ϰڴٴ� �ɼ�
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

}

void CGraphic_Device::Render_End(HWND hWnd)
{
	m_pSprite->End();
	m_pDevice->EndScene();

	// �ĸ���ۿ� ����Ǿ� �ִ� ���ǽ��� ���� ���ۿ� ����� ���ǽ��� ��ȯ�ϴ� ����
	m_pDevice->Present(nullptr, nullptr, hWnd, nullptr);
	// 1,2���� : ����ü�� ����� D3DSWAPEFFECT_COPY�� �ƴ� �̻� NULL
	// 3���� : ��� ��� ������ �ڵ�, �⺻ nullptr�� ��� d3dpp.hDeviceWindow�� ����
	// 4���� :  ����ü�� ����� D3DSWAPEFFECT_COPY�� �ƴ� �̻� NULL

}

void CGraphic_Device::Free()
{
	if (0 != Safe_Release(m_pFont))
		MSG_BOX("Failed To Release : Font");

	if (0 != Safe_Release(m_pSprite))
		MSG_BOX("Failed To Release : Sprite");
	
	if (0 != Safe_Release(m_pDevice))
		MSG_BOX("Failed To Release : Device");

	if (0 != Safe_Release(m_p3D))
		MSG_BOX("Failed To Release : SDK");
}