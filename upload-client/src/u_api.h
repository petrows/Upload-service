#ifndef U_API_H
#define U_API_H

#include <QObject>
#include "global.h"

#include "u_core.h"

class u_api : public QObject
{
	Q_OBJECT
public:
	explicit u_api(QObject *parent = 0);

	QNetworkRequest req;
	QUrl            req_url;
	QDomDocument    ans_dom;
	QDomNode        ans_node;
	QString         last_error;
	QString         last_error_code;

	QString         login;
	QString         passw;
	QString         sid;
	
	QString         post_data;

	QNetworkAccessManager mng;
	QNetworkRequest std_request();
	QString         std_cookies();
	void set_action (QString action);
	bool do_action();
	bool parse_answer(QString data);
	QString parse_error_code(QString code);

signals:

public slots:

};

#endif // U_API_H
