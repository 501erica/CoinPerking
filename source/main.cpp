#include<iostream>
#include <string>
#include <regex>
#include "Proxy.h"
#include "Judger.h"

int main(int argc, char** argv) {

	//���X������
	std::string InDate;
	std::string OutDate;
	enum answer {
		CONTINUE,
		END
	};

	bool LoopFlag = false;
	do {
		//���͏���
		std::cout << "���ɓ�������͂��Ă��������i2021�N01��15���̏ꍇ�F2021/01/15-11:05�j";
		std::cin >> InDate;
		std::cout << std::endl;
		std::cout << "�o�ɓ�������͂��Ă��������i2021�N01��15���̏ꍇ�F2021/01/15-11:05�j";
		std::cin >> OutDate;
		std::cout << std::endl;
		Judger* inputJudger = new Judger();;

		//���͒l�ɖ��Ȃ��H
		if((inputJudger->judge(InDate,OutDate))){
			//�v�Z�`�����\�����{
			Proxy * p_Proxy = new Proxy(InDate,OutDate);
			delete p_Proxy;
		}

		delete inputJudger;

		//�p���m�F
		std::cout << "�������p�����܂����H" << std::endl;
		std::cout << "�p���Fy�@�I���Fn" << std::endl;
		std::string answer;
		std::cin >> answer;
		auto rx = std::regex{ R"(([yY]))" };
		if (std::regex_match(answer.c_str(), rx)) {
			LoopFlag = true;
		}
		else {
			LoopFlag = false;
		}
	} while (LoopFlag);

	return 0;
}