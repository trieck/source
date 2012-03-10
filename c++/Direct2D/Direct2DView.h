// wtlappView.h : interface of the CWtlappView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CWtlappView : public CWindowImpl<CWtlappView>
{
public:
	DECLARE_WND_CLASS(NULL)

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		pMsg;
		return FALSE;
	}

	BEGIN_MSG_MAP(CWtlappView)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		HRESULT hr = D2D1CreateFactory(
			D2D1_FACTORY_TYPE_SINGLE_THREADED,
			&m_factory
		);
		
		if (FAILED(hr))
			return -1;
		
		return 0;
	}

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		bHandled = FALSE;

		m_target.Release();
		m_factory.Release();
	
		return 1;
	}


	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CPaintDC dc(m_hWnd);
		Render(dc);

		return 0;
	}

	LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
	{
		CDC dc;
		dc.Attach((HDC)wParam);

		RECT rc;
		dc.GetClipBox(&rc);

		HRESULT hr;
		if (m_target == NULL) {
			hr = CreateRenderTarget(rc);			
			if (FAILED(hr))
				return 0;
		}

		if ((m_target->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED) == 0) {
			m_target->BeginDraw();
            m_target->SetTransform(D2D1::Matrix3x2F::Identity());
            m_target->Clear(D2D1::ColorF(D2D1::ColorF::SeaGreen));

            if (D2DERR_RECREATE_TARGET == m_target->EndDraw()) {
				m_target.Release();
            }
		}

		bHandled = TRUE;

		return 1;
	}

private:
	void Render(CPaintDC &dc) {
		
		HRESULT hr;

		if (m_target == NULL) {
			hr = CreateRenderTarget(dc.m_ps.rcPaint);			
			if (FAILED(hr))
				return;	
		}

		
	}

	HRESULT CreateRenderTarget(const RECT &rc) {

		m_target.Release();
		
		HRESULT hr = m_factory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(
				m_hWnd,
				D2D1::SizeU(rc.right - rc.left,
					rc.bottom - rc.top)
			),
			&m_target
		);

		return hr;
	}

	CComPtr<ID2D1HwndRenderTarget> m_target;	
	CComPtr<ID2D1Factory> m_factory;
};
