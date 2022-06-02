#pragma once

#include "Component.h"

/* 부모클래스다. */

/* Vertex Buffer, Index Buffer */

BEGIN(Engine)

class ENGINE_DLL CVIBuffer abstract : public CComponent
{
protected:
	CVIBuffer(LPDIRECT3DDEVICE9 pGraphic_Device);
	CVIBuffer(const CVIBuffer& Prototype);
	virtual ~CVIBuffer() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
public:
	LPDIRECT3DVERTEXBUFFER9			Get_VertexBuffer();
	LPDIRECT3DINDEXBUFFER9			Get_IndexBuffer();
	virtual HRESULT					Render() = 0;
protected:
	LPDIRECT3DVERTEXBUFFER9			m_pVB = nullptr;
	_uint							m_iStride = 0; /* 정점하나의 바이트 크기 .*/
	_uint							m_iNumVertices = 0; /* 정점의 갯수 */
	_ulong							m_dwFVF = 0;
protected:
	LPDIRECT3DINDEXBUFFER9			m_pIB = nullptr;
	_uint							m_iIndexSize = 0;
	_uint							m_iNumIndices = 0;

protected:
	virtual HRESULT Create_VertexBuffer();
	virtual HRESULT Create_IndexBuffer();
public:	
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free() override;

};

END