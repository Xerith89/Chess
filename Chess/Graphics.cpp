#include "Graphics.h"
#include <assert.h>
Graphics::Graphics(HWND hWnd)
{
	assert(hWnd != nullptr);
	//Initialise the swap chain description struct as empty
	DXGI_SWAP_CHAIN_DESC sSCD = {};
	
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
		NULL,D3D_DRIVER_TYPE_HARDWARE,NULL, D3D11_CREATE_DEVICE_DEBUG,
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

	D3D11_BUFFER_DESC sBufferDesc;
	sBufferDesc = {};
	sBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	sBufferDesc.ByteWidth = sizeof(Vertex)*3;
	sBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	sBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	if (FAILED(hr = pDevice->CreateBuffer(&sBufferDesc, NULL, &pVertexBuffer)))
	{
		throw std::runtime_error("Failed to create vertex buffer: " + hr);
	}

	D3D11_INPUT_ELEMENT_DESC ied[] = 
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
	};


	if (FAILED(hr = pDevice->CreateInputLayout(ied, 2, VertexShaderByteCode->GetBufferPointer(), VertexShaderByteCode->GetBufferSize(), &pInputLayout)))
	{
		throw std::runtime_error("Failed to create input layout: " + hr);
	}

	D3D11_SAMPLER_DESC sSampDesc;
	sSampDesc = {};
	sSampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sSampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sSampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sSampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sSampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sSampDesc.MinLOD = 0;
	sSampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	if (FAILED(hr = pDevice->CreateSamplerState(&sSampDesc, &pSampleState)))
	{
		throw std::runtime_error("Failed to create sampler state: " + hr);
	}

}

Graphics::~Graphics()
{
	//Release allocated resources
	VertexShaderByteCode->Release();
	pSampleState->Release();
	PixelShaderByteCode->Release();
	pInputLayout->Release();
	pVertexBuffer->Release();
	pVertexShader->Release();
	pPixelShader->Release();
	pBackBuffer->Release();
	pSwapChain->Release();
	pDevice->Release();
	pDeviceCon->Release();
}

void Graphics::RenderFrame()
{
	//Map the vertex buffer and allow the CPU to write to it
	D3D11_MAPPED_SUBRESOURCE sMapSubResource;
	if (FAILED(hr = pDeviceCon->Map(pVertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &sMapSubResource)))
	{
		throw std::runtime_error("Failed to map vertex buffer: " + hr);
	}
	
	//Triangle Test Vertices
	Vertex tri[] =
	{
		{-0.5f,0.5f,0.5f,1.0f,0.0f,0.0f,1.0f},
		{0.5f,0.5f,0.5f,0.0f,1.0f,0.0f,1.0f},
		{-0.5f,-0.5f,0.5f,0.0f,0.0f,1.0f,1.0f}
	};

	memcpy(sMapSubResource.pData, tri, sizeof(Vertex));
	//Unmap and set a number of attributes
	pDeviceCon->Unmap(pVertexBuffer, NULL);
	pDeviceCon->IASetInputLayout(pInputLayout);
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0;
	pDeviceCon->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
	pDeviceCon->VSSetShader(pVertexShader, 0, 0);
	pDeviceCon->PSSetShader(pPixelShader, 0, 0);
	pDeviceCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pDeviceCon->PSSetSamplers(0, 1, &pSampleState);
	pDeviceCon->ClearRenderTargetView(pBackBuffer, COLOUR{ 0.0f,0.0f,0.0f,0.0f });
	pDeviceCon->Draw(3, 0);
	//Swap the back and front buffers.
	if (FAILED(hr = pSwapChain->Present(0, 0)))
	{
		throw std::runtime_error("Failed to perform swap: " + hr);
	}
	
}

