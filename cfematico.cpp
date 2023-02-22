// Archivos
#include <stdio.h>
#define NUM 100
#include <string.h>
struct clientes
{
	char nombre[30];
	char dir[30];
	int numed;
	float saldo;
};
struct clientes *p, cli[NUM];
FILE *fich;
void Pagar_cuenta(int, struct clientes *);
void menu_user(int *, struct clientes *, int);
void menu_maq(int *);
// Funciones del admin
void menu_admin(int *);
void menu_admin2(int *);
void Agregar_clientes(int, struct clientes *);
int registros(struct clientes *);
void escribir_estructs(struct clientes *, int);
int main()
{
	p = cli;
	fich = fopen("clientes.txt", "a+b");
	int i, band = 0, clave, o, q;
	int admin, a, e, x;
	int f;
	x = registros(p);
	do
	{
		menu_admin(&a);
		switch (a)
		{
		case 1:
			printf("Dame tu clave\n");
			scanf("%d", &admin);
			if (admin == 5090)
			{
				do
				{
					menu_admin2(&e);
					if (e == 1)
					{
						Agregar_clientes(x, p);
						x++;
					}
				} while (e != 2);
			}
			else
				printf("No eres admnistrador\n");
			break;
		case 2:
			if (x == 0)
				printf("No hay usuarios que mostrar\n");
			else
			{
				i = 0;
				menu_maq(&q);
				do
				{
					if (q == (p + i)->numed)
					{
						do
						{
							menu_user(&o, p, i);
							switch (o)
							{
							case 1:
								printf("--------------------------------\n");
								printf("Nombre:%s\n", (p + i)->nombre);
								printf("Direccion:%s\n", (p + i)->dir);
								printf("Clave de recibo:%d\n", (p + i)->numed);
								printf("--------------------------------\n");
								break;
							case 2:
								printf("--------------------------------\n");
								printf("Tu adeudo es:$%.2f\n", (p + i)->saldo);
								printf("--------------------------------\n");
								break;
							case 3:
								printf("Deuda:$%.2f\n", (p + i)->saldo);
								Pagar_cuenta(i, p);
								break;
							}
						} while (o != 4);
						printf("Gracias por utilizar nuestros servicios\n");
						printf("Que tenga un excelente día :)\n@CFEmático\n");
						band = 1;
					}
					else
					{
						band = 0;
						i++;
					}
				} while (band == 0 && i < x);
				if (band == 0)
					printf("Clave no existente\n");
			}
			break;
		case 3:
			fich = fopen("clientes.txt", "wb");
			if (fich == NULL)
				printf("Error en la escritura del fichero");
			else
			{
				escribir_estructs(p, x);
				fclose(fich);
			}
			break;
		}
	} while (a != 3);
	printf("%d", x);
	getchar();
	fclose(fich);
}
void Pagar_cuenta(int a, struct clientes *b)
{
	float cambio, x;
	if ((b + a)->saldo != 0)
	{
		do
		{
			printf("Dame la cantidad\n");
			scanf("%f", &x);
			if (x < (b + a)->saldo)
			{
				(b + a)->saldo -= x;
				printf("Te falta:$%.2f\n", (b + a)->saldo);
			}
			else if (x >= (b + a)->saldo)
			{
				cambio = (b + a)->saldo - x;
				if (cambio == 0)
				{
					printf("--------------------------------\n");
					printf("¡¡¡Tu adeudo está PAGADO!!!\n");
					printf("--------------------------------\n");
					(b + a)->saldo = 0;
				}
				else
				{
					printf("--------------------------------\n");
					printf("Tu cambio es:$%.2f\n", -(cambio));
					printf("--------------------------------\n");
					printf("******PAGADO*******\n");
					(b + a)->saldo = 0;
				}
			}
		} while ((b + a)->saldo != 0);
		printf("--------------------------------\n");
		printf("Gracias por tu pago\n");
		printf("********************************\n");
	}
	else
		printf("Tu adeudo está *****PAGADO****\n");
}
void menu_user(int *opc, struct clientes *b, int a)
{
	printf("--------------------------------\n");
	printf("¿Que le gustaría hacer?\n");
	printf("--------------------------------\n");
	printf("1.-Consultar datos de cuenta\n2.-Verificar saldo\n");
	if ((b + a)->saldo != 0)
		printf("3.-Pagar.\n");
	printf("4.-Salir de usuario\n");
	scanf("%d", opc);
}
void menu_maq(int *clave)
{
	printf("--------------------------------\n");
	printf("Bienvenido a CFEmático\n");
	printf("Dame la clave de tu recibo\n");
	scanf("%d", clave);
}
// Primera funcion en usar administrador
void menu_admin(int *cla)
{
	printf("CFEm@tico\n1.Administrador\n2.-Cliente\n3.-Salir\n");
	scanf("%d", cla);
}
// Primera funcion en usar, segundo menu del admin
void menu_admin2(int *clave)
{
	printf("Que deseas hacer?\n");
	printf("1.-Alta de cliente\n");
	printf("2.-Salir al menu\n");
	scanf("%d", clave);
}
void Agregar_clientes(int a, struct clientes *b)
{
	char nom[30], direc[30];
	printf("Dame el nombre\n");
	fflush(stdin);
	gets(nom);
	strcpy((b + a)->nombre, nom);
	printf("Dame la direccion\n");
	fflush(stdin);
	gets(direc);
	strcpy((b + a)->dir, direc);
	printf("Dame la clave de recibo\n");
	scanf("%d", &(b + a)->numed);
	printf("Dame la deuda del cliente\n");
	scanf("%f", &(b + a)->saldo);
}
int registros(struct clientes *b)
{
	int i = 0;
	fich = fopen("clientes.txt", "rb");
	if (fich == NULL)
	{
		printf("Error en la apertura del fichero");
		return 0;
	}
	else
	{
		fread(b, sizeof(struct clientes), 1, fich);
		while (!feof(fich))
		{
			fread(b, sizeof(struct clientes), 1, fich);
			i++;
		}
		fclose(fich);
		return (i);
	}
}
void escribir_estructs(struct clientes *b, int x)
{
	fwrite(b, sizeof(struct clientes), x, fich);
	return;
}
