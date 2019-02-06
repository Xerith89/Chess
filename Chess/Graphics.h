#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include "Window.h"

#pragma comment (lib, "d3d11.lib") 
#pragma comment (lib, "d3dx11.lib")

class Graphics {
public:
	Graphics(HWND hWnd);
	~Graphics();
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	void RenderFrame();
	using COLOUR = float[4];
private:
	HRESULT hr;

	IDXGISwapChain *pSwapChain;
	ID3D11DeviceContext *pDeviceCon;
	ID3D11Device *pDevice;
	ID3D11RenderTargetView *pBackBuffer;
	ID3D11Texture2D *pBufferTexture;
	ID3D10Blob *VertexShaderByteCode, *PixelShaderByteCode;
	ID3D11VertexShader *pVertexShader;
	ID3D11PixelShader *pPixelShader;
	ID3D11Buffer *pVertexBuffer;
	ID3D11InputLayout *pInputLayout;
	D3D11_BUFFER_DESC sBufferDesc;
	D3D11_MAPPED_SUBRESOURCE sMapSubResource;

	struct Vertex {
		float x, y, z;
		COLOUR col;
	};

	//Triangle Test Vertices
	static constexpr Vertex tri[] =
	{
		{0.0f,0.5f,0.0f,1.0f,0.0f,0.0f,1.0f},
		{0.45f,-1.0f,0.0f,0.0f,1.0f,0.0f,1.0f},
		{-0.45f,-0.5f, 0.0f,0.0f,0.0f,1.0f,1.0f}
	};

private:
	static constexpr int ScreenHeight = 600u;
	static constexpr int ScreenWidth = 800u;
};