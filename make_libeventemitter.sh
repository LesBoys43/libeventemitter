if [ ! -d scripts ]; then
  if [ ! -d ../scripts ]; then
    echo Fatal Error: scripts not found!
    exit 1
  fi
  cd ..
fi
if [ ! -r LocalSettings.ini ]; then
  echo Fatal Error: please configure first, run meson setup \<anything\> and run this script again
  exit 1
fi
source scripts/libini
GLibCflags=$(ini_get "$PWD/LocalSettings.ini" "LocalSettings" "wgGlibCflags")
GLibLdflags=$(ini_get "$PWD/LocalSettings.ini" "LocalSettings" "wgGlibLdflags")
FullCflags="-I$PWD/includes/defines -DLBLIBEE -Wall -Wextra $GLibCflags -c -pipe -O0 -g3 -rdynamic -DVER=$(ini_get  "$PWD/LocalSettings.ini" "LocalSettings" "wgVer") -fPIC"
BaseLdflags="$(gcc -print-file-name=crti.o) $(gcc -print-file-name=crt1.o) $(gcc -print-file-name=crtn.o) -lc -lm $(readelf -l /bin/sh | grep -oP '(?<=interpreter: )/.*?(?=])') -lpthread -ldl -lz"
FullLdflags1="$BaseLdflags $GLibLdflags -shared"
FullLdflags2="$BaseLdflags $GLibLdflags -lc"
Cc=$CC
[[ -z "$CC" ]] && Cc=gcc
Ld=ld
make -j$(nproc) -rRB $* ACTORS="$Cc $Ld $Ld" CFLAGS="$FullCflags" LDFLAGS1="$FullLdflags1" LDFLAGS2="$FullLdflags2"