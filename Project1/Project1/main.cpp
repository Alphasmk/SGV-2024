#include "stdafx.h"
#include <cstdlib>
using namespace std;

void printCentered(const std::string& text) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int consoleWidth = 80; // Значение по умолчанию

	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
		consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	}

	int padding = (consoleWidth - text.size()) / 2;
	if (padding > 0) {
		std::cout << std::string(padding, ' ') << text << std::endl;
	}
	else {
		std::cout << text << std::endl;
	}
}

int _tmain(int argc, const _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	Parm::PARM parm;
	Log::LOG log = Log::INITLOG;
	try
	{
		parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::INTAB in = In::getin(parm.in, parm.out);

		vector<pair<string, IT::Entry>> ids;
		LT::LexTable lextable = LT::Create(in.size);
		IT::IdTable idtable = IT::Create(in.size);
		OT::OpTable optable = OT::Create();
		IT::Entry enter;

		LA::LexAnalize(in, lextable, idtable, optable, ids);
		cout << "\n\n\n\n\n\n";
		printCentered("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ |-------------------------------------------|~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
		printCentered("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ |   Лексический анализ завершен без ошибок  |~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
		printCentered(" ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ |-------------------------------------------|~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
		Sleep(800);
		system("cls");
		*log.stream << "\n~ ~ ~ ~ ~ ~ ~ ~ ~ ~|       Разбор цепочек      |~ ~ ~ ~ ~ ~ ~ ~ ~ ~" << endl;
		MFST_TRACE_START						//отладка
			MFST::Mfst mfst(lextable, GRB::getGreibach(), log);			//автомат
		mfst.start(log);											// старт синтаксического анализа

		mfst.savededucation();									//сохранить правила вывода

		mfst.printrules(log);
		cout << "\n\n\n\n\n\n";
		printCentered("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ |-------------------------------------------|~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
		printCentered("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ | Синтаксический анализ завершен без ошибок |~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
		printCentered(" ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ |-------------------------------------------|~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
		Sleep(800);
		system("cls");
		SemAnalize::SemAnalize(lextable, idtable);
		cout << "\n\n\n\n\n\n";
		printCentered("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ |-------------------------------------------|~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
		printCentered("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ |  Семантический анализ завершен без ошибок |~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
		printCentered(" ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ |-------------------------------------------|~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
		Sleep(800);
		system("cls");
		cout << "\n\n\n\n\n\n";
		system("color 02");
		printCentered("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ |-------------------------------------------|~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
		printCentered("~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ |             Успешное выполнение!          |~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
		printCentered(" ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ |-------------------------------------------|~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
		cout << "\n\n";
		for (int i = 0; i < lextable.size; i++)
		{
			if (lextable.table[i - 1].lexema == LEX_EQUALS)
			{
				PolishNotation::PolishNotation(i, idtable, lextable, optable);
			}

		}
		*log.stream << "~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ |      Таблица лексем     | ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~" << endl;
		LA::printLexTable(lextable, log);
		*log.stream << "\n~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ | Таблица идентификаторов | ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~" << endl;
		LA::printIdTable(idtable, log);
		*log.stream << "\n~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ |     Таблица операций    | ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~" << endl;
		OT::Print(optable, log);
		CG::Generator(lextable, idtable, optable, parm);
		//system("start E:\\unic\\courseKPO\\muzyka-dlya-raboty-ceremoniya-nagrazhdeniya.mp3");
		//system("start https://www.youtube.com/watch?v=xvFZjo5PgG0&ab_channel=Duran");
		system("start E:\\unic\\courseKPO\\Project1\\SGVBAT\\start.bat");
		Log::Close(log);
		LT::Delete(lextable);
		IT::Delete(idtable);
		OT::Delete(optable);
	}
	catch (Error::ERRORS e)
	{
		system("color 04");
		cout << "Ошибка " << e.id << ": " << e.message << endl << "Подробнее в файле ";
		wcout << parm.log << endl << endl;
		if (e.inext.line)
			Log::WriteError(log, e, parm);
		if (e.id != 90)
		{
			Log::Close(log);
		}
	}
	system("pause");
	return 0;
}
