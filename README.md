# filler

Program-player for virtual machine in resources folder.
This game looks like tetris, but rules are different. You have a field with two start points for two players (O and X) and empty places as dots. You get a random figure, which you have to place on field, but one and only one block of it must be connected to previous block. Goal is to put as many figures, as possible. If you cannot place figure - you wont get figures any more. Game ends when last player cannot put figure.

To clone with submodule:

git clone https://github.com/nekitoss/ft_printf.git

git submodule init

git submodule update

To run:

make

then pass to virtual machine players, maps and parameters.
To run my player with carli bot on map00 (you can find it in folder maps), run:

./resources/filler_vm -f ./resources/maps/map00 -p1 ./filler -p2 ./resources/carli.filler
