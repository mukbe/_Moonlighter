#include "ShaderHeader.h"

cbuffer Buffer_Camera : register(b0)
{
    float4 View;

    float2 CameraPos;
    float2 Padding_Camera;
}

struct LightDesc
{
	int isActive;
	float Range;
	float2 Position;

	float4 Color;
	float4 Transform;
};

cbuffer Buffer_Light : register(b2)
{
    float4 SunLight;

	LightDesc LightTable[LIGHT_MAX];
}


RWTexture2D<float4> RWLgihtMap : register(u0);
Texture2D backBuffer : register(t0);

[numthreads(20, 30, 1)]
void CSMain( uint3 DTid : SV_DispatchThreadID )
{
	uint2 pixel = uint2(1600, 900);
    uint2 index = clamp(DTid.xy, uint2(0, 0), pixel.xy);

	RWLgihtMap[index] = float4(0, 0, 0, 0);
	float4 color = float4(0, 0, 0, 0);
    float4 gbuffer = backBuffer.Load(DTid) * SunLight.a;
    gbuffer.r *= SunLight.r;
    gbuffer.b *= SunLight.b;

   // gbuffer.b *= 3.0f;
    //gbuffer와 전역Light를 계산해줘야함
    //gbuffer.a = 0.f;
    [loop]
	for (int i = 0; i < LIGHT_MAX; i++)
	{
		LightDesc light = LightTable[i];
        if (light.isActive == false)
            continue;
        
		float3 position = float3(0, 0, 1);
    
		position.xy = mul(position, float3x2(light.Transform, light.Position));
		position.xy = mul(position, float3x2(View.xyzw, CameraPos));


		float range = light.Range * abs(View.x);

		if (position.x + range < 0 || position.y + range < 0 ||
			 position.x - range > 1600 || position.y - range > 900)
		{
			continue;
		}
    
    
		float2 delta = abs(position.xy - DTid.xy);
		float distance = length(delta);
    
        //알파값이 빛의 세기
		if (distance < range)
		{
            float factor = (distance) / range;
            float4 temp = light.Color * (1 - pow(factor, 3));
            
            if (factor < 0.6f)
                temp.rgb *= 1.1f;

            color.rgb += temp.rgb * temp.a;
            
        }
	}
	
    RWLgihtMap[index] = (float4(color.rgb, 1.f) + gbuffer) * Padding_Camera.x;
}