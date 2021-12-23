#pragma once
#include <iostream>
//tm構造体にしてから色々と修正が必要
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
		if (y % 4 == 0 && y % 100 != 0 || y % 400 == 0) { //[4で割り切れる]かつ[100で割り切れない、または400で割り切れる]
			return true;
		}
		else {
			return false;
		}
	}
	//y年m月に含まれる日数を計算する関数
	int num_days_in_month(int y, int m)
	{
		int days = 0;
		if (is_leap_year(y) == true && m == month::Febrary) { //うるう年で2月のとき
			days = 28;
		}
		else if (is_leap_year(y) == false && m == month::Febrary) { //うるう年ではない2月
			days = 29;
		}
		else if (m == month::April || m == month::June || m == month::September || m == month::November) { //４月、６月、９月、１１月のとき
			days = 30;
		}
		else { //上記以外
			days = 31;
		}
		return days;
	}
	struct date advance(int Day)
	{
		struct date nextDate = *this;
		nextDate.information.tm_mday += Day;
		while (nextDate.information.tm_mday > num_days_in_month(nextDate.information.tm_year, nextDate.information.tm_mon)) { //その月の日数よりdayが小さくなるまで繰り返す(dayは減っていく)
			nextDate.information.tm_mday -= num_days_in_month(nextDate.information.tm_year, nextDate.information.tm_mon);
			if ((nextDate.information.tm_mon++) > 11 ){ //12月までいったら1月に戻る
				nextDate.information.tm_year++;
				nextDate.information.tm_mon = 0;
			}
		}
		return nextDate;
	}

};