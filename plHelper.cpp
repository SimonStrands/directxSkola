#include "plHelper.h"
#include <wrl.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION 
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool loadShader(ID3D11Device* device, ID3D11VertexShader*& vShader, ID3D11PixelShader*& pShader, std::string& vShaderByteCode) 
{
	std::string shaderData;
	std::ifstream reader;
	reader.open("../Debug/VertexShader.cso", std::ios::binary | std::ios::ate);
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
	reader.open("../Debug/PixelShader.cso", std::ios::binary | std::ios::ate);
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
	D3D11_INPUT_ELEMENT_DESC inputDesc[3] = 
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0,12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	HRESULT hr = device->CreateInputLayout(inputDesc, 3, byteCode.c_str(), byteCode.length(), &inputLayout);

	return !FAILED(hr);
}

bool CreateTexture(ID3D11Device* device, ID3D11Texture2D*& tex, ID3D11ShaderResourceView*& texSRV) 
{
	//int textureWidth = 512;
	//int textureHeight = 512;

	int textureWidth;
	int textureHeight;
	int channels;

	std::string file = "babyyoda.jpg";
	unsigned char * textureData = stbi_load(file.c_str(), &textureWidth, &textureHeight, &channels, 4);

	D3D11_TEXTURE2D_DESC desc;
	desc.Width = textureWidth;
	desc.Height = textureHeight;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_IMMUTABLE;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = (void*)textureData;
	data.SysMemPitch = textureWidth * 4;
	data.SysMemSlicePitch = textureWidth * textureHeight * 4;

	//!FAIELD?
	if (FAILED(device->CreateTexture2D(&desc, &data, &tex))) {
		printf("cannot create texture");
		return false;
	}
	HRESULT hr = device->CreateShaderResourceView(tex, nullptr, &texSRV);
	delete[] textureData;
	return !FAILED(hr);
}

bool CreateSamplerState(ID3D11Device* device, ID3D11SamplerState*& sampler) 
{
	D3D11_SAMPLER_DESC desc;
	desc.Filter = D3D11_FILTER_ANISOTROPIC;
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.MipLODBias = 0;
	desc.MaxAnisotropy = 16;
	desc.BorderColor[0] = desc.BorderColor[1] = desc.BorderColor[2] = desc.BorderColor[3] = 0;
	desc.MinLOD = 0;
	desc.MaxLOD = D3D11_FLOAT32_MAX;

	HRESULT hr = device->CreateSamplerState(&desc, &sampler);
	return !FAILED(hr);
}

bool SetupPipeline(ID3D11Device* device, ID3D11Buffer*& vBuffer, 
	ID3D11VertexShader*& vShader, ID3D11PixelShader*& pShader, 
	ID3D11InputLayout*& inputLayout, ID3D11Texture2D*& tex, 
	ID3D11ShaderResourceView*& textureRSV, ID3D11SamplerState*& sampler)
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
	if (!CreateTexture(device, tex, textureRSV))
	{
		std::cerr << "cant load texture" << std::endl;
		return false;
	}
	if (!CreateSamplerState(device, sampler))
	{
		std::cerr << "cant load sampler" << std::endl;
		return false;
	}

	return true;
}



