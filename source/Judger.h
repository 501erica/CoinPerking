#pragma once
#include "Status.h"
#include "Mode.h"
#include "Date.h"

class Judger
{
public:
	static Judger* getInstance();
	static Judger* judger;
	//���[�h����
	CalculateMode judge(struct date);
	//���t�̑召����
	bool judge(struct tm);
	//���͒l����
	bool judge(std::string, std::string);
private:
	Judger();
	~Judger();
};
