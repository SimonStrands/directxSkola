#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <iostream>

bool SetupD3D11(UINT width,
	UINT height,
	HWND wnd,
	ID3D11Device*& device,
	ID3D11DeviceContext*& immediateContext,
	IDXGISwapChain*& swapChain,
	ID3D11RenderTargetView*& renderTarget,
	ID3D11Texture2D*& dsTexture,
	ID3D11DepthStencilView*& dsView,
	D3D11_VIEWPORT& viewPort);
