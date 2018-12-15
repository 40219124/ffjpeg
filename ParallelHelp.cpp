#include "ParallelHelp.h"
#include <thread>

using namespace std;

int ParallelHelp::_threadCount = thread::hardware_concurrency();

ParallelHelp::ParallelHelp(){}


ParallelHelp::~ParallelHelp(){}
