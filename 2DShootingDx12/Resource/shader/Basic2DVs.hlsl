#include "Basic2D.hlsli"

VsOutput main(float4 pos : POSITION,
float2 uv : TEXCOORD0)
{
	VsOutput output;
	output.pos = mul(transMat,pos);
	output.svPos = mul(rtMat, output.pos);
	output.uv = uv;
	return output;
}