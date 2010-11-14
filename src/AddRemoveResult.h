/***************************************************************************
* This file is part of libmygpo-qt                                         *
* Copyright (c) 2010 Stefan Derkits <stefan@derkits.at>                    *
* Copyright (c) 2010 Christian Wagner <christian.wagner86@gmx.at>          *
* Copyright (c) 2010 Felix Winter <ixos01@gmail.com>                       *
*                                                                          *
* This library is free software; you can redistribute it and/or            *
* modify it under the terms of the GNU Lesser General Public               *
* License as published by the Free Software Foundation; either             *
* version 2.1 of the License, or (at your option) any later version.       *
*                                                                          *
* This library is distributed in the hope that it will be useful,          *
* but WITHOUT ANY WARRANTY; without even the implied warranty of           *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU        *
* Lesser General Public License for more details.                          *
*                                                                          *
* You should have received a copy of the GNU Lesser General Public         *
* License along with this library; if not, write to the Free Software      *
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 *
* USA                                                                      *
***************************************************************************/

#ifndef ADDREMOVERESULT_H
#define ADDREMOVERESULT_H

#include <QObject>
#include <QList>
#include <QUrl>

#include "mygpo_export.h"

namespace mygpo {

class MYGPO_EXPORT AddRemoveResult : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qulonglong timestamp READ timestamp CONSTANT)
    //updateUrls not (yet) available in Property System because they would have to be saved as QVariant
    //Q_PROPERTY(QList<QPair<QUrl,QUrl>> updateUrls READ updateUrls CONSTANT)
public:
    AddRemoveResult(qulonglong timestamp, const QList<QPair<QUrl, QUrl> >& updateUrls ,QObject* parent = 0);
    AddRemoveResult(const AddRemoveResult& other);
    AddRemoveResult operator=(const AddRemoveResult& other);
    const qulonglong timestamp() const;
    const QList<QPair<QUrl, QUrl> > updateUrls() const;
private:
    qulonglong m_timestamp;
    QList<QPair<QUrl, QUrl> > m_updateUrls;
};

}

#endif // ADDREMOVERESULT_H