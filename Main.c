#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define StackSize 200000

void dump(int *Stack)
{
  //dump the stack
  for(int i = 0; i < StackSize; i++)
  {
    printf("%d : %d\n", i, Stack[i]);
  }

}



/*
idk i just want to have higher process speed,
because python is slow

The S1monsAssembly3 program that should be executed,
is put in file called "main.txt"
*/


int main(void) {
  FILE *File;
  char FileBuffer[1000];

  File = fopen("main.txt", "r");

  if(File == NULL)
  {
    exit(1);
  }

  fscanf(File, "%[^EOF]", FileBuffer);

  char Delimiter[] = " ";

  char *Splitter;
  int Code[1000];
  int CodeSize = 0;


  Splitter = strtok(FileBuffer, Delimiter);
  while(Splitter != NULL)
  {
    int Data = (int)strtol(Splitter, NULL, 16);
    Code[CodeSize++] = Data;


    Splitter = strtok(NULL, Delimiter);
  }


  int Inst, Attr, Index = 0;

  int Acc = 0;
  int Reg = 0;

  int Mem[256] = {0};
  
  int Stack[StackSize] = {};
  int StackPointer = 0;

  while(Index < CodeSize)
  {
    Inst = Code[Index];
    Attr = Code[Index + 1];

    if(Stack[StackSize - 1] != 0)
    {
      dump(Stack);
      printf("\nError: StackOverflow\n");
      exit(1);
    } 

    switch(Inst){
      case 0:
        break;  

      case 1:
        Reg = Attr;
        break;  

      case 2:
        Acc += Reg;
        break;  

      case 3:
        Acc -= Reg;
        break;  

      case 4:
        Acc <<= 1;
        break;  

      case 5:
        Acc >>= 1;
        break;  

      case 6:
        Acc = Mem[Attr];
        break;  

      case 7:
        Reg = Mem[Attr];
        break;  

      case 8:
        Mem[Attr] = Acc;
        break;  

      case 9:
        Mem[Attr] = Reg;
        break;  

      case 10:
        printf(">>> %d\n", Mem[Attr]);
        break;  

      case 11:
        printf(": ");
        scanf("%d", &Mem[Attr]);
        break;  

      case 12:
        Index = Attr;

        continue;


      case 13:
        if (Acc == 0)
        {
          Index = Attr;
          continue;
        }
        break;  

      case 14:
        if (Acc == Reg)
        {
          Index = Attr;
          continue;
        }
        break;  

      case 15:
        Stack[StackPointer] = Index;
        StackPointer++;

        Index = Attr;
        break;  

      case 16:
        StackPointer--;
        Index = Stack[StackPointer];
        break;  

      case 17:
        Stack[StackPointer] = Acc;
        StackPointer++;
        break;  

      case 18:
        StackPointer--;
        Acc = Stack[StackPointer];
        break;  

      case 19:
        Index = CodeSize + 1;
        break;  

      case 20:
        //this doesnt work here, because there is not KeyIn
        break;        
      
      case 21:
        printf("%c", (char)Acc);
        break;

      case 22:
        system("@cls||clear");
        break;

      case 32:
        Acc = Acc || Reg;
        break;

      case 33:
        Acc = Acc & Reg;
        break;

      case 34:
        Acc = ~ Acc;
        break;

      case 35:
        Acc = Acc ^ Reg;
        break;

      case 36:
        Acc = Mem[Mem[Attr]];
        break;

      case 37:
        Reg = Mem[Mem[Attr]];
        break;

      case 38:
        Mem[Mem[Attr]] = Acc;
        break;

      case 39:
        Mem[Mem[Attr]] = Reg;
        break;

      case 40:
        if (Acc > Reg)
          {
            Index = Attr;
            continue;
          }
          break;  

      case 41:
        if (Acc < Reg)
          {
            Index = Attr;
            continue;
          }
          break;  



    }
  
    Index += 2;

  }




  return 0;
}