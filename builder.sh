source "$stdenv"/setup

cp --recursive "$src" ./
chmod --recursive u=rwx ./"$(basename "$src")"
cd ./"$(basename "$src")"

if [ ! -d "build" ]; then
  mkdir build
fi

mkdir $out
cd build

$src/configure --prefix=$out
make -j24
make install