
struct VsInput
{
	float4 pos : POSITION;
	float2 uv : TEXCOORD0;
};

struct VsOutput
{
	float4 svPos : SV_POSITION;
	float4 pos : POSITION0;
	float2 uv : POSITION1;
};

struct PsOutput
{
	float4 svColor : SV_TARGET0;
};

cbuffer RenderTarget : register(b0)
{
	matrix rtMat;		// 変換用行列
}

cbuffer Transform : register(b1)
{
	matrix transMat;		// 頂点に対しての変換用
}

// テクスチャ
Texture2D<float4> tex : register(t0);

// サンプラー
SamplerState smp : register(s0);
