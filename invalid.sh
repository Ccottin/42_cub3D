#! /bin/bash

VALGRIND="valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes"
SEP="===================================================="

execMandatory() {

	echo $VALGRIND ./cub3d $1
	$VALGRIND ./cub3D $1
	echo $SEP
	sleep 1;
}

make

execMandatory invalid/maptest10.cub
execMandatory invalid/maptest11.cub
execMandatory invalid/maptest12.cub
execMandatory invalid/maptest13.cub
execMandatory invalid/maptest14.cub
execMandatory invalid/maptest15.cub
execMandatory invalid/maptest16.cub
execMandatory invalid/maptest17.cub
execMandatory invalid/maptest18.cub
execMandatory invalid/maptest19.cub
execMandatory invalid/maptest1.cub
execMandatory invalid/maptest20.cub
execMandatory invalid/maptest21.cub
execMandatory invalid/maptest22.cub
execMandatory invalid/maptest23.cub
execMandatory invalid/maptest24.cub
execMandatory invalid/maptest25.cub
execMandatory invalid/maptest26.cub
execMandatory invalid/maptest27.cub
execMandatory invalid/maptest28.cub
execMandatory invalid/maptest29.cub
execMandatory invalid/maptest2.cub
execMandatory invalid/maptest30.cub
execMandatory invalid/maptest31.cub
execMandatory invalid/maptest32.cub
execMandatory invalid/maptest33.cub
execMandatory invalid/maptest34.cub
execMandatory invalid/maptest35.cub
execMandatory invalid/maptest36.cub
execMandatory invalid/maptest37.cub
execMandatory invalid/maptest38.cub
execMandatory invalid/maptest39.cub
execMandatory invalid/maptest3.cub
execMandatory invalid/maptest40.cub
execMandatory invalid/maptest41.cub
execMandatory invalid/maptest42.cub
execMandatory invalid/maptest43.cub
execMandatory invalid/maptest44.cub
execMandatory invalid/maptest45.cub
execMandatory invalid/maptest46.cub
execMandatory invalid/maptest47.cub
execMandatory invalid/maptest48.cub
execMandatory invalid/maptest49.cub
execMandatory invalid/maptest4.cub
execMandatory invalid/maptest5.cub
execMandatory invalid/maptest6.cub
execMandatory invalid/maptest7.cub
execMandatory invalid/maptest8.cub
execMandatory invalid/maptest9.cub
