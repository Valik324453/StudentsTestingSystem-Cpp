#include <iostream>
#include <conio.h>
#include <iomanip>
#include <io.h>
#include <algorithm>

#include <map>
#include <set>
#include <list>

#include "User.h"
#include "Item.h"
#include "Test.h"
#include "Result.h"


using namespace std;

struct UserResult
{
	string login;
	UserResult(string login) { this->login = login; }
	bool operator()(const Result& r)
	{
		return r.get_login() == login;
	}
};

void CheckMenuItem(int from, int to, int menu, bool getch_swither)
{
	try
	{
		if (menu < from || menu > to)
		{
			throw exception("Выбран несуществующий пункт меню. Нажмите любую клавишу...\n");
		}
		
	}
	catch (const exception& e)
	{
		cout << e.what();
		if (getch_swither)
		{
			_getch();
			system("CLS");
		}
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
		
	int a = 10, b = 1;

	


	int main_menu;
	set<User> user_database;

	if (_access("user.txt", 0) == -1)
	{
		/*User u1("SP", "sp", "Pavel", "Sidorov", "Chisinev", "060343811", "spavel@mail.ru");
		User u2("BA", "ba", "Alexei", "Bobrov", "Chisinev", "068772435", "bobrovalex@mail.ru");
		User u3("OV", "ov", "Valeriya", "Ovcinnikova", "Chisinev", "079125009", "valeryval@mail.ru");

		user_database.insert(u1);
		user_database.insert(u2);
		user_database.insert(u3);*/
	}
	else
	{
		ifstream fin("user.txt", ios::binary);
		if(fin)
		{
			int count;
			User user;
			fin.read((char*)&count, sizeof(count));
			for (int i = 0; i < count; i++)
			{
				fin >> user;
				user_database.insert(user);
			}
			fin.close();
		}
		else cout << "read error";
	}

	do {
		cout << "Выберите пункт меню:\n";
		cout << "1 - Регистрация\n";
		cout << "2 - Войти в аккаунт\n";
		cout << "3 - Войти как админ\n";
		cout << "0 - Выход из программы\n";
		cin >> main_menu;
		
		CheckMenuItem(0, 3, main_menu, 1);

		cin.get();

		if (main_menu == 1)
		{
			User new_user;
			string new_user_login;
			bool already_in = false;
			cout << "Введите логин: ";
			cin >> new_user_login;

			for (auto user : user_database)
			{
				if (new_user_login == user.get_login())
				{
					already_in = true;
					break;
				}
			}

			if (already_in)
			{
				cout << "\nТакой пользователь уже есть.";
			}
			else
			{
				new_user.init(new_user_login);
				user_database.insert(new_user);
			}

			_getch();
			system("CLS");
		}
		else if (main_menu == 2)
		{
			bool already_in = false;
			bool correct_password = false;

			string login_user;
			string password_user;

			cout << "Введите логин: ";
			cin >> login_user;

				User find_user(login_user);
				auto it_user = user_database.find(find_user);

				if (it_user != user_database.end())
				{
					User user = *it_user;
					already_in = true;
					int repeat_password;
					do
					{
						cout << "Введите пароль: ";
						cin >> password_user;
						if (password_user == user.get_password())
						{
							int user_menu;
							correct_password = true;
							cout << "Добро пожаловать, " << user.get_name() << "! Нажмите любую клавишу для продолжения...\n";
							do {
								_getch();
								system("CLS");
								
								//------------------------------------
								int answer_options;
								int correct_answers = 0;
								list<Result> result_list;
								list<Result> user_session_result_list;
								string user_session;
								user_session = login_user;

								ifstream fin_result("result.txt", ios::binary);
								if (fin_result)
								{
									int count;
									Result res;
									fin_result.read((char*)&count, sizeof(count));
									for (int i = 0; i < count; i++)
									{
										fin_result >> res;
										result_list.push_back(res);
									}
									fin_result.close();
								}
								//else cout << "read result error";

								//Выбираем результаты для залогиненного пользователя
								auto it_result = find_if(result_list.begin(), result_list.end(), UserResult(user_session));
								if (it_result != result_list.end())
								{
									while (it_result != result_list.end())
									{
										user_session_result_list.push_back(*it_result);
										it_result++;
										it_result = find_if(it_result, result_list.end(), UserResult(user_session));
									}
								}

								//------------------------------------

								cout << "\nДобро пожаловать, " << user.get_name() << "!\n";

								//Тут будет тест
								cout << "Выберите пункт меню:\n";
								cout << "1 - Посмотреть результаты\n";
								cout << "2 - Пройти тест\n";
								cout << "0 - Выход в главное меню\n";
								cin >> user_menu;
								CheckMenuItem(0, 2, user_menu, 0);

								if (user_menu == 1)
								{
									auto it_show_current_ress = user_session_result_list.begin();
									if (it_show_current_ress != user_session_result_list.end())
									{
										for (auto r : user_session_result_list)
										{
											cout << r << endl;
										}
									}
									else
										cout << "\nУ данного студента пока нет пройденных тестов\n";
								}
								else if (user_menu == 2)
								{
									string biology1_question1 = "Что относится к неживой материи?";
									pair<string, bool> biology1_answer1_1("Бактерии", false);
									pair<string, bool> biology1_answer1_2("Грибы", false);
									pair<string, bool> biology1_answer1_3("Растения", false);
									pair<string, bool> biology1_answer1_4("Горы", true);
									vector<pair<string, bool>> biology1_answers1 =
									{ biology1_answer1_1, biology1_answer1_2, biology1_answer1_3, biology1_answer1_4 };

									string biology1_question2 = "Какие вещества необходимы для фотосинтеза?";
									pair<string, bool> biology1_answer2_1("Вода, углекислый газ", false);
									pair<string, bool> biology1_answer2_2("Солнечный свет, минеральные вещества", false);
									pair<string, bool> biology1_answer2_3("Вода, солнечный свет, углекислый газ", true);
									pair<string, bool> biology1_answer2_4("Другие живые существа", false);
									vector<pair<string, bool>> biology1_answers2 =
									{ biology1_answer2_1, biology1_answer2_2, biology1_answer2_3, biology1_answer2_4 };

									string biology1_question3 = "Какие организмы являются автотрофами?";
									pair<string, bool> biology1_answer3_1("Грибы", false);
									pair<string, bool> biology1_answer3_2("Бактерии", false);
									pair<string, bool> biology1_answer3_3("Растения", true);
									pair<string, bool> biology1_answer3_4("Животные", false);
									vector<pair<string, bool>> biology1_answers3 =
									{ biology1_answer3_1, biology1_answer3_2, biology1_answer3_3, biology1_answer3_4 };

									string biology1_question4 = "Что такое метаболизм?";
									pair<string, bool> biology1_answer4_1("Способность к размножению", false);
									pair<string, bool> biology1_answer4_2("Обмен веществ", true);
									pair<string, bool> biology1_answer4_3("Процесс роста", false);
									pair<string, bool> biology1_answer4_4("Питание", false);
									vector<pair<string, bool>> biology1_answers4 =
									{ biology1_answer4_1, biology1_answer4_2, biology1_answer4_3, biology1_answer4_4 };

									string biology1_question5 = "Что является частью метаболизма?";
									pair<string, bool> biology1_answer5_1("Рост", false);
									pair<string, bool> biology1_answer5_2("Раздражимость", false);
									pair<string, bool> biology1_answer5_3("Дыхание", true);
									pair<string, bool> biology1_answer5_4("Размножение", false);
									vector<pair<string, bool>> biology1_answers5 =
									{ biology1_answer5_1, biology1_answer5_2, biology1_answer5_3, biology1_answer5_4 };

									string biology1_question6 = "Что происходит при обмене веществ?";
									pair<string, bool> biology1_answer6_1("Простые вещества, поступающие из внешней среды, преобразуются в сложные.", false);
									pair<string, bool> biology1_answer6_2("В клетке из сложных веществ образуются простые вещества", false);
									pair<string, bool> biology1_answer6_3("Сложные вещества распадаются на простые, из которых клетка образует новые вещества", true);
									pair<string, bool> biology1_answer6_4("Сложные вещества используются клеткой в неизменном виде.", false);
									vector<pair<string, bool>> biology1_answers6 =
									{ biology1_answer6_1, biology1_answer6_2, biology1_answer6_3, biology1_answer6_4 };



									Item biology1_task1(biology1_question1, biology1_answers1);
									Item biology1_task2(biology1_question2, biology1_answers2);
									Item biology1_task3(biology1_question3, biology1_answers3);
									Item biology1_task4(biology1_question4, biology1_answers4);
									Item biology1_task5(biology1_question5, biology1_answers5);
									Item biology1_task6(biology1_question6, biology1_answers6);

									list<Item> biology1_questions;
									biology1_questions.push_back(biology1_task1);
									biology1_questions.push_back(biology1_task2);
									biology1_questions.push_back(biology1_task3);
									biology1_questions.push_back(biology1_task4);
									biology1_questions.push_back(biology1_task5);
									biology1_questions.push_back(biology1_task6);

									Test biology1("Биология", "Свойства живых организмов", biology1_questions);

									//-----------------------------------------------------------------------------------

									//-----------------------------------------------------------------------------------

									string biology2_question1 = "Когда впервые человечество стало использовать огонь?";
									pair<string, bool> biology2_answer1_1("500 тыс. лет назад", false);
									pair<string, bool> biology2_answer1_2("1,5 млн лет назад", true);
									pair<string, bool> biology2_answer1_3("2,6 млн лет назад", false);
									pair<string, bool> biology2_answer1_4("9 млн лет назад", false);
									vector<pair<string, bool>> biology2_answers1 =
									{ biology2_answer1_1, biology2_answer1_2, biology2_answer1_3, biology2_answer1_4 };

									string biology2_question2 = "Кто является предком всех человекообразных обезьян?";
									pair<string, bool> biology2_answer2_1("Австралопитек", false);
									pair<string, bool> biology2_answer2_2("Дриопитек", false);
									pair<string, bool> biology2_answer2_3("Хелмеи", false);
									pair<string, bool> biology2_answer2_4("Проконсул", true);
									vector<pair<string, bool>> biology2_answers2 =
									{ biology2_answer2_1, biology2_answer2_2, biology2_answer2_3, biology2_answer2_4 };

									string biology2_question3 = "Где жили дриопитеки?";
									pair<string, bool> biology2_answer3_1("На деревьях", true);
									pair<string, bool> biology2_answer3_2("В саванне", false);
									pair<string, bool> biology2_answer3_3("В пещерах", false);
									pair<string, bool> biology2_answer3_4("В примитивных домах", false);
									vector<pair<string, bool>> biology2_answers3 =
									{ biology2_answer3_1, biology2_answer3_2, biology2_answer3_3, biology2_answer3_4 };

									string biology2_question4 = "Когда появились прямоходящие предки человека?";
									pair<string, bool> biology2_answer4_1("400 тыс. лет назад", false);
									pair<string, bool> biology2_answer4_2("7 млн лет назад", true);
									pair<string, bool> biology2_answer4_3("1,5 млн лет назад", false);
									pair<string, bool> biology2_answer4_4("12 млн лет назад", false);
									vector<pair<string, bool>> biology2_answers4 =
									{ biology2_answer4_1, biology2_answer4_2, biology2_answer4_3, biology2_answer4_4 };

									string biology2_question5 = "Кто является предком неандертальца?";
									pair<string, bool> biology2_answer5_1("Homo sapiens idaltu", false);
									pair<string, bool> biology2_answer5_2("Homo erectus", true);
									pair<string, bool> biology2_answer5_3("Homo sapiens sapiens", false);
									pair<string, bool> biology2_answer5_4("Homo helmei", false);
									vector<pair<string, bool>> biology2_answers5 =
									{ biology2_answer5_1, biology2_answer5_2, biology2_answer5_3, biology2_answer5_4 };

									string biology2_question6 = "Как выглядели австралопитеки?";
									pair<string, bool> biology2_answer6_1("Покрытые шерстью обезьяны, передвигающиеся на четырех лапах", false);
									pair<string, bool> biology2_answer6_2("Прямоходящие обезьяны с волосатым телом и мощными челюстями", true);
									pair<string, bool> biology2_answer6_3("Прямоходящие обезьяны с волосатым телом и «человеческими» чертами лица", false);
									pair<string, bool> biology2_answer6_4("Обезьяны, напоминающие современных горилл", false);
									vector<pair<string, bool>> biology2_answers6 =
									{ biology2_answer6_1, biology2_answer6_2, biology2_answer6_3, biology2_answer6_4 };

									Item biology2_task1(biology2_question1, biology2_answers1);
									Item biology2_task2(biology2_question2, biology2_answers2);
									Item biology2_task3(biology2_question3, biology2_answers3);
									Item biology2_task4(biology2_question4, biology2_answers4);
									Item biology2_task5(biology2_question5, biology2_answers5);
									Item biology2_task6(biology2_question6, biology2_answers6);

									list<Item> biology2_questions;
									biology2_questions.push_back(biology2_task1);
									biology2_questions.push_back(biology2_task2);
									biology2_questions.push_back(biology2_task3);
									biology2_questions.push_back(biology2_task4);
									biology2_questions.push_back(biology2_task5);
									biology2_questions.push_back(biology2_task6);

									Test biology2("Биология", "Как появился человек на Земле", biology2_questions);

									vector<Test> vector_of_tests;
									vector_of_tests.push_back(biology1);
									vector_of_tests.push_back(biology2);

									/*ifstream fin_tests("test.txt", ios::binary);
									if (fin_tests)
									{
										int count;
										Test test_tmp;
										fin_tests.read((char*)&count, sizeof(count));
										vector_of_tests.resize(count);

										for (int i = 0; i < count; i++)
										{
											fin_tests >> test_tmp;
											vector_of_tests.push_back(test_tmp);
										}
										fin_tests.close();
									}
									else cout << "read tests error";*/

									/*ofstream fout_tests("test.txt", ios::binary);
									if (fout_tests)
									{
										int write_count = vector_of_tests.size();
										fout_tests.write(reinterpret_cast<char*>(&write_count), sizeof(write_count));
										for (auto t : vector_of_tests)
										{
											fout_tests << t;
										}
										fout_tests.close();
									}
									else cout << "write tests error";*/

									int i = 0;
									int tests_select;
									for (auto test : vector_of_tests)
									{
										cout << ++i << ". " << test.get_subject() << endl;
										cout << " - " << test.get_chapter();
										cout << endl << endl;
									}

									cout << "Выберите тему теста: ";
									cin >> tests_select;
									cout << "Вы выбрали: ";


									Test selected_test = vector_of_tests[tests_select - 1];

									//Если уже есть результат для этого теста, то удаляем его, так как позже заменим текущим
									bool result_already_in = 0;
									auto it_result_already_in = user_session_result_list.begin();
									for (auto r : user_session_result_list)
									{
										if (r.get_subject() == selected_test.get_subject()
											&& r.get_chapter() == selected_test.get_chapter())
										{
											cout << "Вы уже проходили этот тест.";
											*it_result_already_in = r;
											result_already_in = 1;
										}
									}
									if (result_already_in) user_session_result_list.erase(it_result_already_in);
									//-------------------------------------------------------------------------------------

									list<Item> items_of_selected_test = selected_test.get_test_list();
									string selected_test_subject = selected_test.get_subject();
									string selected_test_chapter = selected_test.get_chapter();
									cout << selected_test_subject << " - ";
									cout << selected_test_chapter << endl;

									for (auto q : items_of_selected_test)
									{
										cout << endl << q;
										cout << "Введите ваш вариант ответа(порядковый номер):";
										cin >> answer_options;
										if (q.get_answer(answer_options - 1))
											correct_answers += 1;
									}
									int number_of_questions = items_of_selected_test.size();
									cout << endl << "Правильных ответов: " << correct_answers << " из " << number_of_questions;
									cout << endl << endl;

									int wrong_answers = number_of_questions - correct_answers;
									int evaluation = 12 / number_of_questions * correct_answers;
									Result test_res(
										user_session,
										selected_test_subject,
										selected_test_chapter,
										number_of_questions,
										correct_answers,
										wrong_answers,
										evaluation);


									cout << "\nРезультат теста: \n" << test_res;

									user_session_result_list.push_back(test_res);

									//Удаляем все предидущие результаты для текущего студента из основного списка результатов
									auto it_del_res = remove_if(result_list.begin(), result_list.end(),
										[user_session](Result r)
										{ return r.get_login() == user_session; }
									);
									result_list.erase(it_del_res, result_list.end());

									//Добавляем в основной список обновленные результаты для текущего студента
									for (auto r : user_session_result_list)
									{
										result_list.push_back(r);
									}

									ofstream fout_result("result.txt", ios::binary);
									if (fout_result)
									{
										int write_count = result_list.size();
										fout_result.write(reinterpret_cast<char*>(&write_count), sizeof(write_count));
										for (auto res : result_list)
										{
											fout_result << res;
										}
										fout_result.close();
									}
									else cout << "write result error";
								}
								else if (user_menu == 0)
								{
								cout << "\nВыход в главное меню\n";
								}
							}while (user_menu != 0);
						}
						else
						{
							cout << "Введен неверный пароль\n";
							cout << "1 - Повторный ввод пароля\n";
							cout << "0 - Отмена\n";
							cin >> repeat_password;
						}
					} while (correct_password == false && repeat_password == 1);
				}
					else cout << "Такого пользователя нет";


			_getch();
			system("CLS");
		}
		else if (main_menu == 3)
		{
			string login_admin;
			string password_admin;
			string check_login_admin;
			string check_password_admin;
			bool correct_log_pas = 0;
			int admin_menu;

			cout << "Введите логин для админа: ";
			cin >> login_admin;
			cout << "Введите пароль для админа: ";
			cin >> password_admin;

			if (_access("admin.txt", 0) == -1)
			{
				ofstream fout_admin("admin.txt", ios::binary);
				if (fout_admin)
				{
					fout_admin << login_admin;
					fout_admin << password_admin;
					fout_admin.close();
					correct_log_pas = 1;
				}
				else cout << "write admin error";
			}
			else 
			{
				
				ifstream fin_admin("admin.txt", ios::binary);
				if (fin_admin)
				{
					fin_admin >> check_login_admin;
					fin_admin >> check_password_admin;
					fin_admin.close();
					
				}
				else cout << "read admin error";

				if(login_admin == check_login_admin && password_admin == check_password_admin)
				{
					correct_log_pas = 1;
				}
				else
				{
					cout << "Логин или пароль не верные";
				}
			}
			if (correct_log_pas)
			{
				cout << "Вы вошли как админ, нажмите любую клавишу чтобы продолжить...";
				do {
					_getch();
					system("CLS");
					cout << "Меню администратора\n";
					cout << "1 - Создание пользователя\n";
					cout << "2 - Удаление пользователя\n";
					cout << "3 - Модификация пользователя\n";
					cout << "4 - Показать список пользователей\n";
					cout << "0 - Выход\n";
					cin >> admin_menu;
					CheckMenuItem(0, 4, admin_menu, 0);

					switch (admin_menu)
					{
					case 1:
					{
						User new_user;
						string new_user_login;
						bool already_in = false;
						cout << "Введите логин: ";
						cin >> new_user_login;

						for (auto user : user_database)
						{
							if (new_user_login == user.get_login())
							{
								already_in = true;
								break;
							}
						}

						if (already_in)
						{
							cout << "\nТакой пользователь уже есть.";
						}
						else
						{
							new_user.init(new_user_login);
							user_database.insert(new_user);
						}
						break;
					}
					case 2:
					{
						User tmp;
						string delete_user;
						cout << "Введите логин пользователя для удаления: ";
						cin >> delete_user;
						for (auto u : user_database)
						{
							if (u.get_login() == delete_user)
							{
								tmp = u;
							}
						}
						if (tmp.get_login() != "no login")
						{
							user_database.erase(tmp);
							cout << "Пользователь удален";
						}
						else cout << "Пользователя с таким логином не существует";
						break;
					}
					case 3:
					{
						string login_user;
						string password_user;

						cout << "Введите логин: ";
						cin >> login_user;

						User find_user(login_user);
						auto it_user = user_database.find(find_user);

						if (it_user != user_database.end())
						{
							User user = *it_user;
							int what_to_change;
							string new_user_data;

							cout << "\nКакие данные желаете поменять: \n";
							cout << "0 - Логин\n";
							cout << "1 - Пароль\n";
							cout << "2 - Имя\n";
							cout << "3 - Фамилия\n";
							cout << "4 - Адрес\n";
							cout << "5 - Телефон\n";
							cout << "6 - Имэйл\n";
							cin >> what_to_change;

							cout << "\nВведите новые данные для этого поля : \n";
							cin >> new_user_data;

							User tmp_user = user;
							user_database.erase(user);

							switch (what_to_change)
							{
							case 0: tmp_user.set_login(new_user_data); break;
							case 1: tmp_user.set_password(new_user_data); break;
							case 2: tmp_user.set_name(new_user_data); break;
							case 3: tmp_user.set_surname(new_user_data); break;
							case 4: tmp_user.set_address(new_user_data); break;
							case 5: tmp_user.set_phone(new_user_data); break;
							case 6: tmp_user.set_mail(new_user_data); break;
							}
							user_database.insert(tmp_user);
							cout << "\nДанные успешно изменены\n";
						}
						else cout << "Такого пользователя нет";
						break;
					}
					case 4:
					{
						if (user_database.size() == 0)
						{
							cout << "Список пуст";
						}
						else
						{
							cout << "\nКоличество пользователей: " << user_database.size() << endl << endl;
							cout << "Список пользователей: \n";
							for (auto user : user_database)
							{
								cout << user.get_login() << endl;
							}
						}
						break;
					}
					case 0:
					{
						cout << "Выход...Для сохранения изменений в файле, необходимо осуществить выход из основного меню!";
						break;
					}
					}
					
				} while (admin_menu != 0);
			}

			
			_getch();
			system("CLS");
		}
		else if (main_menu == 0)
		{
			ofstream fout("user.txt", ios::binary);
			if (fout)
			{
				int write_count = user_database.size();
				fout.write(reinterpret_cast<char*>(&write_count), sizeof(write_count));
				for (auto user : user_database)
				{
					fout << user;
				}
				fout.close();
			}
			else cout << "write error";
		}

	} while (main_menu != 0);

	_getch();
	return 0;

}

