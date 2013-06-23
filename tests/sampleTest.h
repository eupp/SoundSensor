#pragma once

#include <QObject>
#include <QtTest/QtTest>
#include "../sample.h"

class SampleTest : public QObject
{
    Q_OBJECT
private slots:
    void toDoubleTest()
    {
        Sample s(0.25);
        QCOMPARE(s.toDouble(), 0.25);
    }
    void toFloatTest()
    {
        Sample s(0.25);
        QCOMPARE(s.toFloat(), (float)0.25);
    }
    void toPcm8Test()
    {
        Sample s(-0.5);
        QCOMPARE(s.toPcm8(), (char)-64);
    }
    void toPcm16LittleEndTest()
    {
        Sample s(-0.5);
        QCOMPARE(s.toPcm16(), (short)-16384);
    }
    void toPcm16BigEndTest()
    {
        Sample s(-0.5);
        s.setByteOrder(Sample::BigEndian);
        short pcm = s.toPcm16();
        char* bytes = reinterpret_cast<char*>(&pcm);
        QCOMPARE(bytes[0], (char)0xC0);
        QCOMPARE(bytes[1], (char)0x00);
    }
    void toUPcm8Test()
    {
        Sample s(-0.5);
        QCOMPARE(s.toUPcm8(), (unsigned char)64);
    }
    void toUPcm16LittleEndTest()
    {
        Sample s(-0.5);
        QCOMPARE(s.toUPcm16(), (unsigned short)16384);
    }
    void toUPcm16BigEndTest()
    {
        Sample s(-0.5);
        s.setByteOrder(Sample::BigEndian);
        short pcm = s.toUPcm16();
        char* bytes = reinterpret_cast<char*>(&pcm);
        QCOMPARE(bytes[0], (char)0x40);
        QCOMPARE(bytes[1], (char)0x00);
    }
    void AssignmentOperatorTest()
    {
        Sample s;
        s = char(127);
        QCOMPARE(s.toDouble(), 1.0);
    }
    void ComparisonOperatorTest()
    {
        Sample s;
        s = 0.2;
        QVERIFY(s.toPcm16() == 6553);
    }
};