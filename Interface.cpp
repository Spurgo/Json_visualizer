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

using NestedJsonArray = unique_ptr<JsonArray>;
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
                cout << file_content.str() << endl; //print di conferma apertura corretta
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

        void printing_test(){
            cout << file_content.rdbuf() << endl;
        }
};

int main(){

    // il nostro file
    JsonParser jsonParser("/home/tullio/Desktop/C++/jsonGraphics/funny.json");
    jsonParser.printing_test();
    return 0;
}