#include "ModeCounter.h"
#include "Mode.h"
#include <iostream>

ModeCounter::ModeCounter()
{
	modejudger = Judger::getInstance();
	this->startDate = {0};
	this->endDate = {0};

}

ModeCounter::~ModeCounter()
{
}

ModeCounter::ModeCounter(struct date InDate, struct date OutDate)
{
	modejudger = Judger::getInstance();
	this->startDate = InDate;
	this->endDate = OutDate;
}

void ModeCounter::ModeCount(std::vector<CostCalculator*>& cost)//��Ԃ��邢�Ƃ�
{
	while (ModeCounter::evalDate(this ->startDate,this -> endDate)) {
		//startDate�������[�h������i�r���j
		CalculateMode mode = modejudger->judge(this -> startDate);
	
		//startDate�����ԋ߂������؂�ւ��������v�Z�i�r���j
		date nextDate = this->startDate;
		if (mode == NOON) {
			nextDate.information.tm_hour = 22;
			nextDate.information.tm_min = 0;
		}
		else if (mode == NIGHT) {
			if (this->startDate.information.tm_hour >= 22) {
				if (modejudger->judge(this->startDate.advance(1)) == SPECIAL_DAY) {
					nextDate = this->startDate.advance(1);
					nextDate.information.tm_hour = 0;
					nextDate.information.tm_min = 0;
				}
				else {
					nextDate.information.tm_hour =7;
					nextDate.information.tm_min = 0;
				}
			}
		}
		else if (mode == SPECIAL_DAY) {
			nextDate = this->startDate.advance(1);
			nextDate.information.tm_hour = 0;
			nextDate.information.tm_min = 0;
		}
		else {
			std::cout << "�����ςȂ̂�ModeCounter.cpp����������";
		}
		//nextDate�̕����傫���ꍇ
		if (ModeCounter::evalDate(this->endDate , nextDate)) {
			nextDate = this->endDate;
		}

		time_t startTime = mktime(&(this->startDate.information));
		time_t nextTime = mktime(&(nextDate.information));

		int minitus = difftime(nextTime, startTime) / 60;

		//vector�ɓ˂�����
		cost.push_back(CreateCostCalculator(mode,minitus));
		//startDate���X�V
		this->startDate.information = nextDate.information;
		//updateStartDate(this->startDate,mode);
	}

}

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

bool ModeCounter::evalDate(date startDate, date endDate)//endDate�̕����f�J��������TRUE
{
	time_t startTime = mktime(&startDate.information);
	time_t endTime = mktime(&(endDate.information));
	if (difftime(startTime, endTime) < 0) {
		return true;
	}
	return false;
}

struct date evalBorderDate(enum CalculateMode mode) {
	struct date borderDate;
	/*switch (mode) {
	case NOON:
	case NIGHT:
	case SPECIAL_DAY:
	}
	*/
	return borderDate;
}







