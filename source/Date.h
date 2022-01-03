#pragma once
#include <iostream>
#include <ctime>
//tm構造体にしてから色々と修正が必要
struct date {
	struct tm information = {0};
	//y年m月に含まれる日数を計算する関数
	int day_of_week()
	{
		auto information = this->information;
		auto time = mktime(&information);
		information = *localtime(&time);
		//曜日[0〜6](日:0 月:1 火:2 水:3 木:4 金:5 土:6)
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