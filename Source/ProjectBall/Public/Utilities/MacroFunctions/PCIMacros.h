#pragma once

#include "CoreMinimal.h"

// Define the PCI_Log macro
#define PCI_Log(Verbosity, Format, ...) \
UE_LOG(LogTemp, Verbosity, TEXT(Format), ##__VA_ARGS__)