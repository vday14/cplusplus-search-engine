//
// Created by nick on 3/13/18.
//

#include <iostream>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

size_t testSum ( );

int main ( )
	{
	int index1 = open( "index0.txt", O_CREAT | O_RDWR, S_IRWXU );
	lseek( index1, 168, SEEK_SET );
	char buffer[100];
	string b;
	while ( read( index1, buffer, 100 ) )
		{
		for ( int i = 0; i < 100; i++ )
			{
			if ( buffer[ i ] == '\0' )
				{
				break;
				}
			cout << buffer[ i ];
			}
		}
//    if(read(index1, buffer, 10) != 10) {
//        cout << "ERROR" << endl;
//    }
	close( index1 );
//    cout << endl;
//    cout << testSum() << endl;
	return 0;
	}

size_t testSum ( )
	{
	string test = "2737761 2109 3775 1544 4821 47 4148 2795 1405 847 35 214 2088 209 2358 1903 896 621 464 1135 570 1833 729 1991 412 367 521 32 1568 12 1392 269 303 5110 2279 2062 1258 4345 24 496 422 2053 8211 1571 247 174 1605 3989";
	size_t sum = 0;
	string currentNum = "";
	for ( char num : test )
		{
		if ( num == ' ' )
			{
			sum += stoll( currentNum );
			currentNum = "";
			}
		else
			{
			currentNum += num;
			}
		}
	sum += stoll( currentNum );
	return sum;
	}