/////////////////////////////////////////////////////////////////////////////
//
//	SMTP.H : simple mail protocol
//
//	Copyright(c) 2001, KnowX.com, All Rights Reserved
//

#ifndef __SMTP_H__
#define __SMTP_H__

/////////////////////////////////////////////////////////////////////////////
class SmtpMail
{
public:
// Construction / Destruction
    SmtpMail(const char *phost);
    ~SmtpMail();

// Interface
    bool send(const char *sender,
              const char *recip,
              const char *subject,
              const char *body);

// Implementation
private:
    bool isReady() const;
    bool connect() const;
    bool gethost(SOCKADDR_IN *host) const;
    bool send_raw(const char *str) const;
    int recv_raw(char *buffer, size_t size) const;
    bool begin_mail(const char *sender) const;
    bool set_recipient(const char *recip) const;
    bool send_data(const char *sender, const char *recip,
                   const char *subject, const char *body) const;
    bool send_header(const char *sender, const char *recip,
                     const char *subject) const;

    void close();
    int getResponse() const;

    string host;
    SOCKET sock;
};
/////////////////////////////////////////////////////////////////////////////

#endif	// __SMTP_H__
