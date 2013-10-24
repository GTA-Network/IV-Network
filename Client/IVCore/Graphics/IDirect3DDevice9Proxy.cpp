//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: IDirect3DDevice9Proxy.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "IDirect3DDevice9Proxy.h"
#include <CCore.h>
extern CCore * g_pCore;

IDirect3DDevice9Proxy::IDirect3DDevice9Proxy(IDirect3DDevice9 *pDevice) :
	m_pDevice(pDevice)
{

}

HRESULT __stdcall IDirect3DDevice9Proxy::Present ( CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
	return m_pDevice->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

HRESULT __stdcall IDirect3DDevice9Proxy::QueryInterface(REFIID riid, void** ppvObj)
{
	return m_pDevice->QueryInterface(riid, ppvObj);
}

ULONG __stdcall IDirect3DDevice9Proxy::AddRef()
{
	return m_pDevice->AddRef();
}

ULONG __stdcall IDirect3DDevice9Proxy::Release()
{
	ULONG uRet = m_pDevice->Release();

	if(uRet == 0)
	{
		delete this;
	}
	return uRet;
}

HRESULT __stdcall IDirect3DDevice9Proxy::TestCooperativeLevel()
{
	return m_pDevice->TestCooperativeLevel();
}

UINT __stdcall IDirect3DDevice9Proxy::GetAvailableTextureMem()
{
	return m_pDevice->GetAvailableTextureMem();
}

HRESULT __stdcall IDirect3DDevice9Proxy::EvictManagedResources()
{
	return m_pDevice->EvictManagedResources();
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetDirect3D(IDirect3D9** ppD3D9)
{
	return m_pDevice->GetDirect3D(ppD3D9);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetDeviceCaps(D3DCAPS9* pCaps)
{
	return m_pDevice->GetDeviceCaps(pCaps);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetDisplayMode(UINT iSwapChain, D3DDISPLAYMODE* pMode)
{
	return m_pDevice->GetDisplayMode(iSwapChain, pMode);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS *pParameters)
{
	return m_pDevice->GetCreationParameters(pParameters);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9* pCursorBitmap)
{
	return m_pDevice->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);
}

void __stdcall IDirect3DDevice9Proxy::SetCursorPosition(int X, int Y, DWORD Flags)
{
	m_pDevice->SetCursorPosition(X, Y, Flags);
}

BOOL __stdcall IDirect3DDevice9Proxy::ShowCursor(BOOL bShow)
{
	return m_pDevice->ShowCursor(bShow);
}

HRESULT __stdcall IDirect3DDevice9Proxy::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain9** pSwapChain)
{
	return m_pDevice->CreateAdditionalSwapChain(pPresentationParameters, pSwapChain);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetSwapChain(UINT iSwapChain, IDirect3DSwapChain9** pSwapChain)
{
	return m_pDevice->GetSwapChain(iSwapChain, pSwapChain);
}

UINT __stdcall IDirect3DDevice9Proxy::GetNumberOfSwapChains()
{
	return m_pDevice->GetNumberOfSwapChains();
}

HRESULT __stdcall IDirect3DDevice9Proxy::Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	if (g_pCore)
	{
		g_pCore->GetGraphics()->OnLostDevice(m_pDevice);
		g_pCore->GetGUI()->OnLostDevice();
	}
#ifdef _DEBUG
	// Windowed mode
	pPresentationParameters->Windowed = 1;
	pPresentationParameters->Flags = 0;
	pPresentationParameters->FullScreen_RefreshRateInHz = 0;
	pPresentationParameters->PresentationInterval = 0;
	LONG_PTR style = GetWindowLongPtr(pPresentationParameters->hDeviceWindow, GWL_STYLE);
	SetWindowLongPtr(pPresentationParameters->hDeviceWindow, GWL_STYLE, style | WS_POPUPWINDOW | WS_CAPTION | WS_THICKFRAME);
	SetWindowPos(pPresentationParameters->hDeviceWindow, HWND_NOTOPMOST, 0, 0, pPresentationParameters->BackBufferWidth, pPresentationParameters->BackBufferHeight, SWP_SHOWWINDOW);
#endif

	HRESULT hr = m_pDevice->Reset(pPresentationParameters);

	if (SUCCEEDED(hr))
	{
		if (g_pCore)
		{
			g_pCore->GetGraphics()->OnRestoreDevice(m_pDevice);
			g_pCore->GetGUI()->OnResetDevice();
		}
	}
	return hr;
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetBackBuffer(UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9** ppBackBuffer)
{
	return m_pDevice->GetBackBuffer(iSwapChain, iBackBuffer, Type, ppBackBuffer);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetRasterStatus(UINT iSwapChain, D3DRASTER_STATUS* pRasterStatus)
{
	return m_pDevice->GetRasterStatus(iSwapChain, pRasterStatus);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetDialogBoxMode(BOOL bEnableDialogs)
{
	return m_pDevice->SetDialogBoxMode(bEnableDialogs);
}

void __stdcall IDirect3DDevice9Proxy::SetGammaRamp(UINT iSwapChain, DWORD Flags, CONST D3DGAMMARAMP* pRamp)
{
	m_pDevice->SetGammaRamp(iSwapChain, Flags, pRamp);
}

void __stdcall IDirect3DDevice9Proxy::GetGammaRamp(UINT iSwapChain, D3DGAMMARAMP* pRamp)
{
	m_pDevice->GetGammaRamp(iSwapChain, pRamp);
}

HRESULT __stdcall IDirect3DDevice9Proxy::CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle)
{
	return m_pDevice->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);
}

HRESULT __stdcall IDirect3DDevice9Proxy::CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture, HANDLE* pSharedHandle)
{
	return m_pDevice->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);
}

HRESULT __stdcall IDirect3DDevice9Proxy::CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture, HANDLE* pSharedHandle)
{
	return m_pDevice->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);
}

HRESULT __stdcall IDirect3DDevice9Proxy::CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle)
{
	return m_pDevice->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);
}

HRESULT __stdcall IDirect3DDevice9Proxy::CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle)
{
	return m_pDevice->CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);
}

HRESULT __stdcall IDirect3DDevice9Proxy::CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	return m_pDevice->CreateRenderTarget(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle);
}

HRESULT __stdcall IDirect3DDevice9Proxy::CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	return m_pDevice->CreateDepthStencilSurface(Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle);
}

HRESULT __stdcall IDirect3DDevice9Proxy::UpdateSurface(IDirect3DSurface9* pSourceSurface, CONST RECT* pSourceRect, IDirect3DSurface9* pDestinationSurface, CONST POINT* pDestPoint)
{
	return m_pDevice->UpdateSurface(pSourceSurface, pSourceRect, pDestinationSurface, pDestPoint);
}

HRESULT __stdcall IDirect3DDevice9Proxy::UpdateTexture(IDirect3DBaseTexture9* pSourceTexture, IDirect3DBaseTexture9* pDestinationTexture)
{
	return m_pDevice->UpdateTexture(pSourceTexture, pDestinationTexture);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetRenderTargetData(IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface)
{
	return m_pDevice->GetRenderTargetData(pRenderTarget, pDestSurface);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetFrontBufferData(UINT iSwapChain, IDirect3DSurface9* pDestSurface)
{
	return m_pDevice->GetFrontBufferData(iSwapChain, pDestSurface);
}

HRESULT __stdcall IDirect3DDevice9Proxy::StretchRect(IDirect3DSurface9* pSourceSurface, CONST RECT* pSourceRect, IDirect3DSurface9* pDestSurface, CONST RECT* pDestRect, D3DTEXTUREFILTERTYPE Filter)
{
	return m_pDevice->StretchRect(pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter);
}

HRESULT __stdcall IDirect3DDevice9Proxy::ColorFill(IDirect3DSurface9* pSurface, CONST RECT* pRect, D3DCOLOR color)
{
	return m_pDevice->ColorFill(pSurface, pRect, color);
}

HRESULT __stdcall IDirect3DDevice9Proxy::CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	return m_pDevice->CreateOffscreenPlainSurface(Width, Height, Format, Pool, ppSurface, pSharedHandle);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9* pRenderTarget)
{
	return m_pDevice->SetRenderTarget(RenderTargetIndex, pRenderTarget);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9** ppRenderTarget)
{
	return m_pDevice->GetRenderTarget(RenderTargetIndex, ppRenderTarget);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil)
{
	return m_pDevice->SetDepthStencilSurface(pNewZStencil);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface)
{
	return m_pDevice->GetDepthStencilSurface(ppZStencilSurface);
}

HRESULT __stdcall IDirect3DDevice9Proxy::BeginScene()
{
	return m_pDevice->BeginScene();
}

HRESULT __stdcall IDirect3DDevice9Proxy::EndScene()
{
	// Call the client render function
	g_pCore->OnDeviceRender( m_pDevice );

	return m_pDevice->EndScene();
}

HRESULT __stdcall IDirect3DDevice9Proxy::Clear(DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
{
	return m_pDevice->Clear(Count, pRects, Flags, Color, Z, Stencil);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* mat)
{
	return m_pDevice->SetTransform(State, mat);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX* mat)
{
	return m_pDevice->GetTransform(State, mat);
}

HRESULT __stdcall IDirect3DDevice9Proxy::MultiplyTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* mat)
{
	return m_pDevice->MultiplyTransform(State, mat);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetViewport(CONST D3DVIEWPORT9* pViewport)
{
	return m_pDevice->SetViewport(pViewport);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetViewport(D3DVIEWPORT9* pViewport)
{
	return m_pDevice->GetViewport(pViewport);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetMaterial(CONST D3DMATERIAL9* pMaterial)
{
	return m_pDevice->SetMaterial(pMaterial);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetMaterial(D3DMATERIAL9* pMaterial)
{
	return m_pDevice->GetMaterial(pMaterial);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetLight(DWORD Index, CONST D3DLIGHT9* pLight)
{
	return m_pDevice->SetLight(Index, pLight);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetLight(DWORD Index, D3DLIGHT9* pLight)
{
	return m_pDevice->GetLight(Index, pLight);
}

HRESULT __stdcall IDirect3DDevice9Proxy::LightEnable(DWORD Index, BOOL Enable)
{
	return m_pDevice->LightEnable(Index, Enable);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetLightEnable(DWORD Index, BOOL* pEnable)
{
	return m_pDevice->GetLightEnable(Index, pEnable);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetClipPlane(DWORD Index, CONST float* pPlane)
{
	return m_pDevice->SetClipPlane(Index, pPlane);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetClipPlane(DWORD Index, float* pPlane)
{
	return m_pDevice->GetClipPlane(Index, pPlane);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
	return m_pDevice->SetRenderState(State, Value);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetRenderState(D3DRENDERSTATETYPE State, DWORD* pValue)
{
	return m_pDevice->GetRenderState(State, pValue);
}

HRESULT __stdcall IDirect3DDevice9Proxy::CreateStateBlock(D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9** ppSB)
{
	return m_pDevice->CreateStateBlock(Type, ppSB);
}

HRESULT __stdcall IDirect3DDevice9Proxy::BeginStateBlock()
{
	return m_pDevice->BeginStateBlock();
}

HRESULT __stdcall IDirect3DDevice9Proxy::EndStateBlock(IDirect3DStateBlock9** ppSB)
{
	return m_pDevice->EndStateBlock(ppSB);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetClipStatus(CONST D3DCLIPSTATUS9* pClipStatus)
{
	return m_pDevice->SetClipStatus(pClipStatus);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetClipStatus(D3DCLIPSTATUS9* pClipStatus)
{
	return m_pDevice->GetClipStatus(pClipStatus);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetTexture(DWORD Stage, IDirect3DBaseTexture9** ppTexture)
{
	return m_pDevice->GetTexture(Stage, ppTexture);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetTexture(DWORD Stage, IDirect3DBaseTexture9* pTexture)
{
	return m_pDevice->SetTexture(Stage, pTexture);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue)
{
	return m_pDevice->GetTextureStageState(Stage, Type, pValue);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
{
	return m_pDevice->SetTextureStageState(Stage, Type, Value);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD* pValue)
{
	return m_pDevice->GetSamplerState(Sampler, Type, pValue);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value)
{
	return m_pDevice->SetSamplerState(Sampler, Type, Value);
}

HRESULT __stdcall IDirect3DDevice9Proxy::ValidateDevice(DWORD* pNumPasses)
{
	return m_pDevice->ValidateDevice(pNumPasses);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetPaletteEntries(UINT PaletteNumber, CONST PALETTEENTRY* pEntries)
{
	return m_pDevice->SetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY* pEntries)
{
	return m_pDevice->GetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetCurrentTexturePalette(UINT PaletteNumber)
{
	return m_pDevice->SetCurrentTexturePalette(PaletteNumber);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetCurrentTexturePalette(UINT *PaletteNumber)
{
	return m_pDevice->GetCurrentTexturePalette(PaletteNumber);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetScissorRect(CONST RECT* pRect)
{
	return m_pDevice->SetScissorRect(pRect);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetScissorRect(RECT* pRect)
{
	return m_pDevice->GetScissorRect(pRect);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetSoftwareVertexProcessing(BOOL bSoftware)
{
	return m_pDevice->SetSoftwareVertexProcessing(bSoftware);
}

BOOL __stdcall IDirect3DDevice9Proxy::GetSoftwareVertexProcessing()
{
	return m_pDevice->GetSoftwareVertexProcessing();
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetNPatchMode(float nSegments)
{
	return m_pDevice->SetNPatchMode(nSegments);
}

float __stdcall IDirect3DDevice9Proxy::GetNPatchMode()
{
	return m_pDevice->GetNPatchMode();
}

HRESULT __stdcall IDirect3DDevice9Proxy::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	return m_pDevice->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

HRESULT __stdcall IDirect3DDevice9Proxy::DrawIndexedPrimitive(D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
	return m_pDevice->DrawIndexedPrimitive(Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

HRESULT __stdcall IDirect3DDevice9Proxy::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return m_pDevice->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT __stdcall IDirect3DDevice9Proxy::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, CONST void* pIndexData, D3DFORMAT IndexDataFormat, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return m_pDevice->DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT __stdcall IDirect3DDevice9Proxy::ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9* pDestBuffer, IDirect3DVertexDeclaration9* pVertexDecl, DWORD Flags)
{
	return m_pDevice->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags);
}

HRESULT __stdcall IDirect3DDevice9Proxy::CreateVertexDeclaration(CONST D3DVERTEXELEMENT9* pVertexElements, IDirect3DVertexDeclaration9** ppDecl)
{
	return m_pDevice->CreateVertexDeclaration(pVertexElements, ppDecl);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl)
{
	return m_pDevice->SetVertexDeclaration(pDecl);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl)
{
	return m_pDevice->GetVertexDeclaration(ppDecl);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetFVF(DWORD FVF)
{
	return m_pDevice->SetFVF(FVF);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetFVF(DWORD* pFVF)
{
	return m_pDevice->GetFVF(pFVF);
}

HRESULT __stdcall IDirect3DDevice9Proxy::CreateVertexShader(CONST DWORD* pFunction, IDirect3DVertexShader9** ppShader)
{
	return m_pDevice->CreateVertexShader(pFunction, ppShader);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetVertexShader(IDirect3DVertexShader9* pShader)
{
	return m_pDevice->SetVertexShader(pShader);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetVertexShader(IDirect3DVertexShader9** ppShader)
{
	return m_pDevice->GetVertexShader(ppShader);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetVertexShaderConstantF(UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount)
{
	return m_pDevice->SetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetVertexShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount)
{
	return m_pDevice->GetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetVertexShaderConstantI(UINT StartRegister, CONST int* pConstantData, UINT Vector4iCount)
{
	return m_pDevice->SetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetVertexShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount)
{
	return m_pDevice->GetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetVertexShaderConstantB(UINT StartRegister, CONST BOOL* pConstantData, UINT BoolCount)
{
	return m_pDevice->SetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetVertexShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount)
{
	return m_pDevice->GetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride)
{
	return m_pDevice->SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9** ppStreamData, UINT* OffsetInBytes, UINT* pStride)
{
	return m_pDevice->GetStreamSource(StreamNumber, ppStreamData, OffsetInBytes, pStride);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetStreamSourceFreq(UINT StreamNumber, UINT Divider)
{
	return m_pDevice->SetStreamSourceFreq(StreamNumber, Divider);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetStreamSourceFreq(UINT StreamNumber, UINT* Divider)
{
	return m_pDevice->GetStreamSourceFreq(StreamNumber, Divider);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetIndices(IDirect3DIndexBuffer9* pIndexData)
{
	return m_pDevice->SetIndices(pIndexData);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetIndices(IDirect3DIndexBuffer9** ppIndexData)
{
	return m_pDevice->GetIndices(ppIndexData);
}

HRESULT __stdcall IDirect3DDevice9Proxy::CreatePixelShader(CONST DWORD* pFunction, IDirect3DPixelShader9** ppShader)
{
	return m_pDevice->CreatePixelShader(pFunction, ppShader);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetPixelShader(IDirect3DPixelShader9* pShader)
{
	return m_pDevice->SetPixelShader(pShader);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetPixelShader(IDirect3DPixelShader9** ppShader)
{
	return m_pDevice->GetPixelShader(ppShader);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetPixelShaderConstantF(UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount)
{
	return m_pDevice->SetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetPixelShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount)
{
	return m_pDevice->GetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetPixelShaderConstantI(UINT StartRegister, CONST int* pConstantData, UINT Vector4iCount)
{
	return m_pDevice->SetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetPixelShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount)
{
	return m_pDevice->GetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT __stdcall IDirect3DDevice9Proxy::SetPixelShaderConstantB(UINT StartRegister, CONST BOOL* pConstantData, UINT BoolCount)
{
	return m_pDevice->SetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT __stdcall IDirect3DDevice9Proxy::GetPixelShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount)
{
	return m_pDevice->GetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT __stdcall IDirect3DDevice9Proxy::DrawRectPatch(UINT Handle, CONST float* pNumSegs, CONST D3DRECTPATCH_INFO* pRectPatchInfo)
{
	return m_pDevice->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
}

HRESULT __stdcall IDirect3DDevice9Proxy::DrawTriPatch(UINT Handle, CONST float* pNumSegs, CONST D3DTRIPATCH_INFO* pTriPatchInfo)
{
	return m_pDevice->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}

HRESULT __stdcall IDirect3DDevice9Proxy::DeletePatch(UINT Handle)
{
	return m_pDevice->DeletePatch(Handle);
}

HRESULT __stdcall IDirect3DDevice9Proxy::CreateQuery(D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery)
{
	return m_pDevice->CreateQuery(Type, ppQuery);
}