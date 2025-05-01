# install dependencies
sudo apt-get install libboost-all-dev
sudo apt-get install libssl-dev

git submodule update --remote --recursive


# build
/usr/bin/cmake --build ./build --config Debug --target all -j 1 --