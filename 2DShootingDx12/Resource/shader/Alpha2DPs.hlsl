#include "Basic2D.hlsli"

cbuffer Alpha : register(b2)
{
	float val;
}

PsOutput main(VsOutput input)
{
	PsOutput output;
	output.svColor = tex.Sample(smp, input.uv);
	output.svColor.a = val;

	return output;
}