#include <stdio.h>

void bubble_sort(int array[], int size);
void selectioun_sort(int array[], int size);

int main()
{
	int array[] = { 9, 11, 55, 44, 33 };
	int n = 5;

	printf("Sorce array:\n");
	for (int i = 0; i < n; i++)
	{
		printf(" %d", array[i]);
	}

	printf("\n");

	bubble_sort(array, n);

	selectioun_sort(array, n);

	printf("Sorted array:\n");
	for (int i = 0; i < n; i++)
	{
		printf(" %d", array[i]);
	}
}

void selectioun_sort(int array[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int min_idx = i;
		for (int j = i + 1; j < size; j++)
		{
			if (array[j] < array[min_idx])
			{
				min_idx = j;
			}

			if (min_idx != i)
			{
				int temp = array[i];
				array[i] = array[min_idx];
				array[min_idx] = temp;
			}
		}
	}
}

void bubble_sort(int array[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (array[j] > array[j + 1])
			{
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}