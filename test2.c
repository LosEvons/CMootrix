#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <locale.h>

struct sWords {
  char *word;
  long frequency;
  struct sWords *nextInLine;
};

struct sWords *getNewWord(char *in_word){
  struct sWords *newWord = NULL;
  newWord = malloc(sizeof(struct sWords));
  if (newWord != NULL){
    newWord->nextInLine = NULL;
    newWord->word = NULL;
    newWord->word = strdup(in_word);
    //newWord->word = malloc(sizeof(strcpy(newWord->word, in_word)));
    //strcpy(newWord->word, in_word);
    newWord->frequency = 1;
  } else {printf("Memory allocation failure\n");}
  return newWord;
}

void printWord(const struct sWords *SWord, const char *comment)
{
  if (!SWord){
    printf("%s is NULL\n", comment);
  } else{
    printf("%s: word:%s frequency:%ld\n",
      comment, SWord->word, SWord->frequency);
  }
}

void printList(const struct sWords *list)
{
  printf("Printing list:\n");
  const struct sWords *t;
  t = list;
  if (t == NULL){
    printf("list is empty\n");
  }
  else
  {
    while(t)
    {
      printWord(t, "Word");
      t = t->nextInLine;
    }
  }
}

void writeList(const struct sWords *list)
{
  const struct sWords *t;
  t = list;

  FILE *fout = fopen("testout.csv", "w");
  while (t)
  {
    fprintf(fout, "[%s,%ld],\n", t->word, t->frequency);
    t = t->nextInLine;
  }
  fclose(fout);
}

void CleanUp(struct sWords *list)
{
  struct sWords *next;
  while(list)
  {
    next = list->nextInLine;
    free(list);
    list = next;
  }
}

bool CheckForDuplicates(struct sWords *list, char *word_in)
{
  bool dup_flag;
  dup_flag = false;
  struct sWords *temp_iter = list;

  while (temp_iter)
  {
    if (strcmp(temp_iter->word, word_in) == 0){
      dup_flag = true;
      ++temp_iter->frequency;
      break;
    }
    temp_iter = temp_iter->nextInLine;
  }
  return dup_flag;
}


int main(){
  //Initializing some variables
  int i, j, l, baa;

  setlocale(LC_CTYPE, "");

  char *buffer = 0;
  long length;

  //Some useful variables :)
  char placeholder_string[50], incoming_word[50];
  struct sWords *first = NULL;
  struct sWords *added = NULL;

  //fileopen
  FILE *f = fopen("sv.txt", "r");

  //fileprocessing
  if (f){
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = malloc(length + 1);
    if (buffer){
      fread(buffer, 1, length, f);
    }
    fclose(f);
    buffer[length] = '\0';
  }

  //content processing
  if (buffer){
    for(i = 0; buffer[i] != '\0'; ++i)
    {
      if (isalnum(buffer[i]) != 8 && (buffer[i] >= '!' && buffer[i] <= '/' && buffer[i] != '\n' && (char)buffer[i] != (char)0x08)){
        for(j = i; buffer[j] != '\0'; ++j)
        {
            buffer[j] = buffer[j+1];
        }
        buffer[j] = '\0'; 
      }
  }
    printf("%ld\n", strlen(buffer));
    for(i=0; buffer[i] != '\0'; ++i)
    {
      if (buffer[i] != ' '){
        buffer[i] = tolower(buffer[i]);
        strncat(placeholder_string, &buffer[i], 1);
      } 
      else {
        if (placeholder_string != (char)0x00){
          if (first==NULL){
            first = getNewWord(placeholder_string);
            if (first != NULL){
              added = first;
            }
          }
          else {
            if (!CheckForDuplicates(first, placeholder_string)){
              added->nextInLine = getNewWord(placeholder_string);
              if(added->nextInLine != NULL)
                added = added->nextInLine;
              memset(placeholder_string, 0, strlen(placeholder_string));
              continue;
            }
          }
          memset(placeholder_string, 0, strlen(placeholder_string));
        }
      }
    }
    //if ((char)*placeholder_string == ((char)0x00))
    if ((long)*placeholder_string == (long)0x00)
      added->nextInLine = getNewWord(placeholder_string);
      if (added->nextInLine != NULL)
        added = added->nextInLine;
    memset(placeholder_string, 0, strlen(placeholder_string));

  writeList(first);
  CleanUp(first);
  first = NULL;
  added = NULL;
  }
  return 0;
}