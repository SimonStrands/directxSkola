#pragma once
#include <d3d11.h>
#include "plHelper.h"
#include "D311Helper.h"
#include "mat.h"

struct cb {
	struct {
		float element[4][4];
	}transform;
};

class Graphics {

private:
	//Debug shit
	float c = 0;
	void getVertexBuffer();
	void debugcd();
	void keyboardDebug();
	bool pressed = false;
private:
	cb cbd = {
		{
			1.0f,0.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,0.0f,
			0.0f,0.0f,1.0f,0.0f,
			0.0f,0.0f,0.0f,1.0f,
		}
	};
	ID3D11Device* device;
	ID3D11DeviceContext* immediateContext;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* renderTarget;
	ID3D11Texture2D* dsTexture;
	ID3D11DepthStencilView* dsView;
	D3D11_VIEWPORT viewPort;
	ID3D11InputLayout* inputLayout;
	ID3D11Buffer* vertexBuffer;
	ID3D11VertexShader* vShader;
	ID3D11PixelShader* pShader;
	ID3D11Buffer* g_pConstantBuffer;
	ID3D11RasterizerState* pRS;
	
	Matrix4x4 makeToCb;//worldMatrix 
	vec3 **TrianglePos;

	void SetTrianglePos();
	bool Rotation();
	bool Scale();
	bool Translate();
	bool Projection();
	bool ScreenSpaceToPubeSpace();

	int nrOfTriangles;
	float yRot;
	float scale;
	int screenWidth, screenHeight;
protected:
	bool CreateVertexBuffer();
	bool movements(float x);
	bool worldMatrix();
public:
	Graphics(UINT WIDTH, UINT HEIGHT, HWND& wnd);
	virtual ~Graphics();
	int getNrOfTriangles();
	void Render();
};