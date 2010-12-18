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

#include "Tag.h"

namespace mygpo {

class TagPrivate : public QObject
{
    Q_OBJECT

public:
    TagPrivate(Tag* qq, const QVariant& variant);
    //TagPrivate(Tag* qq, QObject* parent = 0 );
    //TagPrivate (Tag* qq, TagPrivate* pp, QObject* parent = 0);
    const QString tag() const;
    uint usage() const;
private:
    Tag* const q;
    QString m_tag;
    uint m_usage;

    bool parse(const QVariant& data);
};

TagPrivate::TagPrivate (Tag* qq, const QVariant& variant) : q(qq)
{
    parse ( variant );
}

const QString TagPrivate::tag() const
{
    return m_tag;
}

uint TagPrivate::usage() const
{
    return m_usage;
}

bool TagPrivate::parse ( const QVariant& data )
{
    if (!data.canConvert(QVariant::Map))
        return false;
    QVariantMap tagMap = data.toMap();
    QVariant v = tagMap.value ( QLatin1String ( "tag" ) );
    if (!v.canConvert(QVariant::String))
        return false;
    m_tag = v.toString();
    v = tagMap.value ( QLatin1String ( "usage" ) );
    if (!v.canConvert(QVariant::UInt))
        return false;
    m_usage = v.toUInt();
    return true;
}

Tag::Tag ( const QVariant& variant, QObject* parent ) : QObject ( parent ), d(new TagPrivate(this, variant))
{

}

Tag::~Tag()
{
	delete d;
}

const QString Tag::tag() const
{
    return d->tag();
}

uint Tag::usage() const
{
    return d->usage();
}

}

#include "Tag.moc"
