#include "Graphics.h"
#include <wrl.h>

const float PI = 3.1415926535897f;

void Graphics::keyboardDebug()
{
	if (GetKeyState('A') & 0x8000)
	{
		yRot += speed * (float)dt.dt();
	}
	if (GetKeyState('D') & 0x8000)
	{
		yRot -= speed * (float)dt.dt();
	}
	if (GetKeyState('W') & 0x8000)
	{
		scale += speed * (float)dt.dt();
	}
	if (GetKeyState('S') & 0x8000)
	{
		scale -= speed * (float)dt.dt();
	}
	if (GetKeyState('F') & 0x8000) {
		c -= 0.001f;
		getVertexBuffer();
	}
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		yCamPos -= speed * (float)dt.dt();
	}
	if (GetKeyState(VK_UP) & 0x8000)
	{
		yCamPos += speed * (float)dt.dt();
	}
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		xCamPos -= speed * (float)dt.dt();
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		xCamPos += speed * (float)dt.dt();
	}
	if (GetKeyState(VK_CONTROL) & 0x8000)
	{
		zCamPos += speed * (float)dt.dt();
	}
	if (GetKeyState(VK_SHIFT) & 0x8000)
	{
		zCamPos -= speed * (float)dt.dt();
	}
	if (yRot > 6.281887f) {
		yRot -= 6.281887f;
	}
	else if (yRot < 6.281887f) {
		yRot += 6.281887f;
	}

}

void Graphics::getVertexBuffer()
{
	//D3D11_MAPPED_SUBRESOURCE resource;
	//vertex triangles[] =
	//{
	//	{{-0.25f, -0.5f, 0.0f  - c }, {1,0,0}},
	//	{{0.25f,  -0.5f, 0.0f  - c }, {0,1,0}},
	//	{{-0.25f,   0.5f, 0.0f - c}, {0,0,1}},
	//
	//
	//	{{0.26f,   0.5f, 0.0f - c}, {1,1,1}},
	//	{{0.26f,  -0.5f, 0.0f - c}, {1,1,1}},
	//	{{-0.24f, 0.5f, 0.0f - c},	{1,1,1}},
	//};
	//
	//immediateContext->Map(vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	//memcpy(resource.pData, &triangles, sizeof(triangles));
	//immediateContext->Unmap(vertexBuffer, 0);
	//
	//ZeroMemory(&resource, sizeof(D3D11_MAPPED_SUBRESOURCE));

}

void Graphics::debugcd()
{
	//float **ma2d = makeToCb.GetMatrix();
	printf("\n");
	//vec4 *test = new vec4(-0.25f, -0.5f, 0.0f , 1.0f);
	//vec4 test2 = makeToCb * (*test);
	//for (int i = 0; i < 4; i++) {
	//	printf("%f", test2.getPoints()[i]);
	//}
	/*for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			printf("%f ", ma2d[x][y]);
		}
		printf("\n\n");
	}
	for (int i = 0; i < 4; i++) {
		delete[] ma2d[i];
	}*/
	//delete[] ma2d;
}
bool Graphics::CreateVertexBuffer()
{
	vertex triangles[] =
	{ 
		{{-0.25f - quadpos.x,  0.5f - quadpos.y, 0.f -quadpos.z}, {0.0f, 0.0f}, {0.0f,0.0f,1.0f,0.0f}},
		{{-0.25f - quadpos.x, -0.5f - quadpos.y, 0.f -quadpos.z}, {0.0f, 1.0f}, {0.0f,0.0f,1.0f,0.0f}},
		{{ 0.25f - quadpos.x, -0.5f - quadpos.y, 0.f -quadpos.z}, {1.0f, 1.0f}, {0.0f,0.0f,1.0f,0.0f}},
		
		
		{{ 0.25f - quadpos.x,  0.5f - quadpos.y, 0.f - quadpos.z}, {1.0f,0.0f}, {0.0f,0.0f,1.0f,0.0f}},
		{{ 0.25f - quadpos.x, -0.5f - quadpos.y, 0.f - quadpos.z}, {1.0f,1.0f}, {0.0f,0.0f,1.0f,0.0f}},
		{{-0.25f - quadpos.x,  0.5f - quadpos.y, 0.f - quadpos.z}, {0.0f,0.0f}, {0.0f,0.0f,1.0f,0.0f}},
	};


	D3D11_BUFFER_DESC bDesc = {};
	nrOfTriangles = ARRAYSIZE(triangles) / 3;
	bDesc.ByteWidth = sizeof(vertex) * ARRAYSIZE(triangles);
	bDesc.Usage = D3D11_USAGE_DYNAMIC;
	bDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
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
	//create vertexConstantBuffer
	D3D11_BUFFER_DESC CbDesc;
	CbDesc.ByteWidth = sizeof(Vcb);
	CbDesc.Usage = D3D11_USAGE_DYNAMIC;
	CbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	CbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	CbDesc.MiscFlags = 0;
	CbDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = &vcbd;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	hr = device->CreateBuffer(&CbDesc, &InitData, &Vg_pConstantBuffer);
	if (FAILED(hr)) {
		printf("failed");
		return false;
	}
	//create PixelConstantBuffer
	CbDesc.ByteWidth = sizeof(Pcb);
	InitData.pSysMem = &pcbd;
	hr = device->CreateBuffer(&CbDesc, &InitData, &Pg_pConstantBuffer);

	return !FAILED(hr);

}

bool Graphics::worldMatrix()
{
	
	keyboardDebug();
	View();
	// a Y rotation
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		printf("yrot = %f\n", yRot);
	}
	float rot[4][4] = {
			{std::cos(yRot), 0.0f, std::sin(yRot), 0.0f },
			{0.0f,			 1.0f,	0.0f,			 0.0f},
			{-std::sin(yRot),0.0f, std::cos(yRot), 0.0f	  },
			{0.0f,			 0.0f,			 0.0f,  1.0f }
	};
	float scal[4][4] = {
			{scale,0.0f,0.0f,0.0f	},
			{0.0f,scale,0.0f,0.0f	},
			{0.0f,0.0f,scale,0.0f	},
			{0.0f,0.0f,0.0f,1.0f	},

	};
	float trans[4][4]{
		{1,    0,    0,	   0},
		{0,    1,    0,	   0},
		{0,    0,    1,	   0},
		{quadRoationPos.x,    quadRoationPos.y,    quadRoationPos.z,    1},
	};

	//makeToCb = Matrix4x4(eh1) * rot * eh2 * scal * trans;
	makeToCb =  Matrix4x4(rot) * Matrix4x4(trans) * Matrix4x4(scal);

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

	//setting cb
	float** arr2d = makeToCb.GetMatrix();
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			vcbd.transform.element[x][y] = arr2d[x][y];
		}
	}
	for (int i = 0; i < 4; i++) {
		delete[] arr2d[i];
	}
	delete[] arr2d;

	//Light
	pcbd.lightPos.element[0] = xCamPos;
	pcbd.lightPos.element[1] = yCamPos;
	pcbd.lightPos.element[2] = zCamPos + 1;
	pcbd.lightPos.element[3] = 1;

	pcbd.cameraPos.element[0] = xCamPos;
	pcbd.cameraPos.element[1] = yCamPos;
	pcbd.cameraPos.element[2] = zCamPos + 1;
	pcbd.cameraPos.element[3] = 1  ;


	D3D11_MAPPED_SUBRESOURCE resource;

	immediateContext->Map(Vg_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	memcpy(resource.pData, &vcbd, sizeof(Vcb));
	immediateContext->Unmap(Vg_pConstantBuffer, 0);
	ZeroMemory(&resource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	immediateContext->Map(Pg_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	memcpy(resource.pData, &pcbd, sizeof(Pcb));
	immediateContext->Unmap(Pg_pConstantBuffer, 0);
	ZeroMemory(&resource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	return true;
}

void Graphics::Projection()
{
	float arr[4][4] = 
	{
		{1/ ratio * tan(fov/2), 0, 0, 0},
		{0, tan(fov / 2), 0, 0},
		{0, 0, farPlane/(farPlane-nearPlane), 1},
		{0, 0, -(farPlane*nearPlane)/farPlane-nearPlane, 0},
	};
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			vcbd.projection.element[x][y] = arr[x][y];
		}
	}
}

void Graphics::View()
{
	float arr[4][4] = {
		{1.0f,0.0f,0.0f,0.0f},
		{0.0f,1.0f,0.0f,0.0f},
		{0.0f,0.0f,1.0f,0.0f},
		{xCamPos,yCamPos,zCamPos,1.0f}
	};
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			vcbd.view.element[x][y] = arr[x][y];
		}
	}
}


Graphics::Graphics(UINT WIDTH, UINT HEIGHT, HWND& wnd) :
	WIDHT(WIDTH),
	HEIGHT(HEIGHT),
	makeToCb(vcbd.transform.element),
	speed(2.5f),
	light(vec32(0,0,2.f)),
	quadpos(0,0,0),
	quadRoationPos(0.5f,0,0)
{
	screenHeight = (int)HEIGHT;
	screenWidth = (int)WIDTH;
	fov = 1.45f;
	ratio = 16 / 9;//just made something up
	farPlane = 40;
	nearPlane = 0.1f;
	
	xCamPos = yCamPos = 0.0; zCamPos = 2.0f;
	yRot = 0;
	scale = 1;
	nrOfTriangles = 0;

	Vg_pConstantBuffer = NULL;
	Pg_pConstantBuffer = NULL;
	inputLayout = nullptr; pShader = nullptr; vShader = nullptr; vertexBuffer = nullptr; texSRV = nullptr;
	//setting up projection matrix
	Projection();
	View();
	//SetTrianglePos();
	if (!SetupD3D11(WIDTH, HEIGHT, wnd, device, immediateContext, swapChain, renderTarget, dsTexture, dsView, viewPort, pRS))
	{
		std::cerr << "cant set up" << std::endl;
		delete this;
	}
	if (!SetupPipeline(device, vertexBuffer, vShader, pShader, inputLayout, tex, texSRV, sampler))
	{
		std::cerr << "cant set up" << std::endl;
		delete this;
	}
	if (!CreateVertexBuffer()) {
		std::cerr << "cant set up" << std::endl;
		delete this;
	}
	
	UINT strid = sizeof(vertex);
	UINT offset = 0;
	immediateContext->PSSetShaderResources(0, 1, &texSRV);
	immediateContext->PSSetSamplers(0, 1, &sampler);
	immediateContext->VSSetShader(vShader, nullptr, 0);
	immediateContext->PSSetShader(pShader, nullptr, 0);
	immediateContext->IASetVertexBuffers(0, 1, &vertexBuffer, &strid, &offset);
	immediateContext->RSSetViewports(1, &viewPort);
	immediateContext->OMSetRenderTargets(1, &renderTarget, dsView);
	immediateContext->RSSetState(pRS);
	immediateContext->VSSetConstantBuffers(0, 1, &Vg_pConstantBuffer);
	immediateContext->PSSetConstantBuffers(0, 1, &Pg_pConstantBuffer);
	immediateContext->IASetInputLayout(inputLayout);
	immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	
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
	if (Vg_pConstantBuffer != nullptr) {
		Vg_pConstantBuffer->Release();
	}
	if (Pg_pConstantBuffer != nullptr) {
		Pg_pConstantBuffer->Release();
	}
	if (pRS != nullptr) {
		pRS->Release();
	}
	if (tex != nullptr) {
		tex->Release();
	}
	if (texSRV != nullptr) {
		texSRV->Release();
	}
	if (sampler != nullptr) {
		sampler->Release();
	}

	//for (int i = 0; i < nrOfTriangles; i++) {
	//	if (TrianglePos[i] != nullptr) {
	//		delete[] TrianglePos[i];
	//	}
	//}
	//delete[] TrianglePos[0];
	//delete[] TrianglePos;
}

int Graphics::getNrOfTriangles()
{
	return this->nrOfTriangles;
}
void Graphics::Render()
{
	//clear background
	dt.restartClock();
	float clearColor[4] = { 0.1f,0.1f,0.1f,0 };
	immediateContext->ClearRenderTargetView(renderTarget, clearColor);
	immediateContext->ClearDepthStencilView(dsView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);

	worldMatrix();
	

	for (int i = 0; i < nrOfTriangles; i++) {
		immediateContext->Draw(3, (i) * 3);
	}
	swapChain->Present(0, 0);
}
