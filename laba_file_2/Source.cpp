#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <locale>

#pragma warning(disable : 4996)

int f_count_p(const char* sentence, const unsigned int& count)
{

	std::locale loc1("russian");

	int punct{ 0 };

	for (unsigned int i = 0; i < count; i++)
	{

		if (std::ispunct(sentence[i], loc1))
		{

			punct++;

		}

	}

	return punct;

}

void f_file_count(const char* endls)
{

	FILE* in_file;
	FILE* out_file;

	out_file = fopen("output_text.txt", "w");

	int max{ 0 };
	int symb_i{ 0 };

	char n_line = '\n';
	char temp_numb[100];
	char* zero_line = new char[] {"Нет предложений с знаками препинания!"};
	char symb;
	char prev_symb{ '.' };
	bool check{ false };

	std::locale loc1("russian");

	unsigned int count{ 0 };
	unsigned int leng{ 4 };
	char* sentence = new char[leng];

	int temp_elem{ 0 };

	if ((in_file = fopen("text.txt", "r")) == NULL)
	{

		std::cerr << "Файл не был найден!!!" << std::endl;
		std::cout << "Проверьте наименование и расположение файла!!!" << std::endl;

	}

	else
	{

		while ((symb_i = getc(in_file)) != EOF)
		{

			symb = static_cast<char>(symb_i);

			if (symb == '\n')
			{

				continue;

			}

			if (count >= leng)
			{

				leng = leng * 2;

				char* temp = new char[leng];

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

					out_file = fopen("output_text.txt", "a");

					fputs(sentence, out_file);

					fputc(prev_symb, out_file);
					fputc(n_line, out_file);

					char* temp_line = new char[] {"Количество знаков в предложении: "};

					sprintf(temp_numb, "%d", temp_elem);

					fputs(temp_line, out_file);
					fputs(temp_numb, out_file);
					fputc(n_line, out_file);

					delete[] temp_line;

					fclose(out_file);

				}

				if (temp_elem > max)
				{

					max = temp_elem;

					out_file = fopen("output_text.txt", "w");

					fputs(sentence, out_file);

					fputc(prev_symb, out_file);
					fputc(n_line, out_file);

					char* temp_line = new char[] {"Количество знаков в предложении: "};

					sprintf(temp_numb, "%d", temp_elem);

					fputs(temp_line, out_file);
					fputs(temp_numb, out_file);
					fputc(n_line, out_file);

					delete[] temp_line;

					fclose(out_file);

				}

				count = 0;
				leng = 4;

				delete[] sentence;
				sentence = new char[leng];
				fflush(in_file);

			}

			prev_symb = symb;

		}

		sentence[count] = '\0';

		temp_elem = f_count_p(sentence, count);

		if (temp_elem == max)
		{

			out_file = fopen("output_text.txt", "a");

			fputs(sentence, out_file);

			fputc(prev_symb, out_file);
			fputc(n_line, out_file);

			char* temp_line = new char[] {"Количество знаков в предложении: "};

			sprintf(temp_numb, "%d", temp_elem);

			fputs(temp_line, out_file);
			fputs(temp_numb, out_file);
			fputc(n_line, out_file);

			delete[] temp_line;

			fclose(out_file);

		}

		if (temp_elem > max)
		{

			max = temp_elem;

			out_file = fopen("output_text.txt", "w");

			fputs(sentence, out_file);

			fputc(prev_symb, out_file);
			fputc(n_line, out_file);

			char* temp_line = new char[] {"Количество знаков в предложении: "};

			sprintf(temp_numb, "%d", temp_elem);

			fputs(temp_line, out_file);
			fputs(temp_numb, out_file);
			fputc(n_line, out_file);

			delete[] temp_line;

			fclose(out_file);

		}

		if (max == 0 ||
			temp_elem < 0)
		{

			out_file = fopen("output_text.txt", "w");

			fputs(zero_line, out_file);

			fclose(out_file);

		}

		fclose(in_file);

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