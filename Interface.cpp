#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <variant>
#include <map>
#include <vector>
#include <memory> //serve per smartpointer

using namespace std;

//apro file json non importa come
//parso il file
//cercare parentesi e suddivisioni 
//prendere i nomi delle classi
//merda grafica

struct DataType;
using JsonArray = vector<DataType>;
using JsonObject = map<string, DataType>;

using NestedJsonArray = unique_ptr<JsonArray>; //utilizzo unique pointer per interrompere la catenza di dipendenze  tra JsonArray/Object e la struct data
using NestedJsonObject = unique_ptr<JsonObject>;

struct DataType
        {
            //variant al posto di enum, stessa cosa ma meglio in teoria. per assegnare il dato corretto. in teoria non serve perchè necessito solo dei nomi dei campi
            //tengo per indicare magari i tipi di dati presenti all'interno
            variant<
                nullptr_t,
                bool, 
                int, 
                float, 
                double, 
                string, 
                NestedJsonArray, 
                NestedJsonObject
            > data;
        };

class JsonParser{
    private:
        string file_json_dir; //directory file 
        ifstream file_input; //file
        stringstream file_content; //contenuto json 

        void skip_space(){
            char nxt = file_content.peek();
            while(isspace(nxt)){ //consumo tutti gli spazi bianchi presenti fino al raggiungimento del carattere
                file_content.get();
                nxt = file_content.peek();
            }
            cout << nxt << endl;
        }

        string parse_string(){
            return "";
        }

        void skip_char(){
            
        }

        void value_parsing(){
            //.peak() per verificare carattere successivo
            //isspace() per verificare se carattere attuale è spazio
            //.get() per ottenere carattere attuale

            char next_ch = file_content.peek();
            if(next_ch == '{'){
                file_content.get();
                object_parsing();
            } 
            else if(next_ch == '['){
                array_parsing();
            }
        }

        void object_parsing(){
            cout << "object parsing called" << endl;
            skip_space();
            string key = parse_string();

        }

        void array_parsing(){
            cout << "array parsing called" << endl;
            skip_space();
        }

    public:
        //costruttore
        JsonParser(const string& path) : file_json_dir(path){
            file_input.open(file_json_dir);

            if(file_input.bad()){ //serve a verificare non ci siano errori in lettura
                cout << "Errore in lettura del file Dio Maiale" << endl;
            }
            else if(!file_input.is_open()){ //verificare se file aperto correttamente
                cout << "File non aperto correttamente" << endl;
            }
            else{
                cout << "File aperto correttamente" << endl;
                file_content << file_input.rdbuf(); //intero contenuto del file json all'interno del buffer. stringa da analizzare per capire struttura del file
            }
        }

        ~JsonParser(){
            file_input.close(); //chiusura file
            file_content.clear(); //pulizia buffer 
            file_json_dir = ""; //pulizia directory
            cout << "File chiuso correttamente e dati puliti" << endl;
        }

        //funzioni per analizzare il file
        // se [ allora inizio array 
        // se { allora oggetto, quindi usare map con chiave valore

        //ora prossima cosa da fare, usare funzioni isspace, .get() e .peek() per consumare e scorrere i caratteri
        //necessario cercare di fare il parsing solo di n blocco di dati all'interno del json, evitando di scorrerlo per intero dato che mi interessa la struttura 
        //e non il contenuto effettivo del file 

        void json_parser(){
            value_parsing();
        }
        
};

int main(){

    // il nostro file
    JsonParser jsonParser("/home/tullio/Desktop/C++/jsonGraphics/funny.json");
    jsonParser.json_parser();
    return 0;
}