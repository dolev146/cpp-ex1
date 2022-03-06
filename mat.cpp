#include "mat.hpp"
// hours wasted: 30

namespace ariel
{
    void check_errors(int width, int height, char first_char, char second_char)
    {
        // according to demo file line 36 mat size is always odd
        if ((width * height) % 2 == 0)
        {
            throw std::invalid_argument("Mat size is always odd");
        }
    }

    char *allocate_mat(int width, int height, char **mat)
    {
        // now we allocate the memory inside the rows and cols
        // https://stackoverflow.com/questions/7684712/2d-matrix-allocation-on-heap-in-c
        char *mat_ptr = new char[width * height];
        for (int i = 0; i < width; ++i)
        {
            mat[i] = mat_ptr + i * height;
        }
        return mat_ptr;
    }

    void make_matress(int width, int height, char **mat, char first_char)
    {
        // i am copying the example an got confused all the time
        // with the a and b so i make the same function identically as possible
        /*
        // fill the pattern of second char according to the rules from the python3 example  from the blog
        // https://tio.run/##Tc6xDoMgFAXQna9gaKJU0KrpYuVLKAOoVYxFQm0KX2@hLl3evck9wzN@m1Zd77vEAne4p0qb95ai/GUWFRKM1Ao9DkBgGbYtFQjHkAhYyljPzxI@VgsVVBqOYeXAUU8v4DOpZYCulUUVZt@KomrAP3VYEIcayxRnntNfSlKS0LsDzgf0WBIfoeNsjlAEdfQAXUarmw8HGBsfS@46yedV6fQpTJocHVuE0L7XsLzCE8y@
            b,a,c,d=input().split()
            g=range
            a,b=int(a),int(b)
            r=[[d]*b for i in g(a)]
            x=y=0
            while x<b/2or y<a/2:
             for i in g(x,a-x):r[i][y]=r[i][b-1-y]=c
             for j in g(y,b-y):r[x][j]=r[a-1-x][j]=c
             x+=2;y+=2
            print('\n'.join(map(''.join,r)))
    */
        /* first attempt */
        // int b = width;
        // int a = height;
        // int y = 0;
        // int x = 0;
        // while (x < b / 2 || y < a / 2)
        // {
        //     for (int i = x; i < (a - x); i++)
        //     {
        //         mat[i][y] = mat[i][b - 1 - y] = first_char;
        //     }
        //     for (int j = y; j < (b - y); j++)
        //     {
        //         mat[x][j] = mat[a - 1 - x][j] = first_char;
        //     }
        //     x += 2;
        //     y += 2;
        // }

        /* printed
        @@@@@@@
        @@-----
        @@@@@@@
        @@@---@
        @@@@@@@
        @@-----
        @@@@@@@
        @@-----
        -------

        @@@@@
        @@@@@
        @@@@@
        @@@@@
        @@@@@
        @@@@@
        @@@--
        -----
        -----
        -----
        -----
        -----
        -----
        */

        /* second attempt */

        // int b = height;
        // int a = width;
        // int y = 0;
        // int x = 0;
        // while (x < b / 2 || y < a / 2)
        // {
        //     for (int i = x; i < (a - x); i++)
        //     {
        //         mat[i][y] = first_char;
        //         mat[i][b - 1 - y] = first_char;
        //     }
        //     for (int j = y; j < (b - y); j++)
        //     {
        //         mat[x][j] = first_char;
        //         mat[a - 1 - x][j] = first_char;
        //     }
        //     x += 2;
        //     y += 2;
        // }
    }

    void print_mat(int width, int height, char **mat)
    {
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                std::cout << mat[i][j];
            }
            std::cout << std::endl;
        }
    }

    std::string mat(int width, int height, char first_char, char second_char)
    {
        // allocated variables
        // char **mat           V
        // char *mat_ptr        V
        // dealocated variables
        // char **mat           V
        // char *mat_ptr        V

        check_errors(width, height, first_char, second_char);

        // allocate matrix memory
        // https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
        char **ary = new char *[height];
        for (int i = 0; i < height; ++i)
        {
            ary[i] = new char[width];
        }

        // initialize with the second char
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                ary[i][j] = second_char;
            }
        }

        /* make the pattern  according to algorithm
            b,a,c,d=input().split()
            g=range
            a,b=int(a),int(b)
            r=[[d]*b for i in g(a)]
            x=y=0
            while x<b/2or y<a/2:
             for i in g(x,a-x):r[i][y]=r[i][b-1-y]=c
             for j in g(y,b-y):r[x][j]=r[a-1-x][j]=c
             x+=2;
            y += 2
            print('\n'.join(map(''.join, r)))
        */

        int b = width;
        int a = height;
        int x = 0;
        int y = 0;
        while (x <= (b / 2) || y <= (a / 2))
        {
            for (int i = x; i < (a - x); ++i)
            {
                ary[i][y] = first_char;
                ary[i][b - 1 - y] = first_char;
            }
            for (size_t j = y; j < (b - y); ++j)
            {
                if (x < a)
                {
                    ary[x][j] = first_char;
                    ary[a - 1 - x][j] = first_char;
                }
            }
            x += 2;
            y += 2;
        }

        /* print the array
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                std::cout << ary[i][j];
            }
            std::cout << '\n';
        }
        */

        // print the array
        std::string output = "";
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                output += ary[i][j];
            }
            output += '\n';
        }

        // memory de-allocate
        delete[] ary[0];
        delete[] ary;

        return output;
    }

}