#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

int preferences[MAX_VOTERS][MAX_CANDIDATES];

typedef struct
{
	char* name;
	int votes;
	bool eliminated;
} candidate;

candidate candidates[MAX_CANDIDATES];

int voter_count;
int candidate_count;

bool vote(int voter, int rank, char* name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int get_int(const char* prompt)
{
	int value;
	printf("%s", prompt);
	while (scanf("%d", &value) != 1)
	{
		while (getchar() != '\n');
		printf("%s", prompt);
	}
	
	while (getchar() != '\n');
	return value;
}

char* get_string(const char* prompt)
{
	static char buffer[256];
	printf("%s", prompt);
	if (fgets(buffer, sizeof(buffer), stdin) == NULL)
	{
		buffer[0] = '\0';
		return buffer;
	}
	
	size_t len = strlen(buffer);
	if (len > 0 && buffer[len - 1] == '\n')
	{
		buffer[len - 1] = '\0';
	}
	return buffer;
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Usage: runoff [candidate ...]\n");
		return 1;
	}

	candidate_count = argc - 1;
	if (candidate_count > MAX_CANDIDATES)
	{
		printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
		return 2;
	}

	for (int i = 0; i < candidate_count; i++)
	{
		candidates[i].name = argv[i + 1];
		candidates[i].votes = 0;
		candidates[i].eliminated = false;
	}

	voter_count = get_int("Number of voters: ");
	if (voter_count > MAX_VOTERS)
	{
		printf("Maximum number of voters is %i\n", MAX_VOTERS);
		return 3;
	}

	for (int i = 0; i < voter_count; i++)
	{
		for (int j = 0; j < candidate_count; j++)
		{
			char* name = get_string("Rank: ");

			if (!vote(i, j, name))
			{
				printf("Invalid vote.\n");
				return 4;
			}
		}
		printf("\n");
	}

	while (true)
	{
		tabulate();

		bool won = print_winner();
		if (won)
		{
			break;
		}

		int min = find_min();
		bool tie = is_tie(min);

		if (tie)
		{
			for (int i = 0; i < candidate_count; i++)
			{
				if (!candidates[i].eliminated)
				{
					printf("%s\n", candidates[i].name);
				}
			}
			break;
		}

		eliminate(min);

		for (int i = 0; i < candidate_count; i++)
		{
			candidates[i].votes = 0;
		}
	}

	return 0;
}

bool vote(int voter, int rank, char* name)
{
	for (int i = 0; i < candidate_count; i++)
	{
		if (strcmp(candidates[i].name, name) == 0)
		{
			preferences[voter][rank] = i;
			return true;
		}
	}
	return false;
}

void tabulate(void)
{
	for (int i = 0; i < voter_count; i++)
	{
		for (int j = 0; j < candidate_count; j++)
		{
			int candidate_index = preferences[i][j];

			if (!candidates[candidate_index].eliminated)
			{
				candidates[candidate_index].votes++;
				break;
			}
		}
	}
}

bool print_winner(void)
{
	int majority = voter_count / 2;
	for (int i = 0; i < candidate_count; i++)
	{
		if (!candidates[i].eliminated && candidates[i].votes > majority)
		{
			printf("%s\n", candidates[i].name);
			return true;
		}
	}
	return false;
}

int find_min(void)
{
	int min_votes = voter_count;

	for (int i = 0; i < candidate_count; i++)
	{
		if (!candidates[i].eliminated && candidates[i].votes < min_votes)
		{
			min_votes = candidates[i].votes;
		}
	}
	return min_votes;
}

bool is_tie(int min)
{
	for (int i = 0; i < candidate_count; i++)
	{
		if (!candidates[i].eliminated && candidates[i].votes != min)
		{
			return false;
		}
	}
	return true;
}

void eliminate(int min)
{
	for (int i = 0; i < candidate_count; i++)
	{
		if (!candidates[i].eliminated && candidates[i].votes == min)
		{
			candidates[i].eliminated = true;
		}
	}
}