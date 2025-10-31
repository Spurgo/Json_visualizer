#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <variant>
#include <map>
#include <vector>
#include <memory> //serve per smartpointer
//commento per test

using namespace std;

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
            //cout << "skip_space() nxt = " << nxt << endl;
        }

        string parse_string(){
            char curr = file_content.peek();
            string s;
            //cout << "parse_string() curr = " << curr << endl;
            if(curr == '"' || curr == ',' || curr == ':'){
                skip_char();
            }
            if(curr == '{' || curr == '['){
                value_parsing();
            }
            getline(file_content, s, '"');
            return s;
        }

        void skip_char(){
            file_content.get();
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
            skip_space();
            string key = parse_string();
            skip_char();
            skip_space();
            string value = parse_string();
            cout << key << ", " << value << endl;
            if (file_content.peek() == ','){
                file_content.get();
                object_parsing();
            }
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
            else if(!file_input.is_open()){ //verifica se file aperto correttamente
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