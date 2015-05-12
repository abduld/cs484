dir=`pwd`
goguitwogtp="${dir}/gogui/bin/gogui-twogtp"

for baseline_threads in 1 2 4 8
do
   for mpi_threads in 2 4 8 12
   do
      if [ ${mpi_threads} -gt ${baseline_threads} ]
      then
	###define pachi commands##
	white="mpiexec -np ${mpi_threads} ${dir}/code/pachi -e montecarlo_mpi -t _10 -T 1"
	if [ ${baseline_threads} -eq 1 ]
	then
		black="${dir}/code/pachi -e montecarlo_original -t _10"
	else
		black="mpiexec -np ${baseline_threads} ${dir}/code/pachi -e montecarlo_mpi -t _10 -T 1"
	fi
	for trial in 1 2
	do
		games=5
		${goguitwogtp} -black "${black}" -white "${white}" -size 9 -auto -games ${games} -sgffile test -time 10 -verbose >gtg_output.txt 2>&1
		${goguitwogtp} -analyze test.dat
		my_test="MPI_${mpi_threads}_vs_${baseline_threads}_${trial}"
		mkdir ${my_test}
		mv gtg_output.txt ./${my_test}/gtg_output.txt
		mv test* ./${my_test}/
	done
      fi
   done
done
