/**
 * Santiago Vázquez - A01177850
 * Adrian Gomez - A00835254
 * Saul Ortega - 
 * v1
 * 
 * Fecha de creación:
 * Fecha de modificación:
 * 
 * Descripción 
 * 
 * Notas 
 * 
 * Referencias
*/

#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
using namespace std;

//Clock


/**
 * @class NodeQueue
 * 
 * @brief Nodo para Queue
 * 
 * Esta clase representa un nodo para una queue. Se utiliza la misma declaración
 * que una lista ligada simple; es decir, donde cada nodo tiene un dato y un apuntador
 * a un nodo sucesor. Se utiliza "Template Class" para representar cualquier tipo de dato que pueda contener el nodo.
 * 
 * @tparam T, tipo de dato que se guardará en el nodo
 * @param T dato, dato a guardar en el nodo
 * @param NodeQueue<T>* next, apuntador al siguiente nodo
*/
template <class T>
class NodeQueue{
    public:
        T dato;
        NodeQueue<T>* next;

        //Constructor por default de un nodo
        NodeQueue(T dataValue){
            dato = dataValue;
            next = nullptr;
        }
};

/**
 * @class Queue
 * 
 * @brief clase para representar una queue
 * 
 * Esta clase representa una fila. Cada nodo tiene un dato y un enlace al siguiente nodo de la lista.
 * Se incluyen métodos para crear, leer y borrar nodos, asi como constructor y destructor para la
 * gestión de memoria dinámica. Sigue la estructura FIFO (First-in, first-out)
 * 
 * @tparam T; tipo de dato de entrada
 * @param NodeQueue<T>* head, apuntador al primer elemento de la queue
 * @param NodeQueue<T>* tail, apuntador al último elemento de la queue
 * @param int size, tamaño de la cola
*/
template <class T>
class Queue{
    private:
        NodeQueue<T>* head;
        NodeQueue<T>* tail;
        int size;
    public:
        //Constructor por default de Queue
        Queue(){
            head = nullptr;
            tail = nullptr;
            size = 0;
        }

        //Destructor de Queue
        ~Queue(){
            NodeQueue<T>* temp = head;
            while(temp != nullptr){
                head = head->next;
                size--;
                delete temp;
                temp = head;
            }
            head = nullptr;
            tail = nullptr;
        }

        //Getter
        /**
         * @brief Obtener el tamaño de la cola
         * 
         * Este método regresa el tamaño de la cola.
         * 
         * @return int, tamaño de la cola
         * 
         * @note Complejidad de tiempo: O(1)
         * @note Complejidad de espacio: O(1)
        */
        int getSize(){
            return size;
        }

        /**
         * @brief checar si la cola está vacía
         * 
         * Este método booleano checa si la cola está vacía.
         * Si está vacía regresa true, de lo contrario regresa false.
         * 
         * @return true, si la lista está vacía
         * @return false, si la lista no está vacía
         * 
         * @note Complejidad de tiempo: O(1)
         * @note Complejidad de espacio: O(1)
        */
        bool isEmpty(){
            return head == nullptr;
        }

        /**
         * @brief Insertar un elemento al final de la lista
         * 
         * Esta función inserta un elemento en la cola en la última posición.
         * Es decir, los primeros elementos en entrar, serán los primeros elementos de la cola.
         * Estos mismos elementos serán los primeros en salir. 
         * 
         * @param[in] T dato, el valor a agregar a la cola
         * 
         * @return void, cola modificada con el valor agregado
         * 
         * @note Complejidad de tiempo: O(1)
         * @note Complejidad de espacio: O(1)
        */
        void enqueue(T dato){
            size++;
            NodeQueue<T>* newNode = new NodeQueue<T>(dato);

            //Checar si la cola está vacía
            if(isEmpty()){
                head = newNode;
                tail = newNode;
            }else{
                tail->next = newNode;
                tail = newNode;
            }
        }

        /**
         * @brief Eliminar un elemento de la cola
         * 
         * Esta función elimina el primer elemento de la cola.
         * Es decir, el primer elemento en entrar, será el primer elemento en salir.
         * 
         * @return void, cola modificada con el primer elemento eliminado
         * 
         * @note Complejidad de tiempo: O(1)
         * @note Complejidad de espacio: O(1)
        */
        void dequeue(){
            size--;
            //Checar si la cola está vacía
            if(isEmpty()){
                cout << "La cola está vacía" << endl;
            }
            else{
                NodeQueue<T>* temp = head;
                head = head->next;
                delete temp;
            }
        }

        /**
         * @brief Obtener el primer elemento de la cola
         * 
         * Esta función regresa el primer elemento de la cola.
         * Es decir, el primer elemento en entrar y el primer elemento en salir.
         * 
         * @return T, el primer elemento de la cola
         * 
         * @note Complejidad de tiempo: O(1)
         * @note Complejidad de espacio: O(1)
        */
        T peek(){
            //Checar si la cola está vacía
            if(isEmpty()){
                cout << "La cola está vacía" << endl;
                return T();
            }
            else{
                return head->dato;
            }
        }
};

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
            Queue<string>* temp = new Queue<string>();
            string aux = "";

            //Parsear y guardar elementos del ip en Queue
            for(int i = 0; i <= ip.size(); i++){
                if(ip[i] == '.'){
                    temp->enqueue(aux);
                    aux = "";
                }
                else{
                    aux += ip[i];
                }
            }
            temp -> enqueue(aux);

            //Convertir los datos de la IP a base 10
            int sizeTemp  = temp -> getSize();
            for(int i = 0; i < sizeTemp; i++){
                total += stoi(temp->peek()) * pow(256, 3-i);
                temp->dequeue();
            }

            delete temp;
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
                cout << "El dato " << info.getIp() << " ya existe" << endl;
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
                if(p == root){
                    cout << "Este nodo es la raíz del árbol" << endl;
                }
                return true;
            }
            if(buscar(p->left, value) || buscar(p->right, value)){
                cout << p->info << " ";
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

        /**
         * @brief Procedimiento de auxiliar para la operación de eliminar.
         * 
         * Procedimiento de búsqueda del nodo más a la derecha del subárbol izquierdo. 
         * Este procedimiento regresa el nodo hoja por el que se va a remplazar el actual para no romper el orden al borrar un nodo. 
         * 
         * @param[in] NodeBST<T>* act, nodo actual
         * @return Nodo hoja por el que se va a remplazar el actual
         * 
         * @note Complejidad de tiempo: O(h)
         * @note Complejidad de espacio: O(1)
        */
        NodeBST<T>* remplazar(NodeBST<T>* act){
            NodeBST<T>* a;
            NodeBST<T>* p;
            p  = act;

            //Subárbol de los menores que la raíz
            a = act -> left;

            //Encontrar el más a la derecha del izquierdo
            while(a -> right != nullptr){
                p = a;
                a = a -> right;
            }

            //Copiar en act el valor del nodo apuntado por a
            act -> info = a -> info;
            if(p == act){
                p -> left = a -> left;
            }
            else{
                p -> right = a -> left;
            }
            return a;
        }
    
        /**
         * @brief preOrder
         * 
         * Recorrer los datos en estilo de preOrder; es decir, 
         * primero se visita a la raíz y luego se continúan visitando sus hijos tambien en preOrder.
         * 
         * @param NodeBST<T>* p, raíz del árbol
         * @return Impresión del recorrido del árbol
         * 
         * @note Complejidad de tiempo: O(n)
         * @note Complejidad de espacio: O(h)
        */
        void preOrder(NodeBST<T>* p){
            if(p != nullptr){
                cout << p->info << " ";
                preOrder(p->left);
                preOrder(p->right);
            }
        }

        /**
         * @brief inOrder
         * 
         * Recorrer los datos en estilo inOrder; es decir,
         * la visita de la raíz queda en medio del recorrido de sus hijos 
         * 
         * @param NodeBST<T>* p, raíz del árbol
         * @return Impresión del recorrido del árbol
         * 
         * @note Complejidad de tiempo: O(n)
         * @note Complejidad de espacio: O(h)
        */
        void inOrder(NodeBST<T>* p){
            if(p != nullptr){
                inOrder(p->left);
                cout << p->info << " ";
                inOrder(p->right);
            }
        }

        /**
         * @brief postOrder
         * 
         * Recorrer los datos en estilo postOrder; es decir,
         * la raíz se visita despues de haber recorrido sus hijos tambien en postOrder.
         * 
         * @param NodeBST<T>* p, raíz del árbol
         * @return Impresión del recorrido del árbol
         * 
         * @note Complejidad de tiempo: O(n)
         * @note Complejidad de espacio: O(h)
        */
        void postOrder(NodeBST<T>* p){
            if(p != nullptr){
                postOrder(p->left);
                postOrder(p->right);
                cout << p->info << " ";
            }
        }

        /**
         * @brief LevelByLevel
         * 
         * Recorrer los datos en estilo nivel por nivel; es decir, se visita cada nivel del árbol antes de pasar al siguiente.
         * 
         * @param NodeBST<T>* p, raíz del árbol
         * @return Impresión del recorrido del árbol
         * 
         * @note Complejidad de tiempo: O(n)
         * @note Complejidad de espacio: O(n)
        */
        void levelByLevel(NodeBST<T>* p){
            if(p == nullptr){
                return;
            }

            //Se utliza una fila para ayudar con el proceso de impresión.
            Queue<NodeBST<T>*> q;
            q.enqueue(p);
            while(!q.isEmpty()){
                int levelSize = q.getSize(); // Use public method to get size
                for(int i = 0; i < levelSize; i++){
                    NodeBST<T>* current = q.peek();
                    q.dequeue();
                    cout << current->info << " ";
                    if(current->left != nullptr){
                        q.enqueue(current->left);
                    }
                    if(current->right != nullptr){
                        q.enqueue(current->right);
                    }
                }
            }

        }

        /**
         * @brief getHeight
         * 
         * Calcular la altura del árbol; es decir, cuantos niveles tiene el árbol.
         * 
         * @param NodeBST<T>* p, raíz del árbol
         * @return Altura del árbol
         * 
         * @note Complejidad de tiempo: O(n)
         * @note Complejidad de espacio: O(h) 
        */
        int getHeight(NodeBST<T>* p){
            if (p == nullptr){
                return 0;
            }
            int leftHeight = getHeight(p->left);
            int rightHeight = getHeight(p->right);
            return max(leftHeight, rightHeight) + 1;
        }
    
        /**
         * @brief getLevel
         * 
         * Encontrar el nivel de un nodo dado; es decir, en que nivel se encuentra el nodo a buscar.
         * 
         * @param NodeBST<T>* p, raíz del árbol
         * @param T value, valor del nodo a buscar
         * @return Nivel del nodo en el árbol, o -1 si no se encuentra
         * 
         * @note Complejidad de tiempo: O(h)
         * @note Complejidad de espacio: O(h)
        */
        int getLevel(NodeBST<T>* p, T value){
            if(p == nullptr){
                return -1;
            }
            if(p->info == value){
                return 0;
            }
            if(value < p->info){
                int leftLevel = getLevel(p->left, value);
                if(leftLevel != -1){
                    return leftLevel + 1;
                }
            }
            else{
                int rightLevel = getLevel(p->right, value);
                if(rightLevel != -1){
                    return rightLevel + 1;
                }
            }
            return -1;
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
        bool ancestors(T info){
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

        /**
         * @brief Desplegar datos almacenados en el BST
         * 
         * Esta función desplegará cada uno de los datos almacenados en el BST
         * dependiendo del parámetro de entrada: 1. Preorder 2. Inorder 3. Postorder 4. getLevel by getLevel
         * 
         * @param[in] int decision, número de 1 a 4 con el tipo de recorrido
         * @return impresión de los elementos en el orden que se haya escogido
         * 
         * @note Complejidad de tiempo: O(h)
         * @note Complejidad de espacio: O(h)
        */
        void visit(int decision){
            switch(decision){
                case 1:
                    cout << endl << "PreOrder" << endl;
                    preOrder(root);
                    break;
                case 2:
                    cout << endl << "InOrder" << endl; 
                    inOrder(root);
                    break;
                case 3:
                    cout << endl << "PostOrder" << endl;
                    postOrder(root);
                    break;
                case 4:
                    cout << endl << "Level By Level" << endl;
                    levelByLevel(root);
                    break;
                default:
                    cout << "Opción no válida" << endl;
                    break;
            }
        }

        /**
         * @brief Mandar a llamar el método para obtener altura
         * 
         * Este método no recibe ningun parámetro pero se encarga de mandar a llamar 
         * la función que cálcula la altura del árbol con la raíz del mismo.
         * 
         * @return Altura del árbol 
         * 
         * @note Complejidad de tiempo: O(n)
         * @note Complejidad de espacio: O(h)
        */
        int height(){
            return getHeight(root);
        }

        /**
         * @brief Mandar a llamar el método para obtener altura 
         * 
         * Este método solamente recibe el valor a buscar y luego manda a llamar a la función getLevel para encontrar en que nivel
         * se encuentra el dato buscado. 
         * 
         * @param[in] T dato, dato mandado a llamar
         * @return En que nivel se encuentra el dato buscado
         * 
         * @note Complejidad de tiempo: O(h)
         * @note Complejidad de espacio: O(h)
        */
        int whatLevelAmI(T dato){
            return getLevel(root, dato);
        }

        
        /**
         * @brief Lee datos de un archivo de registro y los almacena en el BST.
         * 
         * Esta función abre el archivo "bitacoraelb.txt" y lee cada línea de registro. Luego, procesa y extrae
         * los datos relevantes de cada línea, como año, mes, día, hora, minuto, segundo, dirección IP y mensaje.
         * Utiliza estos datos para crear un objeto Linea y lo inserta al final de la lista doblemente enlazada.
         * 
         * @return Nada se devuelve explícitamente ya que la función modifica la lista en su lugar.
         * 
         * @note Complejidad de tiempo: O(N) - Donde N es la cantidad de líneas en el archivo de registro.
         * @note Complejidad de espacio: O(1) - Se asignan recursos para almacenar los datos de cada línea, pero no se utiliza memoria adicional significativa.
        */
        void read() {
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
                insertar(linea);
            }
            file.close();
        }
};

//Arbol biselado

int main(){
    BST<Linea> * arbol = new BST<Linea>();
    arbol -> read();
    return 0;
}