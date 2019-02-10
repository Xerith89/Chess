#include "Graphics.h"
#include <assert.h>

Graphics::Graphics(HWND hWnd)
{
	assert(hWnd != nullptr);

	//Create and fill our swap chain struct
	DXGI_SWAP_CHAIN_DESC SwapchainDesc;
	SwapchainDesc = {};

	SwapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapchainDesc.OutputWindow = hWnd;
	SwapchainDesc.BufferCount = 1;
	SwapchainDesc.BufferDesc.Width = ScreenWidth;
	SwapchainDesc.BufferDesc.Height = ScreenHeight;
	SwapchainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	SwapchainDesc.SampleDesc.Count = 1;
	SwapchainDesc.SampleDesc.Quality = 0;
	SwapchainDesc.Windowed = TRUE;
	SwapchainDesc.BufferDesc.RefreshRate.Numerator = 1;
	SwapchainDesc.BufferDesc.RefreshRate.Denominator = 60;
	
	//Try to create a device and swap chain, pointers to be stored in the variables we have provided
	if (FAILED(hr = D3D11CreateDeviceAndSwapChain(nullptr,D3D_DRIVER_TYPE_HARDWARE,nullptr,D3D11_CREATE_DEVICE_DEBUG,nullptr,0,D3D11_SDK_VERSION,&SwapchainDesc,&pSwapChain,&pDevice,nullptr,&pDeviceContext)))
	{
		throw std::runtime_error("Could not create a device and/or swapchain: "+hr);
	}
	//Get a handle to the backbuffer
	if (FAILED(hr = pSwapChain->GetBuffer(0,__uuidof(ID3D11Texture2D),(LPVOID*)&pBackBuffer)))
	{
		throw std::runtime_error("Failed to get handle to back buffer: "+hr);
	}

	//Create render target view from our backbuffer handle
	if (FAILED(hr = pDevice->CreateRenderTargetView(pBackBuffer,nullptr,&pRenderTargetView)))
	{
		throw std::runtime_error("Failed to create render target view: " + hr);
	}
	//Set the render target
	pDeviceContext->OMSetRenderTargets(1, &pRenderTargetView, nullptr);

	//Create a viewport struct and fill it
	D3D11_VIEWPORT Viewport;
	Viewport = {};
	Viewport.MinDepth = 0.0f;
	Viewport.MaxDepth = 1.0f;
	Viewport.Width = ScreenWidth;
	Viewport.Height = ScreenHeight;
	Viewport.TopLeftX = 0.0f;
	Viewport.TopLeftY = 0.0f;
	
	//Set the viewport
	pDeviceContext->RSSetViewports(1, &Viewport);

	//create and fill our Texture Description struct
	D3D11_TEXTURE2D_DESC TextureDescription;
	TextureDescription = {};
	TextureDescription.Width = ScreenWidth;
	TextureDescription.Height = ScreenHeight;
	TextureDescription.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	TextureDescription.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	TextureDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	TextureDescription.MiscFlags = 0;
	TextureDescription.SampleDesc.Count = 1;
	TextureDescription.SampleDesc.Quality = 0;
	TextureDescription.Usage = D3D11_USAGE_DYNAMIC;
	TextureDescription.MipLevels = 1;
	TextureDescription.ArraySize = 1;
	
	// create the texture
	if (FAILED(hr = pDevice->CreateTexture2D(&TextureDescription, nullptr, &pSysBufferTexture)))
	{
		throw std::runtime_error("Failed to create system texture: " + hr);
	}

	//Create and fill our resource view desc struct
	D3D11_SHADER_RESOURCE_VIEW_DESC ShaderResourceViewDesc;
	ShaderResourceViewDesc= {};
	ShaderResourceViewDesc.Format = TextureDescription.Format;
	ShaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	ShaderResourceViewDesc.Texture2D.MipLevels = 1;

	// create the resource view on the texture
	if (FAILED(hr = pDevice->CreateShaderResourceView(pSysBufferTexture,
		&ShaderResourceViewDesc, &pSysBufferTextureView)))
	{
		throw std::runtime_error("Failed to create resource view: " + hr);
	}

	//Compile our vertex and pixel shaders into bytecode and store it in a D3D blob
	if (FAILED(hr = D3DCompileFromFile(L"VertexShader.hlsl", 0, 0, "main", "vs_4_0", 0, 0, &VertexShaderByteCode, NULL)))
	{
		throw std::runtime_error("Failed to compile vertex shader: " + hr);
	}

	if (FAILED(hr = D3DCompileFromFile(L"PixelShader.hlsl", 0, 0, "main", "ps_4_0", 0, 0, &PixelShaderByteCode, NULL)))
	{
		throw std::runtime_error("Failed to compile pixel shader: " + hr);
	}

	//Create the shaders from the stored bytecode
	if (FAILED(hr = pDevice->CreatePixelShader(PixelShaderByteCode->GetBufferPointer(),PixelShaderByteCode->GetBufferSize(),nullptr,&pPixelShader)))
	{
		throw std::runtime_error("Failed to create pixel shader: " + hr);
	}
	if (FAILED(hr = pDevice->CreateVertexShader(VertexShaderByteCode->GetBufferPointer(), VertexShaderByteCode->GetBufferSize(), nullptr, &pVertexShader)))
	{
		throw std::runtime_error("Failed to create vertex shader: " + hr);
	}

	//x,y,z,u,v - 6 verts to make 2 triangles to make 1 quad the size of the screen (These are in NDC)
	const Vertex vertices[] =
	{
		{ -1.0f,1.0f,0.5f,0.0f,0.0f },
		{ 1.0f,1.0f,0.5f,1.0f,0.0f },
		{ 1.0f,-1.0f,0.5f,1.0f,1.0f },
		{ -1.0f,1.0f,0.5f,0.0f,0.0f },
		{ 1.0f,-1.0f,0.5f,1.0f,1.0f },
		{ -1.0f,-1.0f,0.5f,0.0f,1.0f },
	};

	D3D11_BUFFER_DESC BufferDesc;
	BufferDesc= {};
	BufferDesc.ByteWidth = sizeof(Vertex) * 6;
	BufferDesc.CPUAccessFlags = 0u;
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA ResourceData;
	ResourceData = {};
	ResourceData.pSysMem = vertices;

	//Create the vertex buffer to hold our vertices
	if (FAILED(hr = pDevice->CreateBuffer(&BufferDesc, &ResourceData, &pVertexBuffer)))
	{
		throw std::runtime_error("Failed to create vertex buffer: " + hr);
	}

	//Tell directx what our vertices in the vertex buffer actually mean
	const D3D11_INPUT_ELEMENT_DESC InputDescription[] =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 }
	};
	//Create the input layout from the description
	if (FAILED(hr = pDevice->CreateInputLayout(InputDescription, 2, VertexShaderByteCode->GetBufferPointer(), VertexShaderByteCode->GetBufferSize(), &pInputLayout)))
	{
		throw std::runtime_error("Failed to create input layout: " + hr);
	}

	//Create and fill our sampler description struct
	D3D11_SAMPLER_DESC SamplerDesc;
	SamplerDesc = {};
	SamplerDesc.MinLOD = 0;
	SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	SamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	
	//create the sampler
	if (FAILED(hr = pDevice->CreateSamplerState(&SamplerDesc, &pSamplerState)))
	{
		throw std::runtime_error("Failed to create sampler: " + hr);
	}

	//Create our colour array that we will access to change pixel colours directly
	pColorBuffer = reinterpret_cast<Color*>(_aligned_malloc(sizeof(Color) * ScreenWidth * ScreenHeight, 16u));
}

Graphics::~Graphics()
{
	//Release allocated resources
	if (pColorBuffer)
	{
		_aligned_free(pColorBuffer);
		pColorBuffer = nullptr;
	}
	pSwapChain->Release();
	pDevice->Release();
	pBackBuffer->Release();
	VertexShaderByteCode->Release();
	PixelShaderByteCode->Release();
	pDeviceContext->Release();
	pRenderTargetView->Release();
	pSysBufferTexture->Release();
	pSysBufferTextureView->Release();
	pPixelShader->Release();
	pVertexShader->Release();
	pVertexBuffer->Release();
	pInputLayout->Release();
	pSamplerState->Release();	
}


void Graphics::RenderFrame()
{
	if (FAILED(hr = pDeviceContext->Map(pSysBufferTexture, 0u,
		D3D11_MAP_WRITE_DISCARD, 0u, &mappedSysBufferTexture)))
	{
		throw std::exception("Mapping sysbuffer" + hr);
	}
	// setup parameters for copy operation
	Color* pDst = reinterpret_cast<Color*>(mappedSysBufferTexture.pData);
	const size_t dstPitch = mappedSysBufferTexture.RowPitch / sizeof(Color);
	const size_t srcPitch = Graphics::ScreenWidth;
	const size_t rowBytes = srcPitch * sizeof(Color);
	// perform the copy line-by-line
	for (size_t y = 0u; y < Graphics::ScreenHeight; y++)
	{
		memcpy(&pDst[y * dstPitch], &pColorBuffer[y * srcPitch], rowBytes);
	}
	// release the adapter memory
	pDeviceContext->Unmap(pSysBufferTexture, 0u);
	// release the adapter memory
	pDeviceContext->IASetInputLayout(pInputLayout);
	pDeviceContext->VSSetShader(pVertexShader, nullptr, 0u);
	pDeviceContext->PSSetShader(pPixelShader, nullptr, 0u);
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	pDeviceContext->IASetVertexBuffers(0u, 1u, &pVertexBuffer, &stride, &offset);
	pDeviceContext->PSSetShaderResources(0u, 1u, &pSysBufferTextureView);
	pDeviceContext->PSSetSamplers(0u, 1u, &pSamplerState);
	pDeviceContext->Draw(6u, 0u);

	if (FAILED(hr = pSwapChain->Present(1u, 0u)))
	{
		throw std::exception("Swapping buffers" + hr);
	}
}

void Graphics::PrepareFrame()
{
	memset(pColorBuffer, 0, sizeof(Color) * ScreenHeight * ScreenWidth);
}

void Graphics::SetPixel(int x, int y, Color c)
{
	pColorBuffer[Graphics::ScreenWidth * y + x] = c;
}

void Graphics::DrawSprite(int x, int y, const Sprite & sprite)
{
	int width = sprite.GetWidth();
	int height = sprite.GetHeight();

	for (int i = 0; i <= height; i++)
	{
		for (int j = 0; j <= width; j++)
		{
			SetPixel(j+x, i+y, sprite.GetColor(j, i));
		}
	}
}

