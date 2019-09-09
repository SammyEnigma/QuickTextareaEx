#include "quicktextareasub.h"
#include <QTextDocument>
#include <QQuickTextDocument>
#include <QTextCursor>
#include <QDebug>
#include <QRegExp>
#include <QException>
//#include <QFontDatabase>
//#include <QFileInfo>

#define QT_BUILD_INTERNAL





#define DEBUG qDebug()<<__LINE__



QuickTextAreaSub::QuickTextAreaSub(QQuickItem *parent) : QuickTextAreaEx(parent)
{

}
