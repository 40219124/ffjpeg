#pragma once
class ParallelHelp
{
public:
	ParallelHelp();
	~ParallelHelp();

	static int ThreadCount() { return _threadCount; }

private:
	static int _threadCount;
};

