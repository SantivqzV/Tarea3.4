/**
 * Santiago Vázquez - A01177850
 * Adrian Gomez - A00835254
 * Saul Ortega Figueroa - A01252717 
 * v1
 * 
 * Fecha de creación: 13/10/2023
 * Fecha de modificación: 18/10/2023
 * 
 * Descripción:
 * Este programa tiene como objetivo leer un archivo de bitácora que contiene registros de accesos por dirección IP. 
 * Una vez leídos estos registros, el programa almacena las direcciones IP en dos estructuras de datos diferentes: 
 * un Árbol Binario de Búsqueda (BST) y un Árbol Biselado.
 * 
 * Posteriormente, el programa compara el tiempo de ejecución de búsquedas de direcciones IP en ambas estructuras. 
 * Las búsquedas se realizan utilizando las direcciones IP del mismo archivo de bitácora y se prueban en diferentes 
 * secuencias: en el orden original, orden ascendente, orden descendente y una misma IP 12006 veces. 
 * 
 * Además, se analizará el tiempo de ejecución de las búsquedas en estos casos utilizando la librería chrono. 
 * 
 * 
 * Referencias
 * Splay Tree Visualzation. (2023). Usfca.edu. https://www.cs.usfca.edu/~galles/visualization/SplayTree.html 
 * Introduction to Splay tree data structure. (2023, February 9). GeeksforGeeks; GeeksforGeeks. https://www.geeksforgeeks.org/introduction-to-splay-tree-data-structure/ 
 * Binary Search Tree. (2015, December 14). GeeksforGeeks; GeeksforGeeks. https://www.geeksforgeeks.org/binary-search-tree-data-structure/ 
 * What is a distributed denial-of-service (DDoS) attack? (2023). Cloudflare. https://www.cloudflare.com/learning/ddos/what-is-a-ddos-attack/ 
*/

//Librerias básicas para el programa
#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
#include <vector>

//libreria para medir tiempos de ejecución
#include <chrono>
using namespace std;

/**
 * @class Linea
 * 
 * @brief Representa una línea de datos con información de fecha, hora, IP y mensaje.
 * 
 * La clase Linea proporciona una estructura para almacenar 
 * y manipular datos relacionados con líneas de información. 
 * Cada objeto Linea contiene información como el año, mes, 
 * día, hora, minuto, segundo, dirección IP y mensaje. 
 * Además, la clase proporciona constructores para inicializar 
 * objetos con estos datos y getters para acceder a ellos.
*/
class Linea{
    private:
        string fecha;       ///< Fecha de la línea de datos
        string time;        ///< Hora de la línea de datos 
        string ip;          ///< Dirección IP asociada a la línea de datos.
        string message;     ///< Mensaje contenido en la línea de datos.
        double key;         ///< Dirección IP en base 10
    public:
        /**
         * @brief Constructor por defecto de la clase Linea.
         * 
         * Inicializa todos los atributos de la clase con valores predeterminados.
        */
        Linea(){
            fecha = "";
            time = "";
            ip = "";
            message = "";
            key = 0;
        }
        
        /**
         * @brief Constructor de la clase Linea con parámetros.
         * 
         * Este constructor permite inicializar un objeto Linea con valores específicos para cada atributo.
         * 
         * @param year Año de la línea de datos.
         * @param month Mes de la línea de datos en formato de tres letras (por ejemplo, "Jan" para enero).
         * @param day Día de la línea de datos.
         * @param hour Hora de la línea de datos.
         * @param minute Minuto de la línea de datos.
         * @param second Segundo de la línea de datos.
         * @param ip Dirección IP asociada a la línea de datos.
         * @param message Mensaje contenido en la línea de datos.
        */
        Linea(string fecha, string time, string ip, string message){
            this -> fecha = fecha;
            this -> time = time;
            this->ip = ip;
            this->message = message;
            this->key = conversion(ip);
        }

        // Getters para acceder a los atributos de la clase.
        string getFecha(){
            return fecha;
        }

        string getTime(){
            return time;
        }

        string getIp(){
            return ip;
        }

        string getMessage(){
            return message;
        }

        double getKey(){
            return key;
        }

        /**
         * @brief Convertir un Ip a un valor en base 10
         * 
         * Este método recibe una ip en string y se encarga de parsear cada elemento de la IP y guardarlo en
         * una fila (La cual sigue la metodología FIFO). Despues se inspeccionarán los elementos de dicha fila, se
         * realizará la operación de conversión correspondiente y se borrarán de ella. Todo esto dará un double con
         * el valor decimal del IP.
         * 
         * @param[in] string ip, string a parsear y convertir a base 10
         * 
         * @return double total, valor del key de la IP
         * 
         * @note Comepljidad de tiempo: O(n)
         * @note Complejidad de espacio: O(1)
         * 
        */
        double conversion(string ip){
            double total;

            //Definir la queue para elementos del IP
            vector<string> temp;
            string aux = "";

            //Parsear y guardar elementos del ip en Queue
            for(int i = 0; i <= ip.size(); i++){
                if(ip[i] == '.'){
                    temp.push_back(aux);
                    aux = "";
                }
                else{
                    aux += ip[i];
                }
            }
            temp.push_back(aux);

            //Convertir los datos de la IP a base 10
            int sizeTemp  = temp.size();
            for(int i = 0; i < sizeTemp; i++){
                total += stoi(temp[i]) * pow(256, 3-i);
            }

            return total;
        }

        /**
         * @brief SobreCarga de "=="
         * 
         * Esta función verifica si dos objetos de la clase Linea son iguales comparando 
         * sus atributos de Key (Ip en base 10). Si estas llaves son iguales, la función 
         * devuelve true, de lo contrario false.
         * 
         * @param[in] linea El objeto linea con el que se va a comparar.
         * 
         * @return true si los objetos son iguales en key, false en caso contrario.
         * 
         * @note Complejidad de tiempo: O(1)
         * @note Complejiad de espacio: O(1)
        */
        bool operator==(Linea linea){
            return this->key == linea.key;
        }

        /**
         * @brief SobreCarga de ">"
         * 
         * Esta función verifica si un objeto de la clase Linea es mayor que otro comparando 
         * sus atributos de Key (Ip en base 10). Si la llave del objeto que llama a la función 
         * es mayor que la llave del objeto que se pasa como parámetro, la función devuelve true, 
         * de lo contrario false.
         * 
         * @param[in] linea El objeto linea con el que se va a comparar.
         * 
         * @return true si el objeto que llama a la función es mayor que el objeto que se pasa como parámetro, false en caso contrario.
         * 
         * @note Complejidad de tiempo: O(1)
         * @note Complejidad de espacio: O(1)
        */
        bool operator>(Linea linea){
            return this->key > linea.key;
        }

        /**
         * @brief SobreCarga de "<"
         * 
         * Esta función verifica si un objeto de la clase Linea es menor que otro comparando 
         * sus atributos de Key (Ip en base 10). Si la llave del objeto que llama a la función 
         * es menor que la llave del objeto que se pasa como parámetro, la función devuelve true, 
         * de lo contrario false.
         * 
         * @param[in] linea El objeto linea con el que se va a comparar.
         * 
         * @return true si el objeto que llama a la función es menor que el objeto que se pasa como parámetro, false en caso contrario.
         * 
         * @note Complejidad de tiempo: O(1)
         * @note Complejidad de espacio: O(1)
        */
        bool operator<(Linea linea){
            return this->key < linea.key;
        }

        /**
         * @brief SobreCarga de ">="
         * 
         * Esta función verifica si un objeto de la clase Linea es mayor o igual que otro comparando 
         * sus atributos de Key (Ip en base 10). Si la llave del objeto que llama a la función 
         * es mayor o igual que la llave del objeto que se pasa como parámetro, la función devuelve true, 
         * de lo contrario false.
         * 
         * @param[in] linea El objeto linea con el que se va a comparar.
         * 
         * @return true si el objeto que llama a la función es mayor o igual que el objeto que se pasa como parámetro, false en caso contrario.
         * 
         * @note Complejidad de tiempo: O(1)
         * @note Complejidad de espacio: O(1)
        */
        bool operator>=(Linea linea){
            return this->key >= linea.key;
        }

        /**
         * @brief SobreCarga de "<="
         * 
         * Esta función verifica si un objeto de la clase Linea es menor o igual que otro comparando 
         * sus atributos de Key (Ip en base 10). Si la llave del objeto que llama a la función 
         * es menor o igual que la llave del objeto que se pasa como parámetro, la función devuelve true, 
         * de lo contrario false.
         * 
         * @param[in] linea El objeto linea con el que se va a comparar.
         * 
         * @return true si el objeto que llama a la función es menor o igual que el objeto que se pasa como parámetro, false en caso contrario.
         * 
         * @note Complejidad de tiempo: O(1)
         * @note Complejidad de espacio: O(1)
        */ 
        bool operator<=(Linea linea){
            return this->key <= linea.key;
        }
};

/**
 * @class NodeBST
 * 
 * @brief Clase para nodo para un BST. Se utiliza "Template class" que representa el tipo de dato que recibe el nodo. 
 * 
 * Esta clase representa un nodo para un árbol binario que contiene un tipo de dato T, con apuntador tanto para el 
 * nodo derecho como el izquierdo.
 * 
 * @tparam T, tipo de dato que se guardará en el nodo
 * @param T info, dato a guardar en el nodo
 * @param Node<T>* left, puntero al nodo izquierdo
 * @param Node<T>* right, puntero al nodo derecho
*/
template <class T>
class NodeBST{
    public:
        T info;
        NodeBST<T> *left;
        NodeBST<T> *right;

        //Constructor por default
        NodeBST(T data){
            info = data;
            left = nullptr;
            right = nullptr;
        }
};

/**
 * @class BST
 * 
 * @brief Clase representando un árbol binario, una estructura de datos que ordena los elementos
 * mientras se agregan haciendo fácil el ordenamiento de la estructura. Esta clase contiene las operaciones
 * que el árbol puede realizar
 * 
 * @tparam T, tipo de dato que se guardará
 * @param NodeBST<T>* p, puntero a la raíz del árbol
*/
template <class T>
class BST{
    private:
        NodeBST<T>* root;

        /**
         * @brief Insertar un elemento en el árbol binario.
         * 
         * Esta función recibe la p y la información del nodo y se encarga de recorrer 
         * el árbol binario hasta llegar a la posición correcta del dato en cuanto a su orden.
         * 
         * @param[in,out] NodeBST<T>* p, puntero a la raíz del árbol
         * @param[in] T info, información a guardar en el árbol
         * @return BST con un elemento adicional
         * 
         * @note Complejidad de tiempo: O(h)
         * @note Complejidad de espacio: O(h)
        */
        NodeBST<T>* insertarRecursivo(NodeBST<T>* p, T info){
            if(p == nullptr){
                p = new NodeBST<T>(info);
            }
            else if(info < p->info){
                p->left = insertarRecursivo(p->left, info);
            }
            else if(info > p->info){
                p->right = insertarRecursivo(p->right, info);
            }
            else{
                //cout << "El dato " << info.getIp() << " ya existe" << endl;
            }
            return p;
        }

        /**
         * @brief Busqueda de un elemento
         * 
         * Buscar un valor dentro del BST. Si el elemento a buscar es menor que la raíz,
         * buscar en el subárbol izquierdo, si es mayor, en el subárbol derecho. 
         * Ésto se repite hasta que el dato sea encontrado o se llegue a un nodo donde sus punteros contengan nullptr. 
         * Para el caso que exista el dato a buscar, se imprimirán los nodos ancestros del dato buscado. 
         * 
         * @param[in, out] NodeBST<T>* p, puntero a la raíz del árbol
         * @param[in] T info, información a buscar en el árbol
         * @return ancestros del nodo buscado
         * 
         * @note Complejidad de tiempo: O(h)
         * @note Complejidad de espacio: O(h)
        */
        bool buscar(NodeBST<T>* p, T value){
            if(p == nullptr){
                return false;
            }
            if(p->info == value){
                return true;
            }
            if(buscar(p->left, value) || buscar(p->right, value)){
                return true;
            }
            return false;
        }
        
        /**
         * @brief Eliminar un elemento
         * 
         * Se elimina un nodo del árbol y se actualizan los putneros de los nodos que colindan
         * con el eliminado para no romper la estructura del árbol. 
         * 
         * @param[in] NodeBST<T>* p, puntero a la raíz del árbol o ramas
         * @param[in] T info, dato a borrar
         * @return árbol sin un elemento
         * 
         * @note Complejidad de tiempo: O(h)
         * @note Complejidad de espacio: O(h)
        */
        NodeBST<T>* eliminarRecursivo(NodeBST<T>* p, T info){
            if(p == nullptr){
                return nullptr;
            }
            else if(info < p->info){
                p->left = eliminarRecursivo(p->left, info);
            }
            else if(info > p->info){
                p->right = eliminarRecursivo(p->right, info);
            }
            else{
                NodeBST<T>* q = p;
                if(q->left == nullptr){
                    p = q->right;
                }
                else if(q->right == nullptr){
                    p = q->left;
                }
                else{
                    q = remplazar(q);
                }
                delete q;
            }
            return p;
        }
        
    public:
        //Constructor por default
        BST(){
            root = nullptr;
        }

        //Destructor
        ~BST(){
            delete root;
        }

        /**
         * @brief Mandar a llamar el método de busquedaRecursiva
         * 
         * Este método solamente recibe la información a buscar como parámetro y luego manda 
         * a llamar el método de busqueda recursiva para poder encontrar si un dato se encuentra
         * en el árbol.
         * 
         * @param[in] T info, valor a buscar en el árbol
         * @return raíz del nodo buscado  
         * 
         * @note Complejidad de tiempo: O(h)
         * @note Complejidad de espacio: O(h)
        */
        bool busqueda(T info){
            bool resultado = buscar(root, info);

            if(!resultado){
                cout << "El elemento buscado no existe" << endl;
            }
            return resultado;
        }

        /**
         * @brief Mandar a llamar el método de insertarRecursivamente
         * 
         * Este método solamente recibe la información a guardar como parametro y luego manda
         * a llamar al método de inserción recursiva para completar la inserción del dato ingresado.
         * 
         * @param[in] T info, dato a guardar en el BST
         * @return BST con un elemento adicional
         * 
         * @note Complejidad de tiempo: O(h)
         * @note Complejidad de espacio: O(h)
        */
        void insertar(T info){
            root = insertarRecursivo(root, info);
        }

        /**
         * @brief Mandar a llamar el método de EliminarRecursivo.
         * 
         * Este método solamente recibe la información que debe de ser borrada como parámetro y luego
         * manda a llamar el método de eliminación recursiva para borrar el elemento ingresado.
         * 
         * @param[in] T info, dato a borrar del BST
         * @return BST sin un elemento
         * 
         * @note Complejidad de tiempo: O(h)
         * @note Complejidad de espacio: O(h)
        */
        void eliminar(T info){
            root = eliminarRecursivo(root, info);
        }
};

//Arbol biselado
/**
 * @class Nodo 
 * 
 * @brief Clase que representa un Nodo para un splay tree
 * 
 * Esta clase representa un nodo para un splay tree. 
 * El nodo contiene un valor, un contador de accesos y punteros hacia su progenitor, nodo izquierdo y nodo derecho.
 * 
 * @tparam T tipo de datos guardado en el nodo
 * @param T value, valor del nodo
 * @param int accesos, contador de cuantas veces un nodo fue accedido
 * @param Node<T>* left, puntero al hijo izquierdo
 * @param Node<T>* right, puntero al hijo derecho
 * @param Node<T>* parent, puntero al nodo padre. 
*/
template <class T>
class Node{
    public:
        T value;
        int accesos;
        Node<T>* left;
        Node<T>* right;
        Node<T>* parent;

        //Constructor por default
        Node(T info){
            value = info;
            accesos = 0;
            left = nullptr;
            right = nullptr;
            parent = nullptr;
        }
};

/**
 * @class SplayTree
 * 
 * @brief Clase representando un Splay tree
 * 
 * Esta clase representa una implementación de un Splay Tree. Esta estructura de datos es un
 * tipo de BST que reajusta el último valor buscado a la primera posición de la estructura. 
 * Se incluyen operaciones para insertar, borrar, buscar, imprimir y obtener el tamaño. 
*/
template <class T>
class SplayTree{
    private:
        Node<T>* root;

        /**
         * @brief Función que busca un valor en el árbol
         * 
         * Esta función busca un valor en el árbol. Si lo encuentra, lo reajusta a la raíz. 
         * Si no lo encuentra, reajusta el último nodo visitado a la raíz. 
         * 
         * @param Node<T>* node, nodo a partir del cual se busca
         * @param T value, valor a buscar
         * @return Node<T>* nodo encontrado
         * 
         * @note Complejidad de tiempo: O(n)
         * @note Complejidad de espacio: O(n)
        */
        Node<T>* buscar(Node<T>* node, T value){
            if(node == nullptr){
                return nullptr;
            }
            else if(node->value == value){
                return node;
            }
            else if(node->value > value){
                return buscar(node->left, value);
            }
            else{
                return buscar(node->right, value);
            }
        }

        /**
         * @brief Función que reajusta un nodo a la raíz
         * 
         * Esta función reajusta un nodo a la raíz. 
         * 
         * @param Node<T>* node, nodo a reajustar
         * 
         * @note Complejidad de tiempo: O(n)
         * @note Complejidad de espacio: O(1)
        */
        void splay(Node<T>* node){
            while(node->parent != nullptr){
                if(node->parent->parent == nullptr){
                    if(node->parent->left == node){
                        rotateRight(node->parent);
                    }
                    else{
                        rotateLeft(node->parent);
                    }
                }
                else if(node->parent->left == node && node->parent->parent->left == node->parent){
                    rotateRight(node->parent->parent);
                    rotateRight(node->parent);
                }
                else if(node->parent->right == node && node->parent->parent->right == node->parent){
                    rotateLeft(node->parent->parent);
                    rotateLeft(node->parent);
                }
                else if(node->parent->left == node && node->parent->parent->right == node->parent){
                    rotateRight(node->parent);
                    rotateLeft(node->parent);
                }
                else{
                    rotateLeft(node->parent);
                    rotateRight(node->parent);
                }
            }
        }

        /**
         * @brief Función que rota un nodo a la derecha
         * 
         * Esta función rota un nodo a la derecha. 
         * 
         * @param Node<T>* node, nodo a rotar
         * 
         * @note Complejidad de tiempo: O(1)
         * @note Complejidad de espacio: O(1)
        */
        void rotateRight(Node<T>* node){
            Node<T>* aux = node->left;
            node->left = aux->right;
            if(aux->right != nullptr){
                aux->right->parent = node;
            }
            aux->parent = node->parent;
            if(node->parent == nullptr){
                root = aux;
            }
            else if(node == node->parent->right){
                node->parent->right = aux;
            }
            else{
                node->parent->left = aux;
            }
            aux->right = node;
            node->parent = aux;
        }

        /**
         * @brief Función que rota un nodo a la izquierda
         * 
         * Esta función rota un nodo a la izquierda. 
         * 
         * @param Node<T>* node, nodo a rotar
         * 
         * @note Complejidad de tiempo: O(1)
         * @note Complejidad de espacio: O(1)
        */
        void rotateLeft(Node<T>* node){
            Node<T>* aux = node->right;
            node->right = aux->left;
            if(aux->left != nullptr){
                aux->left->parent = node;
            }
            aux->parent = node->parent;
            if(node->parent == nullptr){
                root = aux;
            }
            else if(node == node->parent->left){
                node->parent->left = aux;
            }
            else{
                node->parent->right = aux;
            }
            aux->left = node;
            node->parent = aux;
        }

        /**
         * @brief Función que imprime el árbol
         * 
         * Esta función imprime el árbol. 
         * 
         * @param Node<T>* node, nodo a partir del cual se imprime
         * 
         * @note Complejidad de tiempo: O(n)
         * @note Complejidad de espacio: O(n)
        */
        void print(Node<T>* node, string indent, bool last){
            if(node != nullptr){
                cout << indent;
                if(last){
                    cout << "R----";
                    indent += "     ";
                }
                else{
                    cout << "L----";
                    indent += "|    ";
                }
                cout << node->value << endl;
                print(node->left, indent, false);
                print(node->right, indent, true);
            }
        }

        /**
         * @brief Función que obtiene el tamaño del árbol
         * 
         * Esta función obtiene el tamaño del árbol. 
         * 
         * @param Node<T>* node, nodo a partir del cual se obtiene el tamaño
         * @return int tamaño del árbol
         * 
         * @note Complejidad de tiempo: O(n)
         * @note Complejidad de espacio: O(n)
        */
        int size(Node<T>* node){
            if(node == nullptr){
                return 0;
            }
            else{
                return 1 + size(node->left) + size(node->right);
            }
        }

        /**
         * @brief Función que obtiene el nodo con el valor mínimo
         * 
         * Esta función obtiene el nodo con el valor mínimo. 
         * 
         * @param Node<T>* node, nodo a partir del cual se obtiene el valor mínimo
         * @return Node<T>* nodo con el valor mínimo
         * 
         * @note Complejidad de tiempo: O(n)
         * @note Complejidad de espacio: O(1)
        */
        Node<T>* minValueNode(Node<T>* node){
            Node<T>* current = node;
            while(current->left != nullptr){
                current = current->left;
            }
            return current;
        }

        /**
         * @brief Función que elimina un nodo
         * 
         * Esta función elimina un nodo. 
         * 
         * @param Node<T>* node, nodo a eliminar
         * 
         * @note Complejidad de tiempo: O(n)
         * @note Complejidad de espacio: O(1)
        */
        void del(Node<T>* node){
            if(node->left == nullptr){
                Node<T>* aux = node->right;
                if(node->parent == nullptr){
                    root = aux;
                }
                else if(node == node->parent->left){
                    node->parent->left = aux;
                }
                else{
                    node->parent->right = aux;
                }
                if(aux != nullptr){
                    aux->parent = node->parent;
                }
                delete node;
            }
            else if(node->right == nullptr){
                Node<T>* aux = node->left;
                if(node->parent == nullptr){
                    root = aux;
                }
                else if(node == node->parent->left){
                    node->parent->left = aux;
                }
                else{
                    node->parent->right = aux;
                }
                if(aux != nullptr){
                    aux->parent = node->parent;
                }
                delete node;
            }
            else{
                Node<T>* aux = minValueNode(node->right);
                node->value = aux->value;
                del(aux);
            }
        }

        public:
            //Constructor por default
            SplayTree(){
                root = nullptr;
            }

            /**
             * @brief Función que busca un valor en el árbol
             * 
             * Esta función busca un valor en el árbol. Si lo encuentra, lo reajusta a la raíz. 
             * Si no lo encuentra, reajusta el último nodo visitado a la raíz. 
             * 
             * @param T value, valor a buscar
             * @return Node<T>* nodo encontrado
             * 
             * @note Complejidad de tiempo: O(n)
             * @note Complejidad de espacio: O(n)
            */
            Node<T>* busqueda(T value){
                Node<T>* node = buscar(root, value);
                if(node){
                    node->accesos++;
                    splay(node);
                }
                return node;
            }

            /**
             * @brief Función que inserta un valor en el árbol
             * 
             * Esta función inserta un valor en el árbol. 
             * 
             * @param T value, valor a insertar
             * 
             * @note Complejidad de tiempo: O(n)
             * @note Complejidad de espacio: O(1)
            */
            void insertar(T value){
                Node<T>* node = new Node<T>(value);
                node -> parent = nullptr;
                node -> left = nullptr;
                node -> right = nullptr;
                Node<T>* y = nullptr;
                Node<T>* x = root;

                while(x != nullptr){
                    y = x;
                    if(node->value < x->value){
                        x = x->left;
                    }
                    else{
                        x = x->right;
                    }
                }

                node->parent = y;
                if(y == nullptr){
                    root = node;
                }
                else if(node->value < y->value){
                    y->left = node;
                }
                else{
                    y->right = node;
                }
                splay(node);
            }

            /**
             * @brief Función que elimina un valor del árbol
             * 
             * Esta función elimina un valor del árbol. 
             * 
             * @param T value, valor a eliminar
             * 
             * @note Complejidad de tiempo: O(n)
             * @note Comepljidad de espacio: O(1)
            */
            void eliminar(T value){
                Node<T>* node = buscar(value);
                if(node){
                    del(node);
                }
            }

            /**
             * @brief Función que imprime el árbol
             * 
             * Esta función imprime el árbol. 
             * 
             * @note Complejidad de tiempo: O(n)
             * @note Complejidad de espacio: O(n)
            */
            void imprimeArbol(){
                print(root, "", true);
            }
};

/**
 * @brief Lee datos de un archivo de registro y los almacena en la estructura de datos correspondiente.
 * 
 * Esta función abre el archivo "bitacoraelb.txt" y lee cada línea de registro. Luego, procesa y extrae
 * los datos relevantes de cada línea, como año, mes, día, hora, minuto, segundo, dirección IP y mensaje.
 * Utiliza estos datos para insertar un objeto Linea y lo inserta al final de la estructura correspondiente.
 * 
 * @param[in,out] T* arbol, estructura de datos donde se guardarán los objetos
 * 
 * @return Estructura de datos con los objetos del archivo
 * 
 * @note Complejidad de tiempo: O(N) - Donde N es la cantidad de líneas en el archivo de registro.
 * @note Complejidad de espacio: O(1) - Se asignan recursos para almacenar los datos de cada línea, pero no se utiliza memoria adicional significativa.
*/
template<typename T>
void read(T* arbol){
    ifstream file;
    file.open("bitacoraelb.txt");
    string line;
    while(getline(file, line)){
        stringstream ss(line);
        string year, month, day, time, ip, message;
        ss >> year;   // Leer el año
        ss >> month;  // Leer el mes
        ss >> day;    // Leer el día
        ss >> time;   // Leer la hora
        ss.ignore(6); // Ignorar " | IP: "
        ss >> ip;     // Leer la IP
        ss.ignore(8); // Ignorar " | INFO: "
        getline(ss, message, '\n'); // Utilizar '\n' en lugar de ' ' para leer el mensaje
        string fecha_completa = year + " " + month + " " + day;
        Linea linea(fecha_completa, time, ip, message);
        arbol -> insertar(linea);
    }
    file.close();
}

/**
 * @brief Realiza la búsqueda de datos en un árbol binario o árbol Splay a partir de un archivo.
 *
 * Esta función lee líneas de un archivo y busca los datos correspondientes en un árbol binario
 * o un árbol Splay. Se espera que el archivo contenga líneas con información, y la función
 * buscará elementos en el árbol basándose en las IP contenidas en esas líneas.
 *
 * @tparam T El tipo de árbol (BST o SplayTree) que se utilizará para la búsqueda.
 * @param[in] file Un flujo de archivo (ifstream) que se utilizará para leer el archivo de entrada.
 * @param[in] arbol Un puntero al árbol (BST o SplayTree) en el que se realizarán las búsquedas.
 *
 * @note Complejidad de tiempo: O(N * log(N)), donde N es el número de elementos en el árbol.
 * @note Complejidad de espacio: O(1) - No se asignan nuevas estructuras de datos.
 */
template<typename T>
void busquedaDeDatos(ifstream& file, T* arbol){
    string line;
    while(getline(file, line)){
        stringstream ss(line);
        string ip;
        ss.ignore(26); // Ignorar hasta la ip
        ss >> ip;     // Leer la IP
        Linea linea("", "", ip, "");
        if(!arbol -> busqueda(linea)){
            cout << "Hay datos inexistentes" << endl;
        }
    }
    file.close();
}

/**
 * @brief Realiza mediciones de tiempo para la búsqueda de datos en árboles BST y Splay Tree.
 *
 * Esta función mide el tiempo requerido para buscar datos en dos árboles diferentes: un árbol binario (BST)
 * y un árbol Splay (Splay Tree). Utiliza un archivo de registro que contiene líneas de información y realiza
 * búsquedas en los árboles basándose en las IP contenidas en esas líneas. Luego, muestra el tiempo de ejecución
 * para cada tipo de árbol.
 *
 * @param[in] file El nombre del archivo de registro que se utilizará para la búsqueda de datos.
 *
 * @note Complejidad de tiempo: O(N * log(N)) para la búsqueda en el árbol (BST o Splay Tree).
 * @note Complejidad de espacio: O(N) - Se crean estructuras de árbol para almacenar los datos.
 */
void tiempoArbol(string file){
    //Leer archivo
    ifstream archivo(file);

    //Crear los ADT correspondientes
    BST<Linea>* arbol = new BST<Linea>();
    SplayTree<Linea>* splay = new SplayTree<Linea>();
    
    //Guardar los elementos del archivo bitacora
    read(arbol);
    read(splay);

    //Buscar los elementos del archivo de busqueda para el BST
    auto inicioBST = chrono::high_resolution_clock::now();
    busquedaDeDatos(archivo, arbol);
    auto finBST = chrono::high_resolution_clock::now();
    auto duracionBST = chrono::duration_cast<chrono::microseconds>(finBST - inicioBST);
    cout << "Tiempo de ejecución BST: " << duracionBST.count() << " microsegundos" << endl;
    
    //Reabrir archivo para la ejecución usando un Splay Tree
    archivo.open(file);

    //Buscar los elementos del archivo de busqueda para el Slay Tree
    auto inicioSplay = chrono::high_resolution_clock::now();
    busquedaDeDatos(archivo, splay);
    auto finSplay = chrono::high_resolution_clock::now();
    auto duracionSplay = chrono::duration_cast<chrono::microseconds>(finSplay - inicioSplay);
    cout << "Tiempo de ejecución Splay Tree: " << duracionSplay.count() << " microsegundos" << endl;
    
    //Liberar espacio de ambas ADT
    delete arbol;
    delete splay;
}

int main(){
    //Iniciar Cronometro de programa
    auto inicioPrograma = chrono::high_resolution_clock::now();    

    string busquedas[] = {"bitacoraelb.txt", "ResultadosOrdenadosAscendente.txt", "ResultadosOrdenadosDescendente.txt", "ResultadosRepetidos.txt"};
    
    //Tamaño de arreglo
    int size = sizeof(busquedas)/sizeof(busquedas[0]);

    for(int i = 0; i < size; i++){
        cout << "Con archivo: " << busquedas[i] << endl;
        tiempoArbol(busquedas[i]);
        cout << endl;
    }

    //Tomar tiempo de ejecución del programa completo
    auto finPrograma = chrono::high_resolution_clock::now();
    auto duracionPrograma = chrono::duration_cast<chrono::microseconds>(finPrograma - inicioPrograma);
    cout << endl << "Tiempo total de ejecución: " << duracionPrograma.count() << " microsegundos" << endl;

    return 0;
}

/**
 * El primer archivo tiene 12006 direcciones IP aleatorias, es decir no siguen ningún tipo de orden predefinido. 
 * Como se puede ver, el splay tree fue más rápido. Esto se puede deber a que, al hacer el reacomodo, las ips que 
 * siguen en buscarse se encuentran más cerca del nodo raíz. De igual manera, la naturaleza del splay tree hace que, 
 * si existen IPs repetidas, están se encontrarán en seguida debido a que, al ser accedido, el nodo se traslada al nodo raíz. 
 * Mientras que el BST siempre buscará por la misma estructura inicial. 
 * 
 * 
 * En el segundo caso donde se buscan 12006 direcciones IP ordenadas de manera ascendente, el Splay Tree fue más rápido. 
 * Al empezar con el nodo más chico, en todas las operaciones se buscará por su lado derecho; es decir, como el último nodo a 
 * ser accedido es el que se coloca en el nodo raíz en la siguiente iteración, después de la primera búsqueda no quedará ningún 
 * nodo a la izquierda de la raíz y mientras se sigan buscando Ips mayores o iguales al nodo raíz, la búsqueda siempre se realizará 
 * en el hijo derecho dejando en la izquierda del nodo raíz a todos los números que ya fueron buscados. Toda esta información nos sirve 
 * para analizar que cada vez que se busca un nodo, ese mismo se elimina del proceso de búsqueda (No del árbol), lo que hace que cada 
 * vez sea más rápido encontrar el siguiente valor en el archivo ordenado de manera ascendente. Mientras que el BST tiene que recorrer 
 * a todos los nodos del árbol sin tener ese proceso de eliminación. 
 * 
 * 
 * Para el tercer archivo donde hay 12006 direcciones Ip ordenadas de manera descendente, el Splay Tree fue más rápido. Al empezar con el nodo más grande, 
 * se repite el mismo proceso que con los ordenados de manera ascendente solamente varía que los nodos buscados se acomodarán a la derecha del nodo raíz y 
 * a la izquierda quedarán todos los nodos a buscar. Mientras que el BST tiene que recorrer a todos los nodos del árbol sin tener ese proceso de eliminación.
 * 
 * 
 * El último caso muestra el poder del splay tree al buscar una misma IP muchas veces. Debido a la caracteristica de reordenamiento del último nodo accedido al nodo raíz, 
 * solo se necesita que se recorra una vez el árbol y despues todas las busquedas se realizarán en tiempo constante debido a que la raíz del árbol siempre será el que 
 * esta siendo buscado. Mientras que el bst tendrá que hacer el mismo recorrido 12006 veces en busqueda de la Ip. 
 * 
*/