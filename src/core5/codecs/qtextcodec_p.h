/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
******************************************************************************/

#ifndef QTEXTCODEC_P_H
#define QTEXTCODEC_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of the QTextCodec class.  This header file may change from
// version to version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/qhash.h>
#include <QtCore/qstring.h>

#include <QtCore5Compat/qtcore5compat-config.h>
#if QT_CONFIG(textcodec)
#include <QtCore5Compat/qtextcodec.h>
#endif

#include <private/qtcore5compat-config_p.h>

QT_BEGIN_NAMESPACE

#if QT_CONFIG(textcodec)

#if defined(Q_OS_MAC) || defined(Q_OS_ANDROID) || defined(Q_OS_QNX) || defined(Q_OS_WASM)
#define QT_LOCALE_IS_UTF8
#endif

typedef void (*QTextCodecStateFreeFunction)(QTextCodec::ConverterState*);

typedef QHash<QByteArray, QTextCodec *> QTextCodecCache;

struct QTextCodecData
{
    QTextCodecData();
    ~QTextCodecData();

    QList<QTextCodec*> allCodecs;
    QAtomicPointer<QTextCodec> codecForLocale;
    QTextCodecCache codecCache;

    static QTextCodecData *instance();
};

bool qTextCodecNameMatch(const char *a, const char *b);

#else // without textcodec:

class QTextCodec
{
public:
    enum ConversionFlag {
        DefaultConversion,
        ConvertInvalidToNull = 0x80000000,
        IgnoreHeader = 0x1,
        FreeFunction = 0x2
    };
    Q_DECLARE_FLAGS(ConversionFlags, ConversionFlag)

    struct ConverterState {
        ConverterState(ConversionFlags f = DefaultConversion)
            : flags(f), remainingChars(0), invalidChars(0), d(nullptr) { state_data[0] = state_data[1] = state_data[2] = 0; }
        ~ConverterState() { }
        ConversionFlags flags;
        int remainingChars;
        int invalidChars;
        uint state_data[3];
        void *d;
    private:
        Q_DISABLE_COPY(ConverterState)
    };
};

#endif // textcodec

QT_END_NAMESPACE

#endif
