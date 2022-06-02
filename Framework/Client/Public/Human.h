#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CVIBuffer_Cube;
class CTransform;
class CFirstPersonCamera;
class CThirdPersonCamera;
END

BEGIN(Client)

class CHuman final : public CGameObject
{
private:
	CHuman(LPDIRECT3DDEVICE9 pGraphic_Device);
	CHuman(const CHuman& Prototype);
	virtual ~CHuman() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg)override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;
private:
	void					Set_Parent_Child(class CCube* _pParent, class CCube* _pChild);
private:
	CRenderer*				m_pRendererCom = nullptr;
	CTransform*				m_pTransformCom = nullptr;
	CFirstPersonCamera*		m_pFirstPersonCameraCom = nullptr;
	CThirdPersonCamera*		m_pThirdPersonCameraCom = nullptr;
private: /* 현재 객체에게 필요한 컴포넌트를 복제해온다. */
	HRESULT SetUp_Components();
	HRESULT SetUp_Parts();
	CCube* Find_Parts(const _tchar* partsName);


private:
	typedef map<const _tchar*, class CCube*>	PARTS;
	PARTS										m_Parts;
	CCube*										m_pRoot = nullptr;
public:
	static CHuman* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
private:

};

END