// Watermeloned on JJJakubJJ implementation found https://stackoverflow.com/questions/7228438/convert-double-double-to-string 
#include <stdio.h>

int n_tu(int number, int count)
{
    int result = 1;
    while(count-- > 0)
        result *= number;

    return result;
}

void double_to_string(double f, char r[])
{
    long long int length, length2, i, number, position, sign;
    double number2;

    sign = -1;
    if (f < 0)
    {
        sign = '-';
        f *= -1;
    }

    number2 = f;
    number = f;
    length = 0;
    length2 = 0;

    while( (number2 - static_cast<double>(number)) != 0.0 && !((number2 - static_cast<double>(number)) < 0.0) )
    {
        number2 = f * (n_tu(10.0, length2 + 1));
        number = number2;

        length2++;
    }

    for (length = (f > 1) ? 0 : 1; f > 1; length++)
        f /= 10;

    position = length;
    length = length + 1 + length2;
    number = number2;
    if (sign == '-')
    {
        length++;
        position++;
    }

    for (i = length; i >= 0 ; i--)
    {
        if (i == (length))
            r[i] = '\0';
        else if(i == (position))
            r[i] = '.';
        else if(sign == '-' && i == 0)
            r[i] = '-';
        else
        {
            r[i] = (number % 10) + '0';
            number /=10;
        }
    }
}
