#include "pqueue.h"
using namespace std;

int priorityFn1(const Patient &patient);
int priorityFn2(const Patient &patient);

int main()
{
    PQueue queue1(priorityFn1);
    PQueue queue2(priorityFn1);

    Patient patient1("Sam", 1, 37, 79,  36, 133, 75);
    Patient patient2("Liz", 5, 37, 98, 26,  70, 100);
    Patient patient3("Nick", 2, 37, 85, 34, 125, 85);
    Patient patient4("Eva", 4, 37, 95,  22, 115, 95);
    queue1.insertPatient(patient3);
    queue1.insertPatient(patient1);
    queue1.insertPatient(patient2);
    queue1.insertPatient(patient4);
    cout << "queue1 dump after inserting 4 patients (Nick, Sam, Liz, Eva):" << endl;
    queue1.dump();
    cout << endl;

    Patient patient5("John", 3, 39, 91, 27, 115, 110);
    Patient patient6("Mia", 3,  33, 93, 28, 118, 98);
    queue2.insertPatient(patient5);
    queue2.insertPatient(patient6);
    cout << "\nqueue2 dump after inserting 2 patients (John, Mia):" << endl;
    queue2.dump();
    cout << endl;
    cout << queue2.numPatients() << endl;

    try
    {
        queue1.mergeWithQueue(queue2);

    }
    catch (const domain_error& e)
    {
        cerr << e.what() << endl;
    }
    cout << endl << "Contents of queue1 after merging with queue2:\n";
    queue1.printPatientQueue();
    cout << endl;
    cout << "Dump queue1 after merging with queue2:\n";
    queue1.dump();
    cout << endl;

    PQueue queue3(priorityFn2);
    queue3.insertPatient(patient3);
    queue3.insertPatient(patient4);
    cout << "\nqueue3 dump after inserting 2 patients (Nick, Eva):" << endl;
    queue3.dump();
    cout << endl;
    cout << "Attempt to merge queue3 with itself" << endl;
    queue3.mergeWithQueue(queue3);

    cout << "Attempt to merge queue3 with queue1 which has a different priority" << endl;
    try
    {
        queue3.mergeWithQueue(queue1);

    }
    catch (const domain_error& e)
    {
        cerr << e.what() << endl;
    }

    cout << "Attempt to get the next patient of empty queue4" << endl;
    PQueue queue4(priorityFn2);
    try
    {
        queue4.getNextPatient();

    }
    catch (const domain_error& e)
    {
        cerr << e.what() << endl;
    }
    cout << endl;

    cout << "************************************************\n"
            "*          Copy Constructor Tests!             *\n"
            "************************************************\n";
    cout << "Attempt to copy empty queue4 into queue5" << endl;
    PQueue queue5(queue4);
    cout << "Copy queue1 into queue6 and dump contents of both queues" << endl;
    PQueue queue6(queue1);
    cout << "Dump queue1 contents" << endl;
    queue1.dump();
    cout << endl;
    cout << "Dump queue6 contents" << endl;
    queue6.dump();
    cout << endl;

    cout << "\n***************************************************\n"
            "*          Assignment Operator Tests!             *\n"
            "***************************************************\n";
    cout << "Attempt to copy empty queue4 into queue7" << endl;
    PQueue queue7(priorityFn1);
    queue7 = queue4;
    cout << "Copy queue1 into queue1 and dump contents of both queues" << endl;
    queue7 = queue1;
    cout << "Dump queue1 contents" << endl;
    queue1.dump();
    cout << endl;
    cout << "Dump queue7 contents" << endl;
    queue7.dump();
    cout << endl;

    cout << "Contents of queue1 after changing the priority function to priorityFn2:\n";
    queue1.setPriorityFn(priorityFn2);
    queue1.printPatientQueue();
    cout << queue1.numPatients() << endl;
    cout << "\nDump queue1 after changing the priority function to priorityFn2:\n";
    queue1.dump();
    cout << endl;

    cout << endl << "Contents of queue1 after changing the priority function back to priorityFn1:\n";
    queue1.setPriorityFn(priorityFn1);
    queue1.printPatientQueue();
    cout << "\nDump queue1 after changing the priority function back to priorityFn1:\n";
    queue1.dump();
    cout << endl;

    return 0;
}

int priorityFn1(const Patient&patient) {
    int pri = 5;
    if ((patient.getOxygen()<80 && (patient.getRR() > 35 || patient.getRR() < 8)) ||
        (patient.getHR() > 130 && patient.getBP() < 80))
        pri = 1;
    else if (((patient.getOxygen() >= 80 && patient.getOxygen() <= 89) &&
              (patient.getRR() >= 31 && patient.getRR() <= 35)) ||
             (patient.getTemperature() >= 40 || patient.getTemperature() <= 32))
        pri = 2;
    else if ((patient.getOxygen() >= 90 && patient.getOxygen() <= 94) &&
             (patient.getRR() >= 26 && patient.getRR() <= 30))
        pri = 3;
    else if ((patient.getOxygen() >= 95 && patient.getOxygen() <= 97) &&
             (patient.getRR() >= 21 && patient.getRR() <= 25))
        pri = 4;
    else
        pri = 5;
    return pri;
}

int priorityFn2(const Patient&patient) {
    //priority only based on triage
    //triage is set by a health care professional
    return patient.getTriage();
}