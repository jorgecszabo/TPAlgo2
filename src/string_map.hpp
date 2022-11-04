string_map::string_map(int tam){
    _raiz = new Nodo(tam);
    _size = 0;
    _tamAlfabeto = tam;
    _longPalMasLarga = 0;
}

string_map::string_map(const string_map& aCopiar) : string_map(this->_tamAlfabeto) { *this = aCopiar; }

void string_map::borrarNodo(string_map::Nodo * n) {
    if (n != nullptr) {
        const int size = n->siguientes.size();
        for (int i = 0; i < size; i++)
            borrarNodo(n->siguientes[i]);
        delete n;
    }
}

string_map& string_map::operator=(const string_map& d) {
    borrarNodo(_raiz);
   _size = d._size;
   _raiz = copiarNodo(d._raiz);
   return *this;
}

void string_map::agregar(const Palabra& palabra) {
    if (palabra.size() > _longPalMasLarga)
        _longPalMasLarga = palabra.size();
    Nodo* actual = _raiz;
    for (int i = 0; i < palabra.size(); i++) {
        if (actual->siguientes[ord(palabra[i])] == nullptr)
            actual->siguientes[ord(palabra[i])] = new Nodo(_tamAlfabeto);
        actual = actual->siguientes[ord(palabra[i])];
    }
    if (actual->finPalabra == false)
        _size++;
    actual->finPalabra = true;
}

string_map::~string_map(){
    borrarNodo(_raiz);
}

bool string_map::pertenece(const Palabra& clave) const{
    Nodo* actual = _raiz;
    int i = 0;
    while (actual != nullptr && i < clave.size()) {
        actual = actual->siguientes[ord(clave[i])];
        i++;
    }
    if (actual != nullptr)
        return actual->finPalabra;
    else return false;
}

int string_map::cantidadHijos(Nodo* n) {
    if (n == nullptr)
        return 0;
    else {
        const int size = n->siguientes.size();
        int hijos = 0;
        for (int i = 0; i < size; i++) {
            if (n->siguientes[i] != nullptr)
                hijos++;
        }
        return hijos;
    }
}

void string_map::borrar(const Palabra& clave) {
    Nodo* actual = _raiz;
    Nodo* ultimo = nullptr;
    int idx;
    for (int i = 0; i < clave.size(); i++) {
        if (cantidadHijos(actual) > 1 || actual->finPalabra == true) {
            ultimo = actual;
            idx = i;
        }
        actual = actual->siguientes[ord(clave[i])];
    }
    actual->finPalabra = false;
    if (ultimo != nullptr) {
        Nodo* aBorrar = ultimo->siguientes[idx];
        ultimo->siguientes[idx] = nullptr;
        borrarNodo(aBorrar);
    }
    _size--;
}

int string_map::cardinal() const{
    return _size;
}

bool string_map::vacio() const{
    return _size == 0;
}

int string_map::palMasLarga() const {
    return _longPalMasLarga;
}