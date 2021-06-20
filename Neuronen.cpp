
#include <iostream>
#include <vector>
#include <ctime>
#include <array>
#include <memory>
#include <fstream>
#include <string>
#include <cmath> 

#define RUHEPOTENTIAL -60
#define SCHWELLENPOTENTIAL -55
#define REFRAKTAERZEIT 10 
#define VERSTAERKEN 1
#define INPUT 1
#define const sss
#define INIT 1 

using namespace std;

class Neuron {
private:
    double aktionspotential; //das Aktionspotential des neurons
    double schwellenpotential; //das Schwellenpotential des Neurons
    double erregung; //welche Erregung erfährt das Neuron durch die Umliegenden?
    double ruhepotential; //das Ruhepotetial des Neurons
    double abweichung; //Abweichung zu Zwecken der Realistik
    double Membranpotential; //das aktuelle Membranpotential des Neurons
    double refraktaerzeit; //die refraktaerzeit des Neurons
    double bias; //für Lerneffetke
    int verstaerken; //hat das Neuron bereits gefeuert? 
public:
    Neuron();
    double getSchwellenpotential(); //welches Schwellenpotential hat das Neuron?
    double getErregung();
    double getAbweichung();
    double getMembranpotential();
    void setMembranpotential(int&); //Membranpotenital setzen 
    void refraktaerZeit(); //Refraktaer Zeit initiieren 
    int aktion(); //aktionspotential aussendne, also eine Zahl an das Cluster geben vi
    void run(); //main loop des Neuronen
    void aufnehmen(double); //aufnehmen eines Signals
    bool validieren(); //Validierung der Signaluebertragung
    void setRefraktaerzeit(); //die Refraktaerzeti fetslegen welche das Neuron abwarten soll
    int getRefraktaerzeit(); //die Refraktaerzeti bestimmen
    void biasErhoehen(); //für Lernen
    int getVerstaerkung();
    void setVerstaerkung(int); 
};
class cluster {
private:
    vector<Neuron> meineNeuronen; //die Neuronen welche das cluster Objekt managed
    vector<vector<int>> verbindungen; //die Verbindungen der Neuronen untereinander
    vector<vector<int>> interaktionen; //die Ausgabedaten
    int anzahlNeuronen; //die Anzahl an Neuronen 
public:
    cluster(int&);
    void run(); //die main Methode des Clusters
    void transmit(); //eine Erregung übertragen
    void getNeuronen(); //Neuronen ausgeben
    void ausgabe(); //finale Daten ausgeben 
    void init(); 
};
class globalClock {
private:
    int counter;
    int timeIntervall;
public:
    globalClock();
    int getTime();//get the time on the clock
    void setTime(int);//set the time
    void increment(); //increment clock
};

int main() {
    srand(time(0)); //seed the random number
    int anzahlNeuronen; //die Anzahl an zu simulierenden NEuronen 
    cout << "Wie viele Neuroenen sollen simulaiert werden (maximal 1000) ? ";
    cin >> anzahlNeuronen;
    if (anzahlNeuronen > 999) {
        cout << "Mit diesem Programm koennen leider nicht mehr als 1000 Neuronen sinnvoll simuliert werden, bitte versucben Sie es erneut." << endl;
        exit(0); 
    }
    cluster meinCluster = cluster(anzahlNeuronen); //instantiate myVCluster Obejct with 10 Neurons 
    string simulieren; //flag for simulation 
    int durchgaenge; //number of runs
    int numberOfNeurons; //the number of neurons the user wants to simualte
    srand(time(0)); //seed random number genrator
    //cout << "Soll die Simualtion mit " << anzahlNeuronen << " gestartet werden (Y)? "; //ask user for input 
    //cout << "Soll die Simualtion mit " << anzahlNeuronen << " gestartet werden (Y)? "; //ask user for input 
    //cin >> simulieren; //take input from user: Simualte Yes/No? 
    //if (simulieren =="y") { //Simulation
        cout << "Wie viele Durchgaenge sollen gemacht werden? "; 
        cin >> durchgaenge; //take number of runs
        //cout << "Wie viele Neuronen sollen simuliert werden? ";
        //cin >> numberOfNeurons; 
        for (int a = 0; a < durchgaenge; a++) { //run cluster as many times, as the user wants 
            meinCluster.run();
        }
        cout << "Die Simulation ist abgeschlossen" << endl;
        meinCluster.ausgabe();
        cout << "Vielen Dank"; 
    //}
    return 0;
}
Neuron::Neuron() {
    int bias = rand() % 10 + 1; //ein Bias zur Simulaion unterschiedlciher Anzahl von Ionenkanälen 
    int valid = rand()%2 +1; //valid für Korrektur auf und ab 
    valid = valid > 1 ? 1 : -1; //Berechnung aus einer zufälligen Zahl 
    schwellenpotential = SCHWELLENPOTENTIAL + valid * bias; //Setzen des Schwellenpotentials
    erregung = 0; //initialisieren der Erregung mit 0
    ruhepotential = RUHEPOTENTIAL; //Initialisierien des Ruhepotentilas
    Membranpotential = ruhepotential; //initialisieren des Membranpotentials
    refraktaerzeit = 0;
    verstaerken = 0; 
}
double Neuron::getErregung() {
    return erregung; 
}
double Neuron::getAbweichung() {
    return abweichung; 
}
double Neuron::getMembranpotential() {
    return Membranpotential; 
}
double Neuron::getSchwellenpotential() {
    return schwellenpotential; 
}
void Neuron::setMembranpotential(int &wert) {
    Membranpotential = wert; 
}
void Neuron::refraktaerZeit() {
    //warte bis die Refraktaerzeit vorbei ist wird vom CLuster üernommen
    if (refraktaerzeit != 0) { //wenn die refraktaerzeit nicht Null ist, soll sie um eins reduziert werden 
        refraktaerzeit--; 
    }
}
int Neuron::aktion() {
    //sende ein Aktionspotential aus
    int lokalesAktionsPotential = rand() % 10 + 1;
    int sign = rand() % 2;
    lokalesAktionsPotential = sign % 2 == 0 ? 1 * lokalesAktionsPotential : -0.5 * lokalesAktionsPotential; //die Potentiale sind zufällig EPSP oder IPSP
    //cout << "Mein generiertes Aktionspotential ist: " << aktionspotential << endl;
    //cout << "Meine Erregung ist: " << erregung << " bei einem Schwellenpotential von " << schwellenpotential <<  endl; 
    if (erregung > schwellenpotential) {
        return lokalesAktionsPotential;
    }
    else{
        return 0; 
    }
}
void Neuron::run() {
    //manage runtime most of the managment is anayways done by the clister, if necesseary this funciton will be called, but ten threads is too much....
    //cout << "Mein Membranpotentila ist : " << Membranpotential << "und meine Erregung ist: " << erregung << endl; 
    if (erregung > 0) { //falls die Erregung zu hoch ist, soll diese gesenkt werden 
        erregung--;
        Membranpotential--; //wenn die Erregung nicht null ist, kann das embranpotential nicht auf dem Normalwert liegen 
    }
    else if (erregung <0) { //falls die Erregung zu klein ist, soll diese erhöht werden 
        erregung++;
        Membranpotential++; //wenn die Erregung nicht Null ist, kann das Membranpotential nicht gleich dem Ruhepotential sein 
    }
    refraktaerZeit(); 
}
void Neuron::aufnehmen(double Signalstaerke) {
    //cout << "Das Signal hat die Staerke (bei der Aufnahme) : " << Signalstaerke << endl; 
    Membranpotential = Membranpotential + Signalstaerke;
    erregung = erregung + Signalstaerke;
    if (erregung > schwellenpotential) {
        int temp = aktion(); 
    }
    else {
        validieren(); 
    }
}
bool Neuron::validieren() {
    return true; 
}
void Neuron::setRefraktaerzeit() {
    refraktaerzeit = 3; 
}
int Neuron::getRefraktaerzeit() {
    return refraktaerzeit; 
}
void Neuron::biasErhoehen() {
    if (VERSTAERKEN == 1) {
        bias++;
    }
}
int Neuron::getVerstaerkung() {
    return verstaerken;
}
void Neuron::setVerstaerkung(int v) {
    verstaerken = v;
}
cluster::cluster(int &anzahlN) {
    //initialisieren des CLusters
    //das Cluster bekommt am Anfang 10 Neuronen ==> nun eine beliebige Zahl
    anzahlNeuronen = anzahlN;
    int uebergabe = rand() % 10 + 1; 
    for (int a = 0; a < anzahlNeuronen; a++) { // can not scale...
        meineNeuronen.push_back(Neuron());
    }
    for (int a = 0; a < anzahlNeuronen; a++) { //initialisieren aller Verbindungen
        vector<int> neueGruppe;
        for (int a1 = 0; a1 < 4; a1++) {
            neueGruppe.push_back(0);
        }
        verbindungen.push_back(neueGruppe);
    }
    for (int a = 0; a < anzahlNeuronen; a++){//es muss über jedes Neuron iterriert werden 
        for (int a1 = 0; a1 < 4; a1++) {//es sollen vier Verbindungen pro Neuron festgelegt werden
            bool flag = false; //wurde das zuordnen beendet?
            int temp = anzahlNeuronen;
            array<bool,1000> availiableNumbers; //ueberprueft einzigaritgkeit
            int counterTrue; //counts how often true appears in flags
            availiableNumbers.fill(true); //auf true initialisieren ==> alle Zahlen sind verfuegbar 
            while (!flag) {
                int neueVerbindung = rand() % anzahlNeuronen ; // die Zhahlen dürfen nur bei 0 starten, weil die Vektor Indexe bei Null starten 
                //for (int a2 = 0; a2 < anzahlNeuronen; a2++) { //die Verindung sollen einzigartig sien, deswegen uss iterriert werden um sicherzustellen
                    //das die Verbindungen wiriklich einzigartig sind, im Prinzip wird also geprüft ob diese neue Verbindung bereits vorkommt und wenn nicht
                    //wird sie aufgeschrieben und es geht weiter
                    if (availiableNumbers.at(neueVerbindung)) { // wenn das Array an der Stelle true ist, muss diese Verbindung noch frei sein
                        verbindungen.at(a).at(a1) = neueVerbindung;
                        availiableNumbers.at(neueVerbindung) = false; //die Zahl ist niht mehr verfuegbar
                        flag = true; 
                    }
                //}
            }
        }
    }
    /*for (int a = 0; a < 10; a++) {
        for (int a1 = 0; a1 < 4; a1++) {b
            cout << verbindungen.at(a).at(a1) << " ";
        }
        cout << endl; 
    }*/ //debug 
    //int uebergabe = rand() % 10 + 1;s
    uebergabe = rand() % 10 + 1;
    uebergabe = rand() % 2 == 1 ? 1 * uebergabe : -1 * uebergabe;
    uebergabe = uebergabe * 1.0; //convert to douvl
    if (INPUT == 1) {
        uebergabe = sin(rand() % 90);
    }
    //cout << "Ich uebergebe hier den Wert " << uebergabe << endl; sdj
    meineNeuronen.at(0).aufnehmen(uebergabe);

    //cout << "Die Initialisierung wurde abgeschlossen." << endl;
}
void cluster::run() {
    //runtime der Simulation
    vector<int> ausgabe;
    globalClock myClock;
    vector<double> inputs; 
    ausgabe.push_back(interaktionen.size()); //die Größe des Vektoras entspricht der ANzahl an durchlaufen durchgängen
    //cout << " es gab biher: " << ausgabe.at(0) << " Interaktionen" << endl; 
    for (int a = 0; a < anzahlNeuronen; a++) { //initialisieren des Vektrs 
        ausgabe.push_back(0); 
    }
    for (int a = 0; a < anzahlNeuronen; a++) {
        inputs.push_back(sin(a)); 
    }
    //cout << "Die Anzahl an Interkationen ist nun: " << ausgabe.at(0) << endl; 
    for (int a = 0; a < anzahlNeuronen; a++) {
        int signal = meineNeuronen.at(a).aktion();
        //cout << "Ein Beispiel fuer ein Signal ist: " << meineNeuronen.at(a).aktion() << endl; 
        meineNeuronen.at(a).run(); //Membranpotential anpassen, sodass es imemr das Ruhepotential anstrebt
        if (meineNeuronen.at(a).getMembranpotential() > meineNeuronen.at(a).getSchwellenpotential() && meineNeuronen.at(a).getRefraktaerzeit() == 0) { //das feuern eines Neurons
            meineNeuronen.at(verbindungen.at(a).at(0)).aufnehmen(signal); //das Neuron darf nur feuern, wenn die Refraktaerzeuit gleich null ist, sie also vorbei ist 
            //das Neuron welches als erstes in den Verbindugen steht, nimmt ein Signal mit der viertel Signalstaerke auf
            //cout << "Die Nummer der Verbindung ist: " << verbindungen.at(a).at(1) << endl;
            //cout << "Neuron Nummer " << a << "wird gerade betrachtet" << endl;
            //cout << "Dabei wird die Konnektion zu 1 betrachtet...." << endl;
            //cout << "Bei der Aussendung hat das Signal die Staerke: " << signal << endl; 
            meineNeuronen.at(verbindungen.at(a).at(1)).aufnehmen(signal); 
            meineNeuronen.at(verbindungen.at(a).at(2)).aufnehmen(signal);
            meineNeuronen.at(verbindungen.at(a).at(3)).aufnehmen(signal);
            meineNeuronen.at(a).setRefraktaerzeit(); //das Neuron geht für 10 Iterationen in Refrataerzeit
            ausgabe.at(a+1) = 1; // das Neuron a hat gefeuert, es muss na Stelle a+1 geschriben werden, weil an Stelle 0 die Iterationsnummer steht
            if (meineNeuronen.at(a).getVerstaerkung() == 1) {
                meineNeuronen.at(a).biasErhoehen();
                meineNeuronen.at(a).setVerstaerkung(0);
            }
            meineNeuronen.at(a).setVerstaerkung(1); 
        }
        else {
            ausgabe.at(a+1) = 0; // es muss an Stelle a+1 geschrieben werden, weil an Stelle 0 die Iterationsnummer stet, aber a wird gebraucht 
        }
        myClock.increment();
        if (INIT == 1) {
            init();
            //cout << "Init" << endl; 
        }
        if (INPUT == 1) {
            meineNeuronen.at(0).aufnehmen(inputs.at(a));
        }
    }
    interaktionen.push_back(ausgabe);

}
void cluster::transmit() {
    //ein Signal übertragen ==>x wird von der Runtime uebernommen 
}
void cluster::getNeuronen() {
    cout << meineNeuronen.size() << endl;
}
void cluster::ausgabe() {
    //ausgabe der Daten
    ofstream writeFile; //write File 
    ifstream readFile; //read File

    string line;
    string ausgabe; 
    writeFile.open("output.txt");
    for (int a = 0; a < interaktionen.size(); a++) {
        for (int a1 = 0; a1 < anzahlNeuronen+1; a1++) {
            writeFile << interaktionen.at(a).at(a1) << " "; 
        }
        writeFile << endl;
    }
    writeFile.close();
    readFile.open("output.txt"); //opens the same file 
    if (readFile.is_open()) {
        while(getline(readFile,line)) {
            cout << line << endl; 
            //cout << "Doing something..." << endl
            //cout << "linr" <<  line << endl; 
        }
    }
    else {
        cout << "Failed to open file" << endl; 
    }
    readFile.close();
    for (long a = 0; a < 100000000; a++) {}
}
void cluster::init() {
    srand(time(0)); 
    for (int a = 0; a < anzahlNeuronen; a++) {//es muss über jedes Neuron iterriert werden 
        for (int a1 = 0; a1 < 4; a1++) {//es sollen vier Verbindungen pro Neuron festgelegt werden
            bool flag = false; //wurde das zuordnen beendet?
            int temp = anzahlNeuronen;
            array<bool, 1000> availiableNumbers; //ueberprueft einzigaritgkeit
            int counterTrue; //counts how often true appears in flags
            availiableNumbers.fill(true); //auf true initialisieren ==> alle Zahlen sind verfuegbar 
            while (!flag) {
                int neueVerbindung = rand() % anzahlNeuronen; // die Zhahlen dürfen nur bei 0 starten, weil die Vektor Indexe bei Null starten 
                //for (int a2 = 0; a2 < anzahlNeuronen; a2++) { //die Verindung sollen einzigartig sien, deswegen uss iterriert werden um sicherzustellen
                    //das die Verbindungen wiriklich einzigartig sind, im Prinzip wird also geprüft ob diese neue Verbindung bereits vorkommt und wenn nicht
                    //wird sie aufgeschrieben und es geht weiter
                if (availiableNumbers.at(neueVerbindung)) { // wenn das Array an der Stelle true ist, muss diese Verbindung noch frei sein
                    verbindungen.at(a).at(a1) = neueVerbindung;
                    availiableNumbers.at(neueVerbindung) = false; //die Zahl ist niht mehr verfuegbar
                    flag = true;
                }
                //}
            }
        }
    }
}
globalClock::globalClock() {

}
int globalClock::getTime() {
    return counter; 
}
void globalClock::setTime(int time) {
    counter = time;
}
void globalClock::increment() {
    counter++; 
}

