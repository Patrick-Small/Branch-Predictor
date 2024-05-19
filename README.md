# Branch-Predictor
Written for CS_441 Computer Systems Architecture during the Spring semester of 2024 at SUNY Polytechnic Institute.

This C++ program is a branch predictor that operates on 4 models, the Fixed-False predictor, Static-First predictor, Bimodal Dynamic predictor, and the Two-layered Dynamic predictor. The program will take a branch trace file as it's only command line argument, and the trace file will consist of '@'s which indicate that the branch was taken, and '.'s which will indicate that the branch was not taken. The program will output each predictor's success ratio (correct pred/total branch count)
