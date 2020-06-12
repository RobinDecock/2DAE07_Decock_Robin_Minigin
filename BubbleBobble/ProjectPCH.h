#pragma once

#include <iostream>
#include "Windows.h"

#include "SDLS.h"
#include "GLMS.h"
#include "BOX2DS.h"

#define UNREF(X) UNREFERENCED_PARAMETER(X)

template <class T>
void SafeDelete(T& pObjectToDelete)
{
	if (pObjectToDelete != nullptr)
	{
		delete(pObjectToDelete);
		pObjectToDelete = nullptr;
	}
}
