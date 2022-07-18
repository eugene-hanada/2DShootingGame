#include "Atlas2D.hlsli"



VsOutput main(VsInput input)
{
	VsOutput output;
	output.pos = mul(transMat[0],input.pos);
	output.svPos = mul(rtMat, output.pos);
	output.uv = input.uv;
	return output;
}