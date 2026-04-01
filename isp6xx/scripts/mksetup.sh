# scripts/mksetup.sh
#
# (c) Copyright 2013
# Allwinner Technology Co., Ltd. <www.allwinnertech.com>
# James Deng <csjamesdeng@allwinnertech.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
TOP_DIR=`pwd`
function select_platform()
{
	local cnt=0
	local choice
	local call=$1
	printf "All available platform:\n"
	for platformdir in ${TOP_DIR}/buildroot/* ; do
		platforms[$cnt]=`basename $platformdir`
		printf "%4d. %s\n" $cnt ${platforms[$cnt]}
		((cnt+=1))
	done

	while true ; do
		read -p "Choice: " choice
		if [ -z "${choice}" ] ; then
			continue
		fi

		if [ -z "${choice//[0-9]/}" ] ; then
			if [ $choice -ge 0 -a $choice -lt $cnt ] ; then
				export TOOLCHAIN_DIR="${platforms[$choice]}"
				if [ x"${TOOLCHAIN_DIR}" = x"gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu" ] ; then
					export V=64
					export CC=${TOP_DIR}/buildroot/"${platforms[$choice]}/bin/aarch64-none-linux-gnu-gcc"
					export AR=${TOP_DIR}/buildroot/"${platforms[$choice]}/bin/aarch64-none-linux-gnu-gcc-ar"
					export STP=${TOP_DIR}/buildroot/"${platforms[$choice]}/bin/aarch64-none-linux-gnu-strip"
					export STAGING_DIR=${TOP_DIR}/buildroot/"${platforms[$choice]}/bin/"
					echo "export V=64" >> .buildconfig
					echo "export CC=${TOP_DIR}/buildroot/${platforms[$choice]}/bin/aarch64-none-linux-gnu-gcc" >> .buildconfig
					echo "export AR=${TOP_DIR}/buildroot/${platforms[$choice]}/bin/aarch64-none-linux-gnu-gcc-ar" >> .buildconfig
					echo "export STP=${TOP_DIR}/buildroot/${platforms[$choice]}/bin/aarch64-none-linux-gnu-strip" >> .buildconfig
					echo "export STAGING_DIR=${TOP_DIR}/buildroot/${platforms[$choice]}/bin/" >> .buildconfig
				elif [ x"${TOOLCHAIN_DIR}" = x"arm-gnu-toolchain-14.2.rel1-x86_64-aarch64-none-linux-gnu" ] ; then
					export V=64
					export CC=${TOP_DIR}/buildroot/"${platforms[$choice]}/bin/aarch64-none-linux-gnu-gcc"
					export AR=${TOP_DIR}/buildroot/"${platforms[$choice]}/bin/aarch64-none-linux-gnu-gcc-ar"
					export STP=${TOP_DIR}/buildroot/"${platforms[$choice]}/bin/aarch64-none-linux-gnu-strip"
					export STAGING_DIR=${TOP_DIR}/buildroot/"${platforms[$choice]}/bin/"
					echo "export V=64" >> .buildconfig
					echo "export CC=${TOP_DIR}/buildroot/${platforms[$choice]}/bin/aarch64-none-linux-gnu-gcc" >> .buildconfig
					echo "export AR=${TOP_DIR}/buildroot/${platforms[$choice]}/bin/aarch64-none-linux-gnu-gcc-ar" >> .buildconfig
					echo "export STP=${TOP_DIR}/buildroot/${platforms[$choice]}/bin/aarch64-none-linux-gnu-strip" >> .buildconfig
					echo "export STAGING_DIR=${TOP_DIR}/buildroot/${platforms[$choice]}/bin/" >> .buildconfig
				fi
				export TLDIR=${platforms[$choice]}
				echo "export TLDIR=${platforms[$choice]}" >> .buildconfig
				export TOOLCHAIN_DIR=${TOP_DIR}/buildroot/"${platforms[$choice]}/bin"
				echo "export TOOLCHAIN_DIR=${TOP_DIR}/buildroot/${platforms[$choice]}/bin" >> .buildconfig
				break
			fi

		fi
		printf "Invalid input ...\n"
	done
}

function select_source()
{
	export SOURCE="libisp"
	echo "export SOURCE=libisp" >> .buildconfig
}

function select_source_sub()
{
	echo ""
	echo "======================================================"
	echo "               ISP 芯片型号对应表"
	echo "======================================================"
	echo ""
	echo "┌──────────────────────────────┬──────────────────┐"
	echo "│        芯片型号               │     使用 ISP     │"
	echo "├──────────────────────────────┼──────────────────┤"
	echo "│  t527 / a527 / a523          │      isp601      │"
	echo "│  a733 / t736                 │      isp602      │"
	echo "│  a537 / a333 / t536 / mr536  │      isp606      │"
	echo "└──────────────────────────────┴──────────────────┘"
	echo ""
	echo "======================================================"
	echo ""

	export SOURCE_SUB=
	echo "0.601"
	echo "1.602"
	echo "2.606"

# 获取用户选择
	read -p "select isp version (0-2): " n
	
# 根据选择设置版本
	case $n in
		0) version="601" ;;
		1) version="602" ;;
		2) version="606" ;;
		*) echo "Invalid selection"; exit 1 ;;
	esac
# 写入配置文件
	export ISP_VERSION=$version
	echo "export ISP_VERSION=$version" >> .buildconfig
	sed -i "/^#define ISP_VERSION/c#define ISP_VERSION ${ISP_VERSION}"  ${SOURCE}/isp_version.h
	export ISP_SMALL_VERSION=100
	sed -i "/^#define ISP_SMALL_VERSION/c#define ISP_SMALL_VERSION ${ISP_SMALL_VERSION}"  ${SOURCE}/isp_version.h
	echo "Selected $version and save to .buildconfig"
}

function mksetup()
{
	rm -f .buildconfig
	printf "\n"
	printf "Welcome to mkscript setup progress\n"

	select_platform
	select_source
	select_source_sub
}

# Setup all variables in setup.
mksetup

