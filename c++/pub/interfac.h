#ifndef _INTERFAC_C_
#define _INTERFAC_H_

// {F206AC00-005C-11d1-B1C9-000000000000}
DEFINE_GUID(IID_IDrawObject,
            0xf206ac00, 0x5c, 0x11d1, 0xb1, 0xc9, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0);

// {60F75E71-0039-11d1-B1C9-000000000000}
DEFINE_GUID(CLSID_DrawObject,
            0x60f75e71, 0x39, 0x11d1, 0xb1, 0xc9, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0);

typedef void ** PPVOID;

DECLARE_INTERFACE_(IDrawObject, IUnknown)
{
	// IUnknown members
	STDMETHOD(QueryInterface) (THIS_ REFIID, PPVOID) PURE;
	STDMETHOD_(ULONG,AddRef)  (THIS) PURE;
	STDMETHOD_(ULONG,Release) (THIS) PURE;

	// IDrawObject members
	STDMETHOD(Randomize)(THIS) PURE;
	STDMETHOD(SetBounds)(THIS_ LPRECT) PURE;
	STDMETHOD(SetColor)(THIS_ COLORREF) PURE;
	STDMETHOD(GetColor)(THIS_ LPCOLORREF) PURE;
};

typedef IDrawObject *PDRAWOBJECT;

#endif // _INTERFAC_H_