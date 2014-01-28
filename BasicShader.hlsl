float4x4 ViewProjection;

texture Tex0;
sampler Texture0;

void ImageVertex ( inout float4 position : SV_Position ) {
	
	position = mul(position, ViewProjection);
}

float4 ImagePixel (  float4 pos : SV_Position ) : SV_Target0 {
	
	return float4(0.5, 0.5, 1, 1);
}

technique Image {
	pass Image {
		VertexShader = compile vs_5_0 ImageVertex( );
		PixelShader = compile ps_5_0 ImagePixel( );
	}
}