#!/usr/bin/env bash
#Android 环境编译 qtdeclarative-opensource-src-5.9.81 环境变量脚本
#export ANDROID_HOME=/cygdrive/e/ProgramFiles/Tools/Android/android-sdk
#export ANDROID_NDK_HOST=windows-x86_64
#export ANDROID_NDK_PLATFORM=android-16
#export ANDROID_NDK_ROOT=/cygdrive/d/ProgramFiles/android-ndk-r17c
#export ANDROID_SDK_ROOT=/cygdrive/e/ProgramFiles/Tools/Android/android-sdk

export ANDROID_HOME=E:/ProgramFiles/Tools/Android/android-sdk
export ANDROID_NDK_HOST=windows-x86_64
export ANDROID_NDK_PLATFORM=android-16
export ANDROID_NDK_ROOT=D:/ProgramFiles/android-ndk-r17c
export ANDROID_SDK_ROOT=E:/ProgramFiles/Tools/Android/android-sdk

export PATH=${PATH/mingw53_32/android_armv7}
export PATH=/cygdrive/d/ProgramFiles/android-ndk-r17c/prebuilt/windows-x86_64/bin:/cygdrive/d/ProgramFiles/android-ndk-r17c/toolchains/arm-linux-androideabi-4.9/prebuilt/windows-x86_64/bin:/cygdrive/d/ProgramFiles/Qt5.9.8/5.9.8/android_armv7/bin/:$PATH


#C++/QmlBook-In-Chinese/ceshi/qtquickcontrols-opensource-src-5.9.8


#qmake qtquickcontrols.pro -spec android-g++ "CONFIG+=debug" "CONFIG+=qml_debug" && make.exe qmake_all