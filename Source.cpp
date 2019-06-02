#include <iostream>
#include <string>
#include <ctime>

using namespace std;

// function prototypes
void encrypt(string message, string key);
void decrypt(string message, string key);
string removeNonAlpha(string key, bool& edited);
string randomKeyGen(int messageLength);

// alphabet array so that the random generator can grab letters (idea from cplusplus.com/forum/windows/88843)
static const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

int main()
{
	// Seed for random key generation
	srand(time(0));
	// Message and key strings for encryption/decryption
	string message = "";
	string key = "";
	// Menu option value holders
	int choice;
	char repeat;
	char random;
	bool edited;
	// Proram repeat do-while loop (infinite)
	// key variable: none
	do {
		edited = false;
		random = 'N';
		// Input validation do-while loop
		// Variable to validate: choice
		do {
			// First menu option, decides where the message is encrypted or decrypted
			cout << "Do you wish to 1) Encrypt or 2) Decrypt a message?\t";
			cin >> choice;
			// check to see if error message should be displayed
			if (choice != 1 && choice != 2)
			{
				cout << "Error invalid entry, please enter either 1 or 2 depending on your need.\n\n";
				choice = -1;
			}
		} while (choice == -1);

		// Message entry is a universal requirement
		// key variable: message
		cout << "Please enter your message:\t";
		cin.ignore();
		getline(cin, message);

		// Encryption path
		if (choice == 1)
		{
			// Input validation do-while
			// key variable: random
			do {
				// Should the program generate a random string
				cout << "Would you like to generate a random key? Y or N\t";
				cin >> random;
				cin.ignore();
				// check to see if error message should be displayed
				if (toupper(random) != 'Y' && toupper(random) != 'N')
					cout << "Invalid input, please enter either Y or N." << endl << endl;
			} while (toupper(random) != 'Y' && toupper(random) != 'N');
			if (toupper(random) == 'Y')
			{
				// Generate random string
				key = randomKeyGen(message.length());
			}
			else if (toupper(random) == 'N')
			{
				// Get user defined string
				cout << "Please enter your desired key:\t";
				getline(cin, key);
				// Call removeNonAlpha to consolidate key
				key = removeNonAlpha(key, edited);
			}
			// Call encryption function
			// Return type: Void
			// Arguement types: string, string
			encrypt(message, key);
		}
		else if (choice == 2)
		{
			cout << "Please enter your key:\t";
			getline(cin, key);
			// Call removeNonAlpha to consolidate key
			key = removeNonAlpha(key, edited);
			// Call decryption function
			// Return type: Void
			// Arguement types: string, string
			decrypt(message, key);
		}
		// If you have a randomly generated key the program will let you know what it is.
		if (toupper(random) == 'Y')
		{
			cout << "Your randomly generated key is:\t" << key << endl;
		}
		// If you have a edited key the program will let you know what it is.
		if (edited == true)
		{
			cout << "Your corrected key is:\t" << key << endl;
		}
		// new line of aesthetics
		cout << endl;
		// Input validation do-while
		// key variable: repeat
		do {
			cout << "Run again? Y or N:\t";
			cin >> repeat;
		} while (toupper(repeat) != 'Y' && toupper(repeat) != 'N');

		// Break condition for infinite loop
		// key variable: repeat
		if (toupper(repeat) == 'N')
			break;
	} while (true);

	// Pausing of program so that console is readable when run in Visual Studios
	system("pause");
	return 0;
}

// Encryption Function
// Arguement types: string, string
// Function: Offset each character in the message by the amount of the corresponding character in the key string to the right
// Preserves the case of the message string
// Outputs the encrypted message
// Return value: Void
void encrypt(string message, string key)
{
	string encryptedMessage = "";
	char messageChar;
	char keyChar;
	int keyl = key.length();
	int offset;
	int keyoffset;

	for (unsigned int i = 0; i < message.length(); i++)
	{
		messageChar = message[i];
		keyChar = key[i % keyl];
		if (messageChar == ' ')
		{
			encryptedMessage += " ";
			continue;
		}
		else if (isalpha(messageChar))
		{
			if (isupper(messageChar))
				offset = 65;
			else
				offset = 97;
			if (isupper(keyChar))
				keyoffset = 65;
			else
				keyoffset = 97;
			encryptedMessage += char((((int(messageChar) - offset) + (int(keyChar) - keyoffset)) % 26) + offset);
		}
		else
		{
			encryptedMessage += messageChar;
		}
	}

	cout << "\nYour encrpyted message is:\t" << encryptedMessage << endl;
	return;
}

// Decryption Function
// Arguement types: string, string
// Function: Offset each character in the message by the amount of the corresponding character in the key string to the left
// Preserves the case of the message string
// Outputs the decrypted message
// Return value: Void
void decrypt(string message, string key)
{

	string decryptedMessage = "";
	char messageChar;
	char keyChar;
	int keyl = key.length();
	int offset;
	int keyoffset;

	for (unsigned int i = 0; i < message.length(); i++)
	{
		messageChar = message[i];
		keyChar = key[i % keyl];
		if (messageChar == ' ')
		{
			decryptedMessage += " ";
			continue;
		}
		else if (isalpha(messageChar))
		{
			if (isupper(messageChar))
				offset = 65;
			else
				offset = 97;
			if (isupper(keyChar))
				keyoffset = 65;
			else
				keyoffset = 97;
			int minusKey = (int(messageChar) - offset) - (int(keyChar) - keyoffset);
			if (minusKey < 0)
				minusKey = 26 + minusKey;
			decryptedMessage += char(minusKey + offset);
		}
		else
		{
			decryptedMessage += messageChar;
		}
	}

	cout << "\nYour decrypted message is:\t" << decryptedMessage << endl;
	return;
}

// Remove space character function
// Arguement types: string
// Function: Take the string and remove any ' ' (ASCII value 32) from the arguement
// Return type: string
string removeNonAlpha(string key, bool& edited)
{
	for (unsigned int i = 0; i < key.length(); i++)
	{
		if (!isalpha(key[i]))
		{
			edited = true;
			key.erase(i, 1);
			i--;
		}
	}

	return key;
}

// Random string generator function
// Arguement types: int
// Function: Generate a random key who's length is greater than or equal to message length and capped at 85 characters
// Return type: string
string randomKeyGen(int messageLength)
{
	string key;
	int keylength = 0;
	while (keylength < messageLength)
	{
		keylength = rand() % 86;
	}

	for (int i = 0; i < keylength; i++)
	{
		key += alphabet[rand() % (sizeof(alphabet) - 1)];
	}

	return key;
}
