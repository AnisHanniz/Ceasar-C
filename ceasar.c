

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Message
{
	char *texte;
	int taille;
};

void alloueMsg (struct Message * msg, int taille)
{
	msg->texte = (char*)malloc(sizeof(char)*taille);
	msg->taille = taille;
}

void desalloueMsg (struct Message * msg)
{
	free(msg->texte);
	msg->texte = NULL;
	msg->taille = 0;
}

void copieMsg (struct Message * msg, struct Message * copie)
{
	copie->texte = (char*)malloc(sizeof(char)*msg->taille);
	strcpy(copie->texte, msg->texte);
	copie->taille = msg->taille;
}

void simplify (struct Message * msg)
{
	int i, j;
	for(i=0; i<msg->taille; i++)
	{
		if(msg->texte[i] < 'A' || (msg->texte[i] > 'Z' && msg->texte[i] < 'a') || msg->texte[i] > 'z')
		{
			for(j=i; j<msg->taille-1; j++)
			{
				msg->texte[j] = msg->texte[j+1];
			}
			msg->taille--;
		}
	}
}

char shift (char c, int k)
{
	if(c >= 'A' && c <= 'Z')
	{
		c = c + k;
		if(c > 'Z')
		{
			c = c - 26;
		}
	}
	else if(c >= 'a' && c <= 'z')
	{
		c = c + k;
		if(c > 'z')
		{
			c =
			c - 26;
		}
	}
	return c;
}

void do_cesar (struct Message * msg, int k, struct Message * res)
{
	int i;
	res->texte = (char*)malloc(sizeof(char)*msg->taille);
	for(i=0; i<msg->taille; i++)
	{
		res->texte[i] = shift(msg->texte[i], k);
	}
	res->taille = msg->taille;
}

void undo_cesar (struct Message * msg, int k, struct Message * res)
{
	int i;
	res->texte = (char*)malloc(sizeof(char)*msg->taille);
	for(i=0; i<msg->taille; i++)
	{
		res->texte[i] = shift(msg->texte[i], -k);
	}
	res->taille = msg->taille;
}

int main()
{
	struct Message msg, copie, res
	;
	int k;
	printf("Entrez le message à chiffrer : ");
	scanf("%s", msg.texte);
	msg.taille = strlen(msg.texte);
	printf("Entrez le décalage : ");
	scanf("%d", &k);
	copieMsg(&msg, &copie);
	simplify(&msg);
	do_cesar(&msg, k, &res);
	printf("Message chiffré : %s\n", res.texte);
	undo_cesar(&res, k, &msg);
	printf("Message déchiffré : %s\n", msg.texte);
	printf("Message original : %s\n", copie.texte);
	desalloueMsg(&msg);
	desalloueMsg(&copie);
	desalloueMsg(&res);
	return 0;
}
