#pragma once
#include <iostream>
#include <ctime>
struct date {
	struct tm information = {0};
	//============================================================
	//Date
	//day_of_week()
	//INPUT : 
	//OUTPUT : int
	//MEMO : �j������ [0�`6](��:0 ��:1 ��:2 ��:3 ��:4 ��:5 �y:6)
	//============================================================
	int day_of_week()
	{
		auto information = this->information;
		auto time = mktime(&information);
		information = *localtime(&time);
		return information.tm_wday;
	}
	//============================================================
	//Date
	//advance(int Day)
	//INPUT : int
	//OUTPUT : date
	//MEMO : �����Ŏw�肳�ꂽ���������t��i�߂�
	//============================================================
	date advance(int Day)
	{
		date nextdate;
		const time_t ONE_DAY = 24 * 60 * 60 ;
		auto time = mktime(&(this->information)) + (Day * ONE_DAY);
		nextdate.information = *localtime(&time);
		return nextdate;
	}

};