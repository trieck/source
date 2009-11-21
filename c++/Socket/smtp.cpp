/////////////////////////////////////////////////////////////////////////////
//
//	SMTP.CPP : simple mail protocol
//
//	Copyright(c) 2006, Thomas A. Rieck, All Rights Reserved
//

#include "stdafx.h"
#include <winsock2.h>
#include "smtp.h"

#define HR_SMTPREADY		220
#define HR_SMTPOK			250
#define HR_SENDMAILDATA		354

#define SMTP_PORT			25
#define REPLY_CODE_SIZE		3

#define CHUNKSIZE			4096

/////////////////////////////////////////////////////////////////////////////
SmtpMail::SmtpMail(const char *phost)
		: host(phost)
{
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
		throw Exception("unable to create socket.");

	if (!connect())
		throw Exception(string("unable to connect to host: " + host).c_str());
}

/////////////////////////////////////////////////////////////////////////////
SmtpMail::~SmtpMail()
{
	close();
}

/////////////////////////////////////////////////////////////////////////////
bool SmtpMail::send(const char *sender, const char *recip,
                    const char *subject, const char *body)
{
	if (!begin_mail(sender))
		throw Exception("unable to initiate mail message.");

	if (!set_recipient(recip))
		throw Exception("unable to set mail recipient.");

	if (!send_data(sender, recip, subject, body))
		throw Exception("unable to send mail message.");

	return true;
}

/////////////////////////////////////////////////////////////////////////////
bool SmtpMail::connect() const
{
	SOCKADDR_IN server;
	if (!gethost(&server))
		return false;

	int n = ::connect(sock,
	                  (LPSOCKADDR)&server, sizeof(SOCKADDR_IN));
	if (SOCKET_ERROR == n)
		return false;

	return isReady();
}

/////////////////////////////////////////////////////////////////////////////
bool SmtpMail::gethost(SOCKADDR_IN *server) const
{
	memset(server, 0, sizeof(SOCKADDR_IN));

	LPHOSTENT ph;
	if (isalpha(host[0])) {
		ph = gethostbyname(host.c_str());
	} else {
		UINT addr = inet_addr(host.c_str());
		ph = gethostbyaddr((const char*)&addr, sizeof(UINT), AF_INET);
	}

	if (ph != NULL) {
		memcpy(&(server->sin_addr), ph->h_addr, ph->h_length);
		server->sin_family = ph->h_addrtype;
		server->sin_port = htons(SMTP_PORT);
	}

	return ph != NULL;
}

/////////////////////////////////////////////////////////////////////////////
bool SmtpMail::send_raw(const char *str) const
{
	size_t len = strlen(str);

	while (len > 0) {
		int n = ::send(sock, str, len, 0);
		if (n == SOCKET_ERROR)
			return false;

		str += n;
		len -= n;
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////
int SmtpMail::recv_raw(char *buffer, size_t size) const
{
	int read = recv(sock, (char*)buffer, size, 0);
	if (read == SOCKET_ERROR)
		return SOCKET_ERROR;

	buffer[read] = '\0';

	return read;
}

/////////////////////////////////////////////////////////////////////////////
void SmtpMail::close()
{
	if (sock != INVALID_SOCKET) {
		closesocket(sock);
		sock = INVALID_SOCKET;
	}
}

/////////////////////////////////////////////////////////////////////////////
bool SmtpMail::isReady() const
{
	if (getResponse() != HR_SMTPREADY)
		return false;

	return true;
}

/////////////////////////////////////////////////////////////////////////////
int SmtpMail::getResponse() const
{
	char buffer[CHUNKSIZE];
	int read = recv_raw(buffer, sizeof(buffer));

	if (read == SOCKET_ERROR || read == 0)
		return 0;

	char code[REPLY_CODE_SIZE + 1];
	memset(code, 0, sizeof(code));
	strncpy(code, buffer, REPLY_CODE_SIZE);

	return atoi(code);
}

/////////////////////////////////////////////////////////////////////////////
bool SmtpMail::begin_mail(const char *sender) const
{
	char buffer[CHUNKSIZE];

	strcpy(buffer, "MAIL FROM: ");
	strcat(buffer, sender);
	strcat(buffer, "\r\n");

	if (!send_raw(buffer))
		return false;

	int response = getResponse();
	if (response != HR_SMTPOK)
		return false;

	return true;
}

/////////////////////////////////////////////////////////////////////////////
bool SmtpMail::set_recipient(const char *recip) const
{
	char buffer[CHUNKSIZE];

	strcpy(buffer, "RCPT TO: ");
	strcat(buffer, recip);
	strcat(buffer, "\r\n");

	if (!send_raw(buffer))
		return false;

	int response = getResponse();
	if (response != HR_SMTPOK)
		return false;

	return true;
}

/////////////////////////////////////////////////////////////////////////////
bool SmtpMail::send_data(const char *sender, const char *recip,
                         const char *subject, const char *body) const
{
	if (!send_raw("DATA \r\n"))
		return false;

	int response = getResponse();
	if (response != HR_SENDMAILDATA)
		return false;

	if (!send_header(sender, recip, subject))
		return false;

	if (!send_raw(body))
		return false;

	if (!send_raw("\r\n.\r\n"))
		return false;

	response = getResponse();
	if (response != HR_SMTPOK)
		return false;

	return true;
}

/////////////////////////////////////////////////////////////////////////////
bool SmtpMail::send_header(const char *sender, const char *recip,
                           const char *subject) const
{
	char buffer[CHUNKSIZE];

	sprintf(buffer, "To: %s\r\n", recip);
	if (!send_raw(buffer))
		return false;

	sprintf(buffer, "From: %s\r\n", sender);
	if (!send_raw(buffer))
		return false;

	sprintf(buffer, "Subject: %s\r\n\r\n", subject);
	if (!send_raw(buffer))
		return false;

	return true;
}
