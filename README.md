# Agent-Potts-Simulator

This is the repository for the agent-potts-simulator.

## Installation and first run

For windows:

1. The simulator runs on top of the [FLAME framework](http://www.flame.ac.uk/).
Go to [their website](http://www.flame.ac.uk/docs/install.html) for installing instructions of FLAME.

2. Run Xparser (part of FLAME) to generate a make-file and some missing C-source-code
    xparser.exe .\model\directory\freepotcell.xml
    
3. copy the libmboard-directory into your .\model\directory\libmboard

4. compile the project with gcc
    make -B

5. generate initial configuration file or use existing one (.\its\0.xml).
The initial configuration file contains the positions and variables of all cells at time 0
    
5. run main.exe
    main.exe <number of iterations> <path to initial configuration e.g. .\its\0.xml> <partitions> -f <write result every Xth timestep>
    main.exe 10000 .\its\0.xml 4 -f 100
    
Parallel execution works best under linux.
Requires MPI (best: [MPICH](http://www.mpich.org/) )
and [pthreads](https://en.wikipedia.org/wiki/POSIX_Threads).
Add the flag -p and adjust partitions to at least the number of processors you have availible.


