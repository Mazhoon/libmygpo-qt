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

#include "ApiRequestTest.h"
#include <QDateTime>

using namespace mygpo;

ApiRequestTest::ApiRequestTest() : m_req( QLatin1String("ase23"),QLatin1String("csf-sepm"), new QNetworkAccessManager() )
{

}

ApiRequestTest::~ApiRequestTest()
{

}

void ApiRequestTest::init()
{
    m_ok = false;
}

void ApiRequestTest::initTestCase()
{

}

void ApiRequestTest::cleanup()
{

}

void ApiRequestTest::cleanupTestCase()
{

}



void ApiRequestTest::testToplist()
{
    QEventLoop loop;
    PodcastListPtr ret = m_req.toplist(10);
    connect(ret.data(),SIGNAL(parseError()), this, SLOT(error()));
    connect(ret.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
    connect(ret.data(),SIGNAL(finished()), this, SLOT(finished()));
    loop.connect(ret.data(),SIGNAL(finished()),SLOT(quit()));
    loop.connect(ret.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.connect(ret.data(),SIGNAL(parseError()),SLOT(quit()));
    loop.exec();
    QVERIFY(m_ok);
    QCOMPARE(ret->list().size(),10);
}

//void ApiRequestTest::testSuggestions()
//{
//    QEventLoop loop;
//    PodcastListPtr ret = m_req.toplist(5);
//    QObject::connect(ret.data(),SIGNAL(parseError()), this, SLOT(error()));
//    QObject::connect(ret.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
//    QObject::connect(ret.data(),SIGNAL(finished()), this, SLOT(finished()));
//    loop.connect(ret.data(),SIGNAL(finished()),SLOT(quit()));
//    loop.connect(ret.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
//    loop.connect(ret.data(),SIGNAL(parseError()),SLOT(quit()));
//    loop.exec();
//    QVERIFY(m_ok);
//    QVERIFY(ret->list().size() <= 5);
//}

void ApiRequestTest::testPodcastsOfTag()
{
    QEventLoop loop;
    PodcastListPtr ret = m_req.podcastsOfTag(3,QLatin1String("fm4"));
    QObject::connect(ret.data(),SIGNAL(parseError()), this, SLOT(error()));
    QObject::connect(ret.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
    QObject::connect(ret.data(),SIGNAL(finished()), this, SLOT(finished()));
    loop.connect(ret.data(),SIGNAL(finished()),SLOT(quit()));
    loop.connect(ret.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.connect(ret.data(),SIGNAL(parseError()),SLOT(quit()));
    loop.exec();
    QVERIFY(m_ok);
    QVERIFY(ret->list().size() <= 3);
}

void ApiRequestTest::testPodcastData()
{
    QEventLoop loop;
    PodcastPtr ret = m_req.podcastData(QUrl(QLatin1String("http://pauldotcom.com/podcast/psw.xml")));
    QObject::connect(ret.data(),SIGNAL(parseError()), this, SLOT(error()));
    QObject::connect(ret.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
    QObject::connect(ret.data(),SIGNAL(finished()), this, SLOT(finished()));
    loop.connect(ret.data(),SIGNAL(finished()),SLOT(quit()));
    loop.connect(ret.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.connect(ret.data(),SIGNAL(parseError()),SLOT(quit()));
    loop.exec();
    QVERIFY(m_ok);
    QCOMPARE(ret->title(),QLatin1String("PaulDotCom Security Weekly"));
    QCOMPARE(ret->url(), QUrl(QLatin1String("http://pauldotcom.com/podcast/psw.xml")));
    QCOMPARE(ret->description(), QLatin1String("PaulDotCom Security Weekly Podcast with Paul, Larry, Mick, Carlos, and special guests!"));
    QCOMPARE(ret->logoUrl(), QUrl(QLatin1String("http://pauldotcom.com/images/psw-logo-sm.png")));
    QCOMPARE(ret->website(), QUrl(QLatin1String("http://pauldotcom.com/")));
    QCOMPARE(ret->mygpoUrl(), QUrl(QLatin1String("http://gpodder.net/podcast/11194")));
}


void ApiRequestTest::testEpisodeData()
{
    QEventLoop loop;
    EpisodePtr ret = m_req.episodeData(QUrl(QLatin1String("http://leo.am/podcasts/twit")),QUrl(QLatin1String("http://www.podtrac.com/pts/redirect.mp3/aolradio.podcast.aol.com/twit/twit0245.mp3")));
    QObject::connect(ret.data(),SIGNAL(parseError()), this, SLOT(error()));
    QObject::connect(ret.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
    QObject::connect(ret.data(),SIGNAL(finished()), this, SLOT(finished()));
    loop.connect(ret.data(),SIGNAL(finished()),SLOT(quit()));
    loop.connect(ret.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.connect(ret.data(),SIGNAL(parseError()),SLOT(quit()));
    loop.exec();
    QVERIFY(m_ok);
    QCOMPARE(ret->title(),QLatin1String("TWiT 245: No Hitler For You"));
    QCOMPARE(ret->url(), QUrl(QLatin1String("http://www.podtrac.com/pts/redirect.mp3/aolradio.podcast.aol.com/twit/twit0245.mp3")));
    QCOMPARE(ret->podcastTitle(), QLatin1String("this WEEK in TECH - MP3 Edition"));
    QCOMPARE(ret->podcastUrl(), QUrl(QLatin1String("http://leo.am/podcasts/twit")));
}



void ApiRequestTest::testFavoriteEpisodes()
{
    QEventLoop loop;
    EpisodeListPtr ret = m_req.favoriteEpisodes(QLatin1String("ase23"));
    QObject::connect(ret.data(),SIGNAL(parseError()), this, SLOT(error()));
    QObject::connect(ret.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
    QObject::connect(ret.data(),SIGNAL(finished()), this, SLOT(finished()));
    loop.connect(ret.data(),SIGNAL(finished()),SLOT(quit()));
    loop.connect(ret.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.connect(ret.data(),SIGNAL(parseError()),SLOT(quit()));
    loop.exec();
    QVERIFY(m_ok);
    QVERIFY(ret->list().size() == 3);
    QCOMPARE(ret->list().at(2)->title(), QLatin1String("Episode 5: Computer vision with opencv"));
    QCOMPARE(ret->list().at(1)->title(), QLatin1String("#420: Neighborhood Watch"));
    QCOMPARE(ret->list().at(2)->podcastTitle(), QLatin1String("Hacker Medley"));
    QCOMPARE(ret->list().at(1)->podcastTitle(), QLatin1String("This American Life"));
    QCOMPARE(ret->list().at(2)->url(),QUrl(QLatin1String("http://hackermedley.org/podcasts/medley5.mp3")));
    QCOMPARE(ret->list().at(1)->url(), QUrl(QLatin1String("http://feeds.thisamericanlife.org/~r/talpodcast/~5/9M6uAGaPVVY/420.mp3")));
    QCOMPARE(ret->list().at(2)->podcastUrl(),QUrl(QLatin1String("http://hackermedley.org/feed/podcast/")));
    QCOMPARE(ret->list().at(1)->podcastUrl(),QUrl(QLatin1String("http://feeds.thisamericanlife.org/talpodcast")));
}


void ApiRequestTest::testTopTags()
{
    QEventLoop loop;
    TagListPtr ret = m_req.topTags(13);
    QObject::connect(ret.data(),SIGNAL(parseError()), this, SLOT(error()));
    QObject::connect(ret.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
    QObject::connect(ret.data(),SIGNAL(finished()), this, SLOT(finished()));
    loop.connect(ret.data(),SIGNAL(finished()),SLOT(quit()));
    loop.connect(ret.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.connect(ret.data(),SIGNAL(parseError()),SLOT(quit()));
    loop.exec();
    QVERIFY(m_ok);
    QVERIFY(ret->list().size() == 13);
}


void ApiRequestTest::testAddRemoveSubscriptionsAdd()
{
    QEventLoop loop;
    QList<QUrl> addList;
    QList<QUrl> removeList;
    addList.append(QUrl(QLatin1String("http://downloads.bbc.co.uk/podcasts/worldservice/scia/rss.xml")));
    AddRemoveResultPtr ret = m_req.addRemoveSubscriptions(QLatin1String("ase23"),QLatin1String("dev0"),addList, removeList);
    QObject::connect(ret.data(),SIGNAL(parseError()), this, SLOT(error()));
    QObject::connect(ret.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
    QObject::connect(ret.data(),SIGNAL(finished()), this, SLOT(finished()));
    loop.connect(ret.data(),SIGNAL(finished()),SLOT(quit()));
    loop.connect(ret.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.connect(ret.data(),SIGNAL(parseError()),SLOT(quit()));
    loop.exec();
    QVERIFY(m_ok);
}

void ApiRequestTest::testAddRemoveSubscriptionsRemove()
{
    QEventLoop loop;
    QList<QUrl> addList;
    QList<QUrl> removeList;
    removeList.append(QUrl(QLatin1String("http://downloads.bbc.co.uk/podcasts/worldservice/scia/rss.xml")));
    AddRemoveResultPtr ret = m_req.addRemoveSubscriptions(QLatin1String("ase23"),QLatin1String("dev0"),addList, removeList);
    QObject::connect(ret.data(),SIGNAL(parseError()), this, SLOT(error()));
    QObject::connect(ret.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
    QObject::connect(ret.data(),SIGNAL(finished()), this, SLOT(finished()));
    loop.connect(ret.data(),SIGNAL(finished()),SLOT(quit()));
    loop.connect(ret.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.connect(ret.data(),SIGNAL(parseError()),SLOT(quit()));
    loop.exec();
    QVERIFY(m_ok);
}

void ApiRequestTest::testListDevices()
{
	QEventLoop loop;
	DeviceListPtr devices = m_req.listDevices(QLatin1String("ase23"));
	QObject::connect(devices.data(),SIGNAL(parseError()), this, SLOT(error()));
	QObject::connect(devices.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
	QObject::connect(devices.data(),SIGNAL(finished()), this, SLOT(finished()));
	loop.connect(devices.data(),SIGNAL(finished()),SLOT(quit()));
	loop.connect(devices.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
	loop.connect(devices.data(),SIGNAL(parseError()),SLOT(quit()));
	loop.exec();
	QVERIFY(m_ok);

	QVERIFY(devices->devicesList().size() == 4);
	DevicePtr device = devices->devicesList().at(1);
	QCOMPARE(device->id(), QLatin1String("foobar"));
	QCOMPARE(device->type(), QLatin1String("server"));
	QCOMPARE(device->caption(), QLatin1String("foobar"));
	QVERIFY(device->subscriptions() == 7);
}

void ApiRequestTest::testRenameDevices()
{
	QEventLoop loop;
	QNetworkReply *reply = m_req.renameDevice(QLatin1String("ase23"), QLatin1String("foobar"), QLatin1String("foobar2"), Device::OTHER);
	QObject::connect(reply,SIGNAL(finished()), this, SLOT(finished()));
	loop.connect(reply,SIGNAL(finished()),SLOT(quit()));
	loop.exec();
	QVERIFY(m_ok);

	m_ok = false;
	reply = m_req.renameDevice(QLatin1String("ase23"), QLatin1String("foobar"), QLatin1String("foobar"), Device::SERVER);
	QObject::connect(reply,SIGNAL(finished()), this, SLOT(finished()));
	loop.connect(reply,SIGNAL(finished()),SLOT(quit()));
	loop.exec();
	QVERIFY(m_ok);
}

void ApiRequestTest::testDeviceUpdates()
{
	QEventLoop loop;
	QDateTime time;
	DeviceUpdatesPtr updates = m_req.deviceUpdates(QLatin1String("ase23"), QLatin1String("foobar"), time.toTime_t());
	QObject::connect(updates.data(),SIGNAL(parseError()), this, SLOT(error()));
	QObject::connect(updates.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
	QObject::connect(updates.data(),SIGNAL(finished()), this, SLOT(finished()));
	loop.connect(updates.data(),SIGNAL(finished()),SLOT(quit()));
	loop.connect(updates.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
	loop.connect(updates.data(),SIGNAL(parseError()),SLOT(quit()));
	loop.exec();
	QVERIFY(m_ok);
	QVERIFY(updates->timestamp() > 0);
}


void ApiRequestTest::error()
{
    m_ok = false;
}

void ApiRequestTest::error(QNetworkReply::NetworkError error)
{
    m_ok = false;
    qDebug() << "NetworkError occurred: " << error;
}

void ApiRequestTest::finished()
{
	m_ok = true;
}





QTEST_MAIN(ApiRequestTest)
