#include "Basic2D.hlsli"

PsOutput main(VsOutput input) 
{
	PsOutput output;
	output.svColor = tex.Sample(smp, input.uv);
	return output;
}