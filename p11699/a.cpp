#include <bits/stdc++.h>

using namespace std;

const int n = 15;
bool grid[n][n];
bool temp[n][n];
char s[n];

int main()
{
	while( true )
	{
		for(int i = 0 ; i < n ; i++)
        {
            scanf("\n%s" ,s);
            if( s[0] == 'E' ) return 0;

			for(int j = 0 ; j < n ; j++){
				grid[i][j] = (s[j] == '#');
			}
		}

		vector< pair<int , int> > rows;
		for(int i = 0 ; i < n ; i++)
		{
			rows.push_back( make_pair(0 ,i) );

			for(int j = 0 ; j < n ; j++){
				rows.back().first += grid[i][j];
			}
		}
		sort(rows.rbegin(), rows.rend());

		int ans = n;
		// try all possible rows and keep the min ans
		for(int rowMask = 0 ; rowMask < (1 << n) ; rowMask ++)
		{
			for(int i = 0 ; i < n ; i++){
				for(int j = 0 ; j < n ; j++){
					temp[i][j] = grid[i][j];
				}
			}

			int l = 0 ,r = (int)rows.size() - 1;
			while( l < (int)rows.size() )
			{
				int T = rowMask & (1 << rows[l].second);
				if( T == 0 )
				{
					l += 1;
					continue;
				}

				int i = -1;
				for(int k = 0 ; i == -1 && k < n ; k++) if( temp[ rows[l].second ][k] ) i = k;
				if( i == -1 )
				{
					l += 1;
					continue;
				}

				if( r < 0 )
				{
					for(int k = 0 ; k < n ; k++){
						temp[ rows[l].second ][k] = false;
					}
				}
				else
				{
					T = rowMask & (1 << rows[r].second);
					if( T != 0 )
					{
						r -= 1;
						continue;
					}

					i = -1;
					for(int k = 0 ; i == -1 && k < n ; k++) if( temp[ rows[r].second ][k] ) i = k;
					if( i == -1 )
					{
						r -= 1;
						continue;
					}

					for(int k = 0 ; k < n ; k++){
						temp[ rows[l].second ][k] = temp[k][i] = false;
					}
				}
			}

			bool flag = true;
			for(int i = 0 ; flag && i < n ; i++){
				for(int j = 0 ; flag && j < n ; j++){
					flag &= !temp[i][j];
				}
			}
			if( flag ){
				ans = min(ans ,__builtin_popcount(rowMask));
			}
		}

		printf("%d\n" ,ans);
	}
}
