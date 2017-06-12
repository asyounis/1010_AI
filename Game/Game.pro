QT += core
QT += widgets
QT -= gui



CONFIG += c++11

# QMAKE_CFLAGS_RELEASE -= -O2
# # QMAKE_CFLAGS_RELEASE += -O3
# QMAKE_CFLAGS_RELEASE += -Os
# QMAKE_CXXFLAGS_RELEASE -= -O2
# # QMAKE_CXXFLAGS_RELEASE += -O3
# QMAKE_CXXFLAGS_RELEASE += -Os

# # QMAKE_LFLAGS_RELEASE -= -O1


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




CUDA_DIR = "/Developer/NVIDIA/CUDA-7.5"


# cuda source
CUDA_SOURCES += cuda_interface.cu

# Path to cuda toolkit install
CUDA_DIR = /usr/local/cuda
INCLUDEPATH += $$CUDA_DIR/include
QMAKE_LIBDIR += $$CUDA_DIR/lib

CUDA_OBJECTS_DIR = ./

CUDA_LIBS = -lcudart 


SYSTEM_TYPE = 64
# GPU architecture
CUDA_ARCH = sm_21

NVCC_OPTIONS = --use_fast_math

# NVCC flags
NVCCFLAGS = --compiler-options -fno-strict-aliasing -use_fast_math --ptxas-options=-v



# join the includes in a line
CUDA_INC = $$join(INCLUDEPATH,' -I','-I',' ')

# Path to libraries
# LIBS += -lcudart -lcuda
LIBS += $$CUDA_LIBS # <-- needed this


# Configuration of the Cuda compiler
CONFIG(debug, debug|release) {
    # Debug mode
    cuda_d.input = CUDA_SOURCES
    cuda_d.output = $$CUDA_OBJECTS_DIR/${QMAKE_FILE_BASE}_cuda.o
    cuda_d.commands = $$CUDA_DIR/bin/nvcc -D_DEBUG $$NVCC_OPTIONS $$CUDA_INC $$NVCC_LIBS --machine $$SYSTEM_TYPE -arch=$$CUDA_ARCH -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
    cuda_d.dependency_type = TYPE_C
    QMAKE_EXTRA_COMPILERS += cuda_d
}
else {
    # Release mode
    cuda.input = CUDA_SOURCES
    cuda.output = $$CUDA_OBJECTS_DIR/${QMAKE_FILE_BASE}_cuda.o
    cuda.commands = $$CUDA_DIR/bin/nvcc $$NVCC_OPTIONS $$CUDA_INC $$NVCC_LIBS --machine $$SYSTEM_TYPE -arch=$$CUDA_ARCH -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
    cuda.dependency_type = TYPE_C
    QMAKE_EXTRA_COMPILERS += cuda
}

# Tell Qt that we want add more stuff to the Makefile
QMAKE_EXTRA_COMPILERS += cuda
