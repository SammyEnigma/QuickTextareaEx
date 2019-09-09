#include "quicktextareaexplugin_plugin.h"
#include "quicktextareaex.h"

#include <qqml.h>

void QuickTextareaExPluginPlugin::registerTypes(const char *uri)
{
    // @uri QuickTextareaEx
    qmlRegisterType<QuickTextAreaEx>(uri, 1, 0, "TextareaEx");
    qmlRegisterType<QQuickTextEdit,7>(uri, 1, 0, "QTextEdit");
    qmlRegisterType<QQuickTextArea,7>(uri, 1, 0, "QTextArea");
}

