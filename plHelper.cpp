#include "plHelper.h"
#include <wrl.h>
#include <string>
#include <iostream>
#include <fstream>

bool loadShader(ID3D11Device* device, ID3D11VertexShader*& vShader, ID3D11PixelShader*& pShader, std::string& vShaderByteCode) 
{
	std::string shaderData;
	std::ifstream reader;
	reader.open("VertexShader.cso", std::ios::binary | std::ios::ate);
	if (!reader.is_open()) 
	{
		std::cerr << "cannot open vertex file" << std::endl;
		return false;
	}

	reader.seekg(0, std::ios::end);
	shaderData.reserve(static_cast<unsigned int>(reader.tellg()));
	reader.seekg(0, std::ios::beg);

	shaderData.assign((std::istreambuf_iterator<char>(reader)), std::istreambuf_iterator<char>());

	if (FAILED(device->CreateVertexShader(shaderData.c_str(), shaderData.length(), nullptr, &vShader))) 
	{
		std::cerr << "cannot create vertexShader" << std::endl;
		return false;
	}

	vShaderByteCode = shaderData;
	shaderData.clear();
	reader.close();
	reader.open("PixelShader.cso", std::ios::binary | std::ios::ate);
	if (!reader.is_open()) 
	{
		std::cerr << "cannot open pixel file" << std::endl;
		return false;
	}

	reader.seekg(0, std::ios::end);
	shaderData.reserve(static_cast<unsigned int>(reader.tellg()));
	reader.seekg(0, std::ios::beg);

	shaderData.assign((std::istreambuf_iterator<char>(reader)), 
		std::istreambuf_iterator<char>());

	if (FAILED(device->CreatePixelShader(shaderData.c_str(), shaderData.length(), nullptr, &pShader))) 
	{
		std::cerr << "cannot create pixelShader" << std::endl;
		return false;
	}

	return true;

}

bool CreateInputLayout(ID3D11Device* device, ID3D11InputLayout*& inputLayout, std::string& byteCode) 
{
	D3D11_INPUT_ELEMENT_DESC inputDesc[2] = 
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	HRESULT hr = device->CreateInputLayout(inputDesc, 2, byteCode.c_str(), byteCode.length(), &inputLayout);

	return !FAILED(hr);
}
float xpos = 0.f;
const int nroftriangles = 2 * 3;
D3D11_SUBRESOURCE_DATA data;
bool CreateVertexBuffer(ID3D11Device* device, ID3D11Buffer*& vBuffer) 
{
	
	vertex triangles[nroftriangles] =
	{
		
		{{0.f,   0.5f, 0.0f}, {0,0,1}},
		{{0.5f,  -0.5f, 0.0f}, {0,1,0}},
		{{0.f, -0.5f, 0.0f}, {1,0,0}},

		{{0.51f,   0.5f, 0.0f}, {1,1,1}},
		{{0.51f,  -0.5f, 0.0f},{1,1,1}},
		{{0.01f, 0.5f, 0.0f},{1,1,1}},
	};
	D3D11_BUFFER_DESC bDesc;
	bDesc.ByteWidth = sizeof(vertex) * ARRAYSIZE(triangles);
	//bDesc.Usage = D3D11_USAGE_IMMUTABLE;
	bDesc.Usage = D3D11_USAGE_DEFAULT;
	bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bDesc.CPUAccessFlags = 0;
	bDesc.MiscFlags = 0;
	bDesc.StructureByteStride = 0;
	
	

	
	data.pSysMem = triangles;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	HRESULT hr = device->CreateBuffer(&bDesc, &data, &vBuffer);
	
	if (FAILED(hr)) {
		std::cout << "failed" << std::endl;
		return false;
	}

	

	return !FAILED(hr);
}

bool rotateTriangles(float angle, ID3D11Device* device, ID3D11DeviceContext*& immediateContext, ID3D11Buffer*& vBuffer)
{
	struct ConstantBuffer {
		struct {
			float element[4][4];
		}transformation;
	};
	const ConstantBuffer cb = {
		{
			std::cos(angle),  std::sin(angle), 0.f, 0.f,
			-std::sin(angle), std::cos(angle), 0.f, 0.f,
			0.f,              0.f,			   1.f, 0.f,
			0.f,              0.f,			   0.f, 1.f,
		}
	};
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
	D3D11_BUFFER_DESC CBD;
	CBD.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	CBD.Usage = D3D11_USAGE_DYNAMIC;
	CBD.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	CBD.MiscFlags = 0u;
	CBD.ByteWidth = sizeof(cb);
	CBD.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &cb;

	HRESULT hr = device->CreateBuffer(&CBD, &data, &vBuffer);
	
	//immediateContext->VSSetConstantBuffers(0, 1, pConstantBuffer.GetAddressOf());

	return !FAILED(hr);
}

bool SetupPipeline(ID3D11Device* device, ID3D11Buffer*& vBuffer, ID3D11VertexShader*& vShader, ID3D11PixelShader*& pShader, ID3D11InputLayout*& inputLayout)
{
	std::string vShaderByteCode;
	if (!loadShader(device, vShader, pShader, vShaderByteCode)) 
	{
		std::cerr << "cant load shaders" << std::endl;
		return false;
	}

	if (!CreateInputLayout(device, inputLayout, vShaderByteCode))
	{
		std::cerr << "cant load inputlayout" << std::endl;
		return false;
	}

	if (!CreateVertexBuffer(device, vBuffer))
	{
		std::cerr << "cant load vBuffer" << std::endl;
		return false;
	}

	return true;
}



