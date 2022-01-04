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
	//MEMO : 曜日判定 [0〜6](日:0 月:1 火:2 水:3 木:4 金:5 土:6)
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
	//MEMO : 引数で指定された数だけ日付を進める
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