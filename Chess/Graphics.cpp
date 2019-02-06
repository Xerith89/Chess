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
	if (FAILED(hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBufferTexture)))
	{
		throw std::runtime_error("Failed to get handle to back buffer: "+hr);
	}

	//Create render target view from our backbuffer handle
	if (FAILED(hr = pDevice->CreateRenderTargetView(pBufferTexture, NULL, &pBackBuffer)))
	{
		throw std::runtime_error("Failed to create render target view: " + hr);
	}

	pBufferTexture->Release();
	
	//Set the render target view to the back buffer that we created above
	pDeviceCon->OMSetRenderTargets(1, &pBackBuffer, NULL);

	//Create and fill the viewport struct
	D3D11_VIEWPORT sVP;
	sVP = {};
	
	sVP.Height = ScreenHeight;
	sVP.Width = ScreenWidth;
	sVP.TopLeftX = 0;
	sVP.TopLeftY = 0;

	//Set our viewport using the viewport struct above
	pDeviceCon->RSSetViewports(1, &sVP);
}

Graphics::~Graphics()
{
	//Release allocated resources
	pBackBuffer->Release();
	pSwapChain->Release();
	pDevice->Release();
	pDeviceCon->Release();
}

void Graphics::RenderFrame()
{
	pDeviceCon->ClearRenderTargetView(pBackBuffer, COLOUR{ 0.0f,0.2f,0.4f,1.0f });
	pSwapChain->Present(0, 0);
}
