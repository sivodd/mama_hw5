#include <iostream>
#include <stdio.h>

#include "MySharedPtr.h"
#include "Variable.h"
#include "Scalar.h"

int main()
{
	VarPtr x = VarPtr(new Scalar(1));
	int y = (*x)[1];

    return 0;
}
