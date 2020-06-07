#pragma once
#include <sys/types.h>

void signalParent(int sigNum);
void signalChild(int sigNum);
