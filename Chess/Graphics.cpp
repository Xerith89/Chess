#include "Graphics.h"
#include <iostream>

Graphics::Graphics(HWND hWnd)
{
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

	//Compile our vertex and pixel shaders into bytecode and store it in a D3D blob
	if (FAILED( hr = D3DX11CompileFromFileA("VertexShader.hlsl",0,0,"main", "vs_4_0",0,0,0,&VertexShaderByteCode,0,0)))
	{
		throw std::runtime_error("Failed to compile vertex shader: " + hr);
	}
	if (FAILED(hr = D3DX11CompileFromFileA("PixelShader.hlsl", 0, 0, "main", "ps_4_0", 0, 0, 0, &PixelShaderByteCode, 0, 0)))
	{
		throw std::runtime_error("Failed to compile pixel shader: " + hr);
	}
	//Use the compiled bytecode to create a pixel and vertex shader in D3D
	pDevice->CreateVertexShader(VertexShaderByteCode->GetBufferPointer(), VertexShaderByteCode->GetBufferSize(), NULL, &pVertexShader);
	pDevice->CreatePixelShader(PixelShaderByteCode->GetBufferPointer(), PixelShaderByteCode->GetBufferSize(), NULL, &pPixelShader);

	sBufferDesc = {};
	sBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	sBufferDesc.ByteWidth = sizeof(Vertex)*3;
	sBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	sBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	pDevice->CreateBuffer(&sBufferDesc, NULL, &pVertexBuffer);

	D3D11_INPUT_ELEMENT_DESC ied[] = 
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOUR",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
	};


	if (FAILED(hr = pDevice->CreateInputLayout(ied, 2, VertexShaderByteCode->GetBufferPointer(), VertexShaderByteCode->GetBufferSize(), &pInputLayout)))
	{
		throw std::runtime_error("Failed to create input layout: " + hr);
	}

}

Graphics::~Graphics()
{
	//Release allocated resources
	VertexShaderByteCode->Release();
	PixelShaderByteCode->Release();
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
	if (FAILED(hr = pDeviceCon->Map(pVertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &sMapSubResource)))
	{
		throw std::runtime_error("Failed to map vertex buffer: " + hr);
	}
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
	pDeviceCon->Draw(3, 0);
	//Fill render target buffer with a colour
	pDeviceCon->ClearRenderTargetView(pBackBuffer, COLOUR{ 0.0f,0.2f,0.4f,1.0f });
	//Swap the back and front buffers.
	pSwapChain->Present(0, 0);
	
}

