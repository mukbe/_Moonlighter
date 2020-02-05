cbuffer Buffer_Camera : register(b0)
{
    float4 View;

    float2 CameraPos;
    float2 Padding_Camera;
}

cbuffer Buffer_World : register(b1)
{
    float4 World;

    float2 Pos;
    float2 Padding_World;
}

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
    float4 color : COLOR0;
    float2 uv : TEXCROOD0;
};

PixelInput VS(uint VertexID : SV_VertexID)
{
    PixelInput output;

   output.position = float4(arrBasePos[VertexID].xy, 0.0, 1.0);
   output.uv = arrUV[VertexID].xy;

    return output;
}


float4 PS(PixelInput input) : SV_TARGET
{
    float4 color = input.color;
    //float2 origin = Position;
    
    float3 position = float3(0,0, 1);
    
    position.xy = mul(position, float3x2(World,  Pos));

    position.xy = mul(position, float3x2(View.xyzw, CameraPos));
    float zoom = length(View.xw);

    color = float4(0, 0, 0, 0.5f);
    float dx = abs(input.position.x - position.x);
    float dy = abs(input.position.y - position.y);
    float distance = sqrt(dx * dx + dy * dy) ;
    
    
    if(distance < 200 * zoom)
    {
        
        float factor = (distance) / (200 * zoom);
        color = lerp(0, color, factor);

       // discard;
   

    }

    return color;
}