#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include "Window.h"
#include "Color.h"

#pragma comment (lib, "d3d11.lib") 
#pragma comment (lib, "D3DCompiler.lib")

class Graphics {
public:
	Graphics(HWND hWnd);
	~Graphics();
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	void RenderFrame();
	void PrepareFrame();
	void SetPixel(int x, int y, Color c);
private:
	HRESULT hr;
	//COM object pointers
	IDXGISwapChain*				pSwapChain;
	ID3D11Device*				pDevice;
	ID3D11Resource*				pBackBuffer;
	ID3DBlob*					VertexShaderByteCode;
	ID3DBlob*					PixelShaderByteCode;
	ID3D11DeviceContext*		pDeviceContext;
	ID3D11RenderTargetView*		pRenderTargetView;
	ID3D11Texture2D*			pSysBufferTexture;
	ID3D11ShaderResourceView*	pSysBufferTextureView;
	ID3D11PixelShader*			pPixelShader;
	ID3D11VertexShader*			pVertexShader;
	ID3D11Buffer*				pVertexBuffer;
	ID3D11InputLayout*			pInputLayout;
	ID3D11SamplerState*			pSamplerState;
	D3D11_MAPPED_SUBRESOURCE	mappedSysBufferTexture;
	//We will use this to create an array of colours the size of the screen
	Color*                      pColorBuffer = nullptr;

	//We'll use this to create a textured quad which is what we will draw onto rather than the screen directly
	struct Vertex 
	{
		float x, y, z;		
		float u, v;			
	};

private:
	static constexpr int ScreenHeight = 600u;
	static constexpr int ScreenWidth = 800u;
};