#ifndef QUICKTEXTAREASUB_H
#define QUICKTEXTAREASUB_H
//#define QT_BUILD_INTERNAL
//#include <QObject>
#include "quicktextareaex.h"

class QuickTextAreaSub : public QuickTextAreaEx
{
    Q_OBJECT
public:
    explicit QuickTextAreaSub(QQuickItem *parent = nullptr);
};

#endif // QUICKTEXTAREA_H
