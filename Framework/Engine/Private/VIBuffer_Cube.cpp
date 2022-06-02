#include "..\Public\VIBuffer_Cube.h"

CVIBuffer_Cube::CVIBuffer_Cube(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CVIBuffer(pGraphic_Device)
{
}

CVIBuffer_Cube::CVIBuffer_Cube(const CVIBuffer_Cube & Prototype)
	: CVIBuffer(Prototype)
{

}

HRESULT CVIBuffer_Cube::Initialize_Prototype()
{
	
	return S_OK;
}

HRESULT CVIBuffer_Cube::Initialize(void * pArg)
{
	m_iStride = sizeof(VTX);
	m_iNumVertices = 8;
	m_dwFVF = D3DFVF_XYZ; /* | D3DFVF_TEXCOORDSIZE2(0) */
	
	/* 정점배열이 할당된다. */
	if (FAILED(__super::Create_VertexBuffer()))
		return E_FAIL;
	VTX*			pVertices = nullptr;	
	m_pVB->Lock(0, m_iStride * m_iNumVertices, (void**)&pVertices, 0);

	pVertices[0] = VTX(-1.0f, -1.0f, -1.0f);
	pVertices[1] = VTX(-1.0f, 1.0f, -1.0f);
	pVertices[2] = VTX(1.0f, 1.0f, -1.0f);
	pVertices[3] = VTX(1.0f, -1.0f, -1.0f);

	pVertices[4] = VTX(-1.0f, -1.0f, 1.0f);
	pVertices[5] = VTX(-1.0f, 1.0f, 1.0f);
	pVertices[6] = VTX(1.0f, 1.0f, 1.0f);
	pVertices[7] = VTX(1.0f, -1.0f, 1.0f);

	m_pVB->Unlock();

	m_iIndexSize = sizeof(WORD);
	m_iNumIndices = 36;
	if (FAILED(__super::Create_IndexBuffer()))
		return E_FAIL;
	WORD* indices = 0;
	m_pIB->Lock(0, 0, (void**)&indices, 0);

	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;
	// 뒷면
	indices[6] = 4; indices[7] = 6; indices[8] = 5;
	indices[9] = 4; indices[10] = 7; indices[11] = 6;
	// left side 
	indices[12] = 4; indices[13] = 5; indices[14] = 1;
	indices[15] = 4; indices[16] = 1; indices[17] = 0;
	// right side
	indices[18] = 3; indices[19] = 2; indices[20] = 6;
	indices[21] = 3; indices[22] = 6; indices[23] = 7;
	// top
	indices[24] = 1; indices[25] = 5; indices[26] = 6;
	indices[27] = 1; indices[28] = 6; indices[29] = 2;
	// bottom
	indices[30] = 4; indices[31] = 0; indices[32] = 3;
	indices[33] = 4; indices[34] = 3; indices[35] = 7;

	m_pIB->Unlock();

	return S_OK;
}

HRESULT CVIBuffer_Cube::Render()
{
	m_pGraphic_Device->SetStreamSource(0, m_pVB, 0, sizeof(VTX));//버텍스 스트림 설정
	m_pGraphic_Device->SetIndices(m_pIB);//인덱스 버퍼 설정
	m_pGraphic_Device->SetFVF(m_dwFVF);//버텍스 타입 설정
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//후면 추려내기 옵션 설정
	m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//CCW일 경우 시계 반대방향으로 그려진 애들
	m_pGraphic_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);//도형 그리기 세팅
	return S_OK;
}

void CVIBuffer_Cube::Update_Vertex()
{
	
}

CVIBuffer_Cube * CVIBuffer_Cube::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CVIBuffer_Cube*		pInstance = new CVIBuffer_Cube(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CVIBuffer_Cube");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CVIBuffer_Cube::Clone(void * pArg)
{
	CVIBuffer_Cube* pInstance = new CVIBuffer_Cube(*this);

	if (FAILED(pInstance->Initialize(nullptr)))
	{
		MSG_BOX("Failed to Clone : CVIBuffer_Cube");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CVIBuffer_Cube::Free()
{
	__super::Free();

}
