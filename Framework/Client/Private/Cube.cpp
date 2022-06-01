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

    //버퍼를 Lock하고 Unlock하는 이유?
   /*
       버스와 정류장의 관계라고 생각했음.
       버스가 정류장이 없이 아무곳에서나 타고 내릴 수 있다고 쳐보자.
       뭐 어디서든 탈 수 있으니 개편하긴하겠지
       근데 만약에 니가 지갑을 잃어버렸음.
       버스기사한테 뭐라고 말해야하지
       개좆된거임 그냥.
       그래서 그냥 정류장같은 개념을 둬서
       한정된 공간에서만 버텍스를 입력받을 수 있도록 했다고
       생각했음.
       Lock와 Unlock가 정류장인거임.

   */
   //z가 -일수록 앞으로 옴
   //z가 +일수록 뒤로감
   //생각해보니까 z버퍼도 뒤로 갈수록 값이 커지지않았나
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

    //앞면
    indices[0] = 0; indices[1] = 1; indices[2] = 2;
    indices[3] = 0; indices[4] = 2; indices[5] = 3;

    /*
    ??? 앞면이랑 뒷면이랑 버텍스위치는 Z값말고 말고 다른게 없는데 왜
    그려지는 순서를 뒤집어서 그리지???
    4 5 6 이 시계방향이고
    465는 시계 반대방향인데
    476도 시계 반대방향이고
    ->이유
    후면 추려내기를 할때 시계 반대방향으로 뒤집힌 애들을 날려버리니까
    뒤에 그려지는애들은 시계 반대방향으로 그리는거임. 그리고 뒤에 애들을
    시계방향으로 그리면 180도 회전시켰을 때 뒤에 오는애들이 시계 반대방향으로 오게 됨
    (시계방향에서 뒤집혀졌으니 시계 반대방향이 되겠지) 그러면 앞에 그려지는 애들이
    날라가붕게 뒤집어서 그리는거임.
*/
//그려지는 순서 개어렵네진짜
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
    m_pGraphic_Device->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(Vertex));//버텍스 스트림 설정
    m_pGraphic_Device->SetIndices(m_pIndexBuffer);//인덱스 버퍼 설정
    m_pGraphic_Device->SetFVF(CUSTOM_FVF);//버텍스 타입 설정
    m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//후면 추려내기 옵션 설정
    m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

    //CCW일 경우 시계 반대방향으로 그려진 애들
    m_pGraphic_Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);//도형 그리기 세팅

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
    //버텍스의 초기화(점 개수 초기화)
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
