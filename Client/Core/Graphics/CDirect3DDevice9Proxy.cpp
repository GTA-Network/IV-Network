//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: CDirect3DDevice9Proxy.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include <CCore.h>
#include <CLogFile.h>
#include "CDirect3DDevice9Proxy.h"
//#include "CGraphics.h"

IDirect3DDevice9 * g_pGlobalDevice;
bool               g_bWindowedMode;
extern CCore			* g_pCore;

Direct3DDevice9Proxy::Direct3DDevice9Proxy(IDirect3D9 * d3d, IDirect3DDevice9 * device)
{
	m_pD3D = d3d;
	m_pD3DDevice = device;
	g_pGlobalDevice = device;
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::QueryInterface(REFIID riid, void ** ppvObj)
{
	return m_pD3DDevice->QueryInterface(riid, ppvObj);
}

ULONG STDMETHODCALLTYPE Direct3DDevice9Proxy::AddRef()
{
	return m_pD3DDevice->AddRef();
}

ULONG STDMETHODCALLTYPE Direct3DDevice9Proxy::Release()
{
	ULONG uRet = m_pD3DDevice->Release();

	if(uRet == 0)
	{
		// If the reference count is 0 delete ourselves
		delete this;
	}

	return uRet;
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::TestCooperativeLevel()
{
	return m_pD3DDevice->TestCooperativeLevel();
}

UINT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetAvailableTextureMem()
{
	return m_pD3DDevice->GetAvailableTextureMem();
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::EvictManagedResources()
{
	return m_pD3DDevice->EvictManagedResources();
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetDirect3D(IDirect3D9 ** ppD3D9)
{
	HRESULT hr = m_pD3DDevice->GetDirect3D(ppD3D9);

	if(SUCCEEDED(hr))
	{
		// Return the device pointer
		*ppD3D9 = m_pD3D;
	}

	return hr;	
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetDeviceCaps(D3DCAPS9 * pCaps)
{
	return m_pD3DDevice->GetDeviceCaps(pCaps);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetDisplayMode(UINT iSwapChain, D3DDISPLAYMODE * pMode)
{
	return m_pD3DDevice->GetDisplayMode(iSwapChain, pMode);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS * pParameters)
{
	return m_pD3DDevice->GetCreationParameters(pParameters);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9 * pCursorBitmap)
{
	return m_pD3DDevice->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);
}

void STDMETHODCALLTYPE Direct3DDevice9Proxy::SetCursorPosition(int X, int Y, DWORD Flags)
{
	return m_pD3DDevice->SetCursorPosition(X, Y, Flags);
}

BOOL STDMETHODCALLTYPE Direct3DDevice9Proxy::ShowCursor(BOOL bShow)
{
	return m_pD3DDevice->ShowCursor(bShow);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS * pPresentationParameters, IDirect3DSwapChain9 ** pSwapChain)
{
	return m_pD3DDevice->CreateAdditionalSwapChain(pPresentationParameters, pSwapChain);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetSwapChain(UINT iSwapChain, IDirect3DSwapChain9 ** pSwapChain)
{
	return m_pD3DDevice->GetSwapChain(iSwapChain, pSwapChain);
}

UINT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetNumberOfSwapChains()
{
	return m_pD3DDevice->GetNumberOfSwapChains();
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::Reset(D3DPRESENT_PARAMETERS * pPresentationParameters)
{
	CLogFile::Printf("PreD3DReset");

	// Call our lost device function
	g_pCore->OnDeviceReset(m_pD3DDevice);

	if(g_bWindowedMode)
	{
		pPresentationParameters->Windowed = 1;
		pPresentationParameters->Flags = 0;
		pPresentationParameters->FullScreen_RefreshRateInHz = 0;
		pPresentationParameters->PresentationInterval = 0;
		LONG_PTR style = GetWindowLongPtr(pPresentationParameters->hDeviceWindow, GWL_STYLE);
		SetWindowLongPtr(pPresentationParameters->hDeviceWindow, GWL_STYLE, style | WS_POPUPWINDOW | WS_CAPTION | WS_THICKFRAME);
		SetWindowPos(pPresentationParameters->hDeviceWindow, HWND_NOTOPMOST, 0, 0, pPresentationParameters->BackBufferWidth, pPresentationParameters->BackBufferHeight, SWP_SHOWWINDOW);
	}

	HRESULT hr = m_pD3DDevice->Reset(pPresentationParameters);

	if(SUCCEEDED(hr))
	{

		CLogFile::Printf("PostD3DReset(1)");
	}
	else
	{
		CLogFile::Printf("PostD3DReset(0)");
	}

	return hr;
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::Present(const RECT * pSourceRect, const RECT * pDestRect, HWND hDestWindowOverride, const RGNDATA * pDirtyRegion)
{
	return m_pD3DDevice->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetBackBuffer(UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9 ** ppBackBuffer)
{
	return m_pD3DDevice->GetBackBuffer(iSwapChain, iBackBuffer, Type, ppBackBuffer);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetRasterStatus(UINT iSwapChain, D3DRASTER_STATUS * pRasterStatus)
{
	return m_pD3DDevice->GetRasterStatus(iSwapChain, pRasterStatus);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetDialogBoxMode(BOOL bEnableDialogs)
{
	return m_pD3DDevice->SetDialogBoxMode(bEnableDialogs);
}

void STDMETHODCALLTYPE Direct3DDevice9Proxy::SetGammaRamp(UINT iSwapChain, DWORD Flags, const D3DGAMMARAMP * pRamp)
{
	return m_pD3DDevice->SetGammaRamp(iSwapChain, Flags, pRamp);
}

void STDMETHODCALLTYPE Direct3DDevice9Proxy::GetGammaRamp(UINT iSwapChain, D3DGAMMARAMP * pRamp)
{
	return m_pD3DDevice->GetGammaRamp(iSwapChain, pRamp);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9 ** ppTexture, HANDLE * pSharedHandle)
{
	return m_pD3DDevice->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9 ** ppVolumeTexture, HANDLE * pSharedHandle)
{
	return m_pD3DDevice->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9 ** ppCubeTexture, HANDLE * pSharedHandle)
{
	return m_pD3DDevice->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9 ** ppVertexBuffer, HANDLE * pSharedHandle)
{
	return m_pD3DDevice->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9 ** ppIndexBuffer, HANDLE * pSharedHandle)
{
	return m_pD3DDevice->CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9 ** ppSurface, HANDLE * pSharedHandle)
{
	return m_pD3DDevice->CreateRenderTarget(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9 ** ppSurface, HANDLE * pSharedHandle)
{
	return m_pD3DDevice->CreateDepthStencilSurface(Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::UpdateSurface(IDirect3DSurface9 * pSourceSurface, const RECT * pSourceRect, IDirect3DSurface9 * pDestinationSurface, const POINT * pDestPoint)
{
	return m_pD3DDevice->UpdateSurface(pSourceSurface, pSourceRect, pDestinationSurface, pDestPoint);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::UpdateTexture(IDirect3DBaseTexture9 * pSourceTexture, IDirect3DBaseTexture9 * pDestinationTexture)
{
	return m_pD3DDevice->UpdateTexture(pSourceTexture, pDestinationTexture);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetRenderTargetData(IDirect3DSurface9 * pRenderTarget, IDirect3DSurface9 * pDestSurface)
{
	return m_pD3DDevice->GetRenderTargetData(pRenderTarget, pDestSurface);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetFrontBufferData(UINT iSwapChain, IDirect3DSurface9 * pDestSurface)
{
	return m_pD3DDevice->GetFrontBufferData(iSwapChain, pDestSurface);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::StretchRect(IDirect3DSurface9 * pSourceSurface, const RECT * pSourceRect, IDirect3DSurface9 * pDestSurface, const RECT * pDestRect, D3DTEXTUREFILTERTYPE Filter)
{
	return m_pD3DDevice->StretchRect(pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::ColorFill(IDirect3DSurface9 * pSurface, const RECT * pRect, D3DCOLOR color)
{
	return m_pD3DDevice->ColorFill(pSurface, pRect, color);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9 ** ppSurface, HANDLE * pSharedHandle)
{
	return m_pD3DDevice->CreateOffscreenPlainSurface(Width, Height, Format, Pool, ppSurface, pSharedHandle);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9 * pRenderTarget)
{
	return m_pD3DDevice->SetRenderTarget(RenderTargetIndex, pRenderTarget);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9 ** ppRenderTarget)
{
	return m_pD3DDevice->GetRenderTarget(RenderTargetIndex, ppRenderTarget);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetDepthStencilSurface(IDirect3DSurface9 * pNewZStencil)
{
	return m_pD3DDevice->SetDepthStencilSurface(pNewZStencil);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetDepthStencilSurface(IDirect3DSurface9 ** ppZStencilSurface)
{
	return m_pD3DDevice->GetDepthStencilSurface(ppZStencilSurface);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::BeginScene()
{
	return m_pD3DDevice->BeginScene();
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::EndScene()
{
	g_pCore->OnDeviceRender();

	return m_pD3DDevice->EndScene();
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::Clear(DWORD Count, const D3DRECT * pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
{
	return m_pD3DDevice->Clear(Count, pRects, Flags, Color, Z, Stencil);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX * pMatrix)
{
	return m_pD3DDevice->SetTransform(State, pMatrix);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX * pMatrix)
{
	return m_pD3DDevice->GetTransform(State, pMatrix);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::MultiplyTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX * pMatrix)
{
	return m_pD3DDevice->MultiplyTransform(State, pMatrix);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetViewport(const D3DVIEWPORT9 * pViewport)
{
	return m_pD3DDevice->SetViewport(pViewport);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetViewport(D3DVIEWPORT9 * pViewport)
{
	return m_pD3DDevice->GetViewport(pViewport);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetMaterial(const D3DMATERIAL9 * pMaterial)
{
	return m_pD3DDevice->SetMaterial(pMaterial);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetMaterial(D3DMATERIAL9 * pMaterial)
{
	return m_pD3DDevice->GetMaterial(pMaterial);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetLight(DWORD Index, const D3DLIGHT9 * pLight)
{
	return m_pD3DDevice->SetLight(Index, pLight);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetLight(DWORD Index, D3DLIGHT9 * pLight)
{
	return m_pD3DDevice->GetLight(Index, pLight);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::LightEnable(DWORD Index, BOOL Enable)
{
	return m_pD3DDevice->LightEnable(Index, Enable);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetLightEnable(DWORD Index, BOOL * pEnable)
{
	return m_pD3DDevice->GetLightEnable(Index, pEnable);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetClipPlane(DWORD Index, const float * pPlane)
{
	return m_pD3DDevice->SetClipPlane(Index, pPlane);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetClipPlane(DWORD Index, float * pPlane)
{
	return m_pD3DDevice->GetClipPlane(Index, pPlane);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
	return m_pD3DDevice->SetRenderState(State, Value);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetRenderState(D3DRENDERSTATETYPE State, DWORD * pValue)
{
	return m_pD3DDevice->GetRenderState(State, pValue);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::CreateStateBlock(D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9 ** ppSB)
{
	return m_pD3DDevice->CreateStateBlock(Type, ppSB);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::BeginStateBlock()
{
	return m_pD3DDevice->BeginStateBlock();
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::EndStateBlock(IDirect3DStateBlock9 ** ppSB)
{
	return m_pD3DDevice->EndStateBlock(ppSB);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetClipStatus(const D3DCLIPSTATUS9 * pClipStatus)
{
	return m_pD3DDevice->SetClipStatus(pClipStatus);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetClipStatus(D3DCLIPSTATUS9 * pClipStatus)
{
	return m_pD3DDevice->GetClipStatus(pClipStatus);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetTexture(DWORD Stage, IDirect3DBaseTexture9 ** ppTexture)
{
	return m_pD3DDevice->GetTexture(Stage, ppTexture);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetTexture(DWORD Stage, IDirect3DBaseTexture9 * pTexture)
{
	return m_pD3DDevice->SetTexture(Stage, pTexture);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD * pValue)
{
	return m_pD3DDevice->GetTextureStageState(Stage, Type, pValue);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
{
	return m_pD3DDevice->SetTextureStageState(Stage, Type, Value);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD * pValue)
{
	return m_pD3DDevice->GetSamplerState(Sampler, Type, pValue);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value)
{
	return m_pD3DDevice->SetSamplerState(Sampler, Type, Value);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::ValidateDevice(DWORD* pNumPasses)
{
	return m_pD3DDevice->ValidateDevice(pNumPasses);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetPaletteEntries(UINT PaletteNumber, const PALETTEENTRY * pEntries)
{
	return m_pD3DDevice->SetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY * pEntries)
{
	return m_pD3DDevice->GetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetCurrentTexturePalette(UINT PaletteNumber)
{
	return m_pD3DDevice->SetCurrentTexturePalette(PaletteNumber);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetCurrentTexturePalette(UINT * PaletteNumber)
{
	return m_pD3DDevice->GetCurrentTexturePalette(PaletteNumber);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetScissorRect(const RECT * pRect)
{
	return m_pD3DDevice->SetScissorRect(pRect);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetScissorRect(RECT * pRect)
{
	return m_pD3DDevice->GetScissorRect(pRect);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetSoftwareVertexProcessing(BOOL bSoftware)
{
	return m_pD3DDevice->SetSoftwareVertexProcessing(bSoftware);
}

BOOL STDMETHODCALLTYPE Direct3DDevice9Proxy::GetSoftwareVertexProcessing()
{
	return m_pD3DDevice->GetSoftwareVertexProcessing();
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetNPatchMode(float nSegments)
{
	return m_pD3DDevice->SetNPatchMode(nSegments);
}

float STDMETHODCALLTYPE Direct3DDevice9Proxy::GetNPatchMode()
{
	return m_pD3DDevice->GetNPatchMode();
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	return m_pD3DDevice->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
	return m_pD3DDevice->DrawIndexedPrimitive(PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, const void * pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return m_pD3DDevice->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, const void * pIndexData, D3DFORMAT IndexDataFormat, const void * pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return m_pD3DDevice->DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat,pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9 * pDestBuffer, IDirect3DVertexDeclaration9 * pVertexDecl, DWORD Flags)
{
	return m_pD3DDevice->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::CreateVertexDeclaration(const D3DVERTEXELEMENT9 * pVertexElements, IDirect3DVertexDeclaration9 ** ppDecl)
{
	return m_pD3DDevice->CreateVertexDeclaration(pVertexElements, ppDecl);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetVertexDeclaration(IDirect3DVertexDeclaration9 * pDecl)
{
	return m_pD3DDevice->SetVertexDeclaration(pDecl);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetVertexDeclaration(IDirect3DVertexDeclaration9 ** ppDecl)
{
	return m_pD3DDevice->GetVertexDeclaration(ppDecl);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetFVF(DWORD FVF)
{
	return m_pD3DDevice->SetFVF(FVF);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetFVF(DWORD * pFVF)
{
	return m_pD3DDevice->GetFVF(pFVF);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::CreateVertexShader(const DWORD * pFunction, IDirect3DVertexShader9 ** ppShader)
{
	return m_pD3DDevice->CreateVertexShader(pFunction, ppShader);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetVertexShader(IDirect3DVertexShader9 * pShader)
{
	return m_pD3DDevice->SetVertexShader(pShader);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetVertexShader(IDirect3DVertexShader9 ** ppShader)
{
	return m_pD3DDevice->GetVertexShader(ppShader);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetVertexShaderConstantF(UINT StartRegister, const float * pConstantData, UINT Vector4fCount)
{
	return m_pD3DDevice->SetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetVertexShaderConstantF(UINT StartRegister, float * pConstantData, UINT Vector4fCount)
{
	return m_pD3DDevice->GetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetVertexShaderConstantI(UINT StartRegister, const int * pConstantData, UINT Vector4iCount)
{
	return m_pD3DDevice->SetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetVertexShaderConstantI(UINT StartRegister, int * pConstantData, UINT Vector4iCount)
{
	return m_pD3DDevice->GetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetVertexShaderConstantB(UINT StartRegister, const BOOL * pConstantData, UINT BoolCount)
{
	return m_pD3DDevice->SetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetVertexShaderConstantB(UINT StartRegister, BOOL * pConstantData, UINT BoolCount)
{
	return m_pD3DDevice->GetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9 * pStreamData, UINT OffsetInBytes, UINT Stride)
{
	return m_pD3DDevice->SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9 ** ppStreamData, UINT * pOffsetInBytes, UINT * pStride)
{
	return m_pD3DDevice->GetStreamSource(StreamNumber, ppStreamData, pOffsetInBytes, pStride);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetStreamSourceFreq(UINT StreamNumber, UINT Setting)
{
	return m_pD3DDevice->SetStreamSourceFreq(StreamNumber, Setting);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetStreamSourceFreq(UINT StreamNumber, UINT * pSetting)
{
	return m_pD3DDevice->GetStreamSourceFreq(StreamNumber, pSetting);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetIndices(IDirect3DIndexBuffer9 * pIndexData)
{
	return m_pD3DDevice->SetIndices(pIndexData);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetIndices(IDirect3DIndexBuffer9 ** ppIndexData)
{
	return m_pD3DDevice->GetIndices(ppIndexData);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::CreatePixelShader(const DWORD * pFunction, IDirect3DPixelShader9 ** ppShader)
{
	return m_pD3DDevice->CreatePixelShader(pFunction, ppShader);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetPixelShader(IDirect3DPixelShader9 * pShader)
{
	return m_pD3DDevice->SetPixelShader(pShader);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetPixelShader(IDirect3DPixelShader9 ** ppShader)
{
	return m_pD3DDevice->GetPixelShader(ppShader);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetPixelShaderConstantF(UINT StartRegister, const float * pConstantData, UINT Vector4fCount)
{
	return m_pD3DDevice->SetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetPixelShaderConstantF(UINT StartRegister, float * pConstantData, UINT Vector4fCount)
{
	return m_pD3DDevice->GetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetPixelShaderConstantI(UINT StartRegister, const int * pConstantData, UINT Vector4iCount)
{
	return m_pD3DDevice->SetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetPixelShaderConstantI(UINT StartRegister, int * pConstantData, UINT Vector4iCount)
{
	return m_pD3DDevice->GetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::SetPixelShaderConstantB(UINT StartRegister, const BOOL * pConstantData, UINT BoolCount)
{
	return m_pD3DDevice->SetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::GetPixelShaderConstantB(UINT StartRegister, BOOL * pConstantData, UINT BoolCount)
{
	return m_pD3DDevice->GetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::DrawRectPatch(UINT Handle, const float * pNumSegs, const D3DRECTPATCH_INFO * pRectPatchInfo)
{
	return m_pD3DDevice->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::DrawTriPatch(UINT Handle, const float * pNumSegs, const D3DTRIPATCH_INFO * pTriPatchInfo)
{
	return m_pD3DDevice->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::DeletePatch(UINT Handle)
{
	return m_pD3DDevice->DeletePatch(Handle);
}

HRESULT STDMETHODCALLTYPE Direct3DDevice9Proxy::CreateQuery(D3DQUERYTYPE Type, IDirect3DQuery9 ** ppQuery)
{
	return m_pD3DDevice->CreateQuery(Type, ppQuery);
}
