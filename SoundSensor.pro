#-------------------------------------------------
#
# Project created by QtCreator 2013-03-24T14:58:22
#
#-------------------------------------------------

QT       += core gui testlib

TARGET = SoundSensor
TEMPLATE = app
CONFIG += mobility
MOBILITY = multimedia

SOURCES += main.cpp\
        testwindow.cpp \
    soundRecorder.cpp \
    QRealFourier/code/sources/qwindowfunction.cpp \
    QRealFourier/code/sources/qfouriervariablecalculator.cpp \
    QRealFourier/code/sources/qfouriertransformer.cpp \
    QRealFourier/code/sources/qfourierfixedcalculator.cpp \
    QRealFourier/code/sources/qfouriercalculator.cpp \
    QRealFourier/code/sources/qcomplexnumber.cpp \
    spectrumAnalyzer.cpp \
    spectrogram.cpp \
    utils.cpp \
    Alglib/fasttransforms.cpp \
    Alglib/ap.cpp \
    Alglib/alglibmisc.cpp \
    correlator.cpp \
    Alglib/alglibinternal.cpp \
    signal.cpp \
    wavFile.cpp \
    voiceCommandSensor.cpp

HEADERS  += testwindow.h \
    soundRecorder.h \
    QRealFourier/code/headers/qwindowfunction.h \
    QRealFourier/code/headers/qfouriervariablecalculator.h \
    QRealFourier/code/headers/qfouriertransformer.h \
    QRealFourier/code/headers/qfourierfixedcalculator.h \
    QRealFourier/code/headers/qfouriercalculator.h \
    QRealFourier/code/headers/qcomplexnumber.h \
    QRealFourier/code/fftreal/OscSinCos.hpp \
    QRealFourier/code/fftreal/OscSinCos.h \
    QRealFourier/code/fftreal/FFTRealUseTrigo.hpp \
    QRealFourier/code/fftreal/FFTRealUseTrigo.h \
    QRealFourier/code/fftreal/FFTRealSelect.hpp \
    QRealFourier/code/fftreal/FFTRealSelect.h \
    QRealFourier/code/fftreal/FFTRealPassInverse.hpp \
    QRealFourier/code/fftreal/FFTRealPassInverse.h \
    QRealFourier/code/fftreal/FFTRealPassDirect.hpp \
    QRealFourier/code/fftreal/FFTRealPassDirect.h \
    QRealFourier/code/fftreal/FFTRealFixLenParam.h \
    QRealFourier/code/fftreal/FFTRealFixLen.hpp \
    QRealFourier/code/fftreal/FFTRealFixLen.h \
    QRealFourier/code/fftreal/FFTReal.hpp \
    QRealFourier/code/fftreal/FFTReal.h \
    QRealFourier/code/fftreal/DynArray.hpp \
    QRealFourier/code/fftreal/DynArray.h \
    QRealFourier/code/fftreal/def.h \
    QRealFourier/code/fftreal/Array.hpp \
    QRealFourier/code/fftreal/Array.h \
    spectrumAnalyzer.h \
    spectrogram.h \
    utils.h \
    Alglib/fasttransforms.h \
    Alglib/ap.h \
    Alglib/alglibinternal.h \
    correlator.h \
    Alglib/alglibmisc.h \
    signal.h \
    wavFile.h \
    tests/signalTest.h \
    voiceCommandSensor.h \
    tests/wavFileTest.h

FORMS    += testwindow.ui \

INCLUDEPATH += /usr/include/QtMultimediaKit
INCLUDEPATH += /usr/include/QtMobility

# подключаем pocketsphinx
INCLUDEPATH +=  /usr/local/include/sphinxbase \
    /usr/local/include/pocketsphinx

LIBS+=  -L/usr/local/lib -lpocketsphinx -lsphinxbase -lsphinxad -lpthread -lm
