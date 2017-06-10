QT += core
QT += widgets
QT -= gui

CONFIG += c++11

TARGET = Game
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    gameboard.cpp \
    window.cpp \
    game.cpp \
    player.cpp \
    pieces.cpp \
    aiplayer.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    gameboard.h \
    Global.h \
    window.h \
    game.h \
    player.h \ pieces.h \
    aiplayer.h






# cuda source
CUDA_SOURCES += cuda_interface.cu

# Path to cuda toolkit install
CUDA_DIR = /usr/local/cuda
INCLUDEPATH += $$CUDA_DIR/include
QMAKE_LIBDIR += $$CUDA_DIR/lib

# GPU architecture
CUDA_ARCH = sm_20
# NVCC flags
NVCCFLAGS = --compiler-options -fno-strict-aliasing -use_fast_math --ptxas-options=-v

# Path to libraries
LIBS += -lcudart -lcuda

# join the includes in a line
CUDA_INC = $$join(INCLUDEPATH,' -I','-I',' ')
cuda.commands = $$CUDA_DIR/bin/nvcc -m64 -O3 -arch=$$CUDA_ARCH -c $$NVCCFLAGS $$CUDA_INC $$LIBS ${QMAKE_FILE_NAME} -o ${QMAKE_FILE_OUT}
cuda.dependcy_type = TYPE_C
cuda.depend_command = $$CUDA_DIR/bin/nvcc -O3 -M $$CUDA_INC $$NVCCFLAGS      ${QMAKE_FILE_NAME}

cuda.input = CUDA_SOURCES
cuda.output = ${OBJECTS_DIR}${QMAKE_FILE_BASE}_cuda.o
# Tell Qt that we want add more stuff to the Makefile
QMAKE_EXTRA_COMPILERS += cuda
