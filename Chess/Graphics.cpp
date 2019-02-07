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
	
	

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,  D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

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

	pDeviceCon->VSSetShader(pVertexShader, 0, 0);
	pDeviceCon->PSSetShader(pPixelShader, 0, 0);
	
	//Create the vertex buffer
	Vertex v[] =
	{
		{-0.25f, 0.25f, 1.0f,  1.0f,0.0f,0.0f,1.0f},
		{0.25f, 0.25f, 0.5f,   0.0f,1.0f,0.0f,1.0f},
		{0.25f, -0.25f, 0.5f,  0.0f,0.0f,1.0f,1.0f},
		{-0.25f, -0.25f, 1.5f, 0.5f,0.5f,0.5f,1.0f},
	};

	int indices[] = {
	  0, 1, 2,
	  0, 2, 3,
	};

	D3D11_BUFFER_DESC sIndBufferDesc;
	sIndBufferDesc = {};

	sIndBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	sIndBufferDesc.ByteWidth = sizeof(int) * 2 * 3;
	sIndBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	sIndBufferDesc.CPUAccessFlags = 0;
	sIndBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = indices;
	
	if (FAILED(hr = pDevice->CreateBuffer(&sIndBufferDesc, &iinitData, &pIndexBuffer)))
	{
		throw std::runtime_error("Failed to create index buffer: " + hr);
	}
	
	pDeviceCon->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	D3D11_BUFFER_DESC sVertexBufferDesc;
	sVertexBufferDesc = {};

	sVertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	sVertexBufferDesc.ByteWidth = sizeof(Vertex) * 4;
	sVertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	sVertexBufferDesc.CPUAccessFlags = 0;
	sVertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA sVertexBufferData;

	sVertexBufferData = {};
	sVertexBufferData.pSysMem = v;

	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = ScreenWidth;
	depthStencilDesc.Height = ScreenHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	if (FAILED(hr = pDevice->CreateBuffer(&sVertexBufferDesc, &sVertexBufferData, &pVertBuffer)))
	{
		throw std::runtime_error("Failed to create vertex buffer: " + hr);
	}

	if (FAILED(hr = pDevice->CreateTexture2D(&depthStencilDesc, NULL, &pDepthStencilBuffer)))
	{
		throw std::runtime_error("Failed to create depth stencil buffer: " + hr);
	}
	
	if (FAILED(hr = pDevice->CreateDepthStencilView(pDepthStencilBuffer, NULL, &pDepthStencilView)))
	{
		throw std::runtime_error("Failed to create depth stencil view: " + hr);
	}

	//Set the vertex buffer
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	pDeviceCon->IASetVertexBuffers(0, 1, &pVertBuffer, &stride, &offset);

	//Create the Input Layout
	pDevice->CreateInputLayout(layout, 2, VertexShaderByteCode->GetBufferPointer(),
		VertexShaderByteCode->GetBufferSize(), &pInputLayout);

	//Set the Input Layout
	pDeviceCon->IASetInputLayout(pInputLayout);

	//Set Primitive Topology
	pDeviceCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Create the Viewport
	D3D11_VIEWPORT sViewport;
	sViewport = {};

	sViewport.TopLeftX = 0;
	sViewport.TopLeftY = 0;
	sViewport.Width = ScreenWidth;
	sViewport.Height = ScreenHeight;
	sViewport.MinDepth = 0;
	sViewport.MaxDepth = 1;

	//Set the Viewport
	pDeviceCon->RSSetViewports(1, &sViewport);

	//Set the render target view to the back buffer that we created above
	pDeviceCon->OMSetRenderTargets(1, &pBackBuffer, pDepthStencilView);
}

Graphics::~Graphics()
{
	//Release allocated resources
	VertexShaderByteCode->Release();
	PixelShaderByteCode->Release();
	pVertexShader->Release();
	pPixelShader->Release();
	pBackBuffer->Release();
	pSwapChain->Release();
	pDevice->Release();
	pDeviceCon->Release();
	pVertBuffer->Release();
	pIndexBuffer->Release();
	pInputLayout->Release();
	pDepthStencilBuffer->Release();
	pDepthStencilView->Release();
}

void Graphics::RenderFrame()
{
	auto bgCol = COLOR{ 0.0f,0.0f,0.0f,1.0f };
	pDeviceCon->ClearRenderTargetView(pBackBuffer, bgCol);
	pDeviceCon->ClearDepthStencilView(pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	pDeviceCon->DrawIndexed(6, 0, 0);
	pSwapChain->Present(0, 0);
}

