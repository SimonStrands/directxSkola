#pragma once
#include <d3d11.h>
#include <array>

struct vertex {
	float pos[3];
	float color[3];

	vertex(const std::array<float, 3>& position, const std::array<float, 3>& rgb) {
		for (int i = 0; i < 3; i++) {
			pos[i] = position[i];
			color[i] = rgb[i];
		}
	}
};

bool SetupPipeline(ID3D11Device* device, ID3D11Buffer*& vBuffer, ID3D11VertexShader*& vShader, ID3D11PixelShader*& pShader, ID3D11InputLayout*& inputLayout);
bool rotateTriangles(float angle, ID3D11Device* device, ID3D11DeviceContext *&immediateContext, ID3D11Buffer*& vBuffer);