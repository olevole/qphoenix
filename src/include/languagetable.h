#pragma once

#include <QMap>
#include <QString>
#include <QStringList>

/*!
 * \brief LanguageTable
 *
 * Provide a table for translators without linear
 * translation betwen languages. (for example, you
 * can translate English word to German or Russian,
 * but you can translate Russian word only to English
 * The key QString is a source langauge, the value -
 * possible result languages. This hash must contain
 * ONLY keys for LanguageList, not a values!
 * The key's MUST be an ISO 639-1 codes.
 * More information: en.wikipedia.org/wiki/List_of_ISO_639-1_codes
 */

typedef QMap <QString, QStringList> LanguageTable;

#define QP_ADD_LANG(X,Y,Z) X.insert(Y,QString(Z).split(','))
