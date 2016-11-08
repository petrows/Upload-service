#include "u_api.h"

#include <QNetworkProxy>
#include <QUrlQuery>

u_api::u_api(QObject *parent) :
	QObject(parent)
{
	this->req_url = QUrl("http://"UPLOAD_DOMAIN"/api/?");
	this->login   = core->login;
	this->passw   = core->passw;
	this->sid     = core->sid;

	if (core->opt_proxy_enable)
	{
		QNetworkProxy prx;
		if (core->opt_proxy_type == "HTTP")
			prx.setType(QNetworkProxy::HttpProxy);
		if (core->opt_proxy_type == "SOCKS5")
			prx.setType(QNetworkProxy::Socks5Proxy);
		prx.setHostName(core->opt_proxy_host);
		prx.setPort(core->opt_proxy_port);
		this->mng.setProxy(prx);
	}

	this->std_request();
}

QNetworkRequest u_api::std_request()
{
	this->req_url = QUrl("http://"UPLOAD_DOMAIN"/api/?");

	this->req = QNetworkRequest();

	this->req.setUrl(this->req_url);
	this->req.setRawHeader("Cookie",this->std_cookies().toStdString().c_str());
	return this->req;
}

QString u_api::std_cookies()
{
	QStringList cc;

	cc.append("v="  + core->version_s);
	cc.append("os=" + core->os);

	// Get valid SID?
	if (!this->sid.isEmpty())
	{
		cc.append("sid=" + core->sid);
		cc.append("uid=" + QString::number(core->uid));
	} else {
		cc.append("login=" + QUrl::toPercentEncoding(this->login));
		cc.append("passw=" + core->str_md5(this->passw));
	}
	return cc.join("; ");
}

void u_api::set_action(QString action)
{
	QUrlQuery urlQuery(req_url);
	urlQuery.addQueryItem("a",action.toLower());
	req_url.setQuery(urlQuery);
}

bool u_api::do_action()
{
	if (!this->req_url.isValid())
		this->std_request();

	this->last_error      = "";
	this->last_error_code = "";

	// qDebug() << "Cookies: " << this->std_cookies();

	this->req.setUrl(this->req_url);
	// qDebug() << "URL: " << this->req_url;

	QNetworkReply * rep;
	if (this->post_data.isEmpty())
		rep = this->mng.get(this->req);
	else
		rep = this->mng.post(this->req,QByteArray(this->post_data.toStdString().c_str()));

	while (!rep->isFinished())
	{
		u_core_sleep::msleep(50);
		QApplication::processEvents();
	}
	return this->parse_answer(QString::fromUtf8(QString(rep->readAll()).toStdString().c_str()));
}

bool u_api::parse_answer(QString data)
{
	qDebug() << data;
	// Okay, check The Res
	if (!this->ans_dom.setContent(data) || (this->ans_dom.documentElement().nodeName()!="api"))
	{
		// Error!!!
		this->last_error = tr("API answer error");
		return false;
	}
	// Valid (XML) error?
	this->ans_node = this->ans_dom.documentElement();
	if (this->ans_node.childNodes().count() > 0 && this->ans_node.childNodes().at(0).nodeName()=="error")
	{
		QString e_code        = this->ans_node.childNodes().at(0).attributes().namedItem("code").nodeValue();
		this->last_error      = this->parse_error_code(e_code);
		this->last_error_code = e_code;
		return false;
	}
	return true;
}

QString u_api::parse_error_code(QString code)
{
	if (code == "UNK_METHOD")
		return tr("Unknown API Method");
	if (code == "LOGIN_ERROR")
		return tr("Login error. Check your Login/Password settings.");
	if (code == "SID_ERROR")
		return tr("Session error. Please, restart program.");
	if (code == "103")
		return tr("File is too large");

	return tr("Unknown error: %1").arg(code);
}
