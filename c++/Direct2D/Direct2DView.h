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
		MSG_WM_PAINT(OnPaint)
		MSG_WM_DISPLAYCHANGE(OnDisplayChange)
		MSG_WM_DESTROY(OnDestroy)
		MSG_WM_CREATE(OnCreate)
		MSG_WM_SIZE(OnSize)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnCreate(LPCREATESTRUCT cs)
	{
		HRESULT hr = D2D1CreateFactory(
			D2D1_FACTORY_TYPE_SINGLE_THREADED,
			&m_factory
		);
		
		if (FAILED(hr))
			return -1;
		
		return 0;
	}

	void OnDestroy()
	{
		DiscardDevResources();
		m_factory.Release();
	}

	void OnDisplayChange(UINT /*bpp*/, CSize /*resolution*/)
	{
		CClientDC dc(*this);
		Render(dc);
	}

	void OnPaint(CDCHandle /*hDC*/)
	{
		CPaintDC dc(*this);
		Render(dc);
	}
	
	void OnSize(UINT /*type*/, CSize size) 
	{
		if (m_target != NULL) {
			if (FAILED(m_target->Resize(D2D1::SizeU(size.cx, size.cy)))) {
				DiscardDevResources();
				Invalidate(FALSE);
			}
		}
	}

private:
	void Render(CDC &dc) {
		HRESULT hr;

		CRect rc;
		dc.GetClipBox(rc);

		if (m_target == NULL) {
			hr = CreateDevResources(rc);			
			if (FAILED(hr))
				return;	
		}	

		m_target->BeginDraw();
		m_target->SetTransform(D2D1::Matrix3x2F::Identity());
		m_target->Clear(D2D1::ColorF(D2D1::ColorF::Olive));
        
		m_target->DrawLine(D2D1::Point2(10.0f, 10.0f), // start
                   D2D1::Point2(200.0f, 200.0f), // end
                   m_brush,
                   10.0f); // stroke width

		const D2D1_POINT_2F center = D2D1::Point2(105.0f, 105.0f);
		const D2D1_ELLIPSE ellipse = D2D1::Ellipse(center,
                                           95.0f, // radius X
                                           95.0f); // radius Y
		m_target->DrawEllipse(&ellipse,
                      m_brush,
                      5.0f); // stroke width

		if (D2DERR_RECREATE_TARGET == m_target->EndDraw()) {
			DiscardDevResources();
		}
	}

	HRESULT CreateDevResources(CRect &rc) {

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

		if (FAILED(hr))
			return hr;

		hr = m_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_brush);

		return hr;
	}

	void DiscardDevResources()
	{
		m_brush.Release();
		m_target.Release();		
	}

	CComPtr<ID2D1HwndRenderTarget> m_target;	
	CComPtr<ID2D1SolidColorBrush> m_brush;
	CComPtr<ID2D1Factory> m_factory;
};
