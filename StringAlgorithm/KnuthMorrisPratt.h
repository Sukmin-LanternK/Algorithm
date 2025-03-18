#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int KMP(char* Text, int TextSize, int Start, char* Pattern, int PatternSize);
void Preprocess(char* Pattern, int PatternSize, int* Border);
