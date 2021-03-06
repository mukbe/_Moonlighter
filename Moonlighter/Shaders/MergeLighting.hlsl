static const float2 arrBasePos[4] =
{
    float2(-1.0, 1.0),
	float2(1.0, 1.0),
	float2(-1.0, -1.0),
	float2(1.0, -1.0),


};
static const float2 WinSize = { 1280, 720 };

static const float2 arrUV[4] =
{
    float2(0.0, 0.0),
	float2(1.0, 0.0),
	float2(0.0, 1.0),
	float2(1.0, 1.0),
};


struct PixelInput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCROOD0;
};

PixelInput VS(uint VertexID : SV_VertexID)
{
    PixelInput output;

    output.position = float4(arrBasePos[VertexID].xy, 0.0, 1.0);
    output.uv = arrUV[VertexID].xy;

    return output;
}

Texture2D lightmap : register(t0);
Texture2D gBuffer : register(t1);
SamplerState samp;

float4 PS(PixelInput input) : SV_TARGET
{
    //TODO LightSystem에서 전역광 버퍼가 필요함
    float4 color = lightmap.Sample(samp, input.uv);
    float4 back = gBuffer.Sample(samp, input.uv) * 0.3f;
    back.b *= 3.f;
    
    back += color;
    return back;
}