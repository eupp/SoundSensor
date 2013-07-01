#pragma once

#include <iostream>
#include <QObject>
#include <QtTest/QtTest>
#include "../wavFile.h"
#include "../soundRecorder.h"

class WavFileTest : public QObject
{
    Q_OBJECT
private slots:
    void init()
    {
        header = new QAudioFormat();
        header->setCodec("audio/pcm");
        header->setSampleRate(8000);
        header->setSampleSize(8);
        header->setChannels(1);
        header->setSampleType(QAudioFormat::UnSignedInt);
        file = new WavFile("wavFileTest.wav");
        file->open(WavFile::WriteOnly, *header);
        signal = new Signal(4);
        (*signal)[0] = 1.0;
        (*signal)[1] = 0.5;
        (*signal)[2] = -0.85;
        (*signal)[3] = -0.1;
    }
    void cleanup()
    {
        delete file;
        delete header;
    }

    // тестируем запись/чтение заголовка wav файла
    void readWriteHeaderTest()
    {
        file->close();
        file->open(WavFile::ReadOnly);
        QAudioFormat readFormat = file->getHeader();
        QCOMPARE(readFormat, *header);
    }
    // тестируем запись/чтение сигнала в файл
    void readWriteSignalTest1()
    {
        int samplesWritten = file->write(*signal);
        QCOMPARE(samplesWritten, 4);
        file->close();
        file->open(WavFile::ReadOnly);
        Signal readSignal = file->readAll();
        QCOMPARE(readSignal, *signal);
    }
    // тестируем запись чтение части сигнала
    void readWriteSignalTest2()
    {
        file->write(*signal, 3);
        file->close();
        file->open(WavFile::ReadOnly);
        Signal readSignal(file->read(2));
        QCOMPARE(readSignal, signal->subSignal(0, 2));
    }
    void sizeTest()
    {
        file->write(*signal);
        QCOMPARE(file->size(), 4);
    }
    void seekPosTest()
    {
        file->write(*signal);
        file->close();
        file->open(WavFile::ReadOnly);
        file->seek(1);
        QCOMPARE(file->pos(), 1);
        Signal signal(file->read(1));
        QCOMPARE(signal[0], Sample(0.5));
    }
    // проверяем запись "с наложением" данных.
    void writeTest()
    {
        file->write(*signal);
        file->seek(1);
        file->write(*signal);
        QCOMPARE(file->size(), 5);
    }
    // проверяем добавление в существующий файл.
    void appendTest()
    {
        file->write(*signal);
        file->close();
        file->open(WavFile::Append);
        Signal signal2(2);
        signal2[0] = 0.8;
        signal2[1] = 0.4;
        file->write(signal2);
        QCOMPARE(file->size(), 6);
    }
    // проверяем, сгенерируется ли исключение при попытке открыть некорректный wav файл.
    void UncorrectFileTest()
    {
        try
        {
            QFile badFile("testUncorrectWavFile.txt");
            badFile.open(QIODevice::WriteOnly);
            for (int i = 0; i < 20; i++)
                badFile.write("Lorem ipsum dolar sit amet ");
            badFile.close();
            file->setFileName("testUncorrectWavFile.txt");
            file->open(WavFile::ReadOnly);
            QFAIL("Exception expected");
        }
        catch (WavFile::OpenFileExc)
        {
        }
    }

    /*
    void init()
    {
        file = new WavFile(QString("test.wav"));
        file->open(WavFile::WriteOnly);
    }
    void cleanup()
    {
        if (file->isOpen())
            file->close();
        delete file;
    }
    void seekTest()
    {
        QVERIFY(file->seek(10));
    }
    void posTest()
    {
        QCOMPARE(file->pos(), (unsigned int)0);
        file->seek(10);
        QCOMPARE(file->pos(), (unsigned int)10);
    }
    void dataSizeTest()
    {
        file->close();
        file->open(WavFile::ReadOnly);
        QCOMPARE(file->dataSize(), (unsigned int)0);
    }
    void writeSignalTest()
    {
        QByteArray bytes;
        bytes[0] = 127;
        bytes[1] = 64;
        bytes[2] = 0;
        bytes[3] = -64;
        Signal signal(bytes, SoundRecorder::defaultAudioFormat());
        file->writeSignal(signal);
        file->close();
        file->open(WavFile::ReadOnly);
        QCOMPARE(file->dataSize(), (unsigned int)4);
    }
    void readSignalTest()
    {
        /*
        QByteArray bytes;
        bytes[0] = 127;
        bytes[1] = 64;
        bytes[2] = 0;
        bytes[3] = -64;
        Signal signal(bytes, SoundRecorder::defaultAudioFormat());
        file->writeSignal(signal);
        file->close();

        file->open(WavFile::ReadOnly);
        Signal readSignal = file->readSignal();
        QByteArray readBytes = readSignal.toByteArray();
        QCOMPARE(char(readBytes[0]), char(127));
        QCOMPARE(char(readBytes[1]), char(64));
        QCOMPARE(char(readBytes[2]), char(0));
        QCOMPARE(char(readBytes[3]), char(-64));
        */
    /*
    }
    */
private:
    WavFile* file;
    QAudioFormat* header;
    Signal* signal;
};
