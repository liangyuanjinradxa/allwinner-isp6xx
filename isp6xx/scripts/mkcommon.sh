#!/bin/bash
#
# scripts/mkcommon.sh
# (c) Copyright 2013
# Allwinner Technology Co., Ltd. <www.allwinnertech.com>
# James Deng <csjamesdeng@allwinnertech.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
TOP_DIR=`pwd`
SCRIPTS_DIR=${TOP_DIR}/scripts

# 目标目录
TARGET_DIR1="buildroot/gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu"
TARGET_DIR2="./buildroot/arm-gnu-toolchain-14.2.rel1-x86_64-aarch64-none-linux-gnu"
# 压缩包源路径
SOURCE_TAR1="../../../../../prebuilt/kernelbuilt/aarch64/gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu.tar.xz"
SOURCE_TAR2="../../../../../prebuilt/kernelbuilt/aarch64/arm-gnu-toolchain-14.2.rel1-x86_64-aarch64-none-linux-gnu.tar.xz"
# 压缩包目标路径
TARGET_TAR1="buildroot/gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu.tar.xz"
TARGET_TAR2="buildroot/arm-gnu-toolchain-14.2.rel1-x86_64-aarch64-none-linux-gnu.tar.xz"
# 检查bin文件夹是否存在
if [ ! -d "${TARGET_DIR1}/bin" ]; then
    echo "工具链gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu不存在，开始拷贝并解压编译工具链..."
    
    # 确保buildroot目录存在
    mkdir -p buildroot
    
    # 拷贝压缩包到buildroot目录
    if cp "${SOURCE_TAR1}" "${TARGET_TAR1}"; then
        echo "压缩包1拷贝成功"
        
        # 解压到当前目录
        if tar -xf "${TARGET_TAR1}" -C buildroot/; then
            echo "解压成功"
            
            # 删除压缩包
            rm -f "${TARGET_TAR1}"
            echo "压缩包1已删除"
        else
            echo "解压失败" >&2
            exit 1
        fi
    else
		echo "压缩包1拷贝失败" >&2
        exit 1
    fi
else
    echo "工具链文件gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu已存在，跳过解压拷贝工具链步骤"
fi

if [ ! -d "${TARGET_DIR2}/bin" ]; then
    echo "工具链arm-gnu-toolchain-14.2.rel1-x86_64-aarch64-none-linux-gnu不存在，开始拷贝并解压编译工具链..."
    
    # 拷贝压缩包到buildroot目录
    if cp "${SOURCE_TAR2}" "${TARGET_TAR2}"; then
        echo "压缩包2拷贝成功"
        
        # 解压到当前目录
        if tar -xf "${TARGET_TAR2}" -C buildroot/; then
            echo "解压成功"
            
            # 删除压缩包
            rm -f "${TARGET_TAR2}"
            echo "压缩包2已删除"
        else
            echo "解压失败" >&2
            exit 1
        fi
    else
		echo "压缩包2拷贝失败" >&2
        exit 1
    fi
else
    echo "工具链文件arm-gnu-toolchain-14.2.rel1-x86_64-aarch64-none-linux-gnu已存在，跳过解压拷贝工具链步骤"
fi

# 继续执行后续操作
echo "继续执行剩余操作..."

[ -f .buildconfig ] && . .buildconfig

if [ "x$1" = "xconfig" ] ; then
	. ${SCRIPTS_DIR}/mksetup.sh

	echo ${TOP_DIR}/${SOURCE}/${SOURCE_SUB}
	cd ${TOP_DIR}/${SOURCE}/${SOURCE_SUB}
	mv ./Makefile Makefile_buildroot
	mv ./Makefile_debian Makefile
	mv ./iniparser/Makefile ./iniparser/Makefile_buildroot
	mv ./iniparser/Makefile_debian ./iniparser/Makefile
	mv ./isp_cfg/Makefile ./isp_cfg/Makefile_buildroot
	mv ./isp_cfg/Makefile_debian ./isp_cfg/Makefile
	mv ./isp_dev/Makefile ./isp_dev/Makefile_buildroot
	mv ./isp_dev/Makefile_debian ./isp_dev/Makefile
	mv ./isp_math/Makefile ./isp_math/Makefile_buildroot
	mv ./isp_math/Makefile_debian ./isp_math/Makefile
	mv ./out/Makefile ./out/Makefile_buildroot
	mv ./out/Makefile_debian ./out/Makefile
	make clean
	make
	mv ./Makefile Makefile_debian
	mv ./Makefile_buildroot Makefile
	mv ./iniparser/Makefile ./iniparser/Makefile_debian
	mv ./iniparser/Makefile_buildroot ./iniparser/Makefile
	mv ./isp_cfg/Makefile ./isp_cfg/Makefile_debian
	mv ./isp_cfg/Makefile_buildroot ./isp_cfg/Makefile
	mv ./isp_dev/Makefile ./isp_dev/Makefile_debian
	mv ./isp_dev/Makefile_buildroot ./isp_dev/Makefile
	mv ./isp_math/Makefile ./isp_math/Makefile_debian
	mv ./isp_math/Makefile_buildroot ./isp_math/Makefile
	mv ./out/Makefile ./out/Makefile_debian
	mv ./out/Makefile_buildroot ./out/Makefile
	rm ../*.o
	rm ./iniparser/src/*.o
    rm ./isp_events/*.o
	rm ./isp_manage/*.o
	rm ./isp_tuning/*.o
	rm ./tuning_app/*.o
	rm ./tuning_app/server/*.o
	rm ./*.o
	exit $?

elif [ "x$1" = "xclean" ] ; then
	find .  -name "*_64bit" -exec rm -rf {} \;
	find .  -name "*_32bit" -exec rm -rf {} \;
	echo "rm all of the csi_test object file"
	. ${SCRIPTS_DIR}/mkclean.sh
	exit $?

elif [ $# -eq 0 ] ; then
	if [ ! -f .buildconfig ] ; then
		. ${SCRIPTS_DIR}/mksetup.sh
	fi

	cd ${TOP_DIR}/${SOURCE}/${SOURCE_SUB}
	mv ./Makefile Makefile_buildroot
	mv ./Makefile_debian Makefile
	mv ./iniparser/Makefile ./iniparser/Makefile_buildroot
	mv ./iniparser/Makefile_debian ./iniparser/Makefile
	mv ./isp_cfg/Makefile ./isp_cfg/Makefile_buildroot
	mv ./isp_cfg/Makefile_debian ./isp_cfg/Makefile
	mv ./isp_dev/Makefile ./isp_dev/Makefile_buildroot
	mv ./isp_dev/Makefile_debian ./isp_dev/Makefile
	mv ./isp_math/Makefile ./isp_math/Makefile_buildroot
	mv ./isp_math/Makefile_debian ./isp_math/Makefile
	mv ./out/Makefile ./out/Makefile_buildroot
	mv ./out/Makefile_debian ./out/Makefile
	make clean
	make
	mv ./Makefile Makefile_debian
	mv ./Makefile_buildroot Makefile
	mv ./iniparser/Makefile ./iniparser/Makefile_debian
	mv ./iniparser/Makefile_buildroot ./iniparser/Makefile
	mv ./isp_cfg/Makefile ./isp_cfg/Makefile_debian
	mv ./isp_cfg/Makefile_buildroot ./isp_cfg/Makefile
	mv ./isp_dev/Makefile ./isp_dev/Makefile_debian
	mv ./isp_dev/Makefile_buildroot ./isp_dev/Makefile
	mv ./isp_math/Makefile ./isp_math/Makefile_debian
	mv ./isp_math/Makefile_buildroot ./isp_math/Makefile
	mv ./out/Makefile ./out/Makefile_debian
	mv ./out/Makefile_buildroot ./out/Makefile
	rm ../*.o
	rm ./iniparser/src/*.o
    rm ./isp_events/*.o
	rm ./isp_manage/*.o
	rm ./isp_tuning/*.o
	rm ./tuning_app/*.o
	rm ./tuning_app/server/*.o
	rm ./*.o
	exit $?
fi
