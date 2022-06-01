#include "Camera_Manager.h"

IMPLEMENT_SINGLETON(CCamera_Manager)

CCamera_Manager::CCamera_Manager()
{
}

HRESULT CCamera_Manager::Add_Prototype(const _tchar* pPrototypeTag, CCamera* pPrototype)
{
	if (nullptr != Find_Camera(pPrototypeTag))
		return E_FAIL;
	m_pPrototypes.emplace(pPrototypeTag, pPrototype);

	return S_OK;
}

CCamera* CCamera_Manager::Clone_Camera(const _tchar* pPrototypeTag, void* pArg)
{
	if (m_pPrototypes.empty())
		return nullptr;

	CCamera* pPrototype = Find_Camera(pPrototypeTag);
	if (nullptr == pPrototype)
		return nullptr;
	return pPrototype->Clone(pArg);
}

HRESULT CCamera_Manager::Set_MainCamera(CCamera* camera)
{
	if (nullptr == camera)
		return E_FAIL;
	m_pMainCamera = camera;
	return S_OK;
}

CCamera* CCamera_Manager::Get_MainCamera()
{
	return m_pMainCamera;
}

CCamera* CCamera_Manager::Find_Camera(const _tchar* pPrototypeTag)
{
	auto	iter = find_if(m_pPrototypes.begin(), m_pPrototypes.end(), CTag_Finder(pPrototypeTag));

	if (iter == m_pPrototypes.end())
		return nullptr;

	return iter->second;
}

void CCamera_Manager::Free()
{
	for (auto& Pair : m_pPrototypes)
		Safe_Release(Pair.second);
	m_pPrototypes.clear();
}

