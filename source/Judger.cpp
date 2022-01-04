#include "Judger.h"
#include "Mode.h"
#include "Date.h"
#include <vector>
#include <regex>

Judger* Judger::judger = nullptr;
//============================================================
//Judger
//Judgeri()
//INPUT :
//OUTPUT :
//MEMO : �R���X�g���N�^
//============================================================
Judger::Judger()
{
}
//============================================================
//Judger
//~Judger
//INPUT : 
//OUTPUT : 
//MEMO : �f�X�g���N�^
//============================================================
Judger::~Judger()
{
}
//============================================================
//Judger
//getInstance()
//INPUT : 
//OUTPUT : Judger*
//MEMO : �V���O���g���p�N���X�Q�ƃ��\�b�h
//============================================================
Judger* Judger::getInstance()
{
    if (!Judger::judger) {
        Judger::judger = new Judger();
    }
    return nullptr;
}
//============================================================
//Judger
//judge(struct date)
//INPUT : struct date
//OUTPUT : CalculateMode
//MEMO : �����̓��t�̃��[�h����
//============================================================
CalculateMode Judger::judge(date date)
{
    std::vector<std::pair<int,int>> specialdaylist;
    specialdaylist.push_back(std::make_pair(8,13));
    specialdaylist.push_back(std::make_pair(8,14));
    specialdaylist.push_back(std::make_pair(8,15));
    specialdaylist.push_back(std::make_pair(12,31));
    specialdaylist.push_back(std::make_pair(1,1));
    specialdaylist.push_back(std::make_pair(1,2));
    specialdaylist.push_back(std::make_pair(1,3));

    if(date.day_of_week() == 0 || date.day_of_week() == 6){
        return CalculateMode::SPECIAL_DAY;
    }
    for(int i = 0; i < specialdaylist.size();i++){
        if((date.information.tm_mon + 1 == specialdaylist.at(i).first) && (date.information.tm_mday == specialdaylist.at(i).second)){
            return CalculateMode::SPECIAL_DAY;
        }
    }

    if(date.information.tm_hour < 7){
        return CalculateMode::NIGHT;
    }
    if(22 <= date.information.tm_hour){
        return CalculateMode::NIGHT;
    }
    return CalculateMode::NOON;
}
//============================================================
//Judger
//judge(tm)
//INPUT : struct tm 
//OUTPUT : bool
//MEMO : �p�r�s��
//============================================================
bool Judger::judge(struct tm Intime ,struct tm OutTime)
{
    return false;
}
//============================================================
//Judger
//judge(std::string, std::string)
//INPUT : string,string
//OUTPUT : bool
//MEMO : ���͒l����
//============================================================
bool Judger::judge(std::string InDate, std::string OutDate)
{
	auto rx = std::regex{ R"((\d{4})(\.|-|/)(\d{2})(\.|-|/)(\d{2})(\.|-|/| )(\d{2})(:|-|/)(\d{2}))" };
	if (!(std::regex_match(InDate.c_str(), rx) && std::regex_match(OutDate.c_str(), rx))) { 
	    std::cout << "input error write yyyy/mm/dd-hh:mm " << std::endl;
        return false;
    }

    struct date Indate,Outdate;
    Indate.information.tm_year = stoi(std::regex_replace(InDate.c_str(), rx, "$1")) - 1900;
    Indate.information.tm_mon = stoi(std::regex_replace(InDate.c_str(), rx, "$3")) - 1;
    Indate.information.tm_mday = stoi(std::regex_replace(InDate.c_str(), rx, "$5"));
    Indate.information.tm_hour = stoi(std::regex_replace(InDate.c_str(), rx, "$7"));
    Indate.information.tm_min = stoi(std::regex_replace(InDate.c_str(), rx, "$9"));
    Indate.information.tm_isdst = -1;

    Outdate.information.tm_year = stoi(std::regex_replace(OutDate.c_str(), rx, "$1")) - 1900;
    Outdate.information.tm_mon = stoi(std::regex_replace(OutDate.c_str(), rx, "$3")) - 1;
    Outdate.information.tm_mday = stoi(std::regex_replace(OutDate.c_str(), rx, "$5"));
    Outdate.information.tm_hour = stoi(std::regex_replace(OutDate.c_str(), rx, "$7"));
    Outdate.information.tm_min = stoi(std::regex_replace(OutDate.c_str(), rx, "$9"));
    Outdate.information.tm_isdst = -1;

    time_t Intime = mktime(&Indate.information);
    time_t Outtime = mktime(&Outdate.information);
    time_t now = time(nullptr);

    if((Outtime - Intime) > 72*3600){
        std::cout << "over 72h" << std::endl;
        return false;
    }

    if(Intime >= Outtime){
        std::cout << "sametime or Intime > Outtime" << std::endl;
        return false;
    }
    
    if(now > Intime){
        std::cout << "Intime past time" << std::endl;
        return false;
    }


    return true;
}


