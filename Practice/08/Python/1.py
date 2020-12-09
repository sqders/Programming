var=input()
a,b=int(var[0]),int(var[4])
if( var[2] =='*'):
	print( a * b )
if( var[2] =='+' ):
	print( a + b )
if( var[2] == '-' ):
	print( a - b )
if( var[2] == '/' ):
	print( a / b )