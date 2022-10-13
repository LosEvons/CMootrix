#include <stdio.h>
#include <stdlib.h>

int check_text_file_lenght(FILE* file){
	fseek(file, 0, SEEK_END);
	int lengthOfFile = ftell(file);
	return lengthOfFile;
}

int main(){
	FILE* fptr;
	fptr = fopen("texttest.txt", "r");

	int file_lenght = check_text_file_lenght(fptr);
	char content[file_lenght];
	
	if (fptr){
		printf("Fileopen success \n");
		while (fgets(content, file_lenght, fptr)){
			printf("%s", content);
		}
	} 

	else {
		printf("Fileopen failure \n");
	}

	return 0;
}