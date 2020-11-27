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


bool SetupPipeline(ID3D11Device* device, ID3D11Buffer*& vBuffer, ID3D11VertexShader*& vShader, ID3D11PixelShader*& pShader, ID3D11InputLayout*& inputLayout)
{
	//ID3D11RasterizerState* RState;
	//immediateContext->RSSetState();
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

	return true;
}



