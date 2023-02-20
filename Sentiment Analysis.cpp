#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <fstream>
#include <math.h>
#include <windows.h>

using namespace std;

struct Naive_Bayes
{
	char words[100] = {};
	float pos_frequency = 0;
	float neg_frequency = 0;
	float pos_probability = 0;
	float neg_probability = 0;

};

void Read_File(char file[5][80], char label[5])
{
	int index = 0;
	ifstream myFile;

	HANDLE colour = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(colour, 6);

	myFile.open("Sentences.txt");
	if (myFile.is_open())
	{
		while (!myFile.eof())
		{


			myFile.getline(file[index], 80);


			index++;

		}

	}

	label[0] = 'P';
	label[1] = 'P';
	label[2] = 'N';
	label[3] = 'N';
	label[4] = 'N';
}

void Print_Read_File(char file[5][80])
{
	cout << "\n\tSentences: " << endl << endl;
	cout << "\tFirst 2 Sentences are Positive and Last 3 Sentences are Negative" << endl << endl;
	for (int index = 0; index < 2; index++)
	{
		HANDLE colour = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(colour, 10);

		cout << "\n\t" << file[index] << endl;

	}

	for (int index = 2; index < 5; index++)
	{

		HANDLE colour = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(colour, 4);

		cout << "\n\t" << file[index] << endl;

	}
	cout << endl;

	HANDLE colour = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(colour, 3);

	cout << "\t-----------------------------------------";

}

void Frequency(Naive_Bayes arr[100], char label, int index, int& Negative_Frequency_Sum, int& Positive_Frequency_Sum)
{

	if (label == 'N')
	{
		arr[index].neg_frequency++;
		Negative_Frequency_Sum++;
	}
	else if (label == 'P')
	{
		arr[index].pos_frequency++;
		Positive_Frequency_Sum++;
	}

}

void Print_Frequency(Naive_Bayes arr[100], int count)
{
	HANDLE colour = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(colour, 3);

	cout << "\t-----------------------------------------" << endl << endl;

	SetConsoleTextAttribute(colour, 10);

	cout << "\tAll Positive Words Frequency: ";
	for (int index = 0; index < count; index++)
		cout << arr[index].pos_frequency << "      ";
	cout << endl << endl;

	SetConsoleTextAttribute(colour, 4);

	cout << "\tAll Negative Words Frequency: ";
	for (int index = 0; index < count; index++)
		cout << arr[index].neg_frequency << "      ";
	cout << endl << endl;

	SetConsoleTextAttribute(colour, 3);

	cout << "\t-----------------------------------------" << endl << endl;

}

void Probabilty(Naive_Bayes arr[100], int Negative_Frequency_Sum, int Positive_Frequency_Sum, int count)
{

	for (int index = 0; index < count; index++)
	{

		arr[index].pos_probability = (arr[index].pos_frequency + 1) / (Positive_Frequency_Sum + count);
		arr[index].neg_probability = (arr[index].neg_frequency + 1) / (Negative_Frequency_Sum + count);

	}


}

void Print_Probability(Naive_Bayes arr[100], int count)
{
	HANDLE colour = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(colour, 10);

	cout << "\tPositive Frequency Words Probability: ";
	for (int index = 0; index < count; index++)
		cout << arr[index].pos_probability << "  ";
	cout << endl << endl;

	SetConsoleTextAttribute(colour, 4);

	cout << "\tNegative Frequency Words Probability: ";
	for (int index = 0; index < count; index++)
		cout << arr[index].neg_probability << "  ";
	cout << endl << endl;

	SetConsoleTextAttribute(colour, 3);

	cout << "\t-----------------------------------------" << endl << endl;

}

void Sum_of_Probability(Naive_Bayes arr[100])
{
	float sum_p_prob = 0;
	float sum_n_prob = 0;
	for (int index = 0; index < 15; index++)
	{

		sum_p_prob = sum_p_prob + arr[index].pos_probability;
		sum_n_prob = sum_n_prob + arr[index].neg_probability;

	}

	HANDLE colour = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(colour, 10);

	cout << "\tSum of All Positive Words Probability: " << sum_p_prob << endl << endl;

	SetConsoleTextAttribute(colour, 4);

	cout << "\tSum of All Negative Words Probability: " << sum_n_prob << endl << endl;

	SetConsoleTextAttribute(colour, 3);

	cout << "\t-----------------------------------------" << endl << endl;

}

void Sentences_and_Words_Probability(char label[80], float& positive_sentence_probability, float& negative_sentence_probability)
{

	float counter_p = 0;
	float counter_n = 0;
	float total_sentences = 0;
	for (int index = 0; index < 5; index++)
	{
		if (label[index] == 'P')
		{
			counter_p++;

		}
		else if (label[index] == 'N')
		{

			counter_n++;

		}

	}
	total_sentences = counter_p + counter_n;

	HANDLE colour = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(colour, 10);

	cout << "\tTotal Positive Sentences: " << counter_p << endl << endl;

	SetConsoleTextAttribute(colour, 4);

	cout << "\tTotal Negative Sentences: " << counter_n << endl << endl;

	SetConsoleTextAttribute(colour, 6);

	cout << "\tTotal Sentences: " << total_sentences << endl << endl;

	SetConsoleTextAttribute(colour, 3);

	cout << "\t-----------------------------------------" << endl << endl;

	SetConsoleTextAttribute(colour, 10);

	cout << "\tTotal Positive Sentences Probability: " << counter_p / total_sentences << endl << endl;

	SetConsoleTextAttribute(colour, 4);

	cout << "\tTotal Negative Sentences Probability: " << counter_n / total_sentences << endl << endl;

	SetConsoleTextAttribute(colour, 3);

	cout << "\t-----------------------------------------" << endl << endl;

	positive_sentence_probability = counter_p / total_sentences;
	negative_sentence_probability = counter_n / total_sentences;

}

void Unique_Words(Naive_Bayes arr[100], char token[100], int& count, char label, int& Negative_Frequency_Sum, int& Positive_Frequency_Sum)
{
	int index = 0;
	int x;
	int y = 1;
	for (index = 0; index < count; index++)
	{
		x = strcmp(arr[index].words, token);
		if (x == 0)
		{
			Frequency(arr, label, index, Negative_Frequency_Sum, Positive_Frequency_Sum);
			y = 0;
		}
	}
	if (y == 1)
	{
		strcpy(arr[index].words, token);
		Frequency(arr, label, index, Negative_Frequency_Sum, Positive_Frequency_Sum);
		count++;
	}

}

void Print_Unique_Words(Naive_Bayes arr[100], int count)
{
	for (int index = 0; index < count; index++)
		cout << arr[index].words << "   ";
	cout << endl << endl;
}

void Tokens(Naive_Bayes arr[100], char file[100], char label, char token[100], int& count, int& Negative_Frequency_Sum, int& Positive_Frequency_Sum)
{
	char delimiter[] = " ";

	char* tok = strtok(file, delimiter);
	while (tok)
	{
		strcpy(token, tok);
		Unique_Words(arr, token, count, label, Negative_Frequency_Sum, Positive_Frequency_Sum);
		tok = strtok(NULL, delimiter);
	}
}

void Result(Naive_Bayes arr[100], int count, float positive_sentence_probability, float negative_sentence_probability)
{
	HANDLE colour = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(colour, 6);

	cout << "\tEnter the New Sentence to Check Whether Sentence is Positive or Negative: " << endl << endl << endl;

	float Positive_Sentence_Probability = 1;
	float Negative_Sentence_Probability = 1;
	char New_Sentence[120];
	cout << "\t";

	SetConsoleTextAttribute(colour, 3);

	cin.getline(New_Sentence, 120);
	cout << endl << endl;

	SetConsoleTextAttribute(colour, 6);

	if (New_Sentence[0] != '\0')
	{
		cout << "\tUnique Words: ";
		Print_Unique_Words(arr, count);

		cout << endl;

		char delimeter[] = " ";
		int d;
		char* tok = strtok(New_Sentence, delimeter);
		while (tok)
		{
			for (int index = 0; index < count; index++)
			{
				d = strcmp(arr[index].words, tok);
				if (d == 0)
				{
					Positive_Sentence_Probability = Positive_Sentence_Probability * arr[index].pos_probability;
					Negative_Sentence_Probability = Negative_Sentence_Probability * arr[index].neg_probability;
					break;
				}
			}
			tok = strtok(NULL, delimeter);
		}
		SetConsoleTextAttribute(colour, 10);

		cout << "\tTotal Positive Words Probability: " << Positive_Sentence_Probability << endl << endl;

		SetConsoleTextAttribute(colour, 4);

		cout << "\tTotal Negative Words Probability: " << Negative_Sentence_Probability << endl << endl;

		Positive_Sentence_Probability = Positive_Sentence_Probability * positive_sentence_probability;
		Negative_Sentence_Probability = Negative_Sentence_Probability * negative_sentence_probability;

		SetConsoleTextAttribute(colour, 10);

		cout << "\tProduct of Total Positive Words Probability & Total Positive Sentences Probability : " << Positive_Sentence_Probability << endl << endl;

		SetConsoleTextAttribute(colour, 4);

		cout << "\tProduct of Total Negative Words Probability & Total Negative Sentences Probability : " << Negative_Sentence_Probability << endl << endl;

		SetConsoleTextAttribute(colour, 3);

		cout << "\t-----------------------------------------" << endl << endl << endl;

		SetConsoleTextAttribute(colour, 6);

		cout << "\tResult: " << endl << endl << endl;

		if (Positive_Sentence_Probability > Negative_Sentence_Probability)
		{
			SetConsoleTextAttribute(colour, 10);

			cout << "\tNew Sentence is Positive." << endl << endl;
		}

		else
		{
			SetConsoleTextAttribute(colour, 4);

			cout << "\tNew Sentence is Negative." << endl << endl;

		}
	}

	else
		cout << " ";


}

void Setup()
{

	HANDLE colour = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(colour, 3);

	cout << endl << endl;
	cout << "\t\t\t\t\tWelcome To PT Sentiment Analysis Project" << endl << endl;
	cout << "\n\n\tFALL-2020 BSCS" << endl;
	cout << "\tSECTION B" << endl;
	cout << "\tGroup 2" << endl << endl;
	cout << "\tGroup Members: " << endl << endl;
	cout << "\tMuhammad Abdur-Rehman-022" << endl;
	cout << "\tMuhammad Ammar Zaid-014" << endl;
	cout << "\tMohammad Ali-052" << endl << endl << endl;


	cout << "\t";
	system("PAUSE");
	system("cls");

}

int main()
{
	Setup();

	float positive_sentence_probability;
	float negative_sentence_probability;
	int count = 0;
	int Negative_Frequency_Sum = 0;
	int Positive_Frequency_Sum = 0;

	Naive_Bayes arr[100];
	char file[5][80];
	char label[5];
	Read_File(file, label);
	Print_Read_File(file);
	char token[100];

	for (int index = 0; index < 5; index++)
	{
		Tokens(arr, file[index], label[index], token, count, Negative_Frequency_Sum, Positive_Frequency_Sum);
	}

	Probabilty(arr, Negative_Frequency_Sum, Positive_Frequency_Sum, count);

	HANDLE colour = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(colour, 6);

	cout << "\n\n\tUnique Words: ";
	Print_Unique_Words(arr, count);

	Print_Frequency(arr, count);

	SetConsoleTextAttribute(colour, 10);

	cout << "\tTotal Positive Words: " << Positive_Frequency_Sum << endl << endl;

	SetConsoleTextAttribute(colour, 4);

	cout << "\tTotal Negative Words: " << Negative_Frequency_Sum << endl << endl;

	SetConsoleTextAttribute(colour, 6);

	cout << "\tTotal Unique Words: " << count << endl << endl;

	SetConsoleTextAttribute(colour, 3);

	cout << "\t-----------------------------------------" << endl << endl;

	Print_Probability(arr, count);
	Sum_of_Probability(arr);
	Sentences_and_Words_Probability(label, positive_sentence_probability, negative_sentence_probability);
	Result(arr, count, positive_sentence_probability, negative_sentence_probability);
	
	SetConsoleTextAttribute(colour, 3);

}
