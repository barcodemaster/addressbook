#include "AddressBook.h"
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)




void Create(AddressBook* addressBook,Long capacity)
{
	addressBook->personals = (Personal(*))calloc(capacity, sizeof(Personal));
	addressBook->capacity = capacity;
	addressBook->length = 0;
}

Long Record(AddressBook* addressBook,const char(*name),const char(*address),const char(*telephoneNumber),const char(*emailAddress))
{
	Long i = 0;
	Personal(*personals);

	while (i < addressBook->capacity && strcmp(addressBook->personals[i].name, "") != 0)
	{
		i++;
	}
	if (i >= addressBook->capacity)
	{
		personals = (Personal(*))calloc(addressBook->capacity + 1, sizeof(Personal));
		i = 0;
		while (i < addressBook->capacity)
		{
			personals[i] = addressBook->personals[i];
			i++;
		}
		addressBook->capacity++;
		if (addressBook->personals != NULL)
		{
			free(addressBook->personals);
		}
		addressBook->personals = personals;
	}
	strcpy(addressBook->personals[i].name, name);
	strcpy(addressBook->personals[i].address, address);
	strcpy(addressBook->personals[i].telephoneNumber, telephoneNumber);
	strcpy(addressBook->personals[i].emailAddress, emailAddress);
	addressBook->length++;
	return addressBook->length-1;
}

void Find(AddressBook* addressBook,const char(*name), Long* (*indexes), Long* count)
{
	int i = 0;
	int j = 0;
	*count = 0;
	*indexes = (Long(*))calloc(addressBook->length, sizeof(Long));
	while (i < addressBook->length)
	{
		if (strcmp(addressBook->personals[i].name, name) == 0)
		{
			(*indexes)[j] = i;
			j++;
			(*count)++;
		}
		i++;
	}
}

Long Correct(AddressBook* addressBook, Long index,const char(*address),const char(*telephoneNumber),const char(*emailAddress))
{
	strcpy(addressBook->personals[index].address, address);
	strcpy(addressBook->personals[index].telephoneNumber, telephoneNumber);
	strcpy(addressBook->personals[index].emailAddress, emailAddress);
	return index;
}

Long Erase(AddressBook* addressBook, Long index)
{
	Long i = 0;
	Long j = 0;
	Personal(*personals);
	personals = (Personal(*))calloc(addressBook->length, sizeof(Personal));
	while (i < addressBook->length)
	{
		if (i != index)
		{
			personals[j] = addressBook->personals[i];
			j++;
		}
		i++;
	}
	if (addressBook->personals != NULL)
	{
		free(addressBook->personals);
	}
	addressBook->personals = personals;
	addressBook->length--;
	addressBook->capacity = addressBook->length;
	index = -1;
	return index;
}

void Arrange(AddressBook* addressBook)
{
	Long i = 0;
	Long j;
	Personal person;
	while (i < addressBook->length - 1)
	{
		j = i + 1;
		while (j < addressBook->length)
		{
			if (strcmp(addressBook->personals[i].name, addressBook->personals[j].name) > 0)
			{
				person = addressBook->personals[i];
				addressBook->personals[i] = addressBook->personals[j];
				addressBook->personals[j] = person;
			}
			j++;
		}
		i++;
	}

}

void Destroy(AddressBook* addressBook, Long* (*indexes))
{
	if (addressBook->personals != NULL)
	{
		free(addressBook->personals);
		addressBook->capacity = 0;
		addressBook->length = 0;
	}
	if (*indexes != NULL)
	{
		free(*indexes);
	}
}

int main()
{
	AddressBook addressBook;
	Long i;
	Long count;
	Long(*indexes);
	Long index;

	Create(&addressBook, 1);

	index = Record(&addressBook, "김예호", "고향시", "01011111111", "arigato@naver.com");
	printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);

	index = Record(&addressBook, "김예호", "뉴욕", "0102222222", "adgedddd@naver.com");
	printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);

	index = Record(&addressBook, "조현준", "부산시", "01033333333", "ollejun@naver.com");
	printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);

	index = Record(&addressBook, "김시무", "오산시", "01044444444", "shamu@naver.com");
	printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);

	Find(&addressBook, "김예호", &indexes, &count);
	i = 0;
	while (i < count)
	{
		printf("%s %s %s %s\n", addressBook.personals[indexes[i]].name, addressBook.personals[indexes[i]].address, addressBook.personals[indexes[i]].telephoneNumber, addressBook.personals[indexes[i]].emailAddress);
		i++;
	}

	index = Correct(&addressBook, 1, "부산시", "01051597020", "ollejun@naver.com");
	printf("%s %s %s %s\n", addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].telephoneNumber, addressBook.personals[index].emailAddress);

	index = Erase(&addressBook, 1);
	if (index == -1)
	{
		printf("지워졌습니다.\n\n");
	}

	index = Erase(&addressBook, 1);
	if (index == -1)
	{
		printf("지워졌습니다.\n\n");
	}

	Arrange(&addressBook);

	i = 0;
	while (i < addressBook.length)
	{
		printf("%s %s %s %s\n", addressBook.personals[i].name, addressBook.personals[i].address, addressBook.personals[i].telephoneNumber, addressBook.personals[i].emailAddress);
		i++;
	}

	Destroy(&addressBook, &indexes);

	return 0;
}