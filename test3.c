#include <stdio.h>
#include <stdlib.h>

struct sPerson {
	int age;
	struct sPerson *nextInLine;
};

struct sPerson *getNewPerson(const int age)
{
	struct sPerson *newPerson = NULL;
	newPerson = malloc(sizeof(struct sPerson));
	newPerson->nextInLine = NULL;
	newPerson->age = age;
	printf("Created new person at %p\n", newPerson);
	return newPerson;
}

void printPerson(const struct sPerson *person, const char *comment)
{
	if (!person){
		printf("%s is NULL\n", comment);
	} else{
		printf("%s: age:%d address:%p nextInLine:%p\n",
			comment, person->age, person, person->nextInLine);

	}
}

int main(){
	struct sPerson *first = NULL;
	struct sPerson *added = NULL;

	


	return 0;
}