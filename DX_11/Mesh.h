#pragma once
#include<wrl/client.h>
#include <vector>
#include<DirectXMath.h>
using namespace DirectX;
using namespace std;

class Mesh
{
public:
	Mesh();
	~Mesh() = default;
	void SetVertices(XMFLOAT3* vertices, UINT num);
	void SetVertNormal(XMFLOAT3* vertNormal, UINT num);
	void SetVertTangent(XMFLOAT4* vertTangent, UINT num);
	void SetVertColor(XMFLOAT4* color, UINT num);
	void SetVertTex(XMFLOAT2* tex, UINT num);
	void SetIndex(UINT* index, UINT num);
	static Mesh* CreatePlane(float width = 10.0f, float depth = 10.0f, float texU = 1.0f, float texV = 1.0f);
	static Mesh* CreateCube(float width = 2.0f, float height = 2.0f, float depth = 2.0f);
	static Mesh* CreateSphere(float radius = 1.0f, UINT levels = 20, UINT slices = 20);
	static Mesh* CreateTriangle(float width = 1.0f, float height = 1.0f);
	static Mesh* CreateTeapot();
public:
	vector<XMFLOAT3> m_verticesList;
	vector<XMFLOAT3> m_vertiNormalList;
	vector<XMFLOAT4> m_vertTangentList;
	vector<XMFLOAT4> m_vectColorList;
	vector<XMFLOAT2> m_vectTexList;
	vector<UINT> m_IndexList;
	UINT m_vertexCount;
	UINT m_offset = 0;
};

