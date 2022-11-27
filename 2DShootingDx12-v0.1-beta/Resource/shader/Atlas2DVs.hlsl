#include "Atlas2D.hlsli"



VsOutput main(VsInput input)
{
	VsOutput output;
	output.pos = mul(transMat[input.no], input.pos);
	output.svPos = mul(rtMat, output.pos);
	output.uv = input.uv;
	return output;
}