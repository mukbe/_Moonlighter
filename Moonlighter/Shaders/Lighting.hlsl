cbuffer Buffer_Camera : register(b0)
{
    float4 View;

    float2 CameraPos;
    float2 Padding_Camera;
}

//cbuffer Buffer_World : register(b1)
//{
//    float4 World;

//    float2 Pos;
//    float2 Padding_World;
//}

//cbuffer Buffer_Light : register(b2)
//{
//    float4 Light_Color;
    
//    float Range;
//    float3 Padding_Light;
//}
static const int LIGHT_MAX = 32;

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
	float Tick;
	float2 Padding;

	LightDesc LightTable[LIGHT_MAX];
}



RWTexture2D<float4> RWLgihtMap : register(u0);

[numthreads(20, 30, 1)]
void CSMain( uint3 DTid : SV_DispatchThreadID )
{
	uint2 temp = uint2(1600, 900);
	uint2 index = clamp(DTid.xy, uint2(0, 0), temp.xy);

	RWLgihtMap[index] = float4(0, 0, 0, 0);

	float4 color = float4(0, 0, 0, 0);
	
	[loop]
	for (int i = 0; i < LIGHT_MAX; i++)
	{
		LightDesc light = LightTable[i];
		
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
    

		if (distance < range)
		{
			color += light.Color;
		}
	}
	
	//color = float4(1, 1, 1, 1);
	RWLgihtMap[index] = color;


}