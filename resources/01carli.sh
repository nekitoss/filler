make -C ../
echo "#######################################################################"
echo "PLAYING AS PLAYER1"
echo "#######################################################################"
./filler_vm -f map01 -p1 ../filler -p2 ./carli.filler -q
./filler_vm -f map01 -p1 ../filler -p2 ./carli.filler -q
./filler_vm -f map01 -p1 ../filler -p2 ./carli.filler -q
./filler_vm -f map01 -p1 ../filler -p2 ./carli.filler -q
./filler_vm -f map01 -p1 ../filler -p2 ./carli.filler -q

echo "#######################################################################"
echo "PLAYING AS PLAYER2"
echo "#######################################################################"
./filler_vm -f map01 -p2 ../filler -p1 ./carli.filler -q
./filler_vm -f map01 -p2 ../filler -p1 ./carli.filler -q
./filler_vm -f map01 -p2 ../filler -p1 ./carli.filler -q
./filler_vm -f map01 -p2 ../filler -p1 ./carli.filler -q
./filler_vm -f map01 -p2 ../filler -p1 ./carli.filler -q
