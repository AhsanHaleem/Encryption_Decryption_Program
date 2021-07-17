#include <stdio.h>
#include <string.h>

#define MAX_BUF 256

unsigned char getBit(unsigned char, int);
unsigned char setBit(unsigned char, int);
unsigned char clearBit(unsigned char, int);
unsigned char counterAndKey(unsigned char, unsigned char);
unsigned char encryptDecrypt(unsigned char, unsigned char);

int main()
{
    printf("HELLO 1\n");
    char str[8];
    unsigned char source_byte[MAX_BUF] = {};
    int choice;
    int source_byte_int = 0;
    printf("HELLO 2\n");
    int input = scanf("%d", &source_byte_int);   // this is user input        // ERROR
    printf("HELLO 3\n");
    // Given values
    unsigned char init_key = 0b10110010;         // initial key
    unsigned char counter_val = 0b00101000;      // initial counter value



    printf("\nYou may:\n");
    printf("  Enter 1) To Encrypt a message \n");
    printf("  Enter 2) To Decrypt a message \n");
    printf("\nWhat is your selection: ");
    fgets(str, sizeof(str), stdin);
    sscanf(str, "%d", &choice);

    if (choice == 1) {
      printf("\nEnter plaintext: \n");
      fgets(source_byte, sizeof(source_byte), stdin);
      for (int i = 0; i < strlen(source_byte) - 1; i++) {
          counter_val = counterAndKey(init_key, counter_val);
          //printf("%u      ", (unsigned char)counter_val);
          init_key++;
          printf("%u  ", (unsigned char)encryptDecrypt(source_byte[i], counter_val));
      }
    }

    else if (choice == 2) {
        printf("\nEnter ciphertext: \n");

        while (input != 0) {
            counter_val = counterAndKey(init_key, counter_val);
            //printf("%u \n", (unsigned char)counter_val);
            init_key++;
            printf("%c", (char)encryptDecrypt(source_byte_int, counter_val));
            //printf("H");
        }
    }

    else {
        printf("Error: Invalid option.\n");
    }

    printf("\n\n");

    return 0;
}

/*
  Function:  getBit
  Purpose:   retrieve value of bit at specified position
       in:   character from which a bit will be returned
       in:   position of bit to be returned
   return:   value of bit n in character c (0 or 1)
*/
unsigned char getBit(unsigned char c, int n)
{
    return ((c & (1 << n)) >> n);
}

/*
  Function:  setBit
  Purpose:   set specified bit to 1
       in:   character in which a bit will be set to 1
       in:   position of bit to be set to 1
   return:   new value of character c with bit n set to 1
*/
unsigned char setBit(unsigned char c, int n)
{
    return (c | (1 << n));
}

/*
  Function:  clearBit
  Purpose:   set specified bit to 0
       in:   character in which a bit will be set to 0
       in:   position of bit to be set to 0
   return:   new value of character c with bit n set to 0
*/
unsigned char clearBit(unsigned char c, int n)
{
    return (c & (~(1 << n)));
}

/*
  Function:  counterAndKey
  Purpose:   This function uses getbit(), setbit() and clearbit() functions to encrypt/decrypt message.
       in:   unsigned char init_key (initial key given)
       in:   unsigned char counter_val (counter value given)
   return:   unsigned char upt_counter_val (updated counter value)
*/
unsigned char counterAndKey(unsigned char init_key, unsigned char counter_val)
{

    // variables
    unsigned char temp_counter = 0;     // temp counter
    unsigned char temp_counter_bit = 0; // temp counter
    unsigned char pos_1 = 0;            // position 1
    unsigned char pos_2 = 0;            // position 2
    unsigned char upt_counter_val = 0;  // updated counter value
    unsigned char upt_key_val = 0;      // updated key value

    // Process 1
    temp_counter = counter_val; //1(a)
    for (int i = 7; i >= 0; i--)
    {
        pos_1 = getBit(temp_counter, i); //pos_1 is set to current bit pos
        // 1(b)(i)(1)
        if (getBit(init_key, i) == 1)
        {
            if (i == 7)
            {
                pos_2 = getBit(temp_counter, 0);
            }
            else
            {
                pos_2 = getBit(temp_counter, i + 1);
            }
        }
        // 1(b)(i)(2)
        else if (getBit(init_key, i) == 0)
        {
            if (i == 7)
            {
                pos_2 = getBit(temp_counter, 1);
            }
            else if (i == 6)
            {
                pos_2 = getBit(temp_counter, 0);
            }
            else
            {
                pos_2 = getBit(temp_counter, i + 2);
            }
        }
        // 1(b)(ii)
        temp_counter_bit = pos_1 ^ pos_2;
        // 1(b)(iii)
        if (temp_counter_bit == 0)
        {
            temp_counter = clearBit(temp_counter, i);
        }
        else if (temp_counter_bit == 1)
        {
            temp_counter = setBit(temp_counter, i);
        }
    }

    // 1(b)(iv)
    upt_counter_val = temp_counter;
    // (2)
    upt_counter_val++;
    return upt_counter_val;
}

/*
  Function:  encryptDecrypt
  Purpose:   encrypt/Decrypt the plaintext/ciphertext into cipertext/plaintext respectively
       in:   unsigned char source_byte (user_input character)
       in:   unsigned char counter_val (counter value given)
   return:   unsigned char cipertext/plaintext (sequence of numbers/text)
*/
unsigned char encryptDecrypt(unsigned char str, unsigned char counter_val)
{
    unsigned char temp_val = 0; // temp value
    unsigned char result2 = 0;  // result: xor between counter bit & source bit
    int result = 0;             // result after counter value % 9

    // (4)(a)
    temp_val = str;
    // (4)(b)
    result = (int)counter_val % 9;
    // (4)(c)
    if (result < 3)
    {
        for (int i = 0; i <= 7; i++)
        {
            if ((i % 2 == 0) || (i == 0))
            {
                result2 = getBit(counter_val, i) ^ getBit(temp_val, i);
                if (result2 == 0)
                {
                    temp_val = clearBit(temp_val, i);
                }
                else if (result2 == 1)
                {
                    temp_val = setBit(temp_val, i);
                }
            }
        }
    }
    // (4)(d)
    else if ((result >= 3) && (result <= 5))
    {
        for (int i = 1; i <= 7; i++)
        {
            if ((i % 2 != 0) || (i == 1))
            {
                result2 = getBit(counter_val, i) ^ getBit(temp_val, i);
                if (result2 == 0)
                {
                    temp_val = clearBit(temp_val, i);
                }
                else if (result2 == 1)
                {
                    temp_val = setBit(temp_val, i);
                }
            }
        }
    }
    // (4)(e)
    else if (result > 5)
    {
        for (int i = 0; i <= 7; i++)
        {
            result2 = getBit(counter_val, i) ^ getBit(temp_val, i);
            if (result2 == 0)
            {
                temp_val = clearBit(temp_val, i);
            }
            else if (result2 == 1)
            {
                temp_val = setBit(temp_val, i);
            }
        }
    }

    return temp_val;
}
