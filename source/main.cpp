#include<iostream>
#include <string>
#include <regex>
#include "Proxy.h"
#include "Status.h"
#include "Judger.h"

int main(int argc, char** argv) {//Status�ŐF�X�撣��

	//���X������
	std::string InDate;
	std::string OutDate;
	enum answer {
		CONTINUE,
		END
	};
	auto rx = std::regex{ R"((\d{4})(\.|-|/)(\d{2})(\.|-|/)(\d{2})(\.|-|/)(\d{2})(:|-|/)(\d{2}))" };
	bool LoopFlag = false;

	do {

		//���͏���
		std::cout << "���Ɏ�������͂��Ă��������i2021�N01��15���̏ꍇ�F2021/01/15.11:05�j";
		std::cin >> InDate;
		std::cout << std::endl;
		std::cout << "�o�Ɏ�������͂��Ă��������i2021�N01��15���̏ꍇ�F2021/01/15.11:05�j";
		std::cin >> OutDate;
		std::cout << std::endl;
		Judger* judger = Judger::getInstance();
		//���͒l�ɖ��Ȃ��H
		if (std::regex_match(InDate.c_str(), rx) && std::regex_match(OutDate.c_str(), rx)) { 

			//�v�Z�`�����\�����{
			Proxy * p_Proxy = new Proxy(InDate,OutDate);
			delete p_Proxy;
		}
		else {
			std::cout << "���͒l�ɖ�肪����܂��B" << std::endl;
		}

		//�p���m�F(���l�ȊO�������ƃ_���Ȃ̂Œ���)
		std::cout << "�������p�����܂����H" << std::endl;
		std::cout << "�p���F0�@�I���F0�ȊO" << std::endl;
		int answer;
		std::cin >> answer;
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