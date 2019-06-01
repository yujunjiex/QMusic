

#屏蔽 msvc 编译器对 rational.h �warning: C4819: 该文件包含不能在当前代码�936)中表示的字符。请将该文件保存�Unicode 格式以防止数据丢�win32-msvc*:QMAKE_CXXFLAGS += /wd"4819"


HEADERS+=\
    $$PWD/musicPlayer.h\
    $$PWD/myMediaList.h\
    $$PWD/playControl.h

SOURCES+=\
    $$PWD/musicPlayer.cpp\
    $$PWD/myMediaList.cpp\
    $$PWD/playControl.cpp



win32{

#根据开发者自�ffmpeg �sdl 库路径，可对如下路径进行修改，不过建�库安装在 C:/lib 下，
#   具体使用步骤，可参看项目�https://github.com/BensonLaur/beslyric-lib

#ffmpeg

FFMPEG_INCLUDE  =   lib/win32/ffmpeg_4_0_1/include
FFMPEG_LIB      =   lib/win32/ffmpeg_4_0_1/lib

#sdl

SDL_INCLUDE     =   lib/SDL_2_0_3/include
SDL_LIB         =   lib/SDL_2_0_3/lib

#other
#OTHER_INCLUDE   =   C:/lib/beslyric-lib/win32/include

INCLUDEPATH +=  $$FFMPEG_INCLUDE \
                $$SDL_INCLUDE \
                $$OTHER_INCLUDE \

LIBS += -L$$FFMPEG_LIB/ -lavcodec\
        -L$$FFMPEG_LIB/ -lavdevice \
        -L$$FFMPEG_LIB/ -lavfilter \
        -L$$FFMPEG_LIB/ -lavutil \
        -L$$FFMPEG_LIB/ -lavformat \
        -L$$FFMPEG_LIB/ -lpostproc \
        -L$$FFMPEG_LIB/ -lswresample \
        -L$$FFMPEG_LIB/ -lswscale \
        -L$$FFMPEG_LIB/ -lswresample \
        -L$$SDL_LIB/ -lSDL2main  \
        -L$$SDL_LIB/ -lSDL2
}


unix:!macx{

#消除ffmpeg中对使用旧接口的警告
QMAKE_CXXFLAGS += -Wno-deprecated-declarations

#根据开发者自�ffmpeg �sdl 库路径，可对如下路径进行修改，不过建�库安装在 /usr/local/ 下，
#   具体使用步骤，可参看项目�https://github.com/BensonLaur/beslyric-lib

# ffmpeg
FFMPEG_INCLUDE  = /usr/local/include
FFMPEG_LIB      = /usr/local/lib

#sdl
SDL_INCLUDE     = /usr/local/beslyric-lib/SDL_2_0_3/include
SDL_LIB         = /usr/local/beslyric-lib/SDL_2_0_3/lib

INCLUDEPATH +=  $$FFMPEG_INCLUDE \
                $$SDL_INCLUDE \

LIBS += $$FFMPEG_LIB/libavcodec.so      \
        $$FFMPEG_LIB/libavdevice.so     \
        $$FFMPEG_LIB/libavfilter.so     \
        $$FFMPEG_LIB/libavformat.so     \
        $$FFMPEG_LIB/libavutil.so       \
        $$FFMPEG_LIB/libswresample.so   \
        $$FFMPEG_LIB/libswscale.so      \
        #$$FFMPEG_LIB/libpostproc.so    \
        -L$$SDL_LIB/ -lSDL2main        \   #can't be $$PSDL_LIB/ -lSDL2main, must be -L$$PSDL_LIB/ -lSDL2main
        -L$$SDL_LIB/ -lSDL2
}


macx{
#根据开发者自�ffmpeg �sdl 库路径，可对如下路径进行修改，不过建�库安装在 /usr/local/ 下，
#   具体使用步骤，可参看项目�https://github.com/BensonLaur/beslyic-lib

# ffmpeg
FFMPEG_INCLUDE  = /usr/local/include
FFMPEG_LIB      = /usr/local/lib

#sdl
SDL_INCLUDE     = /usr/local/include/SDL2
SDL_LIB         = /usr/local/lib

INCLUDEPATH +=  $$FFMPEG_INCLUDE \
                $$SDL_INCLUDE \

LIBS += -L$$FFMPEG_LIB/ -lavcodec      \
        -L$$FFMPEG_LIB/ -lavdevice     \
        -L$$FFMPEG_LIB/ -lavfilter     \
        -L$$FFMPEG_LIB/ -lavformat     \
        -L$$FFMPEG_LIB/ -lavutil       \
        -L$$FFMPEG_LIB/ -lswresample   \
        -L$$FFMPEG_LIB/ -lswscale   \
        -L$$SDL_LIB/ -lSDL2main        \
        -L$$SDL_LIB/ -lSDL2

}
