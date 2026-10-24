#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef char *string;

struct candidate
{
	string name;
	int votes;
};

struct candidate candidates[3] = {
	{"Alice", 0},
	{"Bob", 0},
	{"Charlie", 0}
};
int candidate_count = 3;

bool vote(string name)
{
	for (int j = 0; j < candidate_count; j++)
	{
		if (strcmp(name, candidates[j].name) == 0)
		{
			candidates[j].votes++;
			return true;
		}
	}
	return false;
}

void print_winner(void)
{
	int max_votes = 0;
	for (int j = 0; j < candidate_count; j++)
	{
		if (candidates[j].votes > max_votes)
		{
			max_votes = candidates[j].votes;
		}
	}

	for (int j = 0; j < candidate_count; j++)
	{
		if (candidates[j].votes == max_votes)
		{
			printf("%s\n", candidates[j].name);
		}
	}
}

int main()
{
	string votes[5] = { "Alice", "Bob", "Alice", "Charlie", "Bob" };

	for (int i = 0; i < 5; i++)
	{
		vote(votes[i]);
	}

	printf("Winner(s):\n");
	print_winner();

	return 0;
}