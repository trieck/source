/////////////////////////////////////////////////////////////////////////////
//
// HANDLER.CPP : Service handler
//
// Copyright(c) 2006 Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include "Conn.h"
#include "BEObject.h"
#include "Dictionary.h"
#include "Integer.h"
#include "List.h"
#include "decode.h"
#include "encode.h"
#include "Handler.h"
#include "MakePoolHandler.h"
#include "CreateHandler.h"
#include "GetHandler.h"
#include "SetHandler.h"
#include "DestroyHandler.h"
#include "Elog.h"
#include "Proto.h"
#include "SockStream.h"

/////////////////////////////////////////////////////////////////////////////
Handler::Handler()
{
	handler_map[FNC_MKPOOL] = new MakePoolHandler();
	handler_map[FNC_CREATE] = new CreateHandler();	
	handler_map[FNC_GET] = new GetHandler();
	handler_map[FNC_SET] = new SetHandler();
	handler_map[FNC_DESTROY] = new DestroyHandler();	
}

/////////////////////////////////////////////////////////////////////////////
Handler::~Handler()
{
	HandlerMap::const_iterator it = handler_map.begin();
	for ( ; it != handler_map.end(); it++) {
		delete (*it).second;
	}
}

/////////////////////////////////////////////////////////////////////////////
BOOL Handler::Initialize(void* pv)
{
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
void Handler::Execute(RequestType pconn, void* pv, OVERLAPPED* pOverlapped)
{
	Connection conn = pconn->release(); // take ownership of the socket
	
	// Receive the request
	BEObjectPtr request(Receive(conn));
	if (request.get() == NULL) {
		EventLog::logerr(
			"Handler::Execute() unable to receive request : %s",
				lasterror().c_str());
		return;
	}

	// Dispatch the request
	BEObjectPtr response(Dispatch(request.get()));

	// Send the response
	if (!Send(conn, response.get())) {
		EventLog::logerr(
			"Handler::Execute() unable to send response : %s",
				lasterror().c_str());
	}
}

/////////////////////////////////////////////////////////////////////////////
void Handler::Terminate(void* pv)
{
}

/////////////////////////////////////////////////////////////////////////////
LPBEOBJECT Handler::Receive(Connection & conn)
{
	IPeekableStreamPtr stream;
	stream.Attach(SockStream::Create(conn.getSock()));
	return BEDecoder::decode(stream);
}

/////////////////////////////////////////////////////////////////////////////
LPBEOBJECT Handler::Dispatch(LPBEOBJECT request)
{
	LPDICTIONARY response = MakeDictionary();

	// request must be a dictionary
	if (request->GetType() != BEObject::BET_DICT) {
		response->Set(KEY_RESPONSE_CD, E_BAD_REQUEST);
		response->Set(KEY_RESPONSE_MSG, RESP_OBJ_FMT);
		return response;
	}

	LPDICTIONARY dreq = static_cast<LPDICTIONARY>(request);

	LPBEOBJECT func = dreq->Get(KEY_REQUEST_FNC);
	if (func == NULL) {	// no function supplied
		response->Set(KEY_RESPONSE_CD, E_INC_REQUEST);
		response->Set(KEY_RESPONSE_MSG, RESP_NO_FNC);
		return response;
	}

	// request function must be an integer
	if (func->GetType() != BEObject::BET_INTEGER) {
		response->Set(KEY_RESPONSE_CD, E_BAD_REQUEST);
		response->Set(KEY_RESPONSE_MSG, RESP_OBJ_FMT);
		return response;
	}

	// call the handler function
	CallHandler(static_cast<LPINTEGER>(func), dreq, response);

	return response;
}

/////////////////////////////////////////////////////////////////////////////
void Handler::CallHandler(LPINTEGER fnc, LPDICTIONARY req, LPDICTIONARY res)
{
	HandlerMap::const_iterator it = handler_map.find(*fnc);
	if (it == handler_map.end()) {
		res->Set(KEY_RESPONSE_CD, E_BAD_FNC);
		res->Set(KEY_RESPONSE_MSG, RESP_BAD_FNC);
		return;
	}

	IHandler *pHandler = (*it).second;

	pHandler->Call(req, res);
}

/////////////////////////////////////////////////////////////////////////////
BOOL Handler::Send(Connection &conn, LPBEOBJECT response)
{
	IPeekableStreamPtr stream;
	stream.Attach(SockStream::Create(conn.getSock()));
	return BEEncoder::encode(response, stream);
}

