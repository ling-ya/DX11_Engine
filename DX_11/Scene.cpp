#include "Scene.h"
#include "RenderStates.h"

Scene::Scene() :m_pWindow(nullptr),m_pLight(nullptr),m_pCamera(nullptr)
{
	m_pCube = nullptr;
	m_pPlane = nullptr;
	m_Walls.resize(4);

	m_WireFence = nullptr;
	m_water = nullptr;

	m_Mirror = nullptr;
}

void Scene::Init()
{
	//Ĭ�ϱ����е����
	m_pLight = GameObject::CreateGameObject("Light");
	m_pLight->AddComponent(new Light());//��ӵƹ����

	m_pCamera = GameObject::CreateGameObject("Camera");
	m_pCamera->GetComponent<Transform>()->SetPosition(0.0f, 0.0f, -10.0f);
	Camera* pCameraComponent = new Camera();
	pCameraComponent->SetFrustum(XM_PI/3, m_pWindow->GetAspect(), 0.5f, 1000.0f);//������׶��
	m_pCamera->AddComponent(pCameraComponent);//���������

	m_Mirror = GameObject::CreateGameObject("Mirror");
	m_Mirror->GetComponent<Transform>()->SetPosition(0.0f, 3.0f, 9.99f);
	m_Mirror->GetComponent<Transform>()->SetRotation(-XM_PIDIV2, 0.0f, 0.0f);
	MeshRender* pMirrorrender = new MeshRender(Mesh::CreatePlane(8.0f, 8.0f, 1.0f, 1.0f));
	pMirrorrender->m_pMat = new Material(Shader::Find("HLSL\\Light"));
	pMirrorrender->m_pMat->SetTexture("Texture\\ice.dds");
	pMirrorrender->m_pMat->SetDiffuse(XMFLOAT4(0.8f, 0.8f, 0.8f, 0.3f));
	m_Mirror->AddComponent(pMirrorrender);
	//��͸������

	//�ذ�
	m_pPlane = GameObject::CreateGameObject("Plane");
	m_pPlane->GetComponent<Transform>()->SetPosition(0.0f, -1.0f, 0.0f);
	MeshRender* pPlanerender = new MeshRender(Mesh::CreatePlane(20.0f,20.0f, 5.0f, 5.0f));
	pPlanerender->m_pMat = new Material(Shader::Find("HLSL\\Light"));
	pPlanerender->m_pMat->SetTexture("Texture\\floor.dds");
	m_pPlane->AddComponent(pPlanerender);

	//ǽ��
	for (int i = 0; i < 4; i++)
	{
		m_Walls[i] = GameObject::CreateGameObject("Wall");
		m_Walls[i]->GetComponent<Transform>()->SetRotation(-XM_PIDIV2, XM_PIDIV2 * i, 0.0f);
		m_Walls[i]->GetComponent<Transform>()->SetPosition(i % 2 ? -10.0f * (i - 2) : 0.0f, 3.0f, i % 2 == 0 ? -10.0f * (i - 1) : 0.0f);
		MeshRender* pWallrender = new MeshRender(Mesh::CreatePlane(20.0f, 8.0f, 5.0f, 1.5f));
		pWallrender->m_pMat = new Material(Shader::Find("HLSL\\Light"));
		pWallrender->m_pMat->SetTexture("Texture\\brick.dds");
		m_Walls[i]->AddComponent(pWallrender);
	}

	//Cube
	m_pCube = GameObject::CreateGameObject("Cube");
	//m_pCube->GetComponent<Transform>()->SetPosition(0.0f, 0.0f, 0.0f);
	//m_pCube->GetComponent<Transform>()->SetRotation(0.0f, 0.0f, 0.0f);
	MeshRender* pcuberender = new MeshRender(Mesh::CreateCube());//����������
	pcuberender->m_pMat = new Material(Shader::Find("HLSL\\Light"));
	pcuberender->m_pMat->SetTexture("Texture\\WoodCrate.dds");
	m_pCube->AddComponent(pcuberender);

	//͸������(���ǿ�������Ȳ��Ե�)
	//�Ȼ�����ʺУ�������������Ѿ��ں󱸻��������ٻ���ˮ�棬ˮ����ͨ����Ȳ��ԣ�ͨ���������ٽ��л��
	m_WireFence = GameObject::CreateGameObject("WireFence");
	m_WireFence->GetComponent<Transform>()->SetPosition(3.0f, 0.1f, 2.0f);
	MeshRender* pwireRender = new MeshRender(Mesh::CreateCube());
	pwireRender->m_pMat = new Material(Shader::Find("HLSL\\Light"));
	pwireRender->m_pMat->SetTexture("Texture\\WireFence.dds");
	//pwireRender->m_pMat->m_pRS = RenderStates::RSNoCull;
	//pwireRender->m_pMat->m_pBS = RenderStates::BSTransparent;
	m_WireFence->AddComponent(pwireRender);

	//ˮ
	m_water = GameObject::CreateGameObject("Water");
	MeshRender* pwaterRender = new MeshRender(Mesh::CreatePlane(20.0f, 20.0f, 5.0f, 5.0f));
	pwaterRender->m_pMat = new Material(Shader::Find("HLSL\\Light"));
	pwaterRender->m_pMat->SetDiffuse(XMFLOAT4(0.8f, 0.8f, 0.8f, 0.5f));
	pwaterRender->m_pMat->SetSpecluar(XMFLOAT4(0.8f, 0.8f, 0.8f, 32.0f));
	pwaterRender->m_pMat->SetTexture("Texture\\water.dds");
	//pwaterRender->m_pMat->m_pBS = RenderStates::BSTransparent;
	m_water->AddComponent(pwaterRender);
}

void Scene::UpdateScene(float deltaTime)
{
	Transform* m_CameraTrans = m_pCamera->GetComponent<Transform>();
	static XMFLOAT3 cameraRotarion = m_pCamera->GetComponent<Transform>()->GetRotation();
	static XMFLOAT3 cameraPosition = m_pCamera->GetComponent<Transform>()->GetPosition();
	//��ȡ���״̬
	Mouse::State  mouseState = m_pWindow->m_pMouse->GetState();
	Mouse::State lastMouseState = MouseTracker.GetLastState();


	//Keyboard::State keyState = m_pWindow->m_pKeyboard->GetState();
	//Keyboard::State lastKeyState = KeyboardTracker.GetLastState();
	MouseTracker.Update(mouseState);

	if (mouseState.rightButton == true && MouseTracker.rightButton == MouseTracker.HELD)
	{
		cameraRotarion.y += (mouseState.x - lastMouseState.x) * 0.001f;
		cameraRotarion.x += (mouseState.y - lastMouseState.y) * 0.001f;
	}
	m_pCamera->GetComponent<Transform>()->SetRotation(cameraRotarion);

	m_CameraTrans->Translate(m_CameraTrans->GetForwardAxis(), mouseState.scrollWheelValue / 120 * 1.0f);

	m_pWindow->m_pMouse->ResetScrollWheelValue();//���ù���ֵ


	if (mouseState.middleButton == true && MouseTracker.middleButton == MouseTracker.HELD) 
	{
		m_CameraTrans->Translate(m_CameraTrans->GetUpAxis(), (mouseState.y - lastMouseState.y) * 0.01f);
		m_CameraTrans->Translate(m_CameraTrans->GetRightAxis(), -(mouseState.x - lastMouseState.x) * 0.01f);
	}


	/*m_pCamera->GetComponent<Transform>()->SetPosition(cameraPosition);

	if (keyState.IsKeyDown(Keyboard::W)) 
	{
		m_CameraTrans->Translate(m_CameraTrans->GetUpAxis(), deltaTime * 6.0f);
	}

	if (keyState.IsKeyDown(Keyboard::S))
	{
		m_CameraTrans->Translate(m_CameraTrans->GetUpAxis(), deltaTime * -6.0f);
	}

	if (keyState.IsKeyDown(Keyboard::A))
	{
		m_CameraTrans->Translate(m_CameraTrans->GetRightAxis(), deltaTime * -6.0f);
	}
	if (keyState.IsKeyDown(Keyboard::D))
	{
		m_CameraTrans->Translate(m_CameraTrans->GetRightAxis(), deltaTime * 6.0f);
	}*/
}

/// <summary>
/// ���淴��״̬����
/// </summary>
void Scene::UpdateReflectState()
{
	m_Mirror->GetComponent<MeshRender>()->m_pMat->m_pRS = nullptr;
	m_Mirror->GetComponent<MeshRender>()->m_pMat->m_pBS = RenderStates::BSNoColorWrite;
	m_Mirror->GetComponent<MeshRender>()->m_pMat->m_pDSS = RenderStates::DSSWriteStencil;
	m_Mirror->GetComponent<MeshRender>()->m_pMat->c_TransformBuffer.isReflection = false;


	m_pPlane->GetComponent<MeshRender>()->m_pMat->m_pRS = RenderStates::RSCullClockWise;//˳ʱ��ü�
	m_pPlane->GetComponent<MeshRender>()->m_pMat->m_pBS = nullptr;
	m_pPlane->GetComponent<MeshRender>()->m_pMat->m_pDSS = RenderStates::DSSDrawWithStencil;
	m_pPlane->GetComponent<MeshRender>()->m_pMat->c_TransformBuffer.isReflection = true;

	m_pCube->GetComponent<MeshRender>()->m_pMat->m_pRS = RenderStates::RSCullClockWise;//˳ʱ��ü�
	m_pCube->GetComponent<MeshRender>()->m_pMat->m_pBS = nullptr;
	m_pCube->GetComponent<MeshRender>()->m_pMat->m_pDSS = RenderStates::DSSDrawWithStencil;
	m_pCube->GetComponent<MeshRender>()->m_pMat->c_TransformBuffer.isReflection = true;

	// ******************
	// 2. ���Ʋ�͸���ķ�������
	//
	for (int i = 0; i < 4; i++)
	{
		m_Walls[i]->GetComponent<MeshRender>()->m_pMat->m_pRS = RenderStates::RSCullClockWise;//˳ʱ��ü�
		m_Walls[i]->GetComponent<MeshRender>()->m_pMat->m_pBS = nullptr;
		m_Walls[i]->GetComponent<MeshRender>()->m_pMat->m_pDSS = RenderStates::DSSDrawWithStencil;
		m_Walls[i]->GetComponent<MeshRender>()->m_pMat->c_TransformBuffer.isReflection = true;
	}

	// ******************
	// 3. ����͸���ķ�������
	//
	m_WireFence->GetComponent<MeshRender>()->m_pMat->m_pRS = RenderStates::RSNoCull;//�޲ü�
	m_WireFence->GetComponent<MeshRender>()->m_pMat->m_pBS = RenderStates::BSTransparent;;
	m_WireFence->GetComponent<MeshRender>()->m_pMat->m_pDSS = RenderStates::DSSDrawWithStencil;
	m_WireFence->GetComponent<MeshRender>()->m_pMat->c_TransformBuffer.isReflection = true;

	m_water->GetComponent<MeshRender>()->m_pMat->m_pRS = RenderStates::RSNoCull;//�޲ü�
	m_water->GetComponent<MeshRender>()->m_pMat->m_pBS = RenderStates::BSTransparent;;
	m_water->GetComponent<MeshRender>()->m_pMat->m_pDSS = RenderStates::DSSDrawWithStencil;
	m_water->GetComponent<MeshRender>()->m_pMat->c_TransformBuffer.isReflection = true;
}

void Scene::UpdateNormalState()
{
	m_Mirror->GetComponent<MeshRender>()->m_pMat->m_pRS = RenderStates::RSNoCull;//�޲ü�
	m_Mirror->GetComponent<MeshRender>()->m_pMat->m_pBS = RenderStates::BSTransparent;;
	m_Mirror->GetComponent<MeshRender>()->m_pMat->m_pDSS = RenderStates::DSSDrawWithStencil;
	m_Mirror->GetComponent<MeshRender>()->m_pMat->c_TransformBuffer.isReflection = true;

	////������������
	for (int i = 0; i < 4; i++)
	{
		m_Walls[i]->GetComponent<MeshRender>()->m_pMat->m_pRS = nullptr;//˳ʱ��ü�
		m_Walls[i]->GetComponent<MeshRender>()->m_pMat->m_pBS = nullptr;
		m_Walls[i]->GetComponent<MeshRender>()->m_pMat->m_pDSS = nullptr;
		m_Walls[i]->GetComponent<MeshRender>()->m_pMat->c_TransformBuffer.isReflection = false;
	}

	m_pPlane->GetComponent<MeshRender>()->m_pMat->m_pRS = nullptr;//˳ʱ��ü�
	m_pPlane->GetComponent<MeshRender>()->m_pMat->m_pBS = nullptr;
	m_pPlane->GetComponent<MeshRender>()->m_pMat->m_pDSS = nullptr;
	m_pPlane->GetComponent<MeshRender>()->m_pMat->c_TransformBuffer.isReflection = false;

	m_pCube->GetComponent<MeshRender>()->m_pMat->m_pRS = nullptr;//˳ʱ��ü�
	m_pCube->GetComponent<MeshRender>()->m_pMat->m_pBS = nullptr;
	m_pCube->GetComponent<MeshRender>()->m_pMat->m_pDSS = nullptr;
	m_pCube->GetComponent<MeshRender>()->m_pMat->c_TransformBuffer.isReflection = false;

	m_WireFence->GetComponent<MeshRender>()->m_pMat->m_pRS = RenderStates::RSNoCull;//�޲ü�
	m_WireFence->GetComponent<MeshRender>()->m_pMat->m_pBS = RenderStates::BSTransparent;;
	m_WireFence->GetComponent<MeshRender>()->m_pMat->m_pDSS = nullptr;
	m_WireFence->GetComponent<MeshRender>()->m_pMat->c_TransformBuffer.isReflection = false;

	m_water->GetComponent<MeshRender>()->m_pMat->m_pRS = RenderStates::RSNoCull;//�޲ü�
	m_water->GetComponent<MeshRender>()->m_pMat->m_pBS = RenderStates::BSTransparent;;
	m_water->GetComponent<MeshRender>()->m_pMat->m_pDSS = nullptr;
	m_water->GetComponent<MeshRender>()->m_pMat->c_TransformBuffer.isReflection = false;
}

/// <summary>
///���淴��״̬����
/// </summary>
//void Scene::UpdateNormalState()
//{
//	//���÷�������
//	// ******************
//	// 1. �����淴������д��ֵ1��ģ�建����
//	// 
//	m_Mirror->GetComponent<MeshRender>()->m_pMat->m_pRS = nullptr;
//	m_Mirror->GetComponent<MeshRender>()->m_pMat->m_pBS = RenderStates::BSNoColorWrite;
//	m_Mirror->GetComponent<MeshRender>()->m_pMat->m_pDSS = RenderStates::DSSWriteStencil;
//	//m_Mirror->GetComponent<MeshRender>()->m_pMat->c_TransformBuffer.isReflection = false;
//
//	// ******************
//	// 2. ���Ʋ�͸���ķ�������
//	//
//	//for (int i = 0; i < 4; i++)
//	//{
//	//	m_Walls[i]->GetComponent<MeshRender>()->m_pMat->m_pRS = RenderStates::RSCullClockWise;//˳ʱ��ü�
//	//	m_Walls[i]->GetComponent<MeshRender>()->m_pMat->m_pBS = nullptr;
//	//	m_Walls[i]->GetComponent<MeshRender>()->m_pMat->m_pDDS = RenderStates::DSSDrawWithStencil;
//	//	m_Walls[i]->GetComponent<MeshRender>()->m_pMat->c_TransformBuffer.isReflection = true;
//	//}
//
//	//m_pPlane->GetComponent<MeshRender>()->m_pMat->m_pRS = RenderStates::RSCullClockWise;//˳ʱ��ü�
//	//m_pPlane->GetComponent<MeshRender>()->m_pMat->m_pBS = nullptr;
//	//m_pPlane->GetComponent<MeshRender>()->m_pMat->m_pDDS = RenderStates::DSSDrawWithStencil;
//	//m_pPlane->GetComponent<MeshRender>()->m_pMat->c_TransformBuffer.isReflection = true;
//
//	//m_pCube->GetComponent<MeshRender>()->m_pMat->m_pRS = RenderStates::RSCullClockWise;//˳ʱ��ü�
//	//m_pCube->GetComponent<MeshRender>()->m_pMat->m_pBS = nullptr;
//	//m_pCube->GetComponent<MeshRender>()->m_pMat->m_pDDS = RenderStates::DSSDrawWithStencil;
//	//m_pCube->GetComponent<MeshRender>()->m_pMat->c_TransformBuffer.isReflection = true;
//	//// ******************
//	//// 3. ����͸���ķ�������
//	////
//	//m_WireFence->GetComponent<MeshRender>()->m_pMat->m_pRS = RenderStates::RSNoCull;//�޲ü�
//	//m_WireFence->GetComponent<MeshRender>()->m_pMat->m_pBS = RenderStates::BSTransparent;;
//	//m_WireFence->GetComponent<MeshRender>()->m_pMat->m_pDDS = RenderStates::DSSDrawWithStencil;
//	//m_WireFence->GetComponent<MeshRender>()->m_pMat->c_TransformBuffer.isReflection = true;
//
//	//m_water->GetComponent<MeshRender>()->m_pMat->m_pRS = RenderStates::RSNoCull;//�޲ü�
//	//m_water->GetComponent<MeshRender>()->m_pMat->m_pBS = RenderStates::BSTransparent;;
//	//m_water->GetComponent<MeshRender>()->m_pMat->m_pDDS = RenderStates::DSSDrawWithStencil;
//	//m_water->GetComponent<MeshRender>()->m_pMat->c_TransformBuffer.isReflection = true;
//}
