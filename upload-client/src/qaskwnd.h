#ifndef QASKWND_H
#define QASKWND_H

#include <QDialog>
#include <QMessageBox>
#include <QCheckBox>

class QAskWndResult
{

};

class QAskWnd : public QDialog
{
	Q_OBJECT
public:
	explicit QAskWnd(QWidget *parent = 0);

	enum StandardButton {
		// keep this in sync with QDialogButtonBox::StandardButton
		NoButton           = 0x00000000,
		Ok                 = 0x00000400,
		Save               = 0x00000800,
		SaveAll            = 0x00001000,
		Open               = 0x00002000,
		Yes                = 0x00004000,
		YesToAll           = 0x00008000,
		No                 = 0x00010000,
		NoToAll            = 0x00020000,
		Abort              = 0x00040000,
		Retry              = 0x00080000,
		Ignore             = 0x00100000,
		Close              = 0x00200000,
		Cancel             = 0x00400000,
		Discard            = 0x00800000,
		Help               = 0x01000000,
		Apply              = 0x02000000,
		Reset              = 0x04000000,
		RestoreDefaults    = 0x08000000,

		FirstButton        = Ok,                // internal
		LastButton         = RestoreDefaults,   // internal

		YesAll             = YesToAll,          // obsolete
		NoAll              = NoToAll,           // obsolete

		Default            = 0x00000100,        // obsolete
		Escape             = 0x00000200,        // obsolete
		FlagMask           = 0x00000300,        // obsolete
		ButtonMask         = ~FlagMask          // obsolete
	};
	typedef StandardButton Button;  // obsolete

	QLabel    * addLabel(QString id, QString text, QLabel * parent);
	QCheckBox * addCheckBox(QString id, QString title);

	int         exec();

signals:
	void link_click(QString addr);

public slots:

};

#endif // QASKWND_H
