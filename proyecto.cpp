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
    NodoExamen *examen;
    Pregunta pregunta;
    do{
        cout<<"Aplicacion de Examen"<<endl;
        cout<<"Generar Examen ...1"<<endl;
        cout<<"Modificar Examen ..2"<<endl;
        cout<<"Aplicar Examen ...3"<<endl;
        cout<<"Mostrar Examen ...4"<<endl;
        cout<<"Salir"<<endl;
        cout<<"Ingrese su opcion: ";
        cin>>opc;
        switch(opc){
            case 1:
                generarExamen(examen, pregunta);
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
    return 0;
}

NodoExamen *crearNodo(Pregunta preg){
    NodoExamen *nuevo = new NodoExamen;
    nuevo->preguntas = preg;
    nuevo->sig = NULL;
    nuevo->ant = NULL;
    return nuevo;
}

void generarExamen(NodoExamen *&examen, Pregunta preg){
    NodoExamen *nuevo = crearNodo(preg);
    NodoExamen *aux = examen;
    FILE *archivo;
    archivo =fopen("examen.txt", "a");
    if(archivo == NULL){
        cout<<"Archivo no encontrado"<<endl;
        return;
    }
    if(examen == NULL){
        examen = nuevo;
    }else{
        while(aux->sig != NULL){
            aux = aux->sig;
        }
        aux->sig = nuevo;
        nuevo->ant = aux;
    }
    fprintf(archivo,":p;%s\n",preg.preg);
    for(int i=0;i<4;i++){
        fprintf(archivo,":op%d;%s\n",i+1,preg.opciones[i]);
    }
    fprintf(archivo,":r;op%d\n",preg.respCorrecta);
    fprintf(archivo,"%d\n",preg.puntos);
    fclose(archivo);
}

void mostrar(NodoExamen *examen){
    NodoExamen *aux = examen;
    while(aux !=NULL){
        cout<<"Pregunta:"<<aux->preguntas.preg<<endl;
        for(int i=0; i<4; i++){
            cout<<i+1<<")"<<aux->preguntas.opciones[i]<<endl;
        }
        cout<<"respuesta correcta"<<aux->preguntas.respCorrecta;
        cout<<"Puntos"<<aux->preguntas.puntos;
        aux = aux->sig;
    }
}
void modificarExamen(NodoExamen *&examen){
    int buscar, contador=1;
    NodoExamen *aux=examen;
    FILE *archivo;
    archivo=fopen("examen.txt", "w");
    if(archivo==NULL){
        cout<<"archivo no encontrado";
    }
    NodoExamen *temp=examen;
    while(aux!=NULL && contador<buscar){
        aux=aux->sig;
        contador++;
    }
    if(aux==NULL){
        cout<<"No existe"<<endl;
        return;
    }
    cin.ignore();
    cout<<"Numero de pregunta a cambiar:";
    cin>>buscar;
    cout<<"Nueva pregunta: ";
    cin.getline(aux->preguntas.preg,100);
    for(int i=0;i<4;i++){
        cout<<"Nueva opcion "<<i+1<<": ";
        cin.getline(aux->preguntas.opciones[i],100);
    }
    cout<<"Nueva respuesta: ";
    cin>>aux->preguntas.respCorrecta;
    cout<<"Nuevos puntos: ";
    cin>>aux->preguntas.puntos;
    while(temp!=NULL){
        fprintf(archivo,":p;%s\n",temp->preguntas.preg);
        for(int i=0;i<4;i++){
            fprintf(archivo,":op%d;%s\n",i+1,temp->preguntas.opciones[i]);
        }
        fprintf(archivo,":r;op%d\n",temp->preguntas.respCorrecta);
        fprintf(archivo,"%d\n",temp->preguntas.puntos);
        temp=temp->sig;
    }
    fclose(archivo);
}

void aplicarExamen(NodoExamen *&examen){
    NodoExamen *act=examen;
    char respuesta;
    int puntosT=0, puntos=0;
    if(examen==NULL){
        cout<<"No encontrado";
        return;
    }
    while(act!=NULL){
        cout<<"Pregunta:"<<act->preguntas.preg;
        for(int i=0; i<4; i++){
            cout<<i+1<<") "<<act->preguntas.opciones[i]<<endl;
        }
        cout<<"Respuesta:";
        cin>>respuesta;
    puntosT+=act->preguntas.puntos;
    if(respuesta-'0'==act->preguntas.respCorrecta){
        puntos+=act->preguntas.puntos;
    }
    cout<<"N=siguiente";
    cout<<"F=finalizar:";
    cin>>respuesta;
    if(respuesta=='F' || respuesta=='f'){
     break;
    }
    act = act->sig;
    }
    cout<<"Examen terminado";
    cout<<"Puntos obtenidos"<<puntos<<"de:"<<puntosT<<endl;
}

void limpiarMemoria(NodoExamen *&examen){
    NodoExamen *aux;
    while(examen !=NULL){
        aux = examen;
        examen = examen->sig;
        delete aux;
    }
}
