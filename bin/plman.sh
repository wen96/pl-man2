if [ $# > 1 ]
then
	./MasterMan $2 &
else
	./MasterMan &
fi
./MasterServer $1
