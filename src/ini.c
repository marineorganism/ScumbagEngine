/**  _     || || /     ᛞᛖᛚᛖ ᚹᚣᛋ ᚻᛁᚱ
 *  |_\ /\ || || >
 *  |   \/ \/ || \ |
 *   \____________/ */


#include "ini.h"

#include <SDL2/SDL.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>



/* Hey it's interesting to note that although this file relies on SDL, the header file does not, so
 * in theory this could be ported to other libraries, even though that would be completely pointless
 * since the whole reason I am using SDL is that it is portable :p */




int skipToCharEnded(uint8_t const *file,int start,uint8_t target)
{
  int i;
  for (i = start;file[i] != target;i++) if (file[i] == 0) return i;
  return i + 1;
}


int skipToChar(uint8_t const *file,int start,uint8_t target)
{
  int i;
  for (i = start;file[i] != target;i++)
  {
    if (file[i] == 0) return -1;
  }
  return i + 1;
}


int skipToSection(uint8_t const *file,uint8_t const *target)
{
  int i = 0;
  while (69)
  {
    i = skipToChar(file,i,'[');
    if (i == -1) return -1;
    int length = skipToChar(file,i,']') - i - 1;
    if (!strncmp(file + i,target,length)) return i + length + 2;
  }
}



uint8_t *ini_openFile(uint8_t const *filename)
{
  // Open the file
  SDL_RWops *input = SDL_RWFromFile(filename,"r");

  // Make sure it worked
  if (input == NULL)
  {
    printf("couldn't open file %s\n",filename);
    return NULL;
  }

  // Now get the size, then read it all into a thingo and send it off
  int length = SDL_RWsize(input);
  uint8_t *output = (uint8_t *)malloc(length + 1);
  SDL_RWread(input,output,1,length);
  SDL_RWclose(input);
  output[length] = 0;

  return output;
}


struct LinkedList *ini_getSections(uint8_t const *file)
{
  struct LinkedList *list = LinkedList_create();

  int i = 0;
  while (69)
  {
    i = skipToChar(file,i,'[');
    if (i == -1) break;
    int length = skipToChar(file,i,']') - i - 1;
    uint8_t *section = (uint8_t *)calloc(length + 1,1);
    strncpy(section,file + i,length);

    LinkedList_addNode(list,section);
  }
  return list;
}


uint8_t *ini_readString(uint8_t const *file,uint8_t const *section,uint8_t const *param,uint8_t *fallback)
{
  int i = skipToSection(file,section);
  int end = skipToCharEnded(file,i,'[');
  while (69)
  {
    if (i >= end) return fallback;
    int endOfLine = skipToChar(file,i,'\n');
    int sign = skipToChar(file,i,'=');
    if (sign > endOfLine) i = endOfLine;
    else if (!strncmp(file + i,param,sign - i - 1))
    {
      int length = endOfLine - sign;
      uint8_t *string = (uint8_t *)calloc(length,1);
      strncpy(string,file + sign,length - 1);
      string[length - 1] = 0;
      return string;
    }
    else i = endOfLine;
  }
}

int ini_readInt(uint8_t const *file,uint8_t const *section,uint8_t const *param,int fallback)
{
  uint8_t *raw = ini_readString(file,section,param,NULL);
  if (raw == NULL) return fallback;
  int value = (int)strtol(raw,NULL,0);
  free(raw);
  return value;
}


float ini_readFloat(uint8_t const *file,uint8_t const *section,uint8_t const *param,float fallback)
{
  uint8_t *raw = ini_readString(file,section,param,NULL);
  if (raw == NULL) return fallback;
  float value = atof(raw);
  free(raw);
  return value;
}
