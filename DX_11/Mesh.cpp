#include "Mesh.h"


Mesh::Mesh():m_vertexCount(0)
{
}

void Mesh::SetVertices(XMFLOAT3* vertices, UINT num)
{
	if (vertices != nullptr)
	{
		m_verticesList.clear();
		for (UINT i = 0; i < num; i++)
		{
			m_verticesList.push_back(vertices[i]);
		}
	}
}

void Mesh::SetVertNormal(XMFLOAT3* vertNormal, UINT num)
{
	if (vertNormal != nullptr)
	{
		m_vertiNormalList.clear();
		for (UINT i = 0; i < num; i++)
		{
			m_vertiNormalList.push_back(vertNormal[i]);
		}
	}
}

void Mesh::SetVertTangent(XMFLOAT4* vertTangent, UINT num)
{
	if (vertTangent != nullptr)
	{
		m_vertTangentList.clear();
		for (UINT i = 0; i < num; i++)
		{
			m_vertTangentList.push_back(vertTangent[i]);
		}
	}
}

void Mesh::SetVertColor(XMFLOAT4* color, UINT num)
{
	if (color != nullptr)
	{
		m_vectColorList.clear();
		for (UINT i = 0; i < num; i++)
		{
			m_vectColorList.push_back(color[i]);
		}
	}
}

void Mesh::SetVertTex(XMFLOAT2* tex, UINT num)
{
	if (tex != nullptr)
	{
		for (UINT i = 0; i < num; i++)
		{
			m_vectTexList.push_back(tex[i]);
		}
	}
}

void Mesh::SetIndex(UINT* index, UINT num)
{
	if (index != nullptr)
	{
		m_IndexList.clear();
		for (UINT i = 0; i < num; i++)
		{
			m_IndexList.push_back(index[i]);
		}
	}
}

Mesh* Mesh::CreatePlane(float width, float depth, float texU, float texV)
{
	Mesh* pMesh = new Mesh();
	float w = width / 2, d = depth / 2;
	vector<XMFLOAT3> verticesList;
	vector<XMFLOAT3> vertNormaList;
	vector<XMFLOAT4> vectColorList;
	vector<XMFLOAT2> vectTexList;
	vector<UINT> indexList;

	verticesList.push_back(XMFLOAT3(-w, 0.0f, -d));//左下点
	verticesList.push_back(XMFLOAT3(-w, 0.0f, d));//左上点
	verticesList.push_back(XMFLOAT3(w, 0.0f, d));//右上点
	verticesList.push_back(XMFLOAT3(w, 0.0f, -d));//左下点
	vertNormaList.push_back(XMFLOAT3(0.0f, 1.0f, 0.0f));
	vertNormaList.push_back(XMFLOAT3(0.0f, 1.0f, 0.0f));
	vertNormaList.push_back(XMFLOAT3(0.0f, 1.0f, 0.0f));
	vertNormaList.push_back(XMFLOAT3(0.0f, 1.0f, 0.0f));
	vectTexList.push_back(XMFLOAT2(0.0f, texV));
	vectTexList.push_back(XMFLOAT2(0.0f, 0.0f));
	vectTexList.push_back(XMFLOAT2(texU, 0.0f));
	vectTexList.push_back(XMFLOAT2(texU, texV));

	for (UINT i = 0; i < 4; i++)
	{
		vectColorList.push_back(XMFLOAT4(1, 1, 1, 1));
	}

	indexList = { 0, 1, 2, 2, 3, 0 };

	pMesh->SetVertices(verticesList.data(), (UINT)verticesList.size());
	pMesh->SetVertNormal(vertNormaList.data(), (UINT)vertNormaList.size());
	pMesh->SetVertTex(vectTexList.data(), (UINT)vectTexList.size());
	pMesh->SetIndex(indexList.data(), (UINT)indexList.size());
	pMesh->SetVertColor(vectColorList.data(), (UINT)vectColorList.size());
	pMesh->m_vertexCount = (UINT)verticesList.size();
	return pMesh;
}

Mesh* Mesh::CreateCube(float width, float height, float depth)
{
	Mesh* pMesh = new Mesh();

	float w = width / 2, h = height / 2, d = depth / 2;
	vector<XMFLOAT3> verticesList;
	vector<XMFLOAT3> vertNormaList;
	vertNormaList.resize(24);
	vector<XMFLOAT4> vectColorList;
	vectColorList.resize(24);
	vector<XMFLOAT2> vectTexList;
	vectTexList.resize(24);
	vector<UINT> indexList;
	//右面(+X面)
	verticesList.push_back(XMFLOAT3(w, -h, -d));
	verticesList.push_back(XMFLOAT3(w, h, -d));
	verticesList.push_back(XMFLOAT3(w, h, d));
	verticesList.push_back(XMFLOAT3(w, -h, d));


	//左面(-X面)
	verticesList.push_back(XMFLOAT3(-w, -h, d));
	verticesList.push_back(XMFLOAT3(-w, h, d));
	verticesList.push_back(XMFLOAT3(-w, h, -d));
	verticesList.push_back(XMFLOAT3(-w, -h, -d));

	//顶面(+Y面)
	verticesList.push_back(XMFLOAT3(-w, h, -d));
	verticesList.push_back(XMFLOAT3(-w, h, d));
	verticesList.push_back(XMFLOAT3(w, h, d));
	verticesList.push_back(XMFLOAT3(w, h, -d));

	//底面(-Y面)
	verticesList.push_back(XMFLOAT3(-w, -h, d));
	verticesList.push_back(XMFLOAT3(w, -h, d));
	verticesList.push_back(XMFLOAT3(w, -h, -d));
	verticesList.push_back(XMFLOAT3(-w, -h, -d));

	//背面(+Z面)
	verticesList.push_back(XMFLOAT3(w, -h, d));
	verticesList.push_back(XMFLOAT3(w, h, d));
	verticesList.push_back(XMFLOAT3(-w, h, d));
	verticesList.push_back(XMFLOAT3(-w, -h, d));

	//正面(-Z面)
	verticesList.push_back(XMFLOAT3(-w, -h, -d));
	verticesList.push_back(XMFLOAT3(-w, h, -d));
	verticesList.push_back(XMFLOAT3(w, h, -d));
	verticesList.push_back(XMFLOAT3(w, -h, -d));

	for (UINT i = 0; i < 6; ++i)
	{
		vectTexList[i * 4] = XMFLOAT2(0.0f, 1.0f);
		vectTexList[i * 4 + 1] = XMFLOAT2(0.0f, 0.0f);
		vectTexList[i * 4 + 2] = XMFLOAT2(1.0f, 0.0f);
		vectTexList[i * 4 + 3] = XMFLOAT2(1.0f, 1.0f);
	}
	//for (UINT i = 0; i < 6; i++)
	//{
	//	vectColorList[i] = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//	vectColorList[i * 4 + 1] = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//	vectColorList[i * 4 + 2] = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//	vectColorList[i * 4 + 3] = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//}
	//for (UINT i = 0; i < 24; i++)
	//{
	//	vectColorList[i] = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//}

	for (UINT i = 0; i < 4; i++)
	{
		vertNormaList[i] = XMFLOAT3(1.0f, 0.0f, 0.0f);
		vectColorList[i] = XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f);

		vertNormaList[i + 4] = XMFLOAT3(-1.0f, 0.0f, 0.0f);
		vectColorList[i + 4] = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

		vertNormaList[i + 8] = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vectColorList[i + 8] = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		vertNormaList[i + 12] = XMFLOAT3(0.0f, -1.0f, 0.0f);
		vectColorList[i + 12] = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		vertNormaList[i + 16] = XMFLOAT3(0.0f, 0.0f, 1.0f);
		vectColorList[i + 16] = XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f);

		vertNormaList[i + 20] = XMFLOAT3(0.0f, 0.0f, -1.0f);
		vectColorList[i + 20] = XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f);
	}
	indexList =
	{ 0, 1, 2, 2, 3, 0,		     // 右面(+X面)
	  4, 5, 6, 6, 7, 4,		     // 左面(-X面)
	  8, 9, 10, 10, 11, 8,	     // 顶面(+Y面)
	 12, 14, 13, 14, 12, 15,	 // 底面(-Y面)
	 16, 17, 18, 18, 19, 16,     // 背面(+Z面)
	 20, 21, 22, 22, 23, 20	     // 正面(-Z面)
	};
	pMesh->SetVertices(verticesList.data(), (UINT)verticesList.size());
	pMesh->SetVertNormal(vertNormaList.data(), (UINT)vertNormaList.size());
	pMesh->SetVertColor(vectColorList.data(), (UINT)vectColorList.size());
	pMesh->SetVertTex(vectTexList.data(), (UINT)vectTexList.size());
	pMesh->SetIndex(indexList.data(), (UINT)indexList.size());
	pMesh->m_vertexCount = (UINT)verticesList.size();
	return pMesh;
}

Mesh* Mesh::CreateSphere(float radius, UINT levels, UINT slices)
{
	Mesh* pMesh = new Mesh();
	UINT vertCount = 2 + (levels - 1) * (slices + 1);
	UINT indexCount = 6 * (levels - 1) * slices;


	vector<XMFLOAT3> verticesList;   //顶点坐标
	vector<XMFLOAT3> vertNormaList;  //法线
	vector<XMFLOAT4>vertTangentList; //切线
	vector<XMFLOAT4> vectColorList;        //顶点色
	vector<XMFLOAT2> vectTexList;    //UV
	vector<UINT> indexList;             //索引列表

	verticesList.resize(vertCount);
	vertNormaList.resize(vertCount);
	vertTangentList.resize(vertCount);
	vectColorList.resize(vertCount);
	vectTexList.resize(vertCount);
	indexList.resize(indexCount);

	float phi = 0.0f, theta = 0.0f;
	float per_phi = XM_PI / levels;
	float per_theta = (2 * XM_PI) / slices;
	float x, y, z;
	UINT vIndex = 0, iIndex = 0;

	//vIndx++;
	//放入顶端点数据
	verticesList[vIndex] = XMFLOAT3(0.0f, radius, 0.0f);
	vertNormaList[vIndex] = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertTangentList[vIndex] = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	vectColorList[vIndex] = XMFLOAT4(1.0f, 0.0f, 0.0f, 0.0f);
	vectTexList[vIndex] = XMFLOAT2(0.0f, 0.0f);
	vIndex++;

	for (UINT i = 1; i < levels; ++i)
	{
		phi = per_phi * i;
		for (UINT j = 0; j <= slices; ++j)
		{
			theta = per_theta * j;
			x = radius * sinf(phi) * cosf(theta);
			y = radius * cosf(phi);
			z = radius * sinf(phi) * sinf(theta);

			XMFLOAT3 pos = XMFLOAT3(x, y, z), normal;
			XMStoreFloat3(&normal, XMVector3Normalize(XMLoadFloat3(&pos)));

			verticesList[vIndex] = XMFLOAT3(x, y, z);
			vertNormaList[vIndex] = normal;
			vertTangentList[vIndex] = XMFLOAT4(-sinf(theta), 0.0f, cosf(theta), 1.0f);
			vectColorList[vIndex] = XMFLOAT4(1.0f, 0.0f, 0.0f, 0.0f);
			vectTexList[vIndex] = XMFLOAT2(theta / XM_2PI, phi / XM_PI);
			vIndex++;
		}
	}

	//放入底端点数据
	//vIndx++;
	verticesList[vIndex] = XMFLOAT3(0.0f, -radius, 0.0f);
	vertNormaList[vIndex] = XMFLOAT3(0.0f, -1.0f, 0.0f);
	vertTangentList[vIndex] = XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f);
	vectColorList[vIndex] = XMFLOAT4(1.0f, 0.0f, 0.0f, 0.0f);
	vectTexList[vIndex] = XMFLOAT2(0.0f, 1.0f);

	//放入索引
	if (levels > 1)
	{
		for (UINT j = 1; j <= slices; ++j)
		{
			indexList[iIndex++] = 0;
			indexList[iIndex++] = j % (slices + 1) + 1;
			indexList[iIndex++] = j;
		}
	}

	for (UINT i = 1; i < levels - 1; ++i)
	{
		for (UINT j = 1; j <= slices; ++j)
		{
			indexList[iIndex++] = (i - 1) * (slices + 1) + j;
			indexList[iIndex++] = (i - 1) * (slices + 1) + j % (slices + 1) + 1;
			indexList[iIndex++] = i * (slices + 1) + j % (slices + 1) + 1;

			indexList[iIndex++] = i * (slices + 1) + j % (slices + 1) + 1;
			indexList[iIndex++] = i * (slices + 1) + j;
			indexList[iIndex++] = (i - 1) * (slices + 1) + j;
		}
	}
	if (levels > 1)
	{
		for (UINT j = 1; j <= slices; ++j)
		{
			indexList[iIndex++] = (levels - 2) * (slices + 1) + j;
			indexList[iIndex++] = (levels - 2) * (slices + 1) + j % (slices + 1) + 1;
			indexList[iIndex++] = (levels - 1) * (slices + 1) + 1;
		}
	}
	pMesh->SetVertices(verticesList.data(), (UINT)verticesList.size());
	pMesh->SetVertNormal(vertNormaList.data(), (UINT)vertNormaList.size());
	pMesh->SetVertTangent(vertTangentList.data(), (UINT)vertTangentList.size());
	pMesh->SetVertColor(vectColorList.data(), (UINT)vectColorList.size());
	pMesh->SetVertTex(vectTexList.data(), (UINT)vectTexList.size());
	pMesh->SetIndex(indexList.data(), (UINT)indexList.size());
	pMesh->m_vertexCount = (UINT)verticesList.size();
	return pMesh;
}

Mesh* Mesh::CreateTriangle(float width, float height)
{
	Mesh* pMesh = new Mesh();
	vector<XMFLOAT3> vertexPos;
	vector<XMFLOAT4> vectexColor;
	vector<UINT> vectrxIndex;;

	vertexPos.push_back(XMFLOAT3(0.0f, 0.5f, 0.5f));
	vertexPos.push_back(XMFLOAT3(0.5f, -0.5f, 0.5f));
	vertexPos.push_back(XMFLOAT3(-0.5f, -0.5f, 0.5f));


	vectexColor.push_back(XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
	vectexColor.push_back(XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
	vectexColor.push_back(XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));


	for (UINT i = 0; i < 3; i++)
	{
		vectrxIndex.push_back(i);
	}

	pMesh->SetVertices(vertexPos.data(), (UINT)vertexPos.size());
	pMesh->SetVertColor(vectexColor.data(), (UINT)vectexColor.size());
	pMesh->SetIndex(vectrxIndex.data(), (UINT)vectrxIndex.size());
	pMesh->m_vertexCount = (UINT)vertexPos.size();
	return pMesh;
}

Mesh* Mesh::CreateTeapot()
{
	return nullptr;
}
