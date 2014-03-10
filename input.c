int factorial(int val)
{
	int result;
	result = 1;
	while( val > 1 )
	{
		result = result * val;
		val = val - 1;
	}
	
	return result;
}

int sqr(int x)
{
	return x * x;
}

void main()
{
	int x;
	
	//pragma(msg, "hi");
	// x = readInt();
	
	x = -5;
	while( x < 4 )
	{
		writeln(x);
		x = x + 1;
	}
	
	writeln(int.min);
}
