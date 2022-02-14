#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <locale>

unsigned int f_count_p(const char* sentence, const unsigned int &count)
{

	std::locale loc1("russian");

	unsigned int punct{ 0 };

	for (int i = 0; i < count; i++)
	{

		if (std::ispunct(sentence[i], loc1))
		{

			punct++;

		}

	}

	return punct;

}

void f_file_count(const char *endls)
{

	std::ifstream file("text.txt");
	std::ofstream output;

	unsigned int max		{ 0 };

	char symb;
	char prev_symb			{ '.' };
	bool check				{ false };

	std::locale loc1("russian");

	unsigned int count		{ 0 };
	unsigned int leng		{ 4 };
	char* sentence			= new char[leng];

	unsigned int temp_elem	{ 0 };

	if (!file)
	{

		std::cerr << "Файл не был найден!!!";
		std::cout << "Проверьте наименование и расположение файла!!!" << std::endl;

	}

	else
	{

		while (file.get(symb))
		{



			if (symb == '\n')
			{

				continue;

			}

			if (count >= leng)
			{

				leng		= leng * 2;

				char* temp	= new char[leng];

				for (int i = 0; i < count; i++)
				{

					temp[i] = sentence[i];

				}

				delete[] sentence;

				sentence = new char[leng];

				for (int i = 0; i < count; i++)
				{

					sentence[i] = temp[i];

				}

				delete[] temp;

			}

			for (int i = 0; i < 3; i++)
			{

				if (prev_symb == endls[i])
				{

					check = true;
					break;

				}

				else
				{

					check = false;

				}

			}

			if (check == false)
			{

				sentence[count] = prev_symb;
				count++;

			}

			if (std::isupper(symb, loc1) && check == true)
			{
				
				sentence[count] = '\0';

				temp_elem = f_count_p(sentence, count);

				if (temp_elem == max)
				{

					output.open("output_text.txt", std::ofstream::app);

					if (output.is_open())
					{

						output << sentence << prev_symb << std::endl;
						output << "Количество знаков припенания: " << f_count_p(sentence, count) << std::endl;

					}

					output.close();

				}

				if (temp_elem > max)
				{
					max = temp_elem;

					output.open("output_text.txt");
					
					if (output.is_open())
					{

						output << sentence << prev_symb << std::endl;
						output << "Количество знаков припенания: " << f_count_p(sentence, count) << std::endl;

					}

					output.close();

				}

				count		= 0;
				leng		= 4;

				delete[] sentence;
				sentence	= new char[leng];
				

			}

			prev_symb = symb;

		}

		sentence[count] = '\0';

		temp_elem = f_count_p(sentence, count);

		if (temp_elem == max)
		{

			output.open("output_text.txt", std::ofstream::app);

			if (output.is_open())
			{

				output << sentence << prev_symb << std::endl;
				output << "Количество знаков припенания: " << f_count_p(sentence, count) << std::endl;

			}

			output.close();

		}

		if (temp_elem > max)
		{
			max = temp_elem;

			output.open("output_text.txt");

			if (output.is_open())
			{

				output << sentence << prev_symb << std::endl;
				output << "Количество знаков припенания: " << f_count_p(sentence, count) << std::endl;

			}

			output.close();

		}

		if (temp_elem	==	0 ||
			temp_elem	<	0)
		{

			output.open("output_text.txt");

			if (output.is_open())
			{

				output << "Знаков препинания в предложениях нет!!! " << std::endl;

			}

			output.close();

		}

		file.close();

	}


}



void main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	

	char endls[3] = { '!', '?', '.' };

	f_file_count(endls);

	std::cout << "Программа была завершена успешно!!!" << std::endl;
	std::cout << "Найти результат выполнения программы можно в файле output_text.txt!!!" << std::endl;

}