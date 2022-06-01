#include "stdafx.h"
#include "Cube.h"
#include "GameInstance.h"
#include "../Default/FirstPersonCamera.h"
CCube::CCube(LPDIRECT3DDEVICE9 pGraphic_Device)
    :CGameObject(pGraphic_Device)
{
}

CCube::CCube(const CCube& Prototype):
    CGameObject(Prototype)
{
}

HRESULT CCube::Initialize_Prototype()
{
    return S_OK;
}

HRESULT CCube::Initialize(void* pArg)
{
    if (FAILED(SetUp_Components()))
        return E_FAIL;
    if (FAILED(SetUp_DrawData()))
        return E_FAIL;
  
    return S_OK;
}

void CCube::Tick(_float fTimeDelta)
{
    __super::Tick(fTimeDelta);

    //���۸� Lock�ϰ� Unlock�ϴ� ����?
   /*
       ������ �������� ������ ��������.
       ������ �������� ���� �ƹ��������� Ÿ�� ���� �� �ִٰ� �ĺ���.
       �� ��𼭵� Ż �� ������ �����ϱ��ϰ���
       �ٵ� ���࿡ �ϰ� ������ �Ҿ������.
       ����������� ����� ���ؾ�����
       �����Ȱ��� �׳�.
       �׷��� �׳� �����尰�� ������ �ּ�
       ������ ���������� ���ؽ��� �Է¹��� �� �ֵ��� �ߴٰ�
       ��������.
       Lock�� Unlock�� �������ΰ���.

   */
   //z�� -�ϼ��� ������ ��
   //z�� +�ϼ��� �ڷΰ�
   //�����غ��ϱ� z���۵� �ڷ� ������ ���� Ŀ�����ʾҳ�
    Vertex* vertices;
    m_pVertexBuffer->Lock(0, 0, (void**)&vertices, 0);
    vertices[0] = Vertex(-1.0f, -1.0f, -1.0f);
    vertices[1] = Vertex(-1.0f, 1.0f, -1.0f);
    vertices[2] = Vertex(1.0f, 1.0f, -1.0f);
    vertices[3] = Vertex(1.0f, -1.0f, -1.0f);

    vertices[4] = Vertex(-1.0f, -1.0f, 1.0f);
    vertices[5] = Vertex(-1.0f, 1.0f, 1.0f);
    vertices[6] = Vertex(1.0f, 1.0f, 1.0f);
    vertices[7] = Vertex(1.0f, -1.0f, 1.0f);

    m_pVertexBuffer->Unlock();
    WORD* indices = 0;
    m_pIndexBuffer->Lock(0, 0, (void**)&indices, 0);

    //�ո�
    indices[0] = 0; indices[1] = 1; indices[2] = 2;
    indices[3] = 0; indices[4] = 2; indices[5] = 3;

    /*
    ??? �ո��̶� �޸��̶� ���ؽ���ġ�� Z������ ���� �ٸ��� ���µ� ��
    �׷����� ������ ����� �׸���???
    4 5 6 �� �ð�����̰�
    465�� �ð� �ݴ�����ε�
    476�� �ð� �ݴ�����̰�
    ->����
    �ĸ� �߷����⸦ �Ҷ� �ð� �ݴ�������� ������ �ֵ��� ���������ϱ�
    �ڿ� �׷����¾ֵ��� �ð� �ݴ�������� �׸��°���. �׸��� �ڿ� �ֵ���
    �ð�������� �׸��� 180�� ȸ�������� �� �ڿ� ���¾ֵ��� �ð� �ݴ�������� ���� ��
    (�ð���⿡�� ������������ �ð� �ݴ������ �ǰ���) �׷��� �տ� �׷����� �ֵ���
    ���󰡺ذ� ����� �׸��°���.
*/
//�׷����� ���� ����Ƴ���¥
// �޸�
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
    m_pIndexBuffer->Unlock();

    _float3 pos = m_pTransformCom->Get_Position();
    pos.z -= 5;
    m_pCamera->Get_Transform()->Set_Position(pos);
    if (GetKeyState(VK_SHIFT) & 0x8000)
    {
        m_pCamera->Set_MainCamera();
    }
    m_pTransformCom->Rotate(_float3(0.001f, 0, 0));
}

void CCube::LateTick(_float fTimeDelta)
{
    if (nullptr == m_pRendererCom)
        return;

    m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
}

HRESULT CCube::Render()
{
    m_pTransformCom->Calc_World();
    _float4x4 world;
    world = m_pTransformCom->Get_Wolrd();
    m_pGraphic_Device->SetTransform(D3DTS_WORLD, &world);
    m_pGraphic_Device->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(Vertex));//���ؽ� ��Ʈ�� ����
    m_pGraphic_Device->SetIndices(m_pIndexBuffer);//�ε��� ���� ����
    m_pGraphic_Device->SetFVF(CUSTOM_FVF);//���ؽ� Ÿ�� ����
    m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//�ĸ� �߷����� �ɼ� ����
    m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

    //CCW�� ��� �ð� �ݴ�������� �׷��� �ֵ�
    m_pGraphic_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);//���� �׸��� ����

    return S_OK;
}

HRESULT CCube::SetUp_Components()
{
    CGameInstance* pGameInstance = CGameInstance::Get_Instance();
    Safe_AddRef(pGameInstance);

    /* For.Com_Renderer */
    m_pRendererCom = (CRenderer*)pGameInstance->Clone_Component(LEVEL_STATIC, TEXT("Prototype_Component_Renderer"));
    if (nullptr == m_pRendererCom)
        return E_FAIL;

    m_pTransformCom = (CTransform*)pGameInstance->Clone_Component(LEVEL_STATIC, TEXT("Prototype_Component_Transform"));
    if (nullptr == m_pTransformCom)
        return E_FAIL;
    
    _float4x4 temp = m_pTransformCom->Get_Wolrd();

    m_pCamera = (CCamera*)pGameInstance->Clone_Camera(TEXT("Prototype_Camera_FirstPerson"));
    if (nullptr == m_pCamera)
        return E_FAIL;
    m_pCamera->Set_MainCamera();

    Safe_Release(pGameInstance);
    return S_OK;
}

HRESULT CCube::SetUp_DrawData()
{
    //���ؽ��� �ʱ�ȭ(�� ���� �ʱ�ȭ)
    m_pGraphic_Device->CreateVertexBuffer(
        8 * sizeof(Vertex),
        D3DUSAGE_WRITEONLY,
        CUSTOM_FVF,
        D3DPOOL_MANAGED,
        &m_pVertexBuffer,
        0);
    m_pGraphic_Device->CreateIndexBuffer(
        36 * sizeof(WORD),
        D3DUSAGE_WRITEONLY,
        D3DFMT_INDEX16,
        D3DPOOL_MANAGED,
        &m_pIndexBuffer,
        0);
    return S_OK;
}

CCube* CCube::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
    CCube* pInstance = new CCube(pGraphic_Device);

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed to Created : CBackGround");
        Safe_Release(pInstance);
    }

    return pInstance;
}

CGameObject* CCube::Clone(void* pArg)
{
    CCube* pInstance = new CCube(*this);

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Created : CBackGround");
        Safe_Release(pInstance);
    }

    return pInstance;
}

void CCube::Free()
{
    __super::Free();

    Safe_Release(m_pRendererCom);
    Safe_Release(m_pTransformCom);

    Safe_Release(m_pVertexBuffer);
    Safe_Release(m_pIndexBuffer);
    Safe_Release(m_pCamera);
}
