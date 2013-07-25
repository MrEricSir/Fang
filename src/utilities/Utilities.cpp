#include "Utilities.h"

Utilities::Utilities()
{
}


QString Utilities::htmlify(const QString& content) {
    return "<html><body>" + content + "</body></html>";
}
