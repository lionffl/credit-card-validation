#include <cs50.h>
#include <stdio.h>

int get_last_digit(long n);
int count_digits(long n);
int sum_digits(long n);
int get_first_sum(long n);
int get_final_sum(long card_number, int first_sum);
int get_subnumber_by_index(long n, int index);
bool is_even(long n);
char* get_card_name(long card_number);

int main(void)
{
  long card_number = get_long("Please, inform your card number (only digits): ");

  int first_sum = get_first_sum(card_number);

  int final_sum = get_final_sum(card_number, first_sum);

  int last_digit = get_last_digit(final_sum);

  if (last_digit != 0)
  {
    printf("INVALID\n");
  }
  else
  {
    char* card_name = get_card_name(card_number);
    printf("%s", card_name);
  }
}

int get_last_digit(long n)
{
  return n % 10;
}

int count_digits(long n)
{
  int counter = 1;
  while (n / 10 != 0)
  {
    n = n / 10;
    counter++;
  }
  return counter;
}

bool is_even(long n)
{
  if (n % 2 == 0)
  {
    return true;
  }
  return false;
}

int sum_digits(long n)
{
  int sum = 0;
  int number_of_digits = count_digits(n);

  for (int i = 0; i < number_of_digits; i++)
  {
    int last_digit = get_last_digit(n);
    sum = sum + last_digit;
    n = n / 10;
  }
  return sum;
}

int get_first_sum(long card_number)
{
  long last_digit = get_last_digit(card_number);
  long digits = count_digits(card_number);
  int check_sum = 0;

  for (int i = 0; i < digits; i++)
  {
    if (!is_even(i))
    {
      int digit = get_last_digit(card_number);
      int product = digit * 2;
      if (count_digits(product) > 1)
      {
        product = sum_digits(product);
        check_sum = check_sum + product;
      }
      else
      {
        check_sum = check_sum + product;
      }
    }
    card_number = card_number / 10;
  }
  return check_sum;
}

int get_final_sum(long card_number, int first_sum)
{
  long last_digit = get_last_digit(card_number);
  long digits = count_digits(card_number);
  int check_sum = first_sum;

  for (int i = 0; i < digits; i++)
  {
    if (is_even(i))
    {
      int digit = get_last_digit(card_number);
      check_sum = check_sum + digit;
    }
    card_number = card_number / 10;
  }
  return check_sum;
}

int get_subnumber_by_index(long n, int index)
{
  int digits = count_digits(n);

  for (int i = 0; i < digits; i++)
  {
    n = n / 10;
    if (count_digits(n) == index)
    {
      break;
    }
  }
  return n;
}

char* get_card_name(long card_number)
{
  int first_digit = get_subnumber_by_index(card_number, 1);
  int two_first_digits = get_subnumber_by_index(card_number, 2);
  int digits = count_digits(card_number);
  string card_name;

  if ((two_first_digits == 34 || two_first_digits == 37) && digits == 15)
  {
    card_name = "AMEX\n";
  }
  else if ((two_first_digits >= 51 && two_first_digits <= 55) && digits == 16)
  {
    card_name = "MASTERCARD\n";
  }
  else if ((digits == 16 || digits == 13) && first_digit == 4)
  {
    card_name = "VISA\n";
  }
  else
  {
    card_name = "INVALID\n";
  }
  return card_name;
}