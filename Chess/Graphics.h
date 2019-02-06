#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include "Window.h"

#pragma comment (lib, "d3d11.lib") 

class Graphics {
public:
	Graphics(HWND hWnd);
	~Graphics();
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
private:
	IDXGISwapChain *pSwapChain;
	ID3D11DeviceContext *pDeviceCon;
	ID3D11Device *pDevice;
	ID3D11RenderTargetView *pBackBuffer;
	ID3D11Texture2D *pBufferTexture;
public:
	static constexpr int ScreenHeight = 600u;
	static constexpr int ScreenWidth = 800u;
};