#include "Judger.h"
#include "Mode.h"
#include "Date.h"
#include <vector>
#include <regex>

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
//judge(std::string, std::string)
//INPUT : string,string
//OUTPUT : bool
//MEMO : ���͒l����
//============================================================
bool Judger::judge(std::string InDate, std::string OutDate)
{
	auto rx = std::regex{ R"((\d{4})(\.|-|/)(\d{2})(\.|-|/)(\d{2})(\.|-|/| )(\d{2})(:|-|/)(\d{2}))" };
	if (!(std::regex_match(InDate.c_str(), rx) && std::regex_match(OutDate.c_str(), rx))) { 
	    std::cout << "���͌`�����s���ł��B�ȉ��̌`���œ����𔼊p�œ��͂��Ă�������" << "yyyy/mm/dd-hh:mm" << std::endl;
        return false;
    }

    auto rx2 = std::regex{ R"(([1-2][0-9][0-9][0-9])(\.|-|/)(0[1-9]|1[0-2])(\.|-|/)(0[1-9]|[12][0-9]|3[01])(\.|-|/| )([01][0-9]|2[0-3])(:|-|/)([0-5][0-9]))" };
    if (!(std::regex_match(InDate.c_str(), rx2) && std::regex_match(OutDate.c_str(), rx2))) {
        std::cout << "���͌`�����s���ł��B���͔N��1000~2999,���͌���01~12,���͓���01~31�œ��͂��Ă��������B" << std::endl;
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
        std::cout << "�ő咓�Ԏ��ԁi72���ԁj�𒴂���������w�肳��Ă��܂��B" << std::endl;
        return false;
    }

    if(Intime > Outtime){
        std::cout << "�����w�肪�s���ł��B�o�ɓ����ɓ��Ɏ������ߋ��̎��Ԃ��w�肳��Ă��܂��B" << std::endl;
        return false;
    }

    if(Intime == Outtime){
        std::cout << "�����w�肪�s���ł��B���ɁE�o�ɓ����������ł��B" << std::endl;
        return false;
    }
    
    if(now > Intime){
        std::cout << "�����w�肪�s���ł��B�{�����ߋ��̓������w�肳��Ă��܂��B" << std::endl;
        return false;
    }

    return true;
}


