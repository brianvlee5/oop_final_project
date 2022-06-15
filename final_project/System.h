#pragma once
class System 
{
public:
	System();
	System(bool f);
	int init();
	void close();
private:
	bool failed;
};