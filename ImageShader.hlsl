float4x4 ViewProjection;

texture Tex0;
sampler Texture0;

void ImageVertex ( inout float4 position : SV_Position,
			  	inout float4 color : COLOR0,
				inout float2 tex : TEXCOORD0 ) {
	
	position = mul(position, ViewProjection);
}

float4 ImagePixel (  float4 pos : SV_Position,
				float4 color : COLOR0,
				float2 tex : TEXCOORD0 ) : SV_Target0 {
	
	return color;
}

technique Image {
	pass Image {
		VertexShader = compile vs_5_0 ImageVertex( );
		PixelShader = compile ps_5_0 ImagePixel( );
	}
}