dir="/home/xunjian1/Documents/CS484/project/"

####set up OMP environment parameters#####
export OMP_NUM_THREADS=12
export OMP_PROC_BIND=true

###define pachi commands##
white=$dir"pachi_warren/pachi -e montecarlo -t _10"
black="pachi -e montecarlo -t _10"

##remove outputfiles from previous run##
#rm test.summary.dat
#rm test.html
rm test*

## play multiple games##
gogui-twogtp -black "$black" -white "$white" -size 9 -auto -games 10 -sgffile test -time 10 -verbose >gtg_output.txt 2>&1

##generate human readable html output file##
gogui-twogtp -analyze test.dat
