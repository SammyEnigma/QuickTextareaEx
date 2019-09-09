#include "quicktextareaex.h"
#include <QTextDocument>
#include <QQuickTextDocument>
#include <QTextCursor>
#include <QDebug>
#include <QRegExp>
#include <QException>
//#include <QFontDatabase>
//#include <QFileInfo>
//#include <QtQuickTemplates2/private/qquicktextarea_p_p.h>
#define QT_BUILD_INTERNAL
#include <QtQuick/private/qquicktextcontrol_p.h>
//#include <qquicktextcontrol_p.h>

//class QuickTextAreaExPrivate : public QQuickTextAreaPrivate
//{
//    Q_DECLARE_PUBLIC(QuickTextAreaEx)

//public:
//    QuickTextAreaExPrivate();
//    ~QuickTextAreaExPrivate();

//    static QuickTextAreaExPrivate *get(QuickTextAreaEx *item)
//    {
//        return static_cast<QuickTextAreaExPrivate *>(QObjectPrivate::get(item));
//    }
//};




#if defined(QT_BUILD_INTERNAL) && defined(QT_SHARED)


#elif defined(QT_SHARED)
#endif

#define DEBUG qDebug()<<__LINE__


QRegExp QuickTextAreaEx::hexreg("[\\da-fA-F]");
QRegExp QuickTextAreaEx::hexregn("[\\da-fA-F\u2028\u2029]");//\\n\\r

QRegExp QuickTextAreaEx::reg64("[\\da-zA-Z\\+\\/=]");
QRegExp QuickTextAreaEx::reg64n("[\\da-zA-Z\\+\\/=\u2028\u2029]");//\\n\\r

QuickTextAreaEx::QuickTextAreaEx(QQuickItem *parent) : QQuickTextArea(parent)
{
    connect(this->textDocument()->textDocument(),&QTextDocument::contentsChange,this,&QuickTextAreaEx::contentsChange);
}

QByteArray QuickTextAreaEx::getByteArray(){
    return  getByteArray(this->text(),m_textType,m_tc);
}

QByteArray QuickTextAreaEx::getByteArray(const QString &text,int tt, QTextCodec *tc){
    QByteArray arr ;
    if(tt == HEX){
        arr =  QByteArray::fromHex(text.toLatin1());
    }else if (tt == BASE64) {
        arr =  QByteArray::fromBase64(text.toLatin1());
    }else{
        arr = tc->fromUnicode(text);
    }
    return arr;
}
QString QuickTextAreaEx::getEncodeStr(const QByteArray&ba,int tt, QTextCodec *tc){
    QString str ;
    if(tt == HEX){
        str =  ba.toHex();
    }else if (tt == BASE64) {
        str =  ba.toBase64();
    }else{
        str = tc->toUnicode(ba);
    }
    return str;
}
QString QuickTextAreaEx::getStrFromByteArray(const QByteArray& ba,int tt, QTextCodec *tc){
    QString str ;
    if(tt == HEX){
        str =  ba.toHex();
    }else if (tt == BASE64) {
        str =  ba.toBase64();
    }else{
        str = tc->toUnicode(ba);
    }
    return str;
}

void QuickTextAreaEx::setTextType(const TextType &textType){
    DEBUG<<"m_textType:"<<m_textType<<";textType:"<<textType<<";length:"<<this->length();
    if(textType == m_textType || textType >2 || textType <0 ) return;
    //QQuickTextAreaPrivate *d = d_func();

    QByteArray arr1;
    QByteArrayList bytesList;

    if(m_multiLines){
        DEBUG;
        bytesList = getBytesListByLines();
    }else if((arr1 = getByteArray()).length()>0){
        bytesList.push_back(arr1);
    }
    DEBUG<<bytesList.size();
    TextType textTypetmp = m_textType;
    try {
        DEBUG;
        m_textType = textType;
        DEBUG;
        if(bytesList.size()>0){
            DEBUG;
            //this->clear();
            setText(QString());
            DEBUG;
            for(QByteArray arr:bytesList){
                DEBUG<<arr.toHex();
                if(textType == HEX){
                    this->append(arr.toHex());
                }else if (textType == BASE64) {
                    this->append(arr.toBase64());
                }else{
                    DEBUG<<m_tc->toUnicode(arr);
                    this->append(m_tc->toUnicode(arr));
                }
            }
        }
    } catch (QException& e) {
        DEBUG<<"err"<<e.what();
        m_textType = textTypetmp;
        return;
    }catch (std::exception &e1) {
        DEBUG<<"err"<<e1.what();
        m_textType = textTypetmp;
        return;
    }catch (... ) {
        DEBUG<<"err";
        m_textType = textTypetmp;
        return;
    }
DEBUG;
    emit textTypeChanged(textType);

}
void QuickTextAreaEx::contentsChange(int position/*from*/, int /*charsRemoved*/, int charsAdded){
    if(m_textType == NORMAL  ||  charsAdded<=0)   return;

    DEBUG<<m_textType<<position<<charsAdded;

    QQuickTextDocument *qqdoc = this->textDocument();
    QQuickTextAreaPrivate *d = d_func();

    //不能选择插入的数据
//            QTextCursor cur = textCursor();//返回当前光标对象
//            cur.setPosition(position, QTextCursor::MoveAnchor);//移到起始位置
//            cur.movePosition(QTextCursor::NoMove, QTextCursor::KeepAnchor, charsAdded);//移动结束位置
//            cur.select(QTextCursor::LineUnderCursor);//选择
//            qDebug()<<"contentsChange"<< cur.selectedText();


    QTextDocument* doc = qqdoc->textDocument();
DEBUG;
    bool notHex = false;
    if(m_textType == HEX){
        for(int i=0;i<charsAdded;++i){
            QChar c=  doc->characterAt(position+i);
            //DEBUG<<c;
            if(!m_hexreg.exactMatch(c)){
                notHex = true;
            }
        }
    }else{//Base64
        for(int i=0;i<charsAdded;++i){
            if(!m_reg64.exactMatch(doc->characterAt(position+i))){
                notHex = true;
            }
        }
    }
    if(notHex){
        //QTextCursor c(d->document)

        QTextCursor cursor = d->control->textCursor();
        if(charsAdded == 1){
            cursor.deletePreviousChar();
            d->control->setTextCursor(cursor);
        }else{
            doc->undo();
        }

    }

}
void QuickTextAreaEx::setCodeName(const QString &codeName){

    QTextCodec *tc = QTextCodec::codecForName(m_codeName.toUtf8());
    if(!tc || tc == m_tc) return;
    m_codeName = codeName;
    m_tc = tc ;
    emit codeNameChanged(m_codeName);
}

void QuickTextAreaEx::setMultiLines(const bool &multiLines){
    if(m_multiLines == multiLines) return;
    //QQuickTextAreaPrivate *d = d_func();
    DEBUG<<multiLines;
    if(multiLines){
        m_hexreg = hexregn;
        m_reg64 = reg64n;
    }else {
        m_hexreg = hexreg;
        m_reg64 = reg64;
    }
    //d->control->
    if(!multiLines && m_textType != NORMAL){//多行变单行

        QStringList list =  getStrListByLines();
        QByteArray arr ;
        for(auto str: list){
            arr.append((m_textType == HEX)?QByteArray::fromHex(str.toLatin1()):QByteArray::fromBase64(str.toLatin1()));
        }
        setText((m_textType == HEX)?arr.toHex():arr.toBase64());
    }

    m_multiLines = multiLines;
    emit multiLinesChanged(m_multiLines);


}

QStringList QuickTextAreaEx::getStrListByLines(){
    static QRegExp spreg("\\n");//[\\n\\r]+

    return this->text().split(spreg);
}
QByteArrayList QuickTextAreaEx::getBytesListByLines(){
    QStringList strlist =  getStrListByLines();

    QByteArrayList byteslist;
    for(auto str: strlist){
        byteslist.append(getByteArray(str,m_textType,m_tc));
    }
    return byteslist;
}
QVariantList QuickTextAreaEx::getBytesVarListByLines(){
    QStringList strlist =  getStrListByLines();

    QVariantList byteslist;
    for(auto str: strlist){
        //DEBUG<<m_textType<<str;
        byteslist.append(getByteArray(str,m_textType,m_tc));
    }
    return byteslist;
}

QVariantList QuickTextAreaEx::getBytesVarListByMultiLines(){
    if(m_multiLines){
        return getBytesVarListByLines();
    }else{
        return {QVariant(getByteArray())};
    }
}

QStringList QuickTextAreaEx::getStrListByTextType(int textType){
    if(textType == m_textType) return {this->text()};

    QVariantList vl= getBytesVarListByMultiLines();
    QStringList lst;
    for(auto v:vl){
        lst.push_back(getEncodeStr(v.toByteArray(),textType,m_tc));
    }

return lst;
}
