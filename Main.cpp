#include <Windows.h>
#include <iostream>
#include <d3d11.h>

#include "WindowHelper.h"
#include "D311Helper.h"
#include "plHelper.h"


void Render(ID3D11DeviceContext* immediateContext, ID3D11RenderTargetView* rtv, ID3D11DepthStencilView* dsview, D3D11_VIEWPORT& viewport,
	ID3D11VertexShader* vShader, ID3D11PixelShader* pShader, ID3D11InputLayout* inputLayout, ID3D11Buffer* vBuffer) {
	
	float clearColor[4] = { 0.1f,0.1f,0.1f,0 };
	immediateContext->ClearRenderTargetView(rtv, clearColor);
	immediateContext->ClearDepthStencilView(dsview, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	
	UINT strid = sizeof(vertex);
	UINT offset = 0;
	immediateContext->IASetVertexBuffers(0, 1, &vBuffer, &strid, &offset);
	immediateContext->IASetInputLayout(inputLayout);
	immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	immediateContext->VSSetShader(vShader, nullptr, 0);
	immediateContext->RSSetViewports(1, &viewport);
	immediateContext->PSSetShader(pShader, nullptr, 0);
	immediateContext->OMSetRenderTargets(1, &rtv, dsview);
	for (int i = 0; i < 2; i++) {
		immediateContext->Draw(3, (i)*3);
	}
	
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	const UINT WIDTH = 1024;
	const UINT HEIGHT = 576;
	HWND wnd;
	
	if (!SetupWindow(hInstance, WIDTH, HEIGHT, nCmdShow, wnd)) {
		std::cerr << "failed" << std::endl;
		return -1;
	}

	ID3D11Device* device;
	ID3D11DeviceContext *immediateContext;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* renderTarget;
	ID3D11Texture2D* dsTexture;
	ID3D11DepthStencilView *dsView;
	D3D11_VIEWPORT viewPort;
	ID3D11InputLayout* inputLayout;
	ID3D11Buffer* vertexBuffer;
	ID3D11VertexShader* vShader;
	ID3D11PixelShader* pShader;

	if (!SetupD3D11(WIDTH, HEIGHT, wnd, device, immediateContext, swapChain, renderTarget, dsTexture, dsView, viewPort)) 
	{
		std::cerr << "cant set up" << std::endl;
		return -1;
	}
	if (!SetupPipeline(device, vertexBuffer, vShader, pShader, inputLayout)) 
	{
		std::cerr << "cant set up" << std::endl;
		return -1;
	}

	MSG msg = {};
	float x = 0;
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Render(immediateContext, renderTarget, dsView, viewPort, vShader, pShader, inputLayout, vertexBuffer);
		//this is not ok
		//x = x + 0.01f;
		if (GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
		{
			if (!rotateTriangles(x, device, immediateContext, vertexBuffer)) {
				std::cout << "wrong" << std::endl;
				break;
			}
		}
		
		swapChain->Present(0, 0);
	}

	vertexBuffer->Release();
	inputLayout->Release();
	vShader->Release();
	pShader->Release();

	dsView->Release();
	dsTexture->Release();
	renderTarget->Release();
	swapChain->Release();
	immediateContext->Release();
	device->Release();
	return 0;
}