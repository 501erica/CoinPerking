#pragma once
#include <iostream>
#include <ctime>
//tm�\���̂ɂ��Ă���F�X�ƏC�����K�v
struct date {
	struct tm information = {0};
	//y�Nm���Ɋ܂܂��������v�Z����֐�
	int day_of_week()
	{
		auto information = this->information;
		auto time = mktime(&information);
		information = *localtime(&time);
		//�j��[0�`6](��:0 ��:1 ��:2 ��:3 ��:4 ��:5 �y:6)
		return information.tm_wday;
	}
	date advance(int Day)
	{
		date nextdate;
		const time_t ONE_DAY = 24 * 60 * 60 ;
		auto time = mktime(&(this->information)) + (Day * ONE_DAY);
		nextdate.information = *localtime(&time);
		return nextdate;
	}

};