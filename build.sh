#!/bin/bash
clear

# define toolchain
CC=${HOME}/android/toolchains/arm-cortex_a15-linux-gnueabihf-linaro_4.8.3-2014.04/bin/arm-cortex_a15-linux-gnueabihf-
# create .config
if [ ! -e ./.config ]; then
echo "**** Creating .config file ****"
env KCONFIG_NOTIMESTAMP=true \
make "m7cdug_defconfig"
else
grep -q "m7cdug_defconfig" ./.config
if [ $? -ne 0 ]; then
echo "**** Discarding old .config file ****"
rm ./.config
echo "**** Creating .config file ****"
env KCONFIG_NOTIMESTAMP=true \
make "m7cdug_defconfig"
fi
fi
# build the kernel
echo "**** Building kernel ****"
make -j3 ARCH=arm SUBARCH=arm CROSS_COMPILE=$CC
if [ -e ./arch/arm/boot/zImage ]; then
echo "**** Successfully built kernel ****"
echo "**** Copying kernel to build_result/kernel/ ****"
mkdir -p ./build_result/kernel/
cp ./arch/arm/boot/zImage ./build_result/kernel/zImage
echo "**** Copying all built modules (.ko) to build_result/modules/ ****"
mkdir -p ./build_result/modules/
for file in $(find ./ -name *.ko); do
cp $file ./build_result/modules/
done
fi
