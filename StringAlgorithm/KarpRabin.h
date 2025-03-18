#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int KarpRabin(char* Text, int TextSize, int Start, char* Pattern, int PatternSize);
int Hash(char* String, int Size);
int ReHash(char* String, int Start, int Size, int HashPrev, int Coefficient);