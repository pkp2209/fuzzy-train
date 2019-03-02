#include <stack>
#include <cctype>
#include <map>
#include <string>
#include <cstdio>
#include <sstream>
#include <windows.h>

TCHAR* Calculate(TCHAR* buf)
{
	std::basic_string<TCHAR> s(buf), srpn, sres;
	std::basic_string<TCHAR>::size_type ind;
	while ((ind = s.find(TEXT(' '))) != std::basic_string<TCHAR>::npos) // удаление пробелов из входной строки
	{
		s.erase(ind, 1);
	}
	std::map<TCHAR, size_t> map; // карата весов символов
	map.insert(std::make_pair(TEXT('*'), 3));
	map.insert(std::make_pair(TEXT('/'), 3));
	map.insert(std::make_pair(TEXT('+'), 2));
	map.insert(std::make_pair(TEXT('-'), 2));
	map.insert(std::make_pair(TEXT('('), 1));
	std::stack<TCHAR> stack;
	for (std::basic_string<TCHAR>::iterator ib = s.begin(); ib != s.end(); ++ib) // формировка результирующей строки в ОПЗ
	{
		if (!isdigit(*ib) && (TEXT('.') != *ib) && !(s.begin() == ib && '-' == *ib))
		{
			srpn += TEXT(' ');
			if (TEXT(')') == *ib)
			{
				while (stack.top() != TEXT('('))
				{
					srpn += stack.top();
					stack.pop();
					srpn += TEXT(' ');
				}
				stack.pop();
			}
			else if (TEXT('(') == *ib)
			{
				stack.push(*ib);
			}
			else if (stack.empty() || (map[stack.top()] < map[*ib]))
			{
				stack.push(*ib);
			}
			else
			{
				do
				{
					srpn += stack.top();
					srpn += TEXT(' ');
					stack.pop();
				} while (!(stack.empty() || (map[stack.top()] < map[*ib])));
				stack.push(*ib);
			}
		}
		else
		{
			srpn += *ib;
		}
	}
	while (!stack.empty())// остаток из стека добавляется в результ. строку
	{
		srpn += stack.top();
		srpn += TEXT(' ');
		stack.pop();
	}
	std::stack<double> dstack;
	std::basic_stringstream<TCHAR> ss(srpn);
	double d, d1;
	TCHAR c;
	while (ss.get(c)) // вычисление результата
	{
		if (isdigit(c) || TEXT('.') == c || (1 == ss.tellg() && TEXT('-') == c))
		{
			ss.unget();
			ss >> d;
			dstack.push(d);
		}
		else if (!isspace(c))
		{
			d1 = dstack.top();
			dstack.pop();
			d = dstack.top();
			dstack.pop();
			switch (c)
			{
			case TEXT('+'):
				dstack.push(d + d1);
				break;
			case TEXT('-'):
				dstack.push(d - d1);
				break;
			case TEXT('*'):
				dstack.push(d * d1);
				break;
			case TEXT('/'):
				dstack.push(d / d1);
				break;
			}
		}
	}
	if (1 == dstack.size())
	{
		_stprintf(buf, TEXT("%lf"), dstack.top());
		dstack.pop();
	}
	else
	{
		_stprintf(buf, TEXT("error"));
	}
	return buf;
}