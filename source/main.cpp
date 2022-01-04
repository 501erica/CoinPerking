#include<iostream>
#include <string>
#include <regex>
#include "Proxy.h"
#include "Status.h"
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
		std::cout << "���Ɏ�������͂��Ă��������i2021�N01��15���̏ꍇ�F2021/01/15-11:05�j";
		//std::getline(std::cin, InDate);
		std::cin >> InDate;
		std::cout << std::endl;
		std::cout << "�o�Ɏ�������͂��Ă��������i2021�N01��15���̏ꍇ�F2021/01/15-11:05�j";
		//std::getline(std::cin , OutDate);
		std::cin >> OutDate;
		std::cout << std::endl;
		Judger* inputJudger = Judger::getInstance();

		//���͒l�ɖ��Ȃ��H
		if((inputJudger->judge(InDate,OutDate))){
			//�v�Z�`�����\�����{
			Proxy * p_Proxy = new Proxy(InDate,OutDate);
			delete p_Proxy;
		}

		//�p���m�F
		std::cout << "�������p�����܂����H" << std::endl;
		std::cout << "�p���F0�@�I���F0�ȊO" << std::endl;
		int answer;
		std::cin >> answer;
		if(std::cin.fail()){
			std::cin.clear();
			std::cin.ignore( 256, '\n' );
			std::cout << "answer is not Integer" << std::endl;
			answer = 1;
		}
		switch (answer) {
		case CONTINUE:
			LoopFlag = true;
			break;
		case END:
			LoopFlag = false;
			break;
		default:
			std::cout << "�����������������I�����܂�����������" << std::endl;
			LoopFlag = false;
			break;
		}

	} while (LoopFlag);

	return 0;
}