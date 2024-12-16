#include "stdafx.h"
namespace Error
{
	ERRORS errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "#SYSTEM - Недопустимый код ошибки"),//LA
		ERROR_ENTRY(1, "#SYSTEM - Системный сбой"),//LA
		ERROR_ENTRY_NODEF(2),//LA
		ERROR_ENTRY_NODEF(3),//LA
		ERROR_ENTRY_NODEF(4),
		ERROR_ENTRY(5, "#SYSTEM - Ошибочное завершение кода программы"),//LA
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20),
		ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80),
		ERROR_ENTRY(90, "#PARAMETERS - Параметр -in должен быть задан"),
		ERROR_ENTRY(91, "#PARAMETERS - Превышена длина входного параметра"),
		ERROR_ENTRY(92, "#PARAMETERS - Не удалось открыть файл с исходным кодом (-in)"),
		ERROR_ENTRY_NODEF(93), 
		ERROR_ENTRY_NODEF(94), 
		ERROR_ENTRY_NODEF(95), 
		ERROR_ENTRY_NODEF(96), 
		ERROR_ENTRY_NODEF(97), 
		ERROR_ENTRY_NODEF(98), 
		ERROR_ENTRY_NODEF(99), 
		ERROR_ENTRY_NODEF(100), 
		ERROR_ENTRY_NODEF(101),
		ERROR_ENTRY_NODEF(102),
		ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY_NODEF(104),
		ERROR_ENTRY_NODEF(105),
		ERROR_ENTRY_NODEF(106),
		ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY(108, "#LEXICAL - Неверный индекс"),
		ERROR_ENTRY(109, "#LEXICAL - Невозможно добавить элемент. Таблица заполнена"),
		ERROR_ENTRY(110, "#LEXICAL - Невозможно создать таблицу. Слишком большой размер"),
		ERROR_ENTRY(111, "#LEXICAL - Недопустимый символ в исходном файле(-in)"),//LA
		ERROR_ENTRY(112, "#LEXICAL - Ошибка при создании файла протокола(-log)"),//LA
		ERROR_ENTRY(113, "#LEXICAL - Ошибка при разборе исходного кода"), //LA
		ERROR_ENTRY(114, "#LEXICAL - Ошибка при анализе лексемы"),//LA
		ERROR_ENTRY(115, "#LEXICAL - Необъявленный идентификатор"), //LA
		ERROR_ENTRY(116, "#LEXICAL - Повторно объявленный идентификатор переменной"), //LA
		ERROR_ENTRY(117, "#LEXICAL - Повторно объявленный идентификатор функции"), //LA
		ERROR_ENTRY(118, "#LEXICAL - Использование зарезервивованного идентификатора функции _pow()"), //LA
		ERROR_ENTRY(119, "#LEXICAL - Использование зарезервивованного идентификатора функции _exp()"), //LA
		ERROR_ENTRY(120, "#LEXICAL - Использование зарезервивованного идентификатора функции _pause()"), //LA
		ERROR_ENTRY(121, "#LEXICAL - Слишком большая длина имени идентификатора функции(>5 символов)"), //LA
		ERROR_ENTRY(122, "#LEXICAL - Использование зарезервированного слова"), //LA
		ERROR_ENTRY(123, "#LEXICAL - Ошибка при объявлении идентификатора"), //LA
		ERROR_ENTRY(124, "#LEXICAL - Слишком большая длина имени идентификатора переменной(>8)"), //LA
		ERROR_ENTRY(125, "#LEXICAL - Конструкция else if() не поддерживается"),
		ERROR_ENTRY(126, "#LEXICAL - If внутри if Запрещен"),
		ERROR_ENTRY_NODEF(127),
		ERROR_ENTRY_NODEF(128),
		ERROR_ENTRY_NODEF(129),
		ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
	  ERROR_ENTRY(600, "#SYNTAX - Неверная структура программы"),
	  ERROR_ENTRY(601, "#SYNTAX - Ошибка в конструкции блока кода"),
	  ERROR_ENTRY(602, "#SYNTAX - Ошибка в выражении"),
	  ERROR_ENTRY(603, "#SYNTAX - Ошибка в параметрах функции"),
	  ERROR_ENTRY(604, "#SYNTAX - Неверная структура программы"),
	  ERROR_ENTRY(605, "#SYNTAX - Ошибка синтаксического анализа: Ошибочный оператор"),//
	  ERROR_ENTRY(606, "#SYNTAX - Ошибка в условной конструкции"),//
	  ERROR_ENTRY(607, "#SYNTAX - Ошибка типа"),
	  ERROR_ENTRY_NODEF(608), ERROR_ENTRY_NODEF(609), ERROR_ENTRY_NODEF(610),
	  ERROR_ENTRY_NODEF10(610), ERROR_ENTRY_NODEF10(620), ERROR_ENTRY_NODEF10(630), ERROR_ENTRY_NODEF10(640), ERROR_ENTRY_NODEF10(650),
	  ERROR_ENTRY_NODEF10(660), ERROR_ENTRY_NODEF10(670), ERROR_ENTRY_NODEF10(680),  ERROR_ENTRY_NODEF10(690),
	  ERROR_ENTRY(700, "#POLISH NOTATION - Ошибка при обработке оператора польской нотации"),
	  ERROR_ENTRY(701, "#SEMANTICS - Main не объявлен"),
	  ERROR_ENTRY(702, "#SEMANTICS - Ошибочное кол-во параметров функции _pow()"),
	  ERROR_ENTRY(703, "#SEMANTICS - Ошибочное кол-во параметров функции _exp()"),
	  ERROR_ENTRY(704, "#SEMANTICS - Неверный тип данных параметра функции _pow()"),
	  ERROR_ENTRY(705, "#SEMANTICS - Неверный тип данных параметра функции _exp()"),
	  ERROR_ENTRY(706, "#SEMANTICS - Функция _pause() должна вызываться без параметров"),
	  ERROR_ENTRY(707, "#SEMANTICS - Ошибочный тип члена выражения"),
	  ERROR_ENTRY(708, "#SEMANTICS - Неверный тип данных функции _print"),
	  ERROR_ENTRY(709, "#SEMANTICS - Ошибочное кол-во параметров функии _print"),
	  ERROR_ENTRY(710, "#SEMANTICS - Несоответствие типа функции ее возвращаемому значению"),
	  ERROR_ENTRY(711, "#SEMANTICS - Ошибка в типе параметров вызываемой функции"),
	  ERROR_ENTRY(712, "#SEMANTICS - Несоответствие количества параметров вызываемой функции"),
	  ERROR_ENTRY(713, "#SEMANTICS - Несоответствие типов при сравнении"),
	  ERROR_ENTRY(714, "#SEMANTICS - Вызов функции в параметрах условной конструкции"),
	  ERROR_ENTRY_NODEF(715),
	  ERROR_ENTRY_NODEF(716),
	  ERROR_ENTRY_NODEF(717),
	  ERROR_ENTRY_NODEF(718),
	  ERROR_ENTRY_NODEF(719),
	  ERROR_ENTRY_NODEF10(720), ERROR_ENTRY_NODEF10(730),
	  ERROR_ENTRY_NODEF10(740), ERROR_ENTRY_NODEF10(750),
	  ERROR_ENTRY_NODEF10(760), ERROR_ENTRY_NODEF10(770),
	  ERROR_ENTRY_NODEF10(780), ERROR_ENTRY_NODEF10(790),
	};

	ERRORS geterror(int id)
	{
		for (int i = 0; i < ERROR_MAX_ENTRY; i++)
		{
			if (errors[i].id == id)
				return errors[i];
		}
		return errors[0];
	}

	ERRORS geterrorin(int id, int line, int col)
	{
		ERRORS err = geterror(id);
		err.inext.line = line;
		err.inext.col = col;
		return err;
	}
}
