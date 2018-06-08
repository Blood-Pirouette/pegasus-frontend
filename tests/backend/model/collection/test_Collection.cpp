// Pegasus Frontend
// Copyright (C) 2017  Mátyás Mustoha
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.


#include <QtTest/QtTest>

#include "model/gaming/Collection.h"


class test_Collection : public QObject {
    Q_OBJECT

private slots:
    void names();
    void gameChanged();
};

void test_Collection::names()
{
    model::Collection collection("myname");
    collection.setShortName("abbrev");
    collection.setCommonLaunchCmd("runner");

    // the properties are read-only and should be called only after the initial setup
    QCOMPARE(collection.property("shortName").toString(), QStringLiteral("abbrev"));
    QCOMPARE(collection.property("name").toString(), QStringLiteral("myname"));
}

void test_Collection::gameChanged()
{
    model::Collection collection("dummy");
    QSignalSpy triggered(&collection, &model::Collection::currentGameChanged);
    QVERIFY(triggered.isValid());

    collection.gameListMut().addGame("dummy1");
    collection.gameListMut().addGame("dummy2");

    collection.gameListMut().lockGameList();
    QCOMPARE(triggered.count(), 1);

    collection.gameListMut().setIndex(1);
    QCOMPARE(triggered.count(), 2);
}


QTEST_MAIN(test_Collection)
#include "test_Collection.moc"