#include "Triangle.hlsli"

// ÏñËØ×ÅÉ«Æ÷
float4 PS(VertexOut pIn) : SV_Target
{
    return float4(0.0f,1.0f,0.0f,1.0f);
    //return pIn.color;
}
