HOW TO COMPILE
--------------
To compile the compiler:
cd src
make

Make sure you have installed the following packages:
bison
flex

If you trouble compiling, install gcc-multilib and try again:
sudo apt-get install gcc-multilib

If you still have problems, run the following command:
sudo ln -s /usr/lib/x86_64-linux-gnu /usr/lib64
