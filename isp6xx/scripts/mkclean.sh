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
function mkclean()
{
	local cnt=0
	local choice
	local call=$1

	printf "All available source directory:\n"
	for platformdir in ${TOP_DIR}/libisp ; do
		source[$cnt]=`basename $platformdir`
		cd ${TOP_DIR}/${source[$cnt]}
		make clean
		((cnt+=1))
	done
}

mkclean

