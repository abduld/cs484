dir=`pwd`

####set up OMP environment parameters#####
# export OMP_NUM_THREADS=12
export OMP_PROC_BIND=true

###define pachi commands##
white="${dir}/code/pachi -e montecarlo -t _10 -T 12"
black="${dir}/code/pachi -e montecarlo -t _10 -T 12"

##remove outputfiles from previous run##
#rm test.summary.dat
#rm test.html
rm -f test*


goguitwogtp="${dir}/gogui/bin/gogui-twogtp"

## play multiple games##
games=1
${goguitwogtp} -black "${black}" -white "${white}" -size 9 -auto -games ${games} -sgffile test -time 10 -verbose >gtg_output.txt 2>&1

##generate human readable html output file##
${goguitwogtp} -analyze test.dat
