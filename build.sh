#!/bin/sh

echo "Starting Build of Hare"
echo "Building Hare Library"
make -f Makefile_libHare OBJ_DIR="objects_libhare" $*
echo "Building Encoders"
make -f Makefile_Encoders OBJ_DIR="objects_encoder" $*
echo "Building Hare"
make -f Makefile_Hare OBJ_DIR="objects_hare" $*
echo "Moving final executable and encoders into dist folder"
mkdir -p dist/add-ons
cp -af objects_hare/Hare dist
cp -af src/Encoders/BeEncoder/objects_encoder/BeEncoder dist/add-ons
cp -af src/Encoders/M3UCreator/objects_encoder/M3U-Creator dist/add-ons
cp -af src/Encoders/MP3GoGo/objects_encoder/MP3-GoGo dist/add-ons
cp -af src/Encoders/MP3Lame/objects_encoder/MP3-Lame dist/add-ons
cp -af src/Encoders/OGGEncoder/objects_encoder/OGG-Encoder dist/add-ons
echo "The Build has Finished!"


