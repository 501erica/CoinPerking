#pragma once
#include <iostream>
//tm�\���̂ɂ��Ă���F�X�ƏC�����K�v
struct date {
	struct tm information = {0};
	enum month {
		January,
		Febrary,
		March,
		April,
		May,
		June,
		July,
		August,
		September,
		Octorber,
		November,
		December
	};
	int day_of_week() {
		if (this->information.tm_mon < month::March) {
			this->information.tm_year--;
			this->information.tm_mon += 12;
		}
		int dayofweek = (this->information.tm_year + this->information.tm_year / 4 - this->information.tm_year / 100 + this->information.tm_year / 400 + (13 * this->information.tm_mon + 8) / 5 + this->information.tm_mday) % 7;
		return dayofweek;
	}
	bool is_leap_year(int y)
	{
		y += 1900;
		if (y % 4 == 0 && y % 100 != 0 || y % 400 == 0) { //[4�Ŋ���؂��]����[100�Ŋ���؂�Ȃ��A�܂���400�Ŋ���؂��]
			return true;
		}
		else {
			return false;
		}
	}
	//y�Nm���Ɋ܂܂��������v�Z����֐�
	int num_days_in_month(int y, int m)
	{
		int days = 0;
		if (is_leap_year(y) == true && m == month::Febrary) { //���邤�N��2���̂Ƃ�
			days = 28;
		}
		else if (is_leap_year(y) == false && m == month::Febrary) { //���邤�N�ł͂Ȃ�2��
			days = 29;
		}
		else if (m == month::April || m == month::June || m == month::September || m == month::November) { //�S���A�U���A�X���A�P�P���̂Ƃ�
			days = 30;
		}
		else { //��L�ȊO
			days = 31;
		}
		return days;
	}
	struct date advance(int Day)
	{
		struct date nextDate = *this;
		nextDate.information.tm_mday += Day;
		while (nextDate.information.tm_mday > num_days_in_month(nextDate.information.tm_year, nextDate.information.tm_mon)) { //���̌��̓������day���������Ȃ�܂ŌJ��Ԃ�(day�͌����Ă���)
			nextDate.information.tm_mday -= num_days_in_month(nextDate.information.tm_year, nextDate.information.tm_mon);
			if ((nextDate.information.tm_mon++) > 11 ){ //12���܂ł�������1���ɖ߂�
				nextDate.information.tm_year++;
				nextDate.information.tm_mon = 0;
			}
		}
		return nextDate;
	}

};