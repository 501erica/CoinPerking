#include "Proxy.h"

//============================================================
//Proxy
//:Proxy()
//INPUT : 
//OUTPUT : 
//MEMO : �R���X�g���N�^
//============================================================
Proxy::Proxy()
{
}
//============================================================
//Proxy
//~Proxy()
//INPUT : 
//OUTPUT : 
//MEMO : �f�X�g���N�^
//============================================================
Proxy::~Proxy()
{
	delete p_ModeCounter;
}
//============================================================
//Proxy
//Proxy(std::string InDate, std::string OutDate)
//INPUT : string , string
//OUTPUT : 
//MEMO : �R���X�g���N�^
//============================================================
Proxy::Proxy(std::string InDate, std::string OutDate)
{
	//�����o�ϐ��̏�����
	this->Initialize(InDate, OutDate);
	//���͒l����(main�֐��ł��Ȃ����߂�)
	Judger* p_judger = Judger::getInstance();
	//===========�������Ă������񂶂�Ȃ���============
	//Mode�����J�E���g
	p_ModeCounter->ModeCount(ModeContainer);
	//�������v�Z���ĕ\��
	this->showCost();
}
//============================================================
//Proxy
//howCost()
//INPUT : 
//OUTPUT : 
//MEMO : �����\��
//============================================================
void Proxy::showCost()
{
	//vector�̗v�f�̗����v�Z���w��
	for (int i = 0; i < this -> ModeContainer.size(); i++) {
		this->Cost += this -> ModeContainer.at(i)->CostCalculate();
	}
	std::cout << "�����́@" << this->Cost << "�@�~�ł��B" << std::endl;
}

//============================================================
//Proxy
//Initialize(std::string InDate, std::string OutDate)
//INPUT : string , string
//OUTPUT : 
//MEMO : �����o�ϐ��̏�����
//============================================================
void Proxy::Initialize(std::string InDate, std::string OutDate)
{
	const auto rx = std::regex{ R"((\d{4})(\.|-|/)(\d{2})(\.|-|/)(\d{2})(\.|-|/| )(\d{2})(:|-|/)(\d{2}))" };

	this->InDate.information.tm_year = stoi(std::regex_replace(InDate.c_str(), rx, "$1")) - 1900;
	this->InDate.information.tm_mon = stoi(std::regex_replace(InDate.c_str(), rx, "$3")) - 1;
	this->InDate.information.tm_mday = stoi(std::regex_replace(InDate.c_str(), rx, "$5"));
	this->InDate.information.tm_hour = stoi(std::regex_replace(InDate.c_str(), rx, "$7"));
	this->InDate.information.tm_min = stoi(std::regex_replace(InDate.c_str(), rx, "$9"));
	this->InDate.information.tm_isdst = -1;

	this->OutDate.information.tm_year = stoi(std::regex_replace(OutDate.c_str(), rx, "$1")) - 1900;
	this->OutDate.information.tm_mon = stoi(std::regex_replace(OutDate.c_str(), rx, "$3")) - 1;
	this->OutDate.information.tm_mday = stoi(std::regex_replace(OutDate.c_str(), rx, "$5"));
	this->OutDate.information.tm_hour = stoi(std::regex_replace(OutDate.c_str(), rx, "$7"));
	this->OutDate.information.tm_min = stoi(std::regex_replace(OutDate.c_str(), rx, "$9"));
	this->OutDate.information.tm_isdst = -1;

	this -> p_ModeCounter = new ModeCounter(this->InDate, this->OutDate);

}