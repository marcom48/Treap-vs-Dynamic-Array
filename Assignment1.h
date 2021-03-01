
#include "Generator.h"

#define PROB_RANGE 1000

#define SEQ_LEN 1000000

#define DELETION_THRESH 50
#define SEARCH_THRESH 100

#define EXP_1 1
#define EXP_2 2
#define EXP_3 3
#define EXP_4 4

vector<Instruction> insert_exp(Generator generator, int n);
vector<Instruction> gen_sequence(Generator generator, int threshold, Actions action);
vector<Instruction> gen_mixed_sequence(Generator generator, int param);
long double get_time(chrono::high_resolution_clock::time_point start, chrono::high_resolution_clock::time_point stop);
void run_sequence(vector<Instruction> sequence);
