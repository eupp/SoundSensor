#pragma once

#include <QObject>
#include <QtTest/QtTest>
#include "../signal.h"
#include "../soundRecorder.h"

class SignalTest : public QObject
{
    Q_OBJECT
private slots:
    void AccessOperatorTest()
    {
        double* values = new double[4];
        values[0] = 1.0;
        values[1] = 0.5;
        values[2] = 0.25;
        values[3] = 0.125;
        Signal signal(values, 4);
        QCOMPARE(signal[0].toPcm16(), (short)32767);
        QCOMPARE(signal[1].toPcm16(), (short)16384);
        QCOMPARE(signal[2].toPcm16(), (short)8192);
        QCOMPARE(signal[3].toPcm16(), (short)4096);
    }
    void EqualityOperatorTest()
    {
        Signal signal1(2);
        signal1[0] = (short)16000;
        signal1[1] = (short)0;
        Signal signal2(2);
        signal2[0] = (short)16000;
        signal2[1] = (short)0;
        QVERIFY(signal1 == signal2);
    }
    // тестирование создания объекта-сигнала из QByteArray
    void ConstructFromQByteArrayTest()
    {
        QAudioFormat format;
        format.setChannels(1);
        format.setSampleSize(16);
        format.setSampleType(QAudioFormat::SignedInt);
        format.setByteOrder(QAudioFormat::LittleEndian);

        QByteArray bytes;
        bytes.append(0xFF);
        bytes.append(0x7F); // = 32767 ~ 1.0
        bytes.append(static_cast<char>(0));
        bytes.append(static_cast<char>(0)); // = 0
        bytes.append(static_cast<char>(0));
        bytes.append(0xC0); // = -16384 ~ -0.5
        bytes.append(0x01);
        bytes.append(0xA0); // = -24575 ~ -0.75

        Signal signal(bytes, format);

        QVERIFY(compare(signal[0].toFloat(), 1.0));
        QVERIFY(compare(signal[1].toFloat(), 0));
        QVERIFY(compare(signal[2].toFloat(), -0.5));
        QVERIFY(compare(signal[3].toFloat(), -0.75));
    }
    void toFloatTest()
    {
        Signal signal(4);
        signal[0] = (short)32767;
        signal[1] = (short)16384;
        signal[2] = (short)8192;
        signal[3] = (short)4096;

        float* values = signal.toFloatArray();
        QVERIFY(compare(values[0], (float)1.0));
        QVERIFY(compare(values[1], (float)0.5));
        QVERIFY(compare(values[2], (float)0.25));
        QVERIFY(compare(values[3], (float)0.125));
    }

    void toByteArrayTest1()
    {
        Signal signal(4);
        signal[0] = 1.0;
        signal[1] = 0.5;
        signal[2] = 0.0;
        signal[3] = -0.2;

        QAudioFormat format;
        format.setSampleSize(8);
        signal.setFormat(format);
        QByteArray bytes = signal.toByteArray();
        QCOMPARE((char)bytes[0], (char)127);
        QCOMPARE((char)bytes[1], (char)64);
        QCOMPARE((char)bytes[2], (char)0);
        QCOMPARE((char)bytes[3], (char)-25);
    }
    void toByteArrayTest2()
    {
        Signal signal(4);
        signal[0] = 1.0;
        signal[1] = 0.5;
        signal[2] = 0.0;
        signal[3] = -0.2;

        QAudioFormat format;
        format.setSampleSize(16);
        format.setByteOrder(QAudioFormat::BigEndian);
        signal.setFormat(format);
        QByteArray bytes = signal.toByteArray();
        QCOMPARE((char)bytes[0], (char)0x7F);
        QCOMPARE((char)bytes[1], (char)0xFF);
        QCOMPARE((char)bytes[2], (char)0x40);
        QCOMPARE((char)bytes[3], (char)0x00);
        QCOMPARE((char)bytes[4], (char)0x00);
        QCOMPARE((char)bytes[5], (char)0x00);
        QCOMPARE((char)bytes[6], (char)0xE6);
        QCOMPARE((char)bytes[7], (char)0x67);
    }
    void timeTest()
    {
        Signal signal(44100, 44100);
        QCOMPARE(signal.time(44099), 1000);
        QCOMPARE(signal.time(22050), 500);
        QCOMPARE(signal.time(0), 0);
    }

private:
    bool compare(double d1, double d2)
    {
        return (qAbs(d1 - d2) < eps);
    }
    static const double eps = 0.001;
};
