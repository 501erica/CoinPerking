#include "ModeCounter.h"
#include "Mode.h"
#include <iostream>
#include <time.h>

//============================================================
//ModeCounter
//ModeCounter()
//INPUT : 
//OUTPUT : 
//MEMO : �R���X�g���N�^
//============================================================
ModeCounter::ModeCounter()
{
	modejudger = Judger::getInstance();
	this->startDate = {0};
	this->endDate = {0};

}
//============================================================
//ModeCounter
//~ModeCounter()
//INPUT : 
//OUTPUT : 
//MEMO : �f�X�g���N�^
//============================================================
ModeCounter::~ModeCounter()
{
}
//============================================================
//ModeCounter
//ModeCounter(struct date InDate, struct date OutDate)
//INPUT : struct date ,struct date
//OUTPUT : 
//MEMO : �R���X�g���N�^
//============================================================
ModeCounter::ModeCounter(struct date InDate, struct date OutDate)
{
	modejudger = Judger::getInstance();
	this->startDate = InDate;
	this->endDate = OutDate;
}
//============================================================
//ModeCounter
//ModeCount(std::vector<CostCalculator*>& cost)
//INPUT : vector<CostCaluculator*>
//OUTPUT : 
//MEMO : ���ꎞ���Ƒޏꎞ�����烂�[�h(���E��E���ʓ�)�̌����v�Z
//============================================================
void ModeCounter::ModeCount(std::vector<CostCalculator*>& cost)
{
	while (ModeCounter::evalDate(this ->startDate,this -> endDate)) {
		//startDate�������[�h������
		CalculateMode mode = modejudger->judge(this -> startDate);
	
		//startDate�����ԋ߂������؂�ւ��������v�Z
		date nextDate = this->evalBorderDate(mode);
		//nextDate�̕����傫���ꍇ
		if (ModeCounter::evalDate(this->endDate , nextDate)) {
			nextDate = this->endDate;
		}

		//���[�h�̎����Z�o
		time_t startTime = mktime(&(this->startDate.information));
		time_t nextTime = mktime(&(nextDate.information));
		int minitus = difftime(nextTime, startTime) / 60;

		//vector�ɓ˂�����
		cost.push_back(CreateCostCalculator(mode,minitus));
		//startDate���X�V
		this->startDate.information = nextDate.information;
	}
}
//============================================================
//ModeCounter
//CreateCostCalculator(CalculateMode mode,int minitus)
//INPUT : CalculateMode mode,int minitus
//OUTPUT : CreateCostCalculator*
//MEMO : ���[�h�A���ɉ�����CreateCostCalculator*���쐬
//============================================================
CostCalculator* ModeCounter::CreateCostCalculator(CalculateMode mode,int minitus)
{
	switch (mode) {
	case CalculateMode::NOON:
		return new CostCalculator_Noon(minitus);
		break;
	case CalculateMode::NIGHT:
		return  new CostCalculator_Night(minitus);
		break;
	case CalculateMode::SPECIAL_DAY:
		return  new CostCalculator_SpecialDay(minitus);
		break;
	default:
		return nullptr;
		std::cout << "ModeError" << std::endl;
	}
}
//============================================================
//ModeCounter
//evalDate(date startDate, date endDate)
//INPUT : struct date,struct date
//OUTPUT : bool
//MEMO : startDate < endDate �̏ꍇture
//============================================================
bool ModeCounter::evalDate(date startDate, date endDate)
{
	time_t startTime = mktime(&startDate.information);
	time_t endTime = mktime(&(endDate.information));
	if (difftime(startTime, endTime) < 0) {
		return true;
	}
	return false;
}
//============================================================
//ModeCounter
//evalBorderDate(enum CalculateMode mode)
//INPUT : enum CalculateMode
//OUTPUT : struct date
//MEMO : startDate����ŒZ�̃��[�h�ύX�������Z�o
//============================================================
struct date ModeCounter::evalBorderDate(enum CalculateMode mode) {
	struct date nextDate = this->startDate;
	switch (mode) {
	case CalculateMode::NOON:
		nextDate.information.tm_hour = 22;
		nextDate.information.tm_min = 0;
		break;
	case CalculateMode::NIGHT:
		if (this->startDate.information.tm_hour >= 22) {
			if (modejudger->judge(this->startDate.advance(1)) == SPECIAL_DAY) {
				nextDate = this->startDate.advance(1);
				nextDate.information.tm_hour = 0;
				nextDate.information.tm_min = 0;
				break;
			}
			nextDate = this->startDate.advance(1);
			nextDate.information.tm_hour =7;
			nextDate.information.tm_min = 0;
			break;
		}
		nextDate.information.tm_hour =7;
		nextDate.information.tm_min = 0;
		break;
	case CalculateMode::SPECIAL_DAY:
		nextDate = this->startDate.advance(1);
		nextDate.information.tm_hour = 0;
		nextDate.information.tm_min = 0;
		break;
	default:
	break;
	}
	return nextDate;
}