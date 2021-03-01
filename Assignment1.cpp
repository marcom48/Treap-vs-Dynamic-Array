/*
Author: Marco Marasco 834482.

Description: Program is the control program for simulating the required 
experiments for Assignment 1 (COMP90077). The program reads in command line
arguments and runs the desired experiment accordingly. The first argument
is the experiment number, the second is the parameter for the execution.

Examples for each experiment are below:
Experiment 1 (n = 1000): ./prog 1 1000
Experiment 2 (percentage = 5): ./prog 2 50
Experiment 3 (percentage = 10): ./prog 3 100
Experiment 4 (n = 2000): ./prog 4 2000

*/
#include "Assignment1.h"

int main(int argc, char const *argv[])
{

    // Seed pseudo-random number generator.
    srand(time(0));

    Generator generator;

    vector<Instruction> sequence;

    // Read experiment number.
    istringstream iss(argv[1]);
    int exp_no;
    iss >> exp_no;

    // Read experiment parameter.
    istringstream iss1(argv[2]);
    int param;

    if (iss1 >> param)
    {
        // Print experiment details for recording.
        cout << "Exp_" << exp_no << "," << param << ",";

        switch (exp_no)
        {
        case EXP_1:
            sequence = insert_exp(generator, param);
            break;

        case EXP_2:
            sequence = gen_sequence(generator, param, DELETION);
            break;

        case EXP_3:
            sequence = gen_sequence(generator, param, SEARCH);
            break;

        case EXP_4:
            sequence = gen_mixed_sequence(generator, param);
            break;

        default:
            cout << "Incorrect input." << endl;
            return 0;
        }

        // Run sequence of operations.
        run_sequence(sequence);
    }
    else
    {
        cout << "Incorrect input." << endl;
    }

    return 0;
}

/*
Method creates sequence of n insertion operations for Experiment 1.
*/
vector<Instruction> insert_exp(Generator generator, int n)
{

    vector<Instruction> sequence;

    for (int i = 0; i < n; i++)
    {
        sequence.push_back(generator.gen_insertion());
    }

    return sequence;
}

/*
Method is passed an operation type, a desired frequency threshold,
and returns sequence of pseudo-randomly generated operations.
*/
vector<Instruction> gen_sequence(Generator generator, int threshold, Actions action)
{

    int prob;

    vector<Instruction> sequence;

    for (int i = 0; i < SEQ_LEN; i++)
    {
        // Generate random value in [1, 1000] to determine what operation to call.
        prob = 1 + rand() % PROB_RANGE;

        // Insert operation specific to experiment.
        if (prob <= threshold)
        {

            if (action == SEARCH)
            {
                sequence.push_back(generator.gen_search());
            }
            else
            {
                sequence.push_back(generator.gen_deletion());
            }
        }
        else
        {
            sequence.push_back(generator.gen_insertion());
        }
    }
    return sequence;
}

/*
Method return a pseudo-randomly operation of n sequences, with roughly:
5% search; 5% deletion; 95% insertions.
*/
vector<Instruction> gen_mixed_sequence(Generator generator, int n)
{

    int prob;

    vector<Instruction> sequence;

    for (int i = 0; i < n; i++)
    {
        prob = 1 + rand() % PROB_RANGE;
        if (prob <= DELETION_THRESH)
        {
            sequence.push_back(generator.gen_deletion());
        }
        else if (prob <= SEARCH_THRESH)
        {
            sequence.push_back(generator.gen_search());
        }
        else
        {
            sequence.push_back(generator.gen_insertion());
        }
    }

    return sequence;
}

/*
Method returns time elapsed between two recorded events.
*/
long double get_time(chrono::high_resolution_clock::time_point start,
                     chrono::high_resolution_clock::time_point stop)
{
    chrono::duration<long double> elapsed = stop - start;
    return elapsed.count();
}

/*
Method runs input sequence of operations on data structures and
prints runtime results.
*/
void run_sequence(vector<Instruction> sequence)
{

    // Initiliase data structures.
    Treap treap;
    DynamicArray arr;

    // Initialise runtime counters.
    long double treap_time = 0.0;
    long double arr_time = 0.0;

    auto start = chrono::high_resolution_clock::now();
    auto stop = chrono::high_resolution_clock::now();

    // Iterate over sequence.
    for (Instruction i : sequence)
    {
        // Determine what type of operation is required.
        switch (i.action)
        {

        case INSERT:

            // Record start time.
            start = chrono::high_resolution_clock::now();

            // Run operation.
            treap.insert(i.el);

            // Record stop time.
            stop = chrono::high_resolution_clock::now();

            // Update runtime counter.
            treap_time += get_time(start, stop);

            start = chrono::high_resolution_clock::now();
            arr.insert(i.el);
            stop = chrono::high_resolution_clock::now();
            arr_time += get_time(start, stop);

            break;

        case DELETION:

            start = chrono::high_resolution_clock::now();
            treap.delete_key(i.key);
            stop = chrono::high_resolution_clock::now();
            treap_time += get_time(start, stop);

            start = chrono::high_resolution_clock::now();
            arr.delete_key(i.key);
            stop = chrono::high_resolution_clock::now();
            arr_time += get_time(start, stop);

            break;

        case SEARCH:

            start = chrono::high_resolution_clock::now();
            treap.search(i.key);
            stop = chrono::high_resolution_clock::now();
            treap_time += get_time(start, stop);

            start = chrono::high_resolution_clock::now();
            arr.search(i.key);
            stop = chrono::high_resolution_clock::now();
            arr_time += get_time(start, stop);

            break;
        }
    }

    // Print results in csv format.
    cout << fixed << treap_time << "," << arr_time;
}