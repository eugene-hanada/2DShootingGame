
struct VsInput
{
	float4 pos : POSITION;
	float2 uv : TEXCOORD0;
	uint no : BONE_NO;
};

struct VsOutput
{
	float4 svPos : SV_POSITION;
	float4 pos : POSITION0;
	float2 uv : POSITION1;
};

struct PsOutput
{
	float4 svColor : SV_TARGET;
};


matrix rtMat : register(b0);

matrix transMat[256] : register(b1);

// テクスチャ
Texture2D<float4> tex : register(t0);

// サンプラー
SamplerState smp : register(s0);
