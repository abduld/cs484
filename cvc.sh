#!/bin/sh
dir=`pwd`
pachi="${dir}/code/pachi"
black="${pachi} -t _100 -T 16 -e montecarlo"
white="${pachi} -t _100 -e montecarlo"
TWOGTP="${dir}/gogui/bin/gogui-twogtp -black \"$black\" -white \"$white\" -size 9"
echo $TWOGTP
gogui="${dir}/gogui/bin/gogui"
${gogui} -size 9 -program "$TWOGTP" -computer-both -auto
