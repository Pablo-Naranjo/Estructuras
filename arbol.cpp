#include <iostream>
#include <bits/stdc++.h>
#include <windows.h>
#define TECLA_ARRIBA 'w'
#define TECLA_ABAJO 's'
#define ENTER 13
#define TRA 100
using namespace std; 
 void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 } 
 char getch2 ()
{
   char c=0;
   DWORD modo, contador;
   HANDLE ih = GetStdHandle(STD_INPUT_HANDLE);
 
   // Desactivamos escritura en terminal
   SetConsoleMode (ih, modo & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));
 
   ReadConsoleA (ih, &c, 1, &contador, NULL);
 
   if (c == 0) {
      ReadConsoleA (ih, &c, 1, &contador, NULL);
   }
 
   SetConsoleMode (ih, modo); // Devolvemos control normal
 
   return c;
}
 int menu(const char* titulo, const char*opciones[], int m);
 
struct Nodo
{
	int valor; 
	Nodo *izquierdo; 
	Nodo *derecho; 
	Nodo *padre;
}*Arbol;

Nodo *crearArbol(int, Nodo *); 
void istNodo(int, Nodo *&, Nodo *);
void mostrar(int, Nodo *);
void AltNod(int, Nodo *, int);
bool buscar(int, Nodo *);
void elimAr(Nodo *&);
void PreOr(Nodo *);
void InOr(Nodo *);
void PosOr(Nodo *);


Nodo *crearArbol(int x, Nodo *padre)
{
	
	Nodo *arbol = new Nodo(); //creamos nuevo puntero de tipo nodo
	
	arbol->valor=x; 
	arbol->izquierdo=NULL;
	arbol->derecho=NULL; 
	arbol->padre=padre;
	
	return arbol;//devolvemos el nodo ya con valores
}

void istNodo(int x, Nodo *&arbol, Nodo *padre)
{
	if (arbol==NULL)
	{
		arbol = crearArbol(x,padre); //Si arbol está vacío se llama a crearArbol y se guarda en arbol el primero nodo
	}
	else 
	{
		int valorR = arbol->valor;//Se obtiene el valor de la raíz
		if (x < valorR)
		{
			istNodo(x, arbol->izquierdo, arbol);//Si el valor dado es menor al nodo raíz se inserta a la izquierda
		}
		else if (x > valorR)
		{
			istNodo(x, arbol->derecho, arbol);//Si el valor dado es mayor al nodo raíz se inserta a la derecha
		}
		
		
	}
	
}

void mostrar(int cnt, Nodo *arbol)
{
	if (arbol == NULL)//arbol sin nodos
	{
	    return;
	}
	else
	{
		
		mostrar(cnt+1, arbol->derecho);//imprimimos los nodos del lado derecho
		for (int i = 0; i < cnt; i++)
		{
			cout << "   ";
		}
		cout << arbol->valor << endl ;
		mostrar(cnt+1, arbol->izquierdo);//Imprimimos los nodos del lado izquierdo
	}
}

bool buscar(int x, Nodo *arbol)
{
	if (arbol == NULL)
	{
		return false; 
	}
	else if (x == arbol->valor)
	{
		return true;
	}
	else if (x > arbol->valor)
	{
		return buscar(x, arbol->derecho);
	}
	else if (x < arbol->valor)
	{
		return buscar(x, arbol->izquierdo);
	}	
}
void menuR()
{
	setlocale(LC_ALL,"Spanish");
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);
	int op; 
	bool repetir = true;
	do
	{
		const char *titulo = "RECORRIDOS"; 
		const char *opciones[] = {"Preorden", "Inorden", "Postorden", "Salir"};
		op = menu(titulo, opciones, 4);
		system("cls");
		switch(op)
		{
			case 1:
			{
				if (Arbol == NULL)
				{
					gotoxy(45, 1);cout << "ÁRBOL VACÍO  "<<endl<<endl;
					system("pause");
				}
				else
				{
					PreOr(Arbol);
					cout << "\n\n";
					system("pause");
				}
				break;
			}
			case 2:
			{
				if (Arbol == NULL)
				{
					gotoxy(45, 1);cout << "ÁRBOL VACÍO  "<<endl<<endl;
					system("pause");
				}
				else
				{
					InOr(Arbol);
					cout << "\n\n";
					system("pause");
				}
				break;
			}
			case 3:
			{
				if (Arbol == NULL)
				{
					gotoxy(45, 1);cout << "ÁRBOL VACÍO  "<<endl<<endl;
					system("pause");
				}
				else
				{
					PosOr(Arbol);
					cout << "\n\n";
					system("pause");
				}
				break;
			}
			case 4:
			{
				repetir = false;
				break;
			}
		}
	}while(repetir);
	
}
void AltNod(int x, Nodo *arbol, int cnt)
{
	if (x == arbol->valor)
	{
		gotoxy(45, 8); cout << "LA ALTURA DEL NODO " << x << " ES " << cnt <<endl;
		system("pause");
	}
	else if(x < arbol->valor)
	{
		AltNod(x, arbol->izquierdo, cnt+=1);
	}
	else if(x > arbol->valor)
	{ 
		AltNod(x, arbol->derecho, cnt+=1);
	}
}
void elimAr(Nodo *&arbol)
{	
	arbol = NULL;
}

void PreOr(Nodo *arbol)
{
	if(arbol == NULL)
	{
		return;
	}
	else
	{
		cout << arbol->valor << " -> ";
		PreOr(arbol->izquierdo);
		PreOr(arbol->derecho);
	}
}

void InOr(Nodo *arbol)
{
	if(arbol == NULL)
	{
		return;
	}
	else
	{
		InOr(arbol->izquierdo);
		cout << arbol->valor << " -> ";
		InOr(arbol->derecho);
	}
}

void PosOr(Nodo *arbol)
{
	if(arbol == NULL)
	{
		return;
	}
	else
	{
		PosOr(arbol->izquierdo);
		PosOr(arbol->derecho);
		cout << arbol->valor << "->";
	}
}

void Elim(Nodo *arbol, int x)
{
	if(arbol == NULL)
	{
		return;
	}
	else if(x < arbol->valor)
	{
		Elim(arbol->izquierdo,x); //si el valor es menor que el nodo padre va a buscar a su izquierda
	}
	else if(x > arbol->valor)
	{
		Elim(arbol->derecho,x); //si el valor es mayor que el nodo padre va a buscar a su derecha
	}
	else	//cuando ya no es mayor ni menor significa que ya encontro el dato
	{
		ElimNod(arbol); //va a mandar la posicon en la que se encuentra actualmente
	}
}

void ElimNod(Nodo *elNodo)
{
	//cuando el nodo tiene dos hijos
	if(elNodo->izquierdo && elNodo->derecho)	//cuando el nodo tiene hijo a la derecha e izuiqerda
	{
		Nodo *menor = buscIzq(elNodo->derecho); //manda el valor del nodo derecho para despuesbuscar a su izquierda
		elNodo->valor = menor->valor; //al encontrar el valor mas a la izquierda posible lo sustituye por el que queriamos eliminar
		ElimNod(menor); 				//llama de nuevo a la funcion para eliminar
	}
	//cuando solo tiene un hijo
	else if(elNodo->izquierdo)	//si es hijo izquierdo
	{
		reemp(elNodo, elNodo->izquierdo);
		borrar(elNodo);
	}
	else if(elNodo->derecho)	//si el hijo esta a la derecha
	{
		reemp(elNodo, elNodo->derecho);
		borrar(elNodo);
	}
	//cuando no tiene hijos (nodo hoja)
	else
	{
		reemp(elNodo,NULL);	//va a remplazar el valor por nulo para poder eliminarlo correctamente
		borrar(elNodo);
	}
}

//funcion par aencontrar el nodo más a la izquierda posible
Nodo *buscIzq(Nodo *arbol)
{
	if(arbol == NULL)
	{
		return NULL;
	}
	if(arbol->izquierdo)	//si tiene hijo izquierdo
	{
		return buscIzq(arbol->izquierdo);//busca de nuevo por la izquierda
	}
	else	//si ya no tiene hijos a la izquierda
	{
		return arbol;//regresa el valor en el que se quedó
	}
}

void reemp(Nodo *arbol, Nodo *nuevo)
{
	if(arbol->padre) //si tene padre, le asignamos a un nuevo hijo
	{
		if(arbol->valor == arbol->padre->izquierdo->valor)
		{
			arbol->padre->izquierdo = nuevo;
		}
		else if(arbol->valor == arbol->padre->derecho->valor)
		{
			arbol->padre->derecho = nuevo;
		}
	}
	if(nuevo) //se le asigna un nuevo padre
	{
		nuevo->padre = arbol->padre;
	}
}

void borrar(Nodo *valor)
{
	//primero le quitamos los hijos para poder eliminarlo
	valor->izquierdo = NULL;
	valor->derecho = NULL;
	
	delete valor;
	
}

int altura(Nodo *arbol)
{
    int AltIzq, AltDer;

    if(arbol==NULL)
        return 0;
    else
    {
        AltIzq = altura(arbol->izquierdo);
        AltDer = altura(arbol->derecho);

        if(AltIzq>AltDer)
            return AltIzq+1;
        else
            return AltDer+1;
    }
}

int main(int argc, char** argv)
{
	setlocale(LC_ALL,"Spanish");
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);
	system("color 71");
	gotoxy(40,13); cout << "BIENVENIDO. NAVEGUE CON W S"<<endl<<endl<<endl;
	system("pause");
	system("cls");
	bool repite1 = true; 
	int cnt = 0;
	int nodos=0, ul=0, x;
	do
	{
		int opcion;		
		const char *titulo = "EJERCICIOS CON ARBOLES"; 
		const char *opciones[] = {"Crear árbol", "Insertar nodo", "Mostrar", "Buscar valor", "Altura del nodo", "Altura del árbol", "Cantidad de Nodos en el árbol", "Recorrer árbol", "Borrar un nodo", "Borre todo el árbol", "Salir"};
		opcion = menu(titulo, opciones, 11);
		system("cls");
		switch(opcion)
		{
			case 1:
			{
				int numero;
				if(Arbol != NULL)
				{
					gotoxy(40,12);cout << " <= YA EXISTE UN ÁRBOL => " << endl;
					system("pause");
				}
				else
				{
					gotoxy(45, 1);cout << "ÁRBOL VACÍO  ";
					gotoxy(40, 3);cout << "DAME EL NÚMERO ENTERO =>  "; 
					cin >> numero;
					nodos +=1;
					ul=numero;
					istNodo(numero, Arbol, NULL);
					system("cls");
					gotoxy(40, 3);cout << "<= VALOR INSERTADO CORRECTAMENTE =>  " << endl << endl ; 
					system("pause");
				}				
				break;
			}
			case 2:
			{
				int numero;
				if (Arbol == NULL)
				{
					gotoxy(45, 1);cout << "ÁRBOL VACÍO  ";
					gotoxy(40, 3);cout << "DAME UN NÚMERO ENTERO =>  "; 
					cin >> numero;
					nodos +=1;
					ul=numero;
					istNodo(numero, Arbol,NULL);
					gotoxy(40, 3);cout << "<= VALOR INSERTADO CORRECTAMENTE =>  " << endl << endl ; 
					system("pause");
				}
				else
				{
					gotoxy(40, 3);cout << "DAME EL NÚMERO ENTERO =>  "; 
					cin >> numero;
					nodos +=1;
					ul=numero;
					istNodo(numero, Arbol,NULL);
					system("cls");
					gotoxy(40, 3);cout << "<= VALOR INSERTADO CORRECTAMENTE =>  " << endl << endl ; 
					system("pause");
				}
				
				break;
			}
			case 3:
			{
				if (Arbol == NULL)
				{
					gotoxy(45, 1);cout << "ÁRBOL VACÍO  "<<endl<<endl;
					system("pause");
				}
				else
				{
					gotoxy(20, 3); cout << "LA RAÍZ DEL ÁRBOL SE MOSTRARÁ A LA IZQUIERDA Y SE SEGUIRÁ LA LÓGICA HACIA LA DERECHA"<< endl << endl; 
					system("pause");
					system("cls"); 
					gotoxy(40, 3); cout << "MOSTRANDO ÁRBOL..."<< endl << endl;  
					
					mostrar(cnt, Arbol);
					system("pause");

				}
			break;
			}
			case 4:
			{
				int numero;
				if (Arbol == NULL)
				{
					gotoxy(40,6);cout << " <= EL ÁRBOL ESTÁ VACÍO => " << endl;
					system("pause");
				}
				else
				{
					gotoxy(40, 3);cout << "DAME EL NÚMERO ENTERO A BUSCAR=>  "; 
					cin >> numero;
					if(buscar(numero, Arbol) == true)
					{
						gotoxy(35, 5);cout << " <= EL NÚMERO " << numero << " EXISTE EN EL ÁRBOL  =>"; 
					}
					else if(buscar(numero, Arbol) == false)
					{
						gotoxy(35, 5);cout << " <= EL NÚMERO " << numero <<  " NO EXISTE EN EL ÁRBOL =>"; 
					}
					cout << endl << endl; 
					system("pause");
				}
				
				break;
			}
			case 5: 
			{
				if (Arbol == NULL)
				{
					gotoxy(45, 1);cout << "ÁRBOL VACÍO  "<<endl;
					system("pause");
				}
				else
				{
					int nd=0;
					cout << "ESCRIBE EL NODO PARA CALCULAR SU ALTURA EN EL ÁRBOL => ";
					cin >> nd;
					if(buscar(nd, Arbol) == true)
					{
						 AltNod(nd, Arbol, 1);
					}
					else if(buscar(nd, Arbol) == false)
					{
						gotoxy(35, 5);cout << " <= EL NÚMERO " << nd <<  " NO EXISTE EN EL ÁRBOL =>"; 
						system("pause");					
					}	
				}				
				break;
			}
			case 6:
			{
				int h;
				h=altura(Arbol);
				gotoxy(45, 8); cout << "LA ALTURA DEL ÁRBOL ES " << h <<endl;
				system("pause");				
				break;
			}
			case 7:
			{
				if (Arbol == NULL)
				{
					gotoxy(45, 1);cout << "ÁRBOL VACÍO  "<<endl;
					system("pause");
				}
				else
				{
					gotoxy(35, 5);cout << "<= EL ÁRBOL TIENE " << nodos <<  " NODOS =>"<<endl<<endl;
					system("pause");
				}
				break;
			}
			case 8:
			{
				menuR();
				break;
			}
			case 9:
			{
				if(Arbol == NULL)
				{
					gotoxy(45, 1);cout << "ÁRBOL VACÍO  "<<endl;
					system("pause");
				}
				else
				{
					cout<<"¿Qué número desea eliminar?"<<endl<<"=>";
					cin>>x;
					Elim(Arbol,x);
					gotoxy(35, 5);cout << "<= ÁRBOL ELIMINADO CORRECTAMENTE =>" <<endl<<endl;
					system("pause");
				}
				break;
			}
			case 10:
			{
				elimAr(Arbol);
				gotoxy(35, 5);cout << "<= NODO ELIMINADO CORRECTAMENTE =>" <<endl<<endl; 
				break;
			}
			case 11:
			{
				repite1 = false;
				break;
			}
		}
		system("cls");
	}while(repite1);	
	return 0;
}

	int menu(const char* titulo, const char*opciones[], int m)
	{
		int opcionSelec=1; 
		int tecla; 
		bool repite = true; 
		do {
			system("cls");
			gotoxy(45,4+opcionSelec);cout << "=>";
			gotoxy(0, 2);cout << "------------------------------------------------------------------------------------------------------------------------";
			gotoxy(48,2); cout <<  titulo;//Imprime el título
			for (int i=0; i<m; i++)
			{
				gotoxy(50, 5+i);cout <<  i+1 <<" "<< opciones[i];	
			}
			gotoxy(0,m+7);cout << "------------------------------------------------------------------------------------------------------------------------";
			do
			{
				tecla = getch2();//captura tecla seleccionada por el usuario en ascii
			}while(tecla != TECLA_ARRIBA && tecla!=TECLA_ABAJO && tecla!=ENTER);//solo permite teclas w, s y enter
			switch(tecla)
			{
				case TECLA_ARRIBA:
				{
					opcionSelec--;
					if (opcionSelec < 1)
					{
						opcionSelec = m;
					}
					break;
				}
				case TECLA_ABAJO:
				{
					opcionSelec++;
					if (opcionSelec > m)
					{
						opcionSelec = 1;
					}
					break;
				}
				case ENTER:
				{
					repite = false;	
					break;
				}
			}
			
			
		}while(repite);
		return opcionSelec;	
	}
