#include "globals.hlsli"

static const float3 QUAD[] = {
	float3(0, 0, 0),
	float3(1, 0, 0),
	float3(0, 1, 0),
	float3(1, 1, 0),
};

struct GSOut
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
};

[maxvertexcount(4)]
void main(
	point float4 input[1] : SV_POSITION, uint vID : SV_PRIMITIVEID,
	inout TriangleStream< GSOut > output
)
{
	GSOut Out[4] = {
		(GSOut)0,
		(GSOut)0,
		(GSOut)0,
		(GSOut)0,
	};

	for (uint i = 0; i < 4; ++i)
	{
		Out[i].pos = float4(QUAD[i], 1);

		float2 dim = g_xColor.xy;
		float2 invdim = g_xColor.zw;

		Out[i].pos.xy *= invdim;
		Out[i].pos.xy += (float2)unflatten2D(vID, dim.xy) * invdim;
		Out[i].pos.xy = Out[i].pos.xy * 2 - 1;

		float4 o = mul(float4(Out[i].pos.xy, 0, 1), g_xFrame_MainCamera_InvVP);
		o.xyz /= o.w;
		float4 r = mul(float4(Out[i].pos.xy, 1, 1), g_xFrame_MainCamera_InvVP);
		r.xyz /= r.w;
		float3 d = normalize(r.xyz - o.xyz);

		float3 planeOrigin = float3(0, 0, 0);
		float3 planeNormal = float3(0, 1, 0);

		float a = dot(planeNormal, d);

		if (a < 0)
		{
			return;
		}

		float t = dot(planeNormal, (planeOrigin - o.xyz) / a);
		float3 worldPos = o.xyz + d.xyz * t;

		Out[i].pos = mul(float4(worldPos, 1), g_xFrame_MainCamera_VP);
		Out[i].color = float4(worldPos, 1);
	}

	for (uint j = 0; j < 4; ++j)
	{
		output.Append(Out[j]);
	}
}