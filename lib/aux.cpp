#include <sstream>
#include <string>

template <typename T>
void PrintVector(vector<T> &v){
    for (short unsigned i = 0; i < v.size(); i++){
        cout << v[i];
        (i < v.size() - 1) ? cout << ", " : cout << endl;
    }
}

// Comprueba si todos los elementos del vector son iguales a 'value'
template <typename T>
bool AllSetTo(vector<T> &v, T value){
    for (short unsigned i = 0; i < v.size(); i++)
        if (v[i] != value)
            return false;
    return true;
}

// Devuelve la posición del valor mínimo encontrado en el vector
// siempre y cuando no esté marcado como 'true' en el vector 'labels'
template <typename T>
int GetminPos(vector<T> &v, vector<bool> &labels){
    int min = MAXINT;
    int pos = -1;
    for (short unsigned i = 0; i < v.size(); i++)
        if ((v[i] < min) && (!labels[i])){
            min = v[i];
            pos = i;
        }
    //cout << "GetMinPos = " << pos << endl; // DEBUG
    return pos;
}

// Convierte un número een un string
template <typename T>
string NumberToString( T Number ){
    ostringstream ss;
    ss << Number;
    return ss.str();
}

// Muestra el camino desde 's' hasta 'i'
void ShowPath(unsigned s, unsigned i, vector<unsigned> &pred, unsigned level , string &result){
    if (i != s){
        if ((i < pred.size()) && (pred[i] < UERROR)){
            ShowPath(s, pred[i], pred, level+1, result);
            result += NumberToString(pred[i]+1) + "->";
        }
    }
    if (level == 0)
        pred[i] < UERROR ? result += NumberToString(i+1) : result = "";
        
}

// Recopila y muestra los caminos mínimos deducibles a partir de los vectores 'd' y 'pred'
void CaminosMinimos(unsigned s, vector<int> &d, vector<unsigned> &pred){
    //En esta parte del código, mostramos los caminos mínimos, si los hay
    cout << "Caminos mínimos:" << endl;
    for (unsigned i = 0; i < pred.size(); i++){
        if (i != s){  // No mostraremos el camino de un nodo a sí mismo
            cout << "[" << s+1 << "-" << i+1 << "] ";
            string path = "";
            ShowPath(s,i,pred,0,path);
            if (path != ""){
                cout << path;
                cout << ", Coste = ";
                d[i] < MAXINT ? cout << d[i] << endl : cout << "∞" << endl;
            } else {
                cout << "No hay camino" << endl;
            }
        }
    }
}
