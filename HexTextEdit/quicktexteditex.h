#ifndef QUICKTEXTEDITEX_H
#define QUICKTEXTEDITEX_H

//#include <QObject>
#include <QtQuick/private/qquicktextedit_p.h>
class QuickTextEditEx : public QQuickTextEdit
{
    Q_OBJECT
public:
    explicit QuickTextEditEx(QQuickItem *parent = nullptr);

signals:

public slots:
};

#endif // QUICKTEXTEDITEX_H
