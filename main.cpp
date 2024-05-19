/*
    Patrick Small
    CS_441 Computer Architecture
    03/28/2024

    This C++ program is a branch predictor that operates on 4 models, the Fixed-False predictor,
    Static-First predictor, Bimodal Dynamic predictor, and the Two-layered Dynamic predictor.
    The program will take a branch trace file as it's only command line argument, and the trace
    file will consist of '@'s which indicate that the branch was taken, and '.'s which will
    indicate that the branch was not taken.
    The program will output each predictor's success ratio (correct pred/total branch count)
*/

/*
    TODO
    - Read in file [DONE]
    - Look through file and count every character first to get total branch count [DONE]
    - Get the first line [DONE]
    - Send it to each predictor [DONE]
        - Fixed-False [DONE]
        - Static-First [DONE]
        - Bimodal Dynamic [DONE]
        - Two-layered Bimodal Dynamic [DONE]
    - Loop through every single line until the eof [DONE]
    - Output the results [DONE]
    - Yippee [YIPPEE]
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Prototypes
int fixed_false(string);
int static_false(string);
int bimodal_dynamic(string);
int two_layered_bimodal_dynamic(string);


int main(int argc, char* argv[])
{

    //Check the input #
    if (argc != 2)
    {
        cerr << "Wrong number of inputs/no inputs" << endl;
    }

    //Opening and reading .tra file
    ifstream f(argv[1]);

    if (!f)
    {
        cerr << "Error: File cannot be opened" << endl;
    }

    //Declarations
    string trace;
    uint64_t totbra = 0;
    uint64_t totff = 0;
    uint64_t totsf = 0;
    uint64_t totbd = 0;
    uint64_t tottlbd = 0;
    


    //Loops until EOF
    while (getline(f, trace))
    {

        //Count the elements
        for (int i = 0; i < trace.length(); i++)
        {
            totbra++;
        }

        //Go do stuff
        totff += fixed_false(trace);
        totsf += static_false(trace);
        totbd += bimodal_dynamic(trace);
        tottlbd += two_layered_bimodal_dynamic(trace);

    }

    //Output results
    cout << "Fixed-F: " << totff << " / " << totbra << endl;
    cout << "StaticF: " << totsf << " / " << totbra << endl;
    cout << "Bimodal: " << totbd << " / " << totbra << endl;
    cout << "2-Layer: " << tottlbd << " / " << totbra << endl;

    return 0;
}

int fixed_false(string tra)
{

    //Local declarations
    int predcnt = 0;

    //Operating on data
    for (int i = 0; i < tra.length(); i++)
    {
        if (tra[i] == '.')
        {
            predcnt++;
        }
    }

    return predcnt;
}

int static_false(string tra)
{

    //Local declarations
    int predcnt = 0;
    char pred = '.';

    //Determining prediction
    if (tra[0] == '@')
    {
        pred = '@';
        predcnt--;
    }

    //Operating on data
    for (int i = 0; i < tra.length(); i++)
    {
        if (tra[i] == pred)
        {
            predcnt++;
        }
    }

    return predcnt;
}

int bimodal_dynamic(string tra)
{

    //Local declarations
    int predcnt = 0;
    int PE = 0b01;
    bool pred;

    //Operating on data
    for (int i = 0; i < tra.length(); i++)
    {
        //Get the prediction
        pred = PE & (1 << 1);

        //If true, reset error count
        if (pred == (tra[i] == '@'))
        {
            PE &= ~(1 << 0);
            predcnt++;
        }
        else
        {
            PE++;
        }

    }

    return predcnt;
}

int two_layered_bimodal_dynamic(string tra)
{

    //Local declarations
    int predcnt = 0;
    int PE[4] = {0b01, 0b11, 0b01, 0b11};
    int history = 0b00;
    bool pred;

    //Operating on data
    for (int i = 0; i < tra.length(); i++)
    {
        //Get the prediction
        pred = PE[history] & (1 << 1);

        //If true, reset error count
        if (pred == (tra[i] == '@'))
        {
            PE[history] &= ~(1 << 0);
            predcnt++;
        }
        else
        {
            PE[history]++;
        }

        //Update history
        history <<= 1;

        if (tra[i] == '@')
        {
            history |= 1 << 0;
        }

        history &= (1 << 1) | (1 << 0);

    }

    return predcnt;
}