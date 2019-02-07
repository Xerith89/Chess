struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
};

VS_OUTPUT main(float4 inPos : POSITION, float4 inCol : COLOR)
{
	VS_OUTPUT output;
	output.Pos = inPos;
	output.Color = inCol;

	return output;
}