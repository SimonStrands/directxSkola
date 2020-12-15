#pragma once
#include <d3d11.h>
#include "plHelper.h"
#include "D311Helper.h"
#include "mat.h"
#include "Light.h"
#include <DirectXMath.h>
#include "deltaTime.h"


struct Vcb {
	struct {
		float element[4][4];
	}transform;
	struct {
		float element[4][4];
	}view;
	struct {
		float element[4][4];
	}projection;
};

struct Pcb {
	struct {
		float element[4];
	}lightPos;
	struct {
		float element[4];
	}cameraPos;
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
	Vcb vcbd = {
		{//transform
			1.0f,0.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,0.0f,
			0.0f,0.0f,1.0f,0.0f,
			0.0f,0.0f,0.0f,1.0f,
		},
		{//view
			1.0f,0.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,0.0f,
			0.0f,0.0f,1.0f,0.0f,
			0.0f,0.0f,0.0f,1.0f,
		},
		{//projection
			1.0f,0.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,0.0f,
			0.0f,0.0f,1.0f,0.0f,
			0.0f,0.0f,0.0f,1.0f,
		},
		
	};
	Pcb pcbd = {
		{//lightPos
			1,1,1,1,
		},
		{
			0,0,1,1,
		},
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
	ID3D11Buffer* Vg_pConstantBuffer;
	ID3D11Buffer* Pg_pConstantBuffer;
	ID3D11RasterizerState* pRS;

	ID3D11Texture2D* tex;
	ID3D11ShaderResourceView* texSRV;
	ID3D11SamplerState* sampler;
	
	Matrix4x4 lightMatrix;
	Matrix4x4 makeToCb;//worldMatrix 

	void Projection();
	void View();

	vec32 quadpos;
	vec32 quadRoationPos;

	PointLight light;
	DeltaTime dt;
	float speed;

	int nrOfTriangles;
	float yRot;
	float scale;
	float xCamPos, yCamPos, zCamPos;
	int screenWidth, screenHeight;
	float fov, ratio, farPlane, nearPlane;
	const int WIDHT, HEIGHT;
protected:
	bool CreateVertexBuffer();
	bool worldMatrix();
public:
	Graphics(UINT WIDTH, UINT HEIGHT, HWND& wnd);
	virtual ~Graphics();
	int getNrOfTriangles();
	void Render();
};