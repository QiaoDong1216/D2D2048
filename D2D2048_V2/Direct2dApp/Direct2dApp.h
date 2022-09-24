#pragma once

#include <wrl/client.h>
#include <dwrite.h>
#include <dxgi1_2.h>
#include <d2d1.h>
#include <d2d1_1.h>
#include <d3d11.h>
#include <dxgi1_2.h>
#include <d2d1_1helper.h>
#include <shobjidl_core.h>
#include <wchar.h>
#include <iostream>
#include <string>
#include <wincodec.h>
#include "../LogSys.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "D3D11.lib")
#pragma comment(lib, "Dwrite.lib")
#pragma comment(lib, "Winmm.lib")

#define RELEASE(ptr) if(ptr != NULL) ptr->Release();

using namespace Microsoft::WRL;

namespace app {
	class Direct2dApp
	{
	public:
		Direct2dApp(HWND hwnd);
		Direct2dApp();
		~Direct2dApp();

		bool initD2d(HWND hwnd);
		void setFullScreen(bool flag);
		void setVerticalSync(bool flag);

		void BeginDraw();
		void Clear(const D2D1_COLOR_F& color);
		void drawLine(const D2D1_POINT_2F& point1, const D2D1_POINT_2F& point2, const D2D1_COLOR_F& color, const float width);
		void drawBitmap(ID2D1Bitmap1* bitmap, D2D1_POINT_2F pos, D2D1_SIZE_F size);
		void drawCenterText(const LPCWSTR text, const D2D1_POINT_2F& pos, float width, float height, const D2D1_COLOR_F& color, const float Textsize);
		void drawText(const LPCWSTR text, const D2D1_POINT_2F& pos, const D2D1_COLOR_F& color, const float Textsize);
		void drawRect(float x, float y, float width, float height, D2D1_COLOR_F color, float strokeWidth);
		void fillRect(float x, float y, float width, float height, D2D1_COLOR_F color);
		void drawRoundedRect(float x, float y, float width, float height, float radiusX, float radiusY, D2D1_COLOR_F color, float strokeWidth);
		void fillRoundedRect(float x, float y, float width, float height, float radiusX, float radiusY, D2D1_COLOR_F color);
		void EndDraw();

		// ������ WM_SIZE ��Ϣʱ���ô˺���
		void ChangeSize(WORD width, WORD height);

		// ���ļ����� ID2D1Bitmap
		bool LoadBitmapFromFile(LPCWSTR file, ID2D1Bitmap1** Bitmap);

		// ���ļ����� IWICBitmap
		bool LoadWicBitmapFromFile(LPCWSTR file, IWICBitmap** Bitmap);

		// �� IWICBitmap תΪ ID2D1Bitmap
		bool WicBitmapToD2dBitmap(IWICBitmap* wicBitmap, ID2D1Bitmap1** d2dBitmap);

		// ��ȡ��ǰ������Ⱦ������
		bool getTarget(ID2D1Bitmap1** Bitmap);

		// ���� Bitmap ���ļ�
		bool saveBitmapToFile(ID2D1Bitmap1* Bitmap, const WCHAR* file);

		// ��ȡ��ǰ�ͻ�����С
		RECT getSize();

		void saveTo();

		ID2D1DeviceContext* getDC();
		ID2D1Factory1* getFactory();

		// ���Ժ���
		void test();

	private:

		RECT rc;	//���ڿͻ�����С
		HWND m_hwnd;

		ComPtr<ID2D1SolidColorBrush> m_Brush;

		ComPtr<ID2D1Factory1> m_d2dFactory;
		ComPtr<ID2D1Device> m_d2dDevice;
		ComPtr<ID2D1DeviceContext> m_d2dDeviceContext;
		ComPtr<ID2D1Bitmap1> m_d2dTarget;

		ComPtr<ID3D11Device> m_d3dDevice;
		ComPtr<ID3D11DeviceContext> m_d3dDeviceContext;
		ComPtr<ID3D11RenderTargetView> m_d3dRenderTar;

		ComPtr<IDXGIFactory2> m_dxgiFactory;
		ComPtr<IDXGIDevice1> m_dxgiDevice;
		ComPtr<IDXGISwapChain1> m_dxgiSwapChain;
		ComPtr<IDXGISurface1> m_dxgiSurface;

		ComPtr<IDWriteFactory> m_pDWriteFactory;
		ComPtr<IDWriteTextFormat> m_pTextFormat;
		ComPtr<IDWriteTextLayout> m_pTextLayout;

		ComPtr<IWICImagingFactory> m_wicImgFactory;

		bool FullScreen = false;
		bool Vertical_sync = false;
		void Release();
		bool createDwrite();
		bool createRT();
		bool initIWIC();

	};
}