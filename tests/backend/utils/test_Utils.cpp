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

#include "utils/CommandTokenizer.h"
#include "utils/PathCheck.h"


class test_Utils : public QObject
{
    Q_OBJECT

private slots:
    void validExtPath_data();
    void validExtPath();

    void tokenize_command();
    void tokenize_command_data();
};

void test_Utils::validExtPath_data()
{
    QTest::addColumn<QString>("path");
    QTest::addColumn<bool>("result");

    QTest::newRow("null path") << QString() << false;
    QTest::newRow("empty path") << "" << false;
    QTest::newRow("app path") << QCoreApplication::applicationFilePath() << true;
    QTest::newRow("app dir path") << QCoreApplication::applicationDirPath() << true;
    QTest::newRow("not existing path") << "nonexistent" << false;
}

void test_Utils::validExtPath()
{
    QFETCH(QString, path);
    QFETCH(bool, result);

    QCOMPARE(::validExtPath(path), result);
}

void test_Utils::tokenize_command()
{
    QFETCH(QString, str);
    QFETCH(QStringList, expected);

    QCOMPARE(utils::tokenize_command(str), expected);
}

void test_Utils::tokenize_command_data()
{
    QTest::addColumn<QString>("str");
    QTest::addColumn<QStringList>("expected");

    QTest::newRow("null") << QString() << QStringList();
    QTest::newRow("empty") << QString("  \t  ") << QStringList();
    QTest::newRow("simple") << QString("test a b c") << QStringList({"test","a","b","c"});
    QTest::newRow("quoted 1") << QString("'test cmd' a 'b c' d") << QStringList({"test cmd","a","b c","d"});
    QTest::newRow("quoted 2") << QString("\"test cmd\" a \"b c\" d") << QStringList({"test cmd","a","b c","d"});
    QTest::newRow("quoted 3") << QString("\"test cmd\"\"a b\"'c'") << QStringList({"test cmd","a b", "c"});
    QTest::newRow("missing quote pair 1") << QString("'test cmd") << QStringList({"'test cmd"});
    QTest::newRow("missing quote pair 2") << QString("\"test cmd") << QStringList({"\"test cmd"});
    QTest::newRow("in-string quotes") << QString("test'cmd\" a'b  c' d") << QStringList({"test'cmd\"","a'b","c'","d"});
    QTest::newRow("whitespaces") << QString("  ' test cmd\t'  a\t \"b  c \"  d ") << QStringList({"test cmd","a","b  c","d"});
}


QTEST_MAIN(test_Utils)
#include "test_Utils.moc"
