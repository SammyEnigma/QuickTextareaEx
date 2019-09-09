#ifndef QUICKTEXTAREAEX_H
#define QUICKTEXTAREAEX_H
//#define QT_BUILD_INTERNAL
//#include <QObject>
#include <QTextCodec>
#include <QtQuickTemplates2/private/qquicktextarea_p.h>


class QuickTextAreaEx : public QQuickTextArea
{
    Q_OBJECT
    Q_DISABLE_COPY(QuickTextAreaEx)
    Q_ENUMS(TextType)
    Q_PROPERTY(TextType texttype READ textType WRITE setTextType NOTIFY textTypeChanged)
    Q_PROPERTY(QString codemname READ codeName WRITE setCodeName NOTIFY codeNameChanged)//CodeName
    Q_PROPERTY(bool multilines READ multiLines WRITE setMultiLines NOTIFY multiLinesChanged)

public:
    enum TextType{NORMAL,HEX,BASE64};
    explicit QuickTextAreaEx(QQuickItem *parent = nullptr);
    //~QuickTextAreaEx();
    Q_INVOKABLE QByteArray getByteArray();
    QByteArray getByteArray(QString);
    Q_INVOKABLE QStringList getStrListByLines();
    Q_INVOKABLE QByteArrayList getBytesListByLines();
    Q_INVOKABLE QVariantList getBytesVarListByLines();


    TextType textType() const{return m_textType;}
    QString codeName() const{return m_codeName;}
    bool multiLines() const{return m_multiLines;}

signals:
    void textTypeChanged(TextType textType);
    void codeNameChanged(QString arg);
    void multiLinesChanged(bool multiLines);

public slots:
    void contentsChange(int from, int charsRemoved, int charsAdded);
    void setTextType(const TextType &textType);
    void setCodeName(const QString &codeName);
    void setMultiLines(const bool &multiLines);

private:
    inline QQuickTextAreaPrivate* d_func() { return reinterpret_cast<QQuickTextAreaPrivate *>(qGetPtrHelper(d_ptr)); }
    inline const QQuickTextAreaPrivate* d_func() const { return reinterpret_cast<const QQuickTextAreaPrivate *>(qGetPtrHelper(d_ptr)); }
    friend class QQuickTextAreaPrivate;

private:
    TextType m_textType = NORMAL;
    QString m_codeName = "UTF-8";//字符编码,utf8
    QTextCodec *m_tc = QTextCodec::codecForName("UTF-8");
    bool m_multiLines = false;//hex base64 允许换行

    QRegExp m_hexreg = hexreg;
    QRegExp m_reg64 = reg64;

    static QRegExp hexreg;
    static QRegExp hexregn;
    static QRegExp reg64;
    static QRegExp reg64n;
};

#endif // QUICKTEXTAREA_H
