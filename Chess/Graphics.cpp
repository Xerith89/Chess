#include "Graphics.h"

Graphics::Graphics(HWND hWnd)
{
	//Initialise the swap chain description struct as empty
	DXGI_SWAP_CHAIN_DESC sSCD = {};
	HRESULT hr;
	//Fill it with our required attributes
	sSCD.Windowed = true;
	sSCD.OutputWindow = hWnd;
	sSCD.BufferDesc.Height = ScreenHeight;
	sSCD.BufferDesc.Width = ScreenWidth;
	sSCD.BufferCount = 1;
	sSCD.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sSCD.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sSCD.SampleDesc.Count = 4;
	//Try to create a device and swap chain, pointers to be stored in the variables we have provided
	if (FAILED(hr = D3D11CreateDeviceAndSwapChain(
		NULL,D3D_DRIVER_TYPE_HARDWARE,NULL,NULL,
		NULL,NULL,D3D11_SDK_VERSION,&sSCD,&pSwapChain,
		&pDevice,NULL,&pDeviceCon))) 
	{
		throw std::runtime_error("Could not create a device and/or swapchain: "+hr);
	}
	//Get a handle to the backbuffer
	if (FAILED(hr = pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&pBufferTexture)))
	{
		throw std::runtime_error("Failed to get handle to back buffer: "+hr);
	}

	//Create render target view from our backbuffer handle
	if (FAILED(hr = pDevice->CreateRenderTargetView(pBufferTexture, NULL, NULL)))
	{
		throw std::runtime_error("Failed to create render target view: " + hr);
	}
}

Graphics::~Graphics()
{
	//Release allocated D3D resources
	pSwapChain->Release();
	pDevice->Release();
	pDeviceCon->Release();
}
