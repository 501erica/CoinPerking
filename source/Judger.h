#pragma once
#include "Mode.h"
#include "Date.h"

class Judger
{
public:
	//static Judger* getInstance();
	//static Judger* judger;
	Judger();
	~Judger();
	//���[�h����
	CalculateMode judge(struct date);
	//���t�̑召����
	bool judge(struct tm,struct tm);
	//���͒l����
	bool judge(std::string, std::string);

};
