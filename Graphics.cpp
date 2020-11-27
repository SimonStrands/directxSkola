#include "Graphics.h"
#include <wrl.h>

void Graphics::keyboardDebug()
{
	if (GetKeyState('A') & 0x8000)
	{
		yRot += 0.001f;
	}
	if (GetKeyState('D') & 0x8000)
	{
		yRot -= 0.001f;
	}
	if (GetKeyState('W') & 0x8000)
	{
		scale += 0.001f;
	}
	if (GetKeyState('S') & 0x8000)
	{
		scale -= 0.001f;
	}
}

void Graphics::debugcd()
{
	float **ma2d = makeToCb.GetMatrix();
	printf("\n");
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			printf("%f ", ma2d[x][y]);
		}
		printf("\n\n");
	}
	for (int i = 0; i < 4; i++) {
		delete[] ma2d[i];
	}
	delete[] ma2d;
}

bool Graphics::CreateVertexBuffer()
{
	vertex triangles[] =
	{ 
		{{-0.25f, -0.5f, 0.0f}, {1,0,0}},
		{{0.25f,  -0.5f, 0.0f}, {0,1,0}},
		{{-0.25f,   0.5f, 0.0f}, {0,0,1}},
		
		
		{{0.26f,   0.5f, 0.0f}, {1,1,1}},
		{{0.26f,  -0.5f, 0.0f}, {1,1,1}},
		{{-0.24f, 0.5f, 0.0f},	{1,1,1}},
	};

	D3D11_BUFFER_DESC bDesc = {};
	bDesc.ByteWidth = sizeof(vertex) * ARRAYSIZE(triangles);
	bDesc.Usage = D3D11_USAGE_DYNAMIC;
	bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bDesc.CPUAccessFlags = 0;
	bDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bDesc.MiscFlags = 0;
	bDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = triangles;
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	HRESULT hr = device->CreateBuffer(&bDesc, &data, &vertexBuffer);

	if (FAILED(hr)) {
		printf("failed");
		return false;
	}

	D3D11_BUFFER_DESC CbDesc;
	CbDesc.ByteWidth = sizeof(ConstantBuffer);
	CbDesc.Usage = D3D11_USAGE_DYNAMIC;
	CbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	CbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	CbDesc.MiscFlags = 0;
	CbDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = &cbd;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;


	hr = device->CreateBuffer(&CbDesc, &InitData, &g_pConstantBuffer);
	return !FAILED(hr);

}

bool Graphics::movements(float x)
{
	D3D11_MAPPED_SUBRESOURCE resource;
	cbd = {
		{
			x,0.0f,0.0f,0.0f,
			0.0f,x,0.0f,0.0f,
			0.0f,0.0f,x,0.0f,
			0.0f,0.0f,0.0f,1.0f,
		}
	};
	immediateContext->Map(g_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	memcpy(resource.pData, &cbd, sizeof(cb));
	immediateContext->Unmap(g_pConstantBuffer, 0);
	

	ZeroMemory(&resource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	return true;
}

bool Graphics::worldMatrix()
{
	D3D11_MAPPED_SUBRESOURCE resource;
	keyboardDebug();
	if (!Rotation()) {//kinda done
		return false;
	}
	if (!Scale()) {
		return false;
	}
	float** arr2d = makeToCb.GetMatrix();
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			cbd.transform.element[x][y] = arr2d[x][y];//this shit
		}
	}
	for (int i = 0; i < 4; i++) {
		delete[] arr2d[i];
	}
	delete[] arr2d;
	scale = 1;
	yRot = 0;
	//if (!Translate()) {
	//	return false;
	//}
	if (GetKeyState('O') & 0x8000)
	{
		if (!pressed) {
			
			debugcd();
		}
		pressed = true;
	}
	else {
		pressed = false;
	}
	
	immediateContext->Map(g_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	memcpy(resource.pData, &cbd, sizeof(cb));
	immediateContext->Unmap(g_pConstantBuffer, 0);

	ZeroMemory(&resource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	return true;
}

bool Graphics::Rotation()
{	
	float rot[4][4] = {
			{std::cos(yRot), 0.0f, -std::sin(yRot), 0.0f },
			{0.0f,			 1.0f,	0.0f,			 0.0f},
			{std::sin(yRot),0.0f, std::cos(yRot), 0.0f	  },
			{0.0f,			 0.0f,			 0.0f,  1.0f }
	};
	makeToCb = (makeToCb * rot);
	return true;
}

bool Graphics::Scale()
{
	float rot[4][4] = {

			{scale,0.0f,0.0f,0.0f	},
			{0.0f,scale,0.0f,0.0f	},
			{0.0f,0.0f,scale,0.0f	},
			{0.0f,0.0f,0.0f,1.0f	},

	};
	makeToCb = (makeToCb * rot);
	return true;
}

bool Graphics::Translate()
{
	
	// need to get xyz value on triangle
	//const float zInv = 1.0f / cbd.transform.element[2][2];
	//cbd.transform.element[0][0] = (cbd.transform.element[0][0] * zInv + 1.0f);
	//cbd.transform.element[1][1] = (-cbd.transform.element[1][1] * zInv + 1.0f);
	cbd.transform.element[2][2] = 0;
	//printf("%f", (cbd.transform.element[0][0] * zInv + 1.0f));

	return true;
}



Graphics::Graphics(UINT WIDTH, UINT HEIGHT, HWND &wnd):
	makeToCb(cbd.transform.element)
{
	yRot = 0;
	scale = 1;
	nrOfTriangles = 2;
	g_pConstantBuffer = NULL;
	
	inputLayout = nullptr; pShader = nullptr; vShader = nullptr; vertexBuffer = nullptr;
	if (!SetupD3D11(WIDTH, HEIGHT, wnd, device, immediateContext, swapChain, renderTarget, dsTexture, dsView, viewPort, pRS))
	{
		std::cerr << "cant set up" << std::endl;
		delete this;
	}
	if (!SetupPipeline(device, vertexBuffer, vShader, pShader, inputLayout))
	{
		std::cerr << "cant set up" << std::endl;
		delete this;
	}
	if (!CreateVertexBuffer()) {
		std::cerr << "cant set up" << std::endl;
		delete this;
	}
}

Graphics::~Graphics()
{
	if (vertexBuffer != nullptr) {
		vertexBuffer->Release();
	}
	if (inputLayout != nullptr) {
		inputLayout->Release();
	}
	if (vShader != nullptr) {
		vShader->Release();
	}
	if (pShader != nullptr) {
		pShader->Release();
	}
	if (dsView != nullptr) {
		dsView->Release();
	}
	if (dsTexture != nullptr) {
		dsTexture->Release();
	}
	if (renderTarget != nullptr) {
		renderTarget->Release();
	}
	if (swapChain != nullptr) {
		swapChain->Release();
	}
	if (immediateContext != nullptr) {
		immediateContext->Release();
	}
	if (device != nullptr) {
		device->Release();
	}
	if (g_pConstantBuffer != nullptr) {
		g_pConstantBuffer->Release();
	}
	if (pRS != nullptr) {
		pRS->Release();
	}
}

int Graphics::getNrOfTriangles()
{
	return this->nrOfTriangles;
}
void Graphics::Render()
{
	//clear background
	float clearColor[4] = { 0.1f,0.1f,0.1f,0 };
	immediateContext->ClearRenderTargetView(renderTarget, clearColor);
	immediateContext->ClearDepthStencilView(dsView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	//alot of memory leaks
	worldMatrix();
	UINT strid = sizeof(vertex);
	UINT offset = 0;
	immediateContext->RSSetState(pRS);
	immediateContext->VSSetConstantBuffers(0, 1, &g_pConstantBuffer);
	immediateContext->IASetVertexBuffers(0, 1, &vertexBuffer, &strid, &offset);
	immediateContext->IASetInputLayout(inputLayout);
	immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	immediateContext->VSSetShader(vShader, nullptr, 0);
	immediateContext->RSSetViewports(1, &viewPort);
	immediateContext->PSSetShader(pShader, nullptr, 0);
	immediateContext->OMSetRenderTargets(1, &renderTarget, dsView);
	for (int i = 0; i < nrOfTriangles; i++) {
		immediateContext->Draw(3, (i) * 3);
	}
	swapChain->Present(0, 0);
}


/*
bool Graphics::RotateTriangleZ(float angle)
{
	cb = {
		{
			std::cos(angle),  std::sin(angle), 0.0f, 0.f,
			-std::sin(angle), std::cos(angle), 0.f,  0.f,
			0.f,              0.f,             1.f,  0.f,
			0.0f,			  0.f,	           0.0f, 1.f,
		}
	};

	D3D11_BUFFER_DESC CbDesc;
	CbDesc.ByteWidth = sizeof(ConstantBuffer);
	CbDesc.Usage = D3D11_USAGE_DYNAMIC;
	CbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	CbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	CbDesc.MiscFlags = 0;
	CbDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = &cb;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;


	HRESULT hr = device->CreateBuffer(&CbDesc, &InitData, &g_pConstantBuffer);
	return true;
}

bool Graphics::RotateTriangleX(float angle)
{
	cb = {
		{
			1.f, 0.f,              0.f,             0.f,
			0.f, std::cos(angle),  std::sin(angle), 0.f,
			0.f, -std::sin(angle), std::cos(angle), 0.f,
			0.f, 0.f,              0.f,             1.f,
		}
	};

	D3D11_BUFFER_DESC CbDesc;
	CbDesc.ByteWidth = sizeof(ConstantBuffer);
	CbDesc.Usage = D3D11_USAGE_DYNAMIC;
	CbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	CbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	CbDesc.MiscFlags = 0;
	CbDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = &cb;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;


	HRESULT hr = device->CreateBuffer(&CbDesc, &InitData, &g_pConstantBuffer);
	return true;
}

bool Graphics::RotateTriangleY(float angle)
{
	cb = {
		{
			std::cos(angle),  0.f, -std::sin(angle), 0.f,
			 0.0f,            1.f, 0.f,				 0.f,
			std::sin(angle),  0.f, std::cos(angle),  0.f,
			0.f,              0.f, 0.f,              1.f,
		}
	};

	D3D11_BUFFER_DESC CbDesc;
	CbDesc.ByteWidth = sizeof(ConstantBuffer);
	CbDesc.Usage = D3D11_USAGE_DYNAMIC;
	CbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	CbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	CbDesc.MiscFlags = 0;
	CbDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = &cb;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;


	HRESULT hr = device->CreateBuffer(&CbDesc, &InitData, &g_pConstantBuffer);
	return true;
}
*/

/*void test(ID3D11Buffer *&vertexBuffer, ID3D11DeviceContext*& immediateContext) {
	D3D11_MAPPED_SUBRESOURCE resource;
	immediateContext->Map(vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	memcpy(resource.pData, sourceData, vertexDataSize);
	immediateContext->Unmap(vertexBuffer, 0);
}*/