#include "Graphics.h"
#include <assert.h>

Graphics::Graphics(HWND hWnd)
{
	assert(hWnd != nullptr);

	DXGI_MODE_DESC sBufferDesc;
	sBufferDesc = {};

	sBufferDesc.Width = ScreenWidth;
	sBufferDesc.Height = ScreenHeight;
	sBufferDesc.RefreshRate.Numerator = 60;
	sBufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sBufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sBufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//Initialise the swap chain description struct as empty
	DXGI_SWAP_CHAIN_DESC sSwapChainDesc = {};
	sSwapChainDesc = {};
	//Fill it with our required attributes
	sSwapChainDesc.BufferDesc = sBufferDesc;
	sSwapChainDesc.BufferCount = 1;
	sSwapChainDesc.SampleDesc.Count = 1;
	sSwapChainDesc.SampleDesc.Quality = 0;
	sSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sSwapChainDesc.OutputWindow = hWnd;
	sSwapChainDesc.Windowed = TRUE;
	sSwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;


	//Try to create a device and swap chain, pointers to be stored in the variables we have provided
	if (FAILED(hr = D3D11CreateDeviceAndSwapChain(
		NULL,D3D_DRIVER_TYPE_HARDWARE,NULL, D3D11_CREATE_DEVICE_DEBUG,
		NULL,NULL,D3D11_SDK_VERSION,&sSwapChainDesc,&pSwapChain,
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

	
	/*
	//Compile our vertex and pixel shaders into bytecode and store it in a D3D blob
	if (FAILED(hr = D3DCompileFromFile(L"VertexShader.hlsl", 0, 0, "main", "vs_4_0", 0, 0, &VertexShaderByteCode, NULL)))
	{
		throw std::runtime_error("Failed to compile vertex shader: " + hr);
	}
	
	if (FAILED(hr = D3DCompileFromFile(L"PixelShader.hlsl", 0, 0, "main", "ps_4_0", 0, 0, &PixelShaderByteCode, NULL)))
	{
		throw std::runtime_error("Failed to compile pixel shader: " + hr);
	}
	
	//Use the compiled bytecode to create a pixel and vertex shader in D3D
	if (FAILED(hr = pDevice->CreateVertexShader(VertexShaderByteCode->GetBufferPointer(), VertexShaderByteCode->GetBufferSize(), NULL, &pVertexShader)))
	{
		throw std::runtime_error("Failed to create vertex shader: " + hr);
	}
	
	if (FAILED(hr = pDevice->CreatePixelShader(PixelShaderByteCode->GetBufferPointer(), PixelShaderByteCode->GetBufferSize(), NULL, &pPixelShader)))
	{
		throw std::runtime_error("Failed to create pixel shader: " + hr);
	}
	*/
}

Graphics::~Graphics()
{
	//Release allocated resources
	//VertexShaderByteCode->Release();
	//PixelShaderByteCode->Release();
	//pVertexShader->Release();
	//pPixelShader->Release();
	pBackBuffer->Release();
	pSwapChain->Release();
	pDevice->Release();
	pDeviceCon->Release();
}

void Graphics::RenderFrame()
{
	auto bgCol = COLOUR{ 1.0f,0.0f,0.0f,1.0f };
	pDeviceCon->ClearRenderTargetView(pBackBuffer, bgCol);
	pSwapChain->Present(0, 0);
}

