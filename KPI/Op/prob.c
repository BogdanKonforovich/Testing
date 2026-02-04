#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <dirent.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[1m\033[32m"
#define BLUE    "\033[1m\033[34m"
#define YELLOW  "\033[33m"
#define REVERSE "\033[7m"

#define max_file_name 20
#define extension ".max"
#define extention_len strlen(extension)

struct record
{
	char name[40];
	double square;
	int people;
};

char save_record(char* filename, struct record* p, char sorted);
int load(char* filename);
int get_decision(int max, char e);
int ask(char* options, char exit);
char ask_yes_no();
int get_int();
double get_double();
char enter_string(char* str, int length);
int get_file_size(char* filename);

void create_file();
void record_to_file(char sorted);
void write_record(char* filename, char sorted);
void delete_record();
void delete_file();
void edit_record();
void sort_records();

char delete_from_file(char* filename, char* data);
int number_of_records(char* filename);
int select_to_edit(char* filename);
char select_records(char* filename, char* selected_records);
void view_records();
char is_file_exist(char* fname);
char get_file_name(char* name);

void sort_name_records(char** arr, double* square, int* people, int n, char s);
void sort_square_records(char** arr, double* square, int* people, int n, char s);
void sort_people_records(char** arr, double* square, int* people, int n, char s);
void swap_arr(char** arr, double* square, int* people, int j);

void print_title()
{
	system("cls");
	printf(YELLOW "\t\t _______________________________________________________________________________________\n");
	printf("\t\t|    ____   ____   __    ____        __  ___   ___    _  __   ___   _____   ____   ___  |\n");
	printf("\t\t|   / __/  /  _/  / /   / __/       /  |/  /  / _ |  / |/ /  / _ | / ___/  / __/  / _ \\ |\n");
	printf("\t\t|  / _/   _/ /   / /__ / _/        / /|_/ /  / __ | /    /  / __ |/ (_ /  / _/   / , _/ |\n");
	printf("\t\t| /_/    /___/  /____//___/       /_/  /_/  /_/ |_|/_/|_/  /_/ |_|\\___/  /___/  /_/|_|  |\n");
	printf("\t\t|_______________________________________________________________________________________|\n\n" RESET);

}

void print_table()
{
	printf("    .----------------------------------------------------------------------.\n");
	printf("    |  N  |                  OBLAST                  |  SQUARE  |  PEOPLE  |\n");
	printf("    |----------------------------------------------------------------------|\n");
}
void close_table()
{
	printf("    '----------------------------------------------------------------------'\n\n");
}


void message(char* mes, char type)
{
	switch (type)
	{
	case '+':
		printf(GREEN);
		break;
	case 'e':
		printf(RED);
		break;
	}
	printf("\n  %s\n" RESET "  Для продовження натисніть будь-яку клавішу...\n", mes);
	_getch();
}

int main()
{
	system("chcp 1251>0");
	char exit_program = 0;
	do
	{	
		switch (ask((char*)"Головне меню | Виберіть:\0Створити файл\0Запис в файл\0Видалення записів\0Видалення файлу\0Редагування записів\0Впорядкування записів\0Вставка записів, щоб записи залишились відсортованими\0Зчитування та вивід записів\0", 1))
		{
		case 0:
			exit_program = 1;
			break;
		case 1:
			create_file();
			break;
		case 2:
			record_to_file(0);
			break;
		case 3:
			delete_record();
			break;
		case 4:
			delete_file();
			break;
		case 5:
			edit_record();
			break;
		case 6:
			sort_records();
			break;
		case 7:
			record_to_file(1);
			break;
		case 8:
			view_records();
			break;
		}

	} while (!exit_program);
	return 0;
}

void create_file()
{
	char* filename = (char*)malloc((max_file_name + extention_len + 1) * sizeof(char));
	if (filename)
	{
		char check;
		do
		{
			check = 0;
			print_title();
			printf(YELLOW "\tГоловне меню > Створити файл\n");
			printf("  Введіть назву файлу (e - щоб вийти): ");

			if (enter_string(filename, max_file_name))
			{
				strcpy(&filename[strlen(filename)], extension);
				if (is_file_exist(filename))
				{
					message((char*)"Файл з такою назвою вже існує!", 'e');
					check = 1;
				}
				else
				{
					FILE* file;
					file = fopen(filename, "w");
					if (file == NULL)
					{
						message((char*)"Не можу створити файл!", 'e');
						check = 1;
					}
					else
					{
						message((char*)"Файл створено", '+');
						fclose(file);
					}
				}
			}
		} while (check);
		free(filename);
	}
	else message((char*)"Сталася помилка. Неможливо виділити пам'ять!", 'e');
}

void record_to_file(char sorted)
{
	char* filename = calloc(max_file_name + extention_len + 1, sizeof(char));
	if (filename)
	{
		if (get_file_name(filename))
		{
			strcpy(&filename[strlen(filename)], extension);
			write_record(filename, sorted);
		}
		free(filename);
	}
	else message((char*)"Сталася помилка. Неможливо виділити пам'ять!", 'e');
}

void write_record(char* filename, char sorted)
{
	char name[40];
	for (int i = 0; i < 40; i++) name[i] = 0;
	char back = 0;
	double square;
	int people;
	do
	{
		print_title();
		printf(YELLOW "  --- Ввід даних в файл \"%s\" ---\n" RESET, filename);
		printf("  Назва області (e - на головне меню): ");
		if ((back == 2) || enter_string(&name, 39))
		{
			if (back == 2) printf(GREEN "%s\n" RESET, name);
			printf("  Площа (0 - повернутися назад): ");
			square = get_double();
			if (square)
			{
				printf("  Кількість населення (0 - повернутися назад): ");
				people = get_int();
				if (people)
				{
					if (!is_file_exist(filename))
					{
						message((char*)"Сталася помилка. Файл більше не існує!", 'e');
					}
					else
					{
						back = 0;
						struct record new_record;
						strcpy(&new_record.name, name);
						new_record.square = square;
						new_record.people = people;
						if (save_record(filename, &new_record, sorted))
						{
							printf(GREEN "  Запис успішно створено!\n\n" RESET YELLOW "  Ви хочете зробити ще один?\n" RESET);
							if (ask_yes_no()) write_record(filename, sorted);
						}
						else message((char*)"Сталася помилка. Неможливо записати в файл!", 'e');
					}
				}
				else back = 2;
			}
			else back = 1;
		}
		else back = 0;
	} while (back);
}

void view_records()
{
	char* filename = calloc(max_file_name + extention_len + 1, sizeof(char));
	if (filename)
	{
		if (get_file_name(filename))
		{
			strcpy(&filename[strlen(filename)], extension);
			
			if (load(filename))
			{
				message((char*)"Записи зчитано!", '+');
			}

		}
		free(filename);
	}
	else message((char*)"Сталася помилка. Неможливо виділити пам'ять!", 'e');
}

void delete_record()
{
	char* filename = calloc(max_file_name + extention_len + 1, sizeof(char));
	if (filename)
	{
		if (get_file_name(filename))
		{
			strcpy(&filename[strlen(filename)], extension);

			int n = number_of_records(filename);
			if (n != 0)
			{
				char* records = calloc(n, sizeof(char));
				if (select_records(filename, records))
				{
					if (delete_from_file(filename, records))
					{
						message((char*)"Вибрані записи успішно видалені!", '+');
					}
				}
				free(records);
			}
			else
			{
				message((char*)"Не знайдено записів!", 'e');
			}

		}
		free(filename);
	}
	else message((char*)"Сталася помилка. Неможливо виділити пам'ять!", 'e');
}

char delete_from_file(char* filename, char* data)
{
	FILE* file1;
	FILE* file2;
	file1 = fopen(filename, "rb");
	if (file1 == NULL)
	{
		message((char*)"Не можу відкрити файл!", 'e');
		return 0;
	}
	file2 = fopen("temp", "wb");
	if (file2 == NULL)
	{
		fclose(file1);
		message((char*)"Не можу створити файл!", 'e');
		return 0;
	}

	int n = number_of_records(filename);
	char buffer = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < sizeof(struct record) && buffer != EOF; j++)
		{
			buffer = fgetc(file1);
			if (buffer == EOF) break;
			if (data[i] == 0) fputc(buffer, file2);
		}
	}
	fclose(file1);
	fclose(file2);
	remove(filename);
	rename("temp", filename);
	return 1;
}

int get_file_size(char* filename)
{
	FILE* file;
	file = fopen(filename, "rb");
	if (file == NULL)
	{
		message((char*)"Не можу відкрити файл!", 'e');
		return 0;
	}
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fseek(file, 0, SEEK_SET);
	fclose(file);
	return size;
}

int number_of_records(char* filename)
{
	return get_file_size(filename) / sizeof(struct record);
}

char select_records(char* filename, char* selected_records)
{
	int n = number_of_records(filename);
	FILE* file;
	struct record load_record;
	file = fopen(filename, "rb");
	if (file == NULL)
	{
		message((char*)"Не можу відкрити файл!", 'e');
		return 0;
	}

	int i = 0;

	char** records_names = (char**)malloc(n * sizeof(char*));
	for (i = 0; i < n; i++)
	{
		records_names[i] = (char*)malloc(40 * sizeof(char));
	}
	double* records_squares = (double*)malloc(n * sizeof(double));
	int* records_people = (int*)malloc(n * sizeof(int));

	i = 0;

	while (fread(&load_record, sizeof(struct record), 1, file))
	{
		strcpy(records_names[i], load_record.name);
		records_squares[i] = load_record.square;
		records_people[i] = load_record.people;
		i++;
	}
	fclose(file);

	char selection = 1;
	do
	{
		print_title();
		printf("\t\t\t\t*** Виберіть записи ***\n");
		print_table();

		for (i = 0; i < n; i++)
		{
			if (selected_records[i]) printf(BLUE "  X " RESET);
			else printf("    ");
			printf("| %3d | %-40s | %-8g | %-8d |\n", i + 1, records_names[i], records_squares[i], records_people[i]);
		}

		close_table();
		printf("  e - на головне меню, a - підтвердити вибір, 0 - вибрати/скасувати все\n");
		int decision = get_decision(n, 2);

		if (decision == -1)
		{
			for (int j = 0; j < n; j++) free(records_names[j]);
			free(records_names);
			free(records_squares);
			free(records_people);
			return 0;
		}

		if (decision == -2)
		{
			selection = 0;
		}
		else if (decision == 0)
		{
			if (selected_records[0] == 0) for (int j = 0; j < n; j++) selected_records[j] = 1;
			else for (int j = 0; j < n; j++) selected_records[j] = 0;
		}
		else selected_records[decision - 1] = !selected_records[decision - 1];

	} while (selection);

	for (i = 0; i < n; i++) free(records_names[i]);
	free(records_names);
	free(records_squares);
	free(records_people);
	return 1;
}

void delete_file()
{
	char* filename = calloc(max_file_name + extention_len + 1, sizeof(char));
	if (filename)
	{
		if (get_file_name(filename))
		{
			print_title();
			strcpy(&filename[strlen(filename)], extension);
			if (!is_file_exist(filename))
			{
				message((char*)"Сталася помилка. Файлу не існує!", 'e');
			}
			else
			{
				printf(YELLOW"  Ви дійсно хочете видалити файл \"%s\"?\n" RESET, filename);
				if (ask_yes_no())
				{
					if (remove(filename) == 0)
					{
						message((char*)"Файл успішно видалено!", '+');
					}
					else message((char*)"Сталася помилка. Неможливо видалити файл!", 'e');
				}
			}
		}
		free(filename);
	}
	else message((char*)"Сталася помилка. Неможливо виділити пам'ять!", 'e');
}

void edit_record()
{
	char* filename = calloc(max_file_name + extention_len + 1, sizeof(char));
	if (filename)
	{
		if (get_file_name(filename))
		{
			print_title();
			strcpy(&filename[strlen(filename)], extension);
			if (!is_file_exist(filename))
			{
				message((char*)"Сталася помилка. Файлу не існує!", 'e');
			}
			else
			{
				select_to_edit(filename);
			}
		}
		free(filename);
	}
	else message((char*)"Сталася помилка. Неможливо виділити пам'ять!", 'e');
}

int select_to_edit(char* filename)
{
	int n = number_of_records(filename);
	if (n == 0)
	{
		message((char*)"Не знайдено записів!", 'e');
		return 0;
	}
	FILE* file;
	struct record load_record;
	file = fopen(filename, "rb");
	if (file == NULL)
	{
		message((char*)"Не можу відкрити файл!", 'e');
		return 0;
	}

	int i = 1;

	char** records_names = (char**)malloc(n * sizeof(char*));
	for (i = 0; i < n; i++)
	{
		records_names[i] = (char*)malloc(40 * sizeof(char));
	}
	i = 0;
	double* records_squares = (double*)malloc(n * sizeof(double));
	int* records_people = (int*)malloc(n * sizeof(int));

	while (fread(&load_record, sizeof(struct record), 1, file))
	{
		strcpy(records_names[i], load_record.name);
		records_squares[i] = load_record.square;
		records_people[i] = load_record.people;
		i++;
	}
	fclose(file);

	int y = -1;
	int x = -1;
	char selection = 1;
	do
	{
		print_title();
		printf("\t\t\t\t*** Ваші записи ***\n");
		print_table();
		for (i = 0; i < n; i++)
		{
			printf("    ");
			if (x == -1)
			{
				if (y == i + 1) printf(REVERSE);
				printf("| %3d | %-40s | %-8g | %-8d |\n", i + 1, records_names[i], records_squares[i], records_people[i]);
				if (y == i + 1) printf(RESET);
			}
			else
			{
				if (y == i + 1)
				{
					printf("| %3d |", i + 1);
					if (x == 1) printf(REVERSE);
					printf(" %-40s ", records_names[i]);
					if (x == 1) printf(RESET);
					printf("|");
					if (x == 2) printf(REVERSE);
					printf(" %-8g ", records_squares[i]);
					if (x == 2) printf(RESET);
					printf("|");
					if (x == 3) printf(REVERSE);
					printf(" %-8d ", records_people[i]);
					if (x == 3) printf(RESET);
					printf("|\n");

				}
				else printf("| %3d | %-40s | %-8g | %-8d |\n", i + 1, records_names[i], records_squares[i], records_people[i]);
			}
		}
		close_table();
		printf("  e - на головне меню, 0 - підтвердити вибір\n");
		int decision = 0;
		if (x == -1)
		{
			decision = get_decision(n, 1);
			if (decision == 0 && y != -1)
			{
				printf("\n  Введіть номер поля (1 - Область, 2 - Площа, 3 - Населення, 0 - скасувати), e - на головне меню\n");
				int decision2 = get_decision(3, 1);
				if (decision2 == -1) decision = -1;
				else if (decision2 == 0) y = -1;
				else
				{
					x = decision2;
				}
			}
			else if (decision != 0)
			{
				y = decision;
			}
		}
		else
		{
			printf("  Введіть нове значення поля (%c - скасувати): " GREEN, x == 1 ? 'e' : '0');
			
			if (x == 1)
			{
				char* value = calloc(40, sizeof(char));
				if (value)
				{
					if (enter_string(value, 39))
					{
						FILE* file1;
						FILE* file2;
						file1 = fopen(filename, "rb");
						if (file1 == NULL)
						{
							message((char*)"Не можу відкрити файл!", 'e');
							decision = -1;
						}
						else
						{
							file2 = fopen("temp", "wb");
							if (file2 == NULL)
							{
								fclose(file1);
								message((char*)"Не можу створити файл!", 'e');
								decision = -1;
							}
							else
							{
								struct record read;
								for (int i = 0; i < n; i++)
								{
									fread(&read, sizeof(struct record), 1, file1);
									if (y == i + 1)
									{
										struct record edited;
										strcpy(&edited.name, value);
										edited.square = records_squares[i];
										edited.people = records_people[i];
										fwrite(&edited, sizeof(struct record), 1, file2);
									}
									else
									{
										fwrite(&read, sizeof(struct record), 1, file2);
									}
								}
								fclose(file1);
								fclose(file2);
								remove(filename);
								rename("temp", filename);
								printf(GREEN "\n  Успішно змінено!\n" RESET YELLOW "  Ви хочете змінити ще щось?\n" RESET);
								if (ask_yes_no())
								{
									strcpy(records_names[y - 1], value);
									x = -1;
									y = -1;
								}
								else selection = 0;
							}
						}
					}
					else x = -1;
					free(value);
				}
				else
				{
					x = -1;
					message((char*)"Сталася помилка. Неможливо виділити пам'ять!", 'e');
				}
			}
			else
			{
				int new_value = 0;
				double new_value2 = 0;
				if (x == 2) new_value2 = get_double();
				else new_value = get_int();
				if (new_value || new_value2)
				{
					FILE* file1;
					FILE* file2;
					file1 = fopen(filename, "rb");
					if (file1 == NULL)
					{
						message((char*)"Не можу відкрити файл!", 'e');
						decision = -1;
					}
					else
					{
						file2 = fopen("temp", "wb");
						if (file2 == NULL)
						{
							fclose(file1);
							message((char*)"Не можу створити файл!", 'e');
							decision = -1;
						}
						else
						{
							struct record read;
							for (int i = 0; i < n; i++)
							{
								fread(&read, sizeof(struct record), 1, file1);
								if (y == i + 1)
								{
									struct record edited;
									strcpy(&edited.name, records_names[i]);
									if (x == 2)
									{
										edited.square = new_value2;
										edited.people = records_people[i];
									}
									else
									{
										edited.square = records_squares[i];
										edited.people = new_value;
									}
									fwrite(&edited, sizeof(struct record), 1, file2);
								}
								else
								{
									fwrite(&read, sizeof(struct record), 1, file2);
								}
							}
							fclose(file1);
							fclose(file2);
							remove(filename);
							rename("temp", filename);
							printf(GREEN "\n  Успішно змінено!\n" RESET YELLOW "  Ви хочете змінити ще щось?\n" RESET);
							if (ask_yes_no())
							{
								if (x == 2) records_squares[y - 1] = new_value2;
								else if (x == 3) records_people[y - 1] = new_value;
								x = -1;
								y = -1;
							}
							else selection = 0;
						}
					}
				}
				else x = -1;
			}
		}
		if (decision == -1)
		{
			for (int j = 0; j < n; j++) free(records_names[j]);
			free(records_names);
			free(records_squares);
			free(records_people);
			return 0;
		}
	} while (selection);

	for (i = 0; i < n; i++) free(records_names[i]);
	free(records_names);
	free(records_squares);
	free(records_people);
	return 1;
}

void sort_records()
{
	char* filename = calloc(max_file_name + extention_len + 1, sizeof(char));
	if (filename)
	{
		if (get_file_name(filename))
		{
			print_title();
			strcpy(&filename[strlen(filename)], extension);
			if (!is_file_exist(filename))
			{
				message((char*)"Сталася помилка. Файлу не існує!", 'e');
			}
			else
			{
				int n = number_of_records(filename);
				if (n > 0)
				{
					FILE* file;
					struct record load_record;
					file = fopen(filename, "rb");
					if (file == NULL)
					{
						message((char*)"Не можу відкрити файл!", 'e');
					}
					else
					{
						int i = 1;
						char** records_names = (char**)malloc(n * sizeof(char*));
						for (i = 0; i < n; i++)
						{
							records_names[i] = (char*)malloc(40 * sizeof(char));
						}
						i = 0;
						double* records_squares = (double*)malloc(n * sizeof(double));
						int* records_people = (int*)malloc(n * sizeof(int));
						while (fread(&load_record, sizeof(struct record), 1, file))
						{
							strcpy(records_names[i], load_record.name);
							records_squares[i] = load_record.square;
							records_people[i] = load_record.people;
							i++;
						}
						fclose(file);
						int decision = ask((char*)"Як ви хочете сортувати? Виберіть:\0За назвою (від 'А' до 'я')\0За назвою (від 'я' до 'А')\0За площею (за зростанням)\0За площею (за спаданням)\0За населенням (за зростанням)\0За населенням (за спаданням)\0", 0);
						if (decision != 0)
						{
							switch (decision)
							{
							case 1:
								sort_name_records(records_names, records_squares, records_people, n, 1);
								break;
							case 2:
								sort_name_records(records_names, records_squares, records_people, n, 0);
								break;
							case 3:
								sort_square_records(records_names, records_squares, records_people, n, 1);
								break;
							case 4:
								sort_square_records(records_names, records_squares, records_people, n, 0);
								break;
							case 5:
								sort_people_records(records_names, records_squares, records_people, n, 1);
								break;
							case 6:
								sort_people_records(records_names, records_squares, records_people, n, 0);
								break;
							}

							file = fopen(filename, "wb");
							if (file == NULL)
							{
								message((char*)"Не можу відкрити файл для запису!", 'e');
							}
							else
							{
								struct record save;
								for (i = 0; i < n; i++)
								{
									strcpy(&save.name, records_names[i]);
									save.square = records_squares[i];
									save.people = records_people[i];
									fwrite(&save, sizeof(struct record), 1, file);
								}
								fclose(file);
								printf(GREEN "\n  Успішно впорядковано!\n" RESET YELLOW "  Ви хочете переглянути відсортовані записи?\n" RESET);
								if (ask_yes_no())
								{
									if (load(filename))
									{
										message((char*)"Записи зчитано!", '+');
									}
								}
							}
						}
					}
				}
				else message((char*)"Помилка! Немає жодного запису!", 'e');
			}
		}
		free(filename);
	}
	else message((char*)"Сталася помилка. Неможливо виділити пам'ять!", 'e');
}

void swap_arr(char** arr, double* square, int* people, int j)
{
	char* swap = arr[j];
	arr[j] = arr[j + 1];
	arr[j + 1] = swap;
	double sq = square[j];
	square[j] = square[j + 1];
	square[j + 1] = sq;
	int pep = people[j];
	people[j] = people[j + 1];
	people[j + 1] = pep;
}

void sort_name_records(char** arr, double* square, int* people, int n, char s)
{
	if (s == 1)
	{
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = 0; j < n - i - 1; j++)
			{
				for (int k = 0; k < 40; k++)
				{
					if (arr[j][k] > arr[j + 1][k])
					{
						swap_arr(arr, square, people, j);
					}
					if (arr[j][k] < arr[j + 1][k])
					{
						break;
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = 1; j < (n - i); j++)
			{
				for (int k = 0; k < 40; k++)
				{
					if (arr[j - 1][k] < arr[j][k])
					{
						swap_arr(arr, square, people, j - 1);
					}
					if (arr[j - 1][k] > arr[j][k])
					{
						break;
					}
				}
			}
		}
	}
}
void sort_square_records(char** arr, double* square, int* people, int n, char s)
{
	if (s == 1)
	{
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = 0; j < n - i - 1; j++)
			{
				if (square[j] > square[j + 1])
				{
					swap_arr(arr, square, people, j);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = 1; j < (n - i); j++)
			{
				if (square[j - 1] < square[j])
				{
					swap_arr(arr, square, people, j - 1);
				}
			}
		}
	}
}
void sort_people_records(char** arr, double* square, int* people, int n, char s)
{
	if (s == 1)
	{
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = 0; j < n - i - 1; j++)
			{
				if (people[j] > people[j + 1])
				{
					swap_arr(arr, square, people, j);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = 1; j < (n - i); j++)
			{
				if (people[j - 1] < people[j])
				{
					swap_arr(arr, square, people, j - 1);
				}
			}
		}
	}
}

char get_file_name(char* name)
{
	print_title();

	struct dirent* dp;
	DIR* dir = opendir(".");
	if (!dir)
	{
		message((char*)"Не можу відкрити папку!", 'e');
		return 0;
	}

	char data[200];
	for (int i = 0; i < 200; i++) data[i] = 0;
	int pos = 1;

	while ((dp = readdir(dir)) != NULL)
	{
		char is_program_file = 0;
		char* filename = dp->d_name;
		int len = strlen(filename);
		if (len > extention_len)
		{
			for (int i = 0; i < extention_len; i++)
			{
				if (filename[i + len - extention_len] != extension[i])
				{
					is_program_file = 0;
					break;
				}
				is_program_file = 1;
			}
		}
		if (is_program_file)
		{
			strcpy(&data[pos], filename);
			pos += (len - extention_len);
			for (int i = 0; i < 4; i++) strcpy(&data[pos + i], "\0");
			pos++;
		}
	}
	closedir(dir);

	if (data[1] == 0)
	{
		message((char*)"Не створено жодного файлу!", 'e');
		return 0;
	}

	int position = ask(&data, 0);
	if (position == 0) return 0;
	strcpy(name, &data[position]);
	return 1;
}

char is_file_exist(char* fname)
{
	FILE* file;
	if ((file = fopen(fname, "r")))
	{
		fclose(file);
		return 1;
	}
	return 0;
}

char enter_string(char* str, int length)
{
	printf(GREEN);
	char check = 0;
	while (!check)
	{
		char exit = 0;
		for (int c = 0; c <= length; c++)
		{
			char inp = getchar();

			if (exit == 1 && inp == '\n') { printf(RESET); return 0; }
			if (inp == 'e' && exit == 0) { exit = 1; str[c] = inp; }
			else if (inp != '\n')
			{
				exit = 2;
				str[c] = inp;
				if (c == length)
				{
					printf(RESET RED "  Помилка ваш ввід дуже великий. Максимум символів: %d!\n  Введіть назву ще раз (або e, щоб вийти): " RESET GREEN, length);
					while ((inp = getchar()) != '\n' && inp != EOF);
				}
			}
			else
			{
				for (int j = c; j <= length; j++) str[j] = 0;
				check = c;
				break;
			}
		}
	}
	printf(RESET);
	return check;
}

int ask(char* options, char exit)
{
	int fc[99];
	int num = 0;
	for (int i = 0; (options[i] != 0 || options[i + 1] != 0); i++)
	{
		if (options[i] == '\0')
		{
			fc[num++] = i + 1;
		}
	}
	char is_file = fc[0] == 1 ? 1 : 0;
	print_title();
	printf(YELLOW "\t%s\n" RESET, is_file ? "Виберіть файл:" : options);
	for (int i = 0; i < num; i++)
	{
		printf("  %d - %s\n", i + 1, &options[fc[i]]);
	}
	printf("  0 - %s\n", exit ? "Вийти" : "Повернутися назад");
	int decision = get_decision(num, 0);
	if (decision == 0) return 0;
	return is_file ? fc[decision - 1] : decision;
}

int get_decision(int max, char select)
{
	int decision = 0;
	do
	{
		printf("  -------> Введіть 0-%d: " GREEN, max);
		char inp = 0;
		int i = 0;
		char is_int = 1;
		char exit = 0;
		while ((inp = getchar()) != '\n')
		{
			if (inp == 'e' && select) exit = 1;
			else if (inp == 'a' && select == 2) exit = 2;
			i++;
			if (inp >= 48 && inp < 58) decision = decision * 10 + inp - 48;
			else is_int = 0;
		}
		printf(RESET);

		if (decision == 0 && i == 1 && is_int) return 0;
		if (exit && i == 1) return -exit;
		if (decision > max || !is_int)
		{
			printf(RED "  Помилка, введіть 0-%d!\n\n" RESET, max);
			decision = 0;
		}
	} while (!decision);
	return decision;
}

char save_record(char* filename, struct record* p, char sorted)
{
	FILE* file;
	if (sorted == 0)
	{
		file = fopen(filename, "ab");
		if (file == NULL)
		{
			message((char*)"Не можу відкрити файл для запису!", 'e');
			return 0;
		}
		fwrite(p, sizeof(struct record), 1, file);
		fclose(file);
		if (!fwrite)
		{
			message((char*)"Не вдалося записати дані!", 'e');
			return 0;
		}
	}
	else
	{
		int n = number_of_records(filename);
		if (n > 0)
		{
			FILE* file;
			struct record load_record;
			file = fopen(filename, "rb");
			if (file == NULL)
			{
				message((char*)"Не можу відкрити файл!", 'e');
				return 0;
			}
			int i = 1;
			char** records_names = (char**)malloc(n * sizeof(char*));
			for (i = 0; i < n; i++)
			{
				records_names[i] = (char*)malloc(40 * sizeof(char));
			}
			i = 0;
			double* records_squares = (double*)malloc(n * sizeof(double));
			int* records_people = (int*)malloc(n * sizeof(int));
			while (fread(&load_record, sizeof(struct record), 1, file))
			{
				strcpy(records_names[i], load_record.name);
				records_squares[i] = load_record.square;
				records_people[i] = load_record.people;
				i++;
			}
			fclose(file);
			int type_sort = 0;
			for (i = 0; i < n - 1; i++)
			{
				if (strcmp(records_names[i], records_names[i + 1]) > 0)
				{
					if (type_sort == 0) type_sort = 1;
					else if (type_sort != 1) { type_sort = -1; break; }
				}
				else if (strcmp(records_names[i], records_names[i + 1]) < 0)
				{
					if (type_sort == 0) type_sort = 2;
					else if (type_sort != 2) { type_sort = -1; break; }
				}
			}
			if (type_sort == -1)
			{
				type_sort = 0;
				for (i = 0; i < n - 1; i++)
				{
					if (records_squares[i] < records_squares[i + 1])
					{
						if (type_sort == 0) type_sort = 3;
						else if (type_sort != 3) { type_sort = -1; break; }
					}
					else if (records_squares[i] > records_squares[i + 1])
					{
						if (type_sort == 0) type_sort = 4;
						else if (type_sort != 4) { type_sort = -1; break; }
					}
				}
			}
			if (type_sort == -1)
			{
				type_sort = 0;
				for (i = 0; i < n - 1; i++)
				{
					if (records_people[i] < records_people[i + 1])
					{
						if (type_sort == 0) type_sort = 5;
						else if (type_sort != 5) { type_sort = -1; break; }
					}
					else if (records_people[i] > records_people[i + 1])
					{
						if (type_sort == 0) type_sort = 6;
						else if (type_sort != 6) { type_sort = -1; break; }
					}
				}
			}
			if (type_sort == -1)
			{
				printf(RED "  Помилка! Записи в файлі не відсортовані!\n" RESET);
			}
			file = fopen(filename, "wb");
			if (file == NULL)
			{
				message((char*)"Не можу відкрити файл для запису!", 'e');
				return 0;
			}
			char not_written = 1;
			for (i = 0; i < n; i++)
			{
				struct record save;
				strcpy(&save.name, records_names[i]);
				save.square = records_squares[i];
				save.people = records_people[i];
				switch (type_sort)
				{
				case 1:
					if (not_written && strcmp(save.name, p->name) < 0)
					{
						fwrite(p, sizeof(struct record), 1, file);
						not_written = 0;
					}
					break;
				case 2:
					if (not_written && strcmp(save.name, p->name) > 0)
					{
						fwrite(p, sizeof(struct record), 1, file);
						not_written = 0;
					}
					break;
				case 3:
					if (not_written && save.square > p->square)
					{
						fwrite(p, sizeof(struct record), 1, file);
						not_written = 0;
					}
					break;
				case 4:
					if (not_written && save.square < p->square)
					{
						fwrite(p, sizeof(struct record), 1, file);
						not_written = 0;
					}
					break;
				case 5:
					if (not_written && save.people > p->people)
					{
						fwrite(p, sizeof(struct record), 1, file);
						not_written = 0;
					}
					break;
				case 6:
					if (not_written && save.people < p->people)
					{
						fwrite(p, sizeof(struct record), 1, file);
						not_written = 0;
					}
					break;
				}
				fwrite(&save, sizeof(struct record), 1, file);
			}
			if (not_written)
			{
				fwrite(p, sizeof(struct record), 1, file);
			}
			fclose(file);
		}
		else if (!save_record(filename, p, 0)) return 0;
	}
	return 1;
}

int load(char* filename)
{
	if (number_of_records(filename) > 0)
	{
		FILE* file;

		struct record load_record;

		file = fopen(filename, "rb");

		if (file == NULL)
		{
			message((char*)"Не можу відкрити файл!", 'e');
			return 0;
		}

		int i = 1;
		print_title();
		printf("\t\t\t\t*** Ваші записи ***\n");
		print_table();
		while (fread(&load_record, sizeof(struct record), 1, file))
		{
			printf("    | %3d | %-40s | %-8g | %-8d |\n", i++, load_record.name, load_record.square, load_record.people);
		}
		close_table();
		fclose(file);
		return 1;
	}
	else
	{
		message((char*)"Помилка! Немає жодного запису!", 'e');
		return 0;
	}
}

int get_int()
{
	int input;
	char buf = 0;
	printf(GREEN);
	do
	{
		if (scanf("%d%c", &input, &buf) && buf == '\n')
		{
			if (input < 0)
			{
				printf(RESET RED "  Помилка, це має бути додатнє число або 0, щоб повернутися назад: " RESET GREEN);
				buf = 0;
			}
			else
			{
				buf = 1;
			}
		}
		else
		{
			char exit = 0;
			while ((buf = getchar()) != '\n' && buf != EOF);
			printf(RESET RED "  Ви маєте ввести ціле число. Спробуйте ще раз: " RESET GREEN);
			buf = 0;
		}
	} while (!buf);
	printf(RESET);
	return input;
}


char ask_yes_no()
{
	printf("  Натисніть enter - так, або щось інше - ні\n");
	char decision = _getch();
	if (decision == '\r')
	{
		return 1;
	}
	return 0;
}

double get_double()
{
	char check = 0;
	char is_drob = 0;
	char buf = 0;
	double input;
	double input2;

	printf(GREEN);
	do
	{
		int gg = scanf("%lf%c", &input, &buf);
		if (buf == '/' && gg)
		{
			is_drob = 1;
			gg = scanf("%lf%c", &input2, &buf);
		}
		if (gg && buf == '\n')
		{
			check = 1;
			if (is_drob)
			{
				if (input2 != 0)
				{
					printf(YELLOW "  %.8g/%.8g було сконвертовано в ", input, input2);
					input = input / input2;
					printf("%.8g\n" RESET, input);
				}
				else
				{
					check = 0;
					printf(RESET RED "  Ділення на 0! Спробуйте ще раз: " GREEN);
				}
			}
		}
		else
		{
			printf(RESET RED "  Це не число! Спробуйте ще раз: " GREEN);
			while ((buf = getchar()) != '\n' && buf != EOF);
		}
		if (check && input < 0)
		{
			printf(RESET RED "  Помилка, це має бути додатнє число або 0, щоб повернутися назад: " GREEN);
			check = 0;
		}
		is_drob = 0;
	} while (!check);
	printf(RESET);

	return input;
}