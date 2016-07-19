#include "fstream"
#include "algorithm"
#include "cstdio"
#include "cstring"

using namespace std;

#define MAX 720000	// So n lon nhat co the sap xep truc tiep

float arr[MAX];

/*********************************************************************/
void obama_sort(char *file_in, char *file_out);
void sort_to_file(FILE *fin, char *file_name, int size_file);
void merge(char *file_tmp, int size_file, float *arr, char *file_out);
void remove_file(char *file_name);
/*********************************************************************/

int main()
{
	obama_sort("sort3mb.inp", "sort3mb.out");
	return 0;
}

/*********************************************************************/
void obama_sort(char *file_in, char *file_out)
{
	FILE *fin = fopen(file_in, "r");
	int n;
	fscanf(fin, "%d", &n);

	char *file_tmp = NULL;

	if(n > MAX){	// Truong hop n vuot qua MAX => phai dung file tam
		int size_file = n - MAX;
		char *file_tmp = "tmp~.txt";
		sort_to_file(fin, file_tmp, size_file);	// Imput so so vuot qua MAX vao mang, sort, dua vao file tmp~.txt

		// Input MAX so con lai vao mang, sort
		for(int i = 0; i < MAX; i++)
			fscanf(fin, "%f", arr + i);
		sort(arr, arr + MAX);

		merge(file_tmp, size_file, arr, file_out);	// Ghep file tmp~.txt va mang arr dua ra output
		remove_file(file_tmp);	// Xoa file tmp~.txt
	}
	else	// Truong hop n < MAX, co the sap xep truc tiep khong can file tam
		sort_to_file(fin, file_out, n);

	fclose(fin);
}

void sort_to_file(FILE *fin, char *file_name, int size_file)
{
	FILE *fout = fopen(file_name, "w");

	for(int i = 0; i < size_file; i++)
		fscanf(fin, "%f", arr + i);
	sort(arr, arr + size_file);

	for(int i = 0; i < size_file; i++)
		fprintf(fout, "%.2f ", arr[i]);

	fclose(fout);
}

void merge(char *file_tmp, int size_file, float *arr, char *file_out)
{
	FILE *ftmp = fopen(file_tmp, "r");
	FILE *fout = fopen(file_out, "w");
	float tmp;
	int count = 0;

	fscanf(ftmp, "%f", &tmp);
	while(size_file > 0 && count < MAX){
		if(tmp < arr[count]){
			fprintf(fout, "%.2f ", tmp);
			fscanf(ftmp, "%f", &tmp);
			size_file--;
		}
		else
			fprintf(fout, "%.2f ", arr[count++]);
	}
	while(size_file-- > 0){
		fprintf(fout, "%.2f ", tmp);
		fscanf(ftmp, "%f", &tmp);
	}
	while(count < MAX)
		fprintf(fout, "%.2f ", arr[count++]);

	fclose(ftmp);
	fclose(fout);
}

void remove_file(char *file_name)
{
	char tmp[20] = "rm ";
	strcat(tmp, file_name);
	system(tmp);
}