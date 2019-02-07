#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include "Window.h"

#pragma comment (lib, "d3d11.lib") 
#pragma comment (lib, "D3DCompiler.lib")

class Graphics {
public:
	Graphics(HWND hWnd);
	~Graphics();
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	void RenderFrame();
	using COLOR = float[4];
private:
	HRESULT hr;
	//COM object variables
	IDXGISwapChain *pSwapChain;
	ID3D11DeviceContext *pDeviceCon;
	ID3D11Device *pDevice;
	ID3D11RenderTargetView *pBackBuffer;
	ID3D11Buffer *pVertBuffer;
	ID3D11InputLayout *pInputLayout;
	ID3D11Texture2D *pBufferTexture;
	ID3DBlob *VertexShaderByteCode, *PixelShaderByteCode;
	ID3D11VertexShader *pVertexShader;
	ID3D11PixelShader *pPixelShader;
	
	struct Vertex 
	{
		float x, y, z;		
		float r, g, b, a;
	};

private:
	static constexpr int ScreenHeight = 600u;
	static constexpr int ScreenWidth = 800u;
};