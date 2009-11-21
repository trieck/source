///////////////////////////////////////////////////////////////////////////////// INETUTIL.CPP : Win32 internet utility classes//#include "common.h"#include "inetutil.h"// initialize the socket librarystatic struct _sockinit {	_sockinit::_sockinit() {		WSADATA data;		WSAStartup(MAKEWORD(2, 2), &data);	}	_sockinit::~_sockinit() {		WSACleanup();	}} sockinit;static LPCTSTR httpVersion = _T("HTTP/1.0");/////////////////////////////////////////////////////////////////////////////Socket::Socket()		: _socket(INVALID_SOCKET){	create();}/////////////////////////////////////////////////////////////////////////////Socket::~Socket(){	close();}/////////////////////////////////////////////////////////////////////////////bool Socket::create(){	close();	_socket = socket(AF_INET, SOCK_STREAM, 0);	return _socket != INVALID_SOCKET;}/////////////////////////////////////////////////////////////////////////////void Socket::close(){	if (_socket != INVALID_SOCKET) {		closesocket(_socket);		_socket = INVALID_SOCKET;	}}bool Socket::bind(LPCTSTR host, int port){	SOCKADDR_IN addr;	memset(&addr, 0, sizeof(SOCKADDR_IN));	addr.sin_family = AF_INET;	if (host == NULL)		addr.sin_addr.s_addr = htonl(INADDR_ANY);	else addr.sin_addr.s_addr = inet_addr(host);	addr.sin_port = htons(port);	int N = ::bind(_socket, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN));	return  N != SOCKET_ERROR;}/////////////////////////////////////////////////////////////////////////////bool Socket::connect(LPCTSTR host, int port){	if (!bind(NULL, 0))		return false;	SOCKADDR_IN addr;	memset(&addr, 0, sizeof(addr));	addr.sin_family = AF_INET;	addr.sin_addr.s_addr = inet_addr(host);	if (addr.sin_addr.s_addr == INADDR_NONE) {		LPHOSTENT phost = gethostbyname(host);		if (phost == NULL)			return false;		addr.sin_addr.s_addr = ((LPIN_ADDR)phost->h_addr)->s_addr;	}	addr.sin_port = htons((u_short)port);	int N = ::connect(_socket, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN));	return N != SOCKET_ERROR;}/////////////////////////////////////////////////////////////////////////////size_t Socket::read(LPVOID pbuff, unsigned int size){	int N = ::recv(_socket, (char *)pbuff, size, 0);	if (N == SOCKET_ERROR)		return 0;	((char *)pbuff)[N] = _T('\0');	return N;}/////////////////////////////////////////////////////////////////////////////bool Socket::write(LPCTSTR pbuff){	int N = ::send(_socket,	               pbuff,	               _tcslen(pbuff) * sizeof(TCHAR),	               0);	return N != SOCKET_ERROR;}const int WebConnect::blocksize = 256;/////////////////////////////////////////////////////////////////////////////WebConnect::WebConnect(){}/////////////////////////////////////////////////////////////////////////////WebConnect::~WebConnect(){}/////////////////////////////////////////////////////////////////////////////bool WebConnect::open(LPCTSTR host, int port){	if (_tcsnicmp(host, _T("http://"), 7) == 0)		host += 7;	// skip it	if (!_socket.connect(host, port))		return false;	return true;}/////////////////////////////////////////////////////////////////////////////bool WebConnect::request(WebConnect::method M, LPCTSTR URI){	TCHAR req[1024];	switch (M) {	case get:		_tcscpy(req, _T("GET"));		break;	case post:		_tcscpy(req, _T("POST"));		break;	case head:		_tcscpy(req, _T("HEAD"));		break;	default:		return false;	// unknown method	}	_tcscat(req, _T(" "));	_tcscat(req, URI);	_tcscat(req, _T(" "));	_tcscat(req, httpVersion);	_tcscat(req, _T("\n\n"));	return _socket.write(req);}/////////////////////////////////////////////////////////////////////////////size_t WebConnect::read(LPVOID pbuff, unsigned int size){	return _socket.read(pbuff, size);}/////////////////////////////////////////////////////////////////////////////tstring WebConnect::readPage(){	tstring page;	char header[4096];	// read the response header	size_t N = read(header, sizeof(header));	if (N == 0)		return _T("");	LPCTSTR endheader = _tcsstr(header, _T("\r\n\r\n"));	if (endheader == NULL)		return _T("");	// not found	endheader += 4;	int headersize = endheader - header;	responseHeader = tstring(header, endheader - header);	tstring contentLength = getHeader(_T("Content-Length"));	int len = _ttoi(contentLength.c_str());	// difference of content length and what has	// already been read minus header	int spill = ( N - headersize );	if (spill) {		len = max(0, len - spill);		page = endheader;	}	if (len) {		TCHAR *pbuff = new char[len + 1];		int j = 0;		for (;;) {			N = read(pbuff + j, min(blocksize, len));			if (N == 0) {				pbuff[j + N] = '\0';				break;			}			j += N;		}		page += pbuff;		delete [] pbuff;	} else {		TCHAR buff[blocksize];		while ((N = read(buff, sizeof(buff)))) {			buff[N] = '\0';			page += buff;		}	}	return page;}/////////////////////////////////////////////////////////////////////////////tstring WebConnect::getHeader(LPCTSTR name) const{	tstring value;	TCHAR *pheader = _tcsdup(responseHeader.c_str());	LPCTSTR ptok = _tcstok(pheader, _T("\r\n"));	while (ptok) {		if (_tcsnicmp(name, ptok, _tcslen(name)) == 0) {			value = ptok + _tcslen(name) + 2; // provisions for ': '			break;		}		ptok = _tcstok(NULL, _T("\r\n"));	}	free(pheader);	return value;}