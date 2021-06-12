- [Získat zdrojové kódy enve](#get-enve-source)
- [Obsahová tabulka](#toc)
- [Licence](#license)

#### TOC

| [Linux][A0]              | [Windows][B0]            | [macOS][C0]       |
| ---------------------- | -------------------------- | -------------------- |
| [Skia][A1]               | [VSC 2017][B1]         | [Skia][C1]            |
| [Libmypaint][A2]     | [Qt][B2]                      | [Libmypaint][C2]  |
| [Gperftools][A3]     | [LLVM][B3]                | [Quazip][C3]       |
| [Qt][A4]                   | [Environment][B4]     | [Gperftools][C4] |
| [QScintilla][A5]       | [FFmpeg and Libmypaint][B5] | [QScintilla][C5] |
| [Quazip][A6]           | [QScintilla][B6]          | [enve][C6]           |
| [FFmpeg][A7]          | [Quazip][B7]             |                 |
| [Other][A8]              | [Skia][B8]                  |                 |
| [enve][A9]               | [enve][B9]                 |                 |
| [Deploying for Linux][A10] |                       |                 |

[A0]: #building-for-linux
[A1]: #skia
[A2]: #libmypaint
[A3]: #gperftools
[A4]: #qt
[A5]: #qscintilla
[A6]: quazip
[A7]: #ffmpeg
[A8]: #other
[A9]: #enve
[A10]: #deploying-for-linux
[B0]: #building-for-windows
[B1]: #visual-studio-community-2017
[B2]: #qt-1
[B3]: #llvm
[B4]: #environment
[B5]: #ffmpeg-and-libmypaint
[B6]: #qscintilla-1
[B7]: #quazip-1
[B8]: #skia-1
[B9]: #enve-1
[C0]: #building-for-macos
[C1]: #skia-2
[C2]: #libmypaint-1
[C3]: #quazip-2
[C4]: #gperftools-1
[C5]: #qscintilla-2
[C6]: #enve-2


## Získat zdrojové kódy enve

Pro získání zdrojových kódu enve budete potřebovat mít nainstalovaný **git** ve vašem systému.

Naklonujte repozitář enve:
```
git clone --recurse-submodules https://github.com/MaurycyLiebner/enve
```
Přejděte do adresáře enve:
```
cd enve
```
Najděte složku se závislostmi třetích stran:
```
cd third_party
```
Použijte záplaty specifické pro knihovnu enve (pro Windows to není potřeba):
```
make patch
```

<h1 align="center">Sestavení na Linuxu</h1>

Některé z uvedených příkazů, jsou použitelné pouze pro Ubuntu 16.04 a 18.04.
Pokud používáte jinou distribuci, berte tyto příkazy spíše jako obecný návod.

### Skia

Přejděte do adresáře Skia:
```
cd skia
```
Synchronizujte závislosti skia:
```
python tools/git-sync-deps
```
Nainstalujte závislosti Skia:
```
tools/install_dependencies.sh
```
Nainstalujte g++-7:
```
sudo add-apt-repository ppa:jonathonf/gcc
sudo apt-get update
sudo apt-get install g++-7
```
Stáhněte si aplikaci Ninja, rozbalte ji a nastavte oprávnění pro spustitelný soubor:
```
wget https://github.com/ninja-build/ninja/releases/download/v1.9.0/ninja-linux.zip
sudo apt-get install unzip
unzip ninja-linux.zip
chmod +x ninja
```
Vytvořte sestavenou verzi (ninja) souborů:
```
bin/gn gen out/Release --args='is_official_build=true is_debug=false extra_cflags=["-Wno-error"] target_os="linux" target_cpu="x64" skia_use_system_expat=false skia_use_system_freetype2=false skia_use_system_libjpeg_turbo=false skia_use_system_libpng=false skia_use_system_libwebp=false skia_use_system_zlib=false skia_use_system_icu=false skia_use_system_harfbuzz=false cc="gcc-7" cxx="g++-7"'
```
Sestavte vydání Skia (můžete použít více než 2 vlákna):
```
./ninja -C out/Release -j 2 skia
```
Pokud chcete, můžete sestavit také odladěnou verzi:
```
bin/gn gen out/Debug --args='extra_cflags=["-Wno-error"] cc="gcc-7" cxx="g++-7"'
./ninja -C out/Debug -j 2 skia
```

Přejděte zpět do svého domovského adresáře:
```
cd ..
```

### Libmypaint
Nainstalujte závislosti Libmypaint
```
sudo apt-get install libjson-c-dev intltool pkg-config
```
Přejděte do adresáře libmypaint:
```
cd libmypaint
```
Nastavte CFLAGS pro lepší optimalizaci:
```
export CFLAGS='-fopenmp -Ofast -ftree-vectorize -fopt-info-vec-optimized -funsafe-math-optimizations -funsafe-loop-optimizations -fPIC'
```
Upravte libmypaint:
```
./configure --enable-static --enable-openmp --enable-shared=false
```
Sestavte libmypaint:
```
sudo make
```
Přejděte zpět do svého domovského adresáře:
```
cd ..
```

### Gperftools
Nainstalujte balíčky, potřebné pro sestavení Gperftools:
```
sudo apt-get install autoconf automake libtool
sudo apt-get install libunwind-dev
```

Sestavte gperftools:
```
cd gperftools
./autogen.sh
./configure --prefix /usr
make
```
Přejděte zpět do svého domovského adrsáře:
```
cd ..
```
### Qt

Jděte na qt.io/download Pro stažení otevřeného Qt instalátoru:
Nainstalujte Qt 5.12.4 Desktop gcc 64-bit.

Nainstalujte Qt do vybraného adresáře (ex. ~/.Qt)

### QScintilla
Sestavte QScintilla:
```
cd qscintilla/Qt4Qt5
qmake
make -j 2
```
Přejděte zpět do svého domovského adrsáře:
```
cd ..
```
### Quazip

```
cd quazip\quazip
qmake INCLUDEPATH+=$$[QT_INSTALL_HEADERS]/QtZlib
make -j 2
```

Vraťte se zpět do hlavního adresáře enve:
```
cd ../../../
```

### FFmpeg
Nainstalujte knihovny, potřebné pro přehrávání videa a audia:
```
sudo add-apt-repository ppa:jonathonf/ffmpeg-4
sudo apt-get update
sudo apt-get install libswresample-dev libswscale-dev libavcodec-dev libavformat-dev libavresample-dev
```

### Jiné
závislosti enve:
```
sudo apt-get install libglib2.0-dev
```
Nainstalujte libxkbcommon-x11-dev pro spuštění QtCreator v Ubuntu 16.04.
Jinak se nespustí správně.
```
sudo apt-get install libxkbcommon-x11-dev
```

### enve

Enve můžete sestavit buď prostřednictvím QtCreator (otevřete soubor enve.pro a nastavte Relase/Debug Kits),
nebo přímo spuštěním qmake a make.

Ve výchozím nastavení není qmake nainstalován v /usr/bin.
Budete jej muset zavolat jeho plnou cestou nebo vytvořit symbolický odkaz:
```
sudo ln -s your_Qt_dir/5.12.4/gcc_64/bin/qmake /usr/bin/qmake
```

Sestavte vydanou verzi enve:
```
cd build/Release
qmake ../../enve.pro
make CC=gcc-7 CPP=g++-7 CXX=g++-7 LD=g++-7
cd ..
```
Stahněte si ladící verzi enve (je to nutné):
```
cd Debug
qmake CONFIG+=debug ../../enve.pro
make CC=gcc-7 CPP=g++-7 CXX=g++-7 LD=g++-7
cd ..
```
Nyní jste úspěšně sestavili enve a libenvecore spolu se všemi příklady.
Pokud si přejete vytvořit vlastní spustitelný soubor, přejděte k části **Uvedení do provozu**.

## Ladění na Linuxu

Ujistěte se, že jste v adresáři pro sestavení.

### Stáhněte potřebné nástroje

Stažení a změna oprávnění pro LinuxDeployQt:
```
wget https://github.com/probonopd/linuxdeployqt/releases/download/6/linuxdeployqt-6-x86_64.AppImage
chmod +x linuxdeployqt-6-x86_64.AppImage
```
Zkopírujte sestavení enve do souboru AppDir:
```
cp Release/src/app/enve AppDir/usr/bin/
cp -av Release/src/core/*.so* AppDir/usr/lib/
```

#### Podpora pro jiné systémy (ex. Ubuntu 16.04)
Stáhněte si opravenou binární knihovnu AppRun a přidruženou knihovnu, která umožní propojení novější verze libstdc++ na starších systémech:
```
wget https://github.com/darealshinji/AppImageKit-checkrt/releases/download/continuous/AppRun-patched-x86_64
mv AppRun-patched-x86_64 AppRun
chmod +x AppRun
cp AppRun AppDir/
```
```
wget https://github.com/darealshinji/AppImageKit-checkrt/releases/download/continuous/exec-x86_64.so
mv exec-x86_64.so exec.so
cp exec.so AppDir/usr/optional
```
Zkopírujte systémovou verzi libstdc++ do svého AppDiru:
```
mkdir AppDir/usr/optional/libstdc++
cp /usr/lib/x86_64-linux-gnu/libstdc++.so.6 AppDir/usr/optional/libstdc++/
```

#### Vytvoření AppImage

Vytvořte AppImage pomocí nástroje LinuxDeployQt:
```
./linuxdeployqt-6-x86_64.AppImage AppDir/usr/share/applications/enve.desktop -appimage
```

A nyní máte vytvořený AppImage aplikace enve!

<h1 align="center">Sestavení pro Windows</h1>

### Visual Studio Community 2017

Nainstalujte si Visual Studio Community 2017 ze stránek **https://visualstudio.microsoft.com/vs/older-downloads**.	
Ujistěte se, že jste nainstalovali **Vývoj na stolním počítači s C++**.

### Qt

Přejděte na qt.io/download pro stažení otevřeného Qt instalátoru.
Nainstalujte Qt 5.12.4 Desktop MSVC 2017 64-bit.

### LLVM

Stáhněte si nejnovější stabilní verzi LLVM z **https://github.com/llvm/llvm-project/releases**, např. **LLVM-10.0.0-win64.exe**.
Nainstalujte LLVM.

### Prostředí

Spusťte všechny příkazy z příkazového řádku **Qt 5.12.4 (MSVC 2017 64-bit)**.
Nezapomeňte zavolat soubor vcvarsall.bat pro inicializaci prostředí MSVC, např,
`"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x64`.

### FFmpeg a Libmypaint

Ke stažení předpřipravených knihoven použijte batch skript:
```
cd third_party
win.bat
```

### QScintilla

```
cd qscintilla\Qt4Qt5
qmake CONFIG-=debug_and_release
nmake
```

### Quazip

```
cd quazip\quazip
qmake CONFIG-=debug_and_release INCLUDEPATH+=$$[QT_INSTALL_HEADERS]/QtZlib
nmake
```

### Skia


Přejděte do adresáře Skia:
```
cd skia
```

```
python tools/git-sync-deps
```

Upravte vydání sestavení:
```
bin\gn.exe gen out/Release --args="is_official_build=true is_debug=false extra_cflags=[\"-Wno-error\",\"/MD\",\"/O2\"] target_os=\"windows\" host_os=\"win\" current_os=\"win\" target_cpu=\"x64\" clang_win=\"C:\Program Files\LLVM\" cc=\"clang-cl\" cxx=\"clang-cl\" skia_use_system_expat=false skia_use_system_icu=false skia_use_system_libjpeg_turbo=false skia_use_system_libpng=false skia_use_system_libwebp=false skia_use_system_zlib=false skia_use_system_harfbuzz=false" --ide=vs
```


Přejděte do sestavovacího adresáře:
```
cd out\Release
```

Sestavte Skia:

```
msbuild all.sln
```

### enve

```
qmake enve.pro -spec win32-clang-msvc -config release
nmake
```

<h1 align="center">Sestavení pro macOS</h1>

Nainstalujte závislosti sestavení pro knihovny třetích stran z Homebrew.
```sh
brew install ninja json-c intltool pkg-config gettext zlib ffmpeg
```

### Skia

```sh
pyenv shell system  # disable pyenv as build script breaks under Python 3
tools/git-sync-deps
bin/gn gen out/Release --args='is_official_build=true is_debug=false extra_cflags=["-Wno-error"] skia_use_system_expat=false skia_use_system_icu=false skia_use_system_libjpeg_turbo=false skia_use_system_libpng=false skia_use_system_libwebp=false skia_use_system_zlib=false'
ninja -C out/Release skia
```

### Libmypaint

```sh
# Manually specify environmental variables for keg-only dependencies.
ACLOCAL_FLAGS="-I/usr/local/opt/gettext/share/aclocal $ACLOCAL_FLAGS"
LDFLAGS="-L/usr/local/opt/gettext/lib $LDFLAGS"
CPPFLAGS="-I/usr/local/opt/gettext/include $CPPFLAGS"
PATH="/usr/local/opt/gettext/bin:$PATH"
./autogen.sh
./configure --enable-openmp --prefix=/usr/local
make
ln -s `pwd` libmypaint
```

### Quazip

```sh
# Explicitly add zlib to path upon build, as Homebrew zlib is keg-only.
# Do not `brew link zlib` as it might conflict with the stock version shipped with macOS.
LDFLAGS="-L/usr/local/opt/zlib/lib $LDFLAGS"
CPPFLAGS="-I/usr/local/opt/zlib/include $CPPFLAGS"
qmake quazip.pro -spec macx-clang CONFIG+=release CONFIG+=x86_64 LIBS+=-lz
make

```

### Gperftools

```sh
CFLAGS="$CFLAGS -Wno-error -D_XOPEN_SOURCE"
./autogen.sh
./configure --disable-dependency-tracking --prefix=/usr/local
make
```

### QScintilla

```sh
cd Qt4Qt5
qmake -spec macx-clang CONFIG+=release
```

### enve

```
qmake enve.pro -spec macx-clang CONFIG+=release
make
```

## Licence

Tento projekt je uvolněn pod GPL3 licencí - podívejte se do [LICENSE.md](LICENSE.md) pro více informací.
