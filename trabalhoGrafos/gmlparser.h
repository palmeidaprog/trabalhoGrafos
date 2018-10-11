#ifndef GMLPARSER_H
#define GMLPARSER_H

#include <fstream>
#include "no.h"

using std::ofstream;
using std::string;
using std::endl;
using grafos::No;

namespace grafos {
class GMLParser {
    No **listaAdj;
    int tamanho;
    const string arquivo;


    void adicionaEspacos(ofstream &out, int n) {
        while(n--) {
            out << " ";
        }
    }

    /*void vm() {
        JavaVM *vm;
        JNIEnv *env;
        JavaVMInitArgs = JNI_VERSION_1_2;
        vm_args.nOptions = 0;
        vm_args.ignoreUnrecognized = 1;

        // Construct a VM
        jint res = JNI_CreateJavaVM(&vm, (void **)&env, &vm_args);

        // Construct a String
        jstring jstr = env->NewStringUTF("Hello World");

        // First get the class that contains the method you need to call
        jclass clazz = env->FindClass("java/lang/String");

        // Get the method that you want to call
        jmethodID to_lower = env->GetMethodID(clazz, "toLowerCase",
                                          "()Ljava/lang/String;");
        // Call the method on the object
        jobject result = env->CallObjectMethod(jstr, to_lower);

        // Get a C-style string
        const char* str = env->GetStringUTFChars((jstring) result, NULL);

        printf("%s\n", str);

        // Clean up
        env->ReleaseStringUTFChars(jstr, str);

        // Shutdown the VM.
        vm->DestroyJavaVM();

    }*/
public:
    GMLParser(No **listaAdj, int tamanho, const string &arquivo) :
        listaAdj(listaAdj), tamanho(tamanho), arquivo(arquivo) { }

    string gerarGML() {
       ofstream out(arquivo, ofstream::out);
       out << "graph" << endl << "[" << endl;
       int esp = 2;

       // colocando os vertices no GML
       for(int i = 0; i < tamanho; i++) {
           adicionaEspacos(out, esp);
           out << "node" << endl;
           adicionaEspacos(out, esp);
           out << "[" << endl;
           adicionaEspacos(out, esp+1);
           out << "id " << i << endl;
           adicionaEspacos(out, esp+1);
           out << "label \"Verice " << i << "\"" << endl;
           adicionaEspacos(out, esp);
           out << "]" << endl;
       }

       // colocando as arestas no GML
       for(int i = 0; i < tamanho; i++) {
           No *lido = listaAdj[i];
           while(lido != nullptr) {
               adicionaEspacos(out, esp);
               out << "edge" << endl;
               adicionaEspacos(out, esp);
               out << "[" << endl;
               adicionaEspacos(out, esp+1);
               out << "source " << i << endl;
               adicionaEspacos(out, esp+1);
               out << "target " << lido->getVertice() << endl;
               adicionaEspacos(out, esp+1);
               out << "label \"Edge " << i << "to " << lido->getVertice() <<
                      "\"" << endl;
               adicionaEspacos(out, esp);
               out << "]" << endl;

               lido = lido->getProx();
           }
       }

       out.close();
       return arquivo;
    }




};
}

#endif // GMLPARSER_H
