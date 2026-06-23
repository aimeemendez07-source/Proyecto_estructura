//proyecto serna
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;

//esructuras
struct Pregunta{
    char preg[100];
    char opciones[4][100];
    int respCorrecta;
    int puntos;
};

struct NodoExamen{
    Pregunta preguntas;
    NodoExamen *sig;
    NodoExamen *ant;
};

//prototipos
NodoExamen *crearNodo(Pregunta preg);
void generarExamen(NodoExamen *&, struct Pregunta);
void modificarExamen(NodoExamen*&);
void aplicarExamen(NodoExamen*&);
void mostrar(NodoExamen *);
void limpiarMemoria(NodoExamen *&);

int main(){
    int opc;
    NodoExamen *examen=NULL;
    Pregunta pregunta;
    do{
        system("cls");
        cout<<"Aplicacion de Examen"<<endl;
        cout<<"Generar Examen....1"<<endl;
        cout<<"Modificar Examen..2"<<endl;
        cout<<"Aplicar Examen....3"<<endl;
        cout<<"Mostrar Examen....4"<<endl;
        cout<<"Salir.............5"<<endl;
        cout<<"Ingrese su opcion: ";
        cin>>opc;
        switch(opc){
            case 1:
                cin.ignore();
                cout<<"Pregunta: ";
                cin.getline(pregunta.preg,100);
                for(int i=0;i<4;i++){
                    cout<<"Opcion "<<i+1<<": ";
                    cin.getline(pregunta.opciones[i],100);
                }
                cout<<"Respuesta correcta (1-4): ";
                cin>>pregunta.respCorrecta;
                cout<<"Puntos: ";
                cin>>pregunta.puntos;
                system("pause");
                generarExamen(examen,pregunta);
                cin.ignore();
                break;
            case 2:
                modificarExamen(examen);
                break;
            case 3:
                aplicarExamen(examen);
                break;
            case 4:
                mostrar(examen);
                break;
        }   
    }while(opc!=5);
    limpiarMemoria(examen);
    return 0;
}

NodoExamen *crearNodo(Pregunta preg){
    NodoExamen *nuevo=new NodoExamen;
    nuevo->preguntas=preg;
    nuevo->sig=NULL;
    nuevo->ant=NULL;
    return nuevo;
}

void generarExamen(NodoExamen *&examen, Pregunta preg){
    system("cls");
    NodoExamen *nuevo=crearNodo(preg);
    NodoExamen *aux=examen;
    FILE *archivo;
    archivo =fopen("examen.txt", "a");

    if(archivo == NULL){
        cout<<"Archivo no encontrado"<<endl;
        return;
    }

    if(examen == NULL){
        examen=nuevo;
    }else{
        while(aux->sig != NULL){
            aux=aux->sig;
        }
        aux->sig=nuevo;
        nuevo->ant=aux;
    }

    fprintf(archivo,":p;%s\n",preg.preg);
    for(int i=0; i<4; i++){
        fprintf(archivo,":op%d;%s\n",i+1,preg.opciones[i]);
    }
    fprintf(archivo,":r;op%d\n",preg.respCorrecta);
    fprintf(archivo,"%d\n",preg.puntos);
    fclose(archivo);
}

void mostrar(NodoExamen *examen){
    system("cls");
    NodoExamen *aux=examen;
    while(aux !=NULL){
        cout<<"Pregunta: "<<aux->preguntas.preg<<endl;
        for(int i=0; i<4; i++){
            cout<<i+1<<")"<<aux->preguntas.opciones[i]<<endl;
        }
        cout<<"Respuesta correcta "<< aux->preguntas.respCorrecta<<endl;
        cout<<"Puntos "<< aux->preguntas.puntos<<endl;
        aux=aux->sig;
    }
    system("pause");
}

void modificarExamen(NodoExamen *&examen){
    system("cls");
    int buscar, contador = 1;
    NodoExamen *aux = examen;
    FILE *archivo;
    NodoExamen *temp = examen;
    if(examen == NULL){
        cout<<"No hay preguntas para modificar"<<endl;
        return;
    }
    cout<<"Numero de pregunta a modificar: ";
    cin>>buscar;
    
    //Buscar la pregunta
    while(aux != NULL && contador<buscar){
        aux=aux->sig;
        contador++;
    }
    if(aux == NULL){
        cout<<"Pregunta no encontrada"<<endl;
        return;
    }
    cin.ignore();

    //Modificar datos
    cout<<"Nueva pregunta: ";
    cin.getline(aux->preguntas.preg,100);
    for(int i=0; i<4; i++){
        cout<<"Nueva opcion "<<i+1<<": ";
        cin.getline(aux->preguntas.opciones[i],100);
    }
    cout<<"Nueva respuesta correcta: ";
    cin>>aux->preguntas.respCorrecta;
    cout<<"Nuevos puntos: ";
    cin>>aux->preguntas.puntos;

    //Actualizar archivo
    archivo = fopen("examen.txt","w");
    if(archivo == NULL){
        cout<<"No se pudo abrir archivo"<<endl;
        return;
    }
    
    while(temp != NULL){
        fprintf(archivo,":p;%s\n",temp->preguntas.preg);
        for(int i=0; i<4; i++){
            fprintf(archivo,":op%d;%s\n",i+1,temp->preguntas.opciones[i]);
        }
        fprintf(archivo,":r;op%d\n",temp->preguntas.respCorrecta);
        fprintf(archivo,"%d\n",temp->preguntas.puntos);
        temp=temp->sig;
    }
    fclose(archivo);

    cout<<"Examen modificado correctamente"<<endl;
    system("pause");
}

void aplicarExamen(NodoExamen *&examen){
    system("cls");
    NodoExamen *act=examen;
    char respuesta, opcion;
    int puntosT=0, puntos=0;
    if(examen == NULL){
        cout<<"No hay preguntas en el examen"<<endl;
        system("pause");
        return;
    }

    while(act != NULL){
        cout<<"Pregunta: "<<act->preguntas.preg<<endl;
        for(int i=0; i<4; i++){
            cout<<i+1<<") "<<act->preguntas.opciones[i]<<endl;
        }

        cout<<"Respuesta (1-4): ";
        cin>>respuesta;
        puntosT+=act->preguntas.puntos;

        if(respuesta-'0'==act->preguntas.respCorrecta){
           puntos+=act->preguntas.puntos;
           cout<<"Respuesta correcta! +"<<act->preguntas.puntos<<" puntos"<<endl;
        }else{
            cout<<"Respuesta incorrecta. La respuesta correcta era: "<<act->preguntas.respCorrecta<<endl;
        }

        cout<<"N=siguiente \t F=finalizar"<<endl;
        cin>>opcion;
        if(opcion=='F' || opcion=='f'){
            break;
        }
        act=act->sig;
    }
    cout<<"Examen terminado :) " << endl;
    cout<<"Puntos obtenidos: "<<puntos<<" de "<<puntosT<<endl;
    system("pause");
}

void limpiarMemoria(NodoExamen *&examen){
    NodoExamen *aux;
    while(examen != NULL){
        aux=examen;
        examen=examen->sig;
        delete aux;
    }
}