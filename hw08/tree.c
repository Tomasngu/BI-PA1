#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


typedef struct TResult{
    struct TResult * m_Next;
    int              m_ID;
    char           * m_Name;
} TRESULT;
#endif /* __PROGTEST__ */
typedef int (*Comp)(const void *, const void *);
typedef struct TPerson{
    int m_ID;
    char * m_Name;
    struct TPerson * m_Parent1;
    struct TPerson * m_Parent2;
} TPERSON;
typedef struct TDatabase{
    TPERSON * m_Data;
    int m_Count;
    int m_Cap;
} TDATABASE;
typedef struct TAncestor{
    int m_ID;
    char *m_Name;
}TANCESTOR;
typedef struct TAncArray{
    TANCESTOR * m_Array;
    int m_Count;
    int m_Cap;
} TANCARRAY;

void initAll (TDATABASE * db ){
    db->m_Data = NULL;
    db->m_Count = 0;
    db->m_Cap = 0;
}
void doneAll (TDATABASE * db ){
    for(int i = 0; i< db->m_Count;i++){
        free(db->m_Data[i].m_Name);
    }
    free(db->m_Data);
}
int inDatabase(TDATABASE * db, int ID){
    for(int i = 0; i < db->m_Count; i++){
        if(db->m_Data[i].m_ID == ID){
            return 1;
        }
    }
    return 0;
}
int databaseIndex(TDATABASE * db, int ID){
    for(int i = 0; i < db->m_Count; i++){
        if(db->m_Data[i].m_ID == ID){
            return i;
        }
    }
    return 0;
}
void addParent1(TDATABASE * db, int ID){
    if(ID != 0){
        int index = databaseIndex(db,ID);
        db->m_Data[db->m_Count].m_Parent1 = &db->m_Data[index];
    }else{
        db->m_Data[db->m_Count].m_Parent1 = NULL;
    }
}
void addParent2(TDATABASE * db, int ID){
    if(ID != 0){
        int index = databaseIndex(db,ID);
        db->m_Data[db->m_Count].m_Parent2 = &db->m_Data[index];
    }else{
        db->m_Data[db->m_Count].m_Parent2 = NULL;
    }
}
void printDatabase(TDATABASE *db);
int addPerson ( TDATABASE * db, int id, const char * name, int id1, int id2 ){
    // I/O checks
    if(inDatabase(db,id) || id == 0) return 0;
    if(id1 != 0 && !inDatabase(db,id1)) return 0;
    if(id2 != 0 && !inDatabase(db,id2)) return 0;
    if(id1 != 0 && id2 != 0 && id1 == id2 ) return 0;

    // Reallocation
    if(db->m_Count>=db->m_Cap){
        db->m_Cap = db->m_Cap*2 + 500000;
        db->m_Data = (TPERSON *) realloc(db->m_Data, db->m_Cap*sizeof(*(db->m_Data)));
    }
    db->m_Data[db->m_Count].m_ID = id;
    db->m_Data[db->m_Count].m_Name = (char *) malloc((strlen(name)+1)*sizeof(char));
    strcpy(db->m_Data[db->m_Count].m_Name, name);
    addParent1(db,id1);
    addParent2(db,id2);
    db->m_Count++;
    //printf("pocet lidi je %d\n",db->m_Count);
    // printDatabase(db);
    return 1;

}
void printDatabase(TDATABASE *db){
    for(int i = 0; i < db->m_Count; i++){
            printf("%d %s\n",db->m_Data[i].m_ID,db->m_Data[i].m_Name);
            if(db->m_Data[i].m_Parent1 != NULL){
                printf("Rodic1 je %d %s, ",db->m_Data[i].m_Parent1->m_ID,db->m_Data[i].m_Parent1->m_Name);
            }
            if(db->m_Data[i].m_Parent2 != NULL){
                printf("Rodic2 je %d %s\n ",db->m_Data[i].m_Parent2->m_ID,db->m_Data[i].m_Parent2->m_Name);
            }
    }
}
void printAncArray(TANCARRAY *ancestors){
    for(int i = 0; i < ancestors->m_Count; i++){
        printf("%d %s\n",ancestors->m_Array[i].m_ID,ancestors->m_Array[i].m_Name);
    }
}
/*___________________________________________________________________________*/
void addPertoAnc(TANCARRAY * ancestors, TPERSON person){
    if(ancestors->m_Count>=ancestors->m_Cap){
        ancestors->m_Cap = ancestors->m_Cap*2 + 10;
        ancestors->m_Array = (TANCESTOR *) realloc(ancestors->m_Array, ancestors->m_Cap*sizeof(*(ancestors->m_Array)));
    }
    ancestors->m_Array[ancestors->m_Count].m_ID = person.m_ID;
    ancestors->m_Array[ancestors->m_Count].m_Name = (char *)malloc((strlen(person.m_Name)+1)*sizeof(char));
    strcpy(ancestors->m_Array[ancestors->m_Count].m_Name,person.m_Name);
    ancestors->m_Count++;
}
void recAncestors(TDATABASE *db, TANCARRAY *ancestors, TPERSON person){
    if(person.m_Parent1 != NULL){
        addPertoAnc(ancestors,*person.m_Parent1);
        recAncestors(db,ancestors,*person.m_Parent1);
    }
    if(person.m_Parent2 != NULL){
        addPertoAnc(ancestors,*person.m_Parent2);
        recAncestors(db,ancestors,*person.m_Parent2);
    }
    return;

}
TANCARRAY findAncestors(TDATABASE * db,int id){
    TANCARRAY ancestors = {};
    int index = databaseIndex(db,id);
    recAncestors(db,&ancestors,(db->m_Data[index]));
    return ancestors;
}
int cmpIDs (const TANCESTOR *aPtr,const TANCESTOR *bPtr){
    int a = aPtr->m_ID, b = bPtr->m_ID;
    return a == b ? 0 : (a < b ? -1 : 1);
}
void addAncToAnc(TANCARRAY * ancestors, TANCESTOR person){
    if(ancestors->m_Count>=ancestors->m_Cap){
        ancestors->m_Cap = ancestors->m_Cap*2 + 10;
        ancestors->m_Array = (TANCESTOR *) realloc(ancestors->m_Array, ancestors->m_Cap*sizeof(*(ancestors->m_Array)));
    }
    ancestors->m_Array[ancestors->m_Count].m_ID = person.m_ID;
    ancestors->m_Array[ancestors->m_Count].m_Name = (char *)malloc((strlen(person.m_Name)+1)*sizeof(char));
    strcpy(ancestors->m_Array[ancestors->m_Count].m_Name,person.m_Name);
    ancestors->m_Count++;
}
TANCARRAY removeDup(TANCARRAY *ancestors){
    qsort(ancestors->m_Array,ancestors->m_Count, sizeof(TANCESTOR), (Comp) cmpIDs);
    TANCARRAY noDup = {};
    for(int i = 0; i < ancestors->m_Count-1 ;i++){
        if(ancestors->m_Array[i].m_ID != ancestors->m_Array[i+1].m_ID){
            addAncToAnc(&noDup, ancestors->m_Array[i]);
        }
    }
    if(ancestors->m_Array[ancestors->m_Count -1 ].m_ID != ancestors->m_Array[ancestors->m_Count -2 ].m_ID) addAncToAnc(&noDup,ancestors->m_Array[ancestors->m_Count -1 ]);
    return noDup;
}
void freeAncestors(TANCARRAY * ancestors){
    for(int i = 0; i < ancestors->m_Count;i++){
        free(ancestors->m_Array[i].m_Name);
    }
    free(ancestors->m_Array);
}
void printLinkedList(TRESULT * l){
    while( l ){
        printf("Node %d %s\n", l->m_ID, l->m_Name);
        l = l->m_Next;
    } 
}
TRESULT * ancestors ( TDATABASE * db, int id ){
    TANCARRAY ancestors = findAncestors(db,id);
    if(!inDatabase(db,id) || ancestors.m_Count == 0) {
        freeAncestors(&ancestors);
        return NULL;
    } 
    // printAncArray(&ancestors);
    TANCARRAY noDup = removeDup(&ancestors);
    freeAncestors(&ancestors);
    // printAncArray(&noDup);
    // printf("pocet unikatnich predku %d\n",noDup.m_Count);
    // TRESULT * l = (TRESULT *) malloc(sizeof(*l));
    TRESULT * head = NULL;
    TRESULT * tail = NULL;
    for(int i = 0; i < noDup.m_Count;i++){
        TRESULT * node = (TRESULT *) malloc(sizeof(*node));
        node->m_ID = noDup.m_Array[i].m_ID;
        node->m_Name = (char *)malloc( (strlen(noDup.m_Array[i].m_Name)+1)*sizeof(char) );
        strcpy(node->m_Name,noDup.m_Array[i].m_Name);
        node -> m_Next = NULL;
        if(i == 0){
            head = node;
            tail = node;
            continue;
        }

        tail->m_Next = node;
        tail = node;
    }
    freeAncestors(&noDup);
    return head;
}
TANCARRAY mergeAncestors(TANCARRAY * anc1, TANCARRAY * anc2){
    TANCARRAY merged = {};
    for(int i = 0; i < anc1->m_Count; i++){
        addAncToAnc(&merged, anc1->m_Array[i]);
    }
    for(int i = 0; i < anc2->m_Count; i++){
        addAncToAnc(&merged, anc2->m_Array[i]);
    }
    return merged;
}
TANCARRAY findDuplicates(TANCARRAY *ancestors){
    qsort(ancestors->m_Array,ancestors->m_Count, sizeof(TANCESTOR), (Comp) cmpIDs);
    TANCARRAY noDup = {};
    for(int i = 0; i < ancestors->m_Count-1 ;i++){
        if(ancestors->m_Array[i].m_ID == ancestors->m_Array[i+1].m_ID){
            addAncToAnc(&noDup, ancestors->m_Array[i]);
        }
    }
    return noDup;
}

TRESULT * commonAncestors  ( TDATABASE * db, int id1, int id2 ){
    TANCARRAY ancestors1 = findAncestors(db,id1);
    TANCARRAY ancestors2 = findAncestors(db,id2);
    if(!inDatabase(db,id1) || !inDatabase(db,id2) || ancestors1.m_Count == 0 || ancestors2.m_Count == 0) {
        freeAncestors(&ancestors1);
        freeAncestors(&ancestors2);
        return NULL;
    }
    TANCARRAY noDup1 = removeDup(&ancestors1);
    TANCARRAY noDup2 = removeDup(&ancestors2);
    freeAncestors(&ancestors1);
    freeAncestors(&ancestors2);
    TANCARRAY merged = mergeAncestors(&noDup1,&noDup2);
    freeAncestors(&noDup1);
    freeAncestors(&noDup2);
    // printAncArray(&merged);
    TANCARRAY noDup = findDuplicates(&merged);
    freeAncestors(&merged);
    if(noDup.m_Count == 0){
        freeAncestors(&noDup);
        return NULL;
    }

    //printf("Spolecni predci:\n");
    // printf("Pocet predku: %d\n", noDup.m_Count);
    // printAncArray(&noDup);
    
    TRESULT * head = NULL;
    TRESULT * tail = NULL;
    for(int i = 0; i < noDup.m_Count;i++){
        TRESULT * node = (TRESULT *) malloc(sizeof(*node));
        node->m_ID = noDup.m_Array[i].m_ID;
        node->m_Name = (char *)malloc( (strlen(noDup.m_Array[i].m_Name)+1)*sizeof(char) );
        strcpy(node->m_Name,noDup.m_Array[i].m_Name);
        node -> m_Next = NULL;
        if(i == 0){
            head = node;
            tail = node;
            continue;
        }

        tail->m_Next = node;
        tail = node;
    }
    freeAncestors(&noDup);
    return head;
    
}
void freeResult ( TRESULT * res ){
    while(res){
        TRESULT * tmp = res->m_Next;
        free(res->m_Name);
        free(res);
        res = tmp;
    }
    res = NULL;
}

#ifndef __PROGTEST__

int main ( int argc, char * argv []){
    char      name[100];
  TDATABASE a, b;
  TRESULT * l;

  initAll ( &a );
  assert ( addPerson ( &a, 1, "John", 0, 0 ) == 1 );
  strncpy ( name, "Jane", sizeof ( name ) );
  assert ( addPerson ( &a, 2, name, 0, 0 ) == 1 );
  assert ( addPerson ( &a, 3, "Caroline", 0, 0 ) == 1 );
  assert ( addPerson ( &a, 4, "Peter", 0, 0 ) == 1 );
  assert ( addPerson ( &a, 5, "George", 1, 2 ) == 1 );
  assert ( addPerson ( &a, 6, "Martin", 1, 2 ) == 1 );
  assert ( addPerson ( &a, 7, "John", 3, 4 ) == 1 );
  assert ( addPerson ( &a, 8, "Sandra", 3, 4 ) == 1 );
  assert ( addPerson ( &a, 9, "Eve", 1, 2 ) == 1 );
  assert ( addPerson ( &a, 10, "Douglas", 1, 4 ) == 1 );
  strncpy ( name, "Phillipe", sizeof ( name ) );
  assert ( addPerson ( &a, 11, name, 6, 8 ) == 1 );
  strncpy ( name, "Maria", sizeof ( name ) );
  assert ( addPerson ( &a, 12, name, 5, 8 ) == 1 );
  l = ancestors ( &a, 11 );
  assert ( l );
  assert ( l -> m_ID == 1 );
  assert ( ! strcmp ( l -> m_Name, "John" ) );
  assert ( l -> m_Next );
  assert ( l -> m_Next -> m_ID == 2 );
  assert ( ! strcmp ( l -> m_Next -> m_Name, "Jane" ) );
  assert ( l -> m_Next -> m_Next );
  assert ( l -> m_Next -> m_Next -> m_ID == 3 );
  assert ( ! strcmp ( l -> m_Next -> m_Next -> m_Name, "Caroline" ) );
  assert ( l -> m_Next -> m_Next -> m_Next );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_ID == 4 );
  assert ( ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_ID == 6 );
  assert ( ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Martin" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_ID == 8 );
  assert ( ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Sandra" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  freeResult ( l );
  assert ( ancestors ( &a, 3 ) == NULL );
  assert ( ancestors ( &a, 13 ) == NULL );
  l = commonAncestors ( &a, 11, 12 );
  assert ( l );
  assert ( l -> m_ID == 1 );
  assert ( ! strcmp ( l -> m_Name, "John" ) );
  assert ( l -> m_Next );
  assert ( l -> m_Next -> m_ID == 2 );
  assert ( ! strcmp ( l -> m_Next -> m_Name, "Jane" ) );
  assert ( l -> m_Next -> m_Next );
  assert ( l -> m_Next -> m_Next -> m_ID == 3 );
  assert ( ! strcmp ( l -> m_Next -> m_Next -> m_Name, "Caroline" ) );
  assert ( l -> m_Next -> m_Next -> m_Next );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_ID == 4 );
  assert ( ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_ID == 8 );
  assert ( ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Sandra" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  freeResult ( l );
  l = commonAncestors ( &a, 10, 9 );
  assert ( l );
  assert ( l -> m_ID == 1 );
  assert ( ! strcmp ( l -> m_Name, "John" ) );
  assert ( l -> m_Next == NULL );
  freeResult ( l );
  assert ( commonAncestors ( &a, 7, 6 ) == NULL );
  l = commonAncestors ( &a, 7, 10 );
  assert ( l );
  assert ( l -> m_ID == 4 );
  assert ( ! strcmp ( l -> m_Name, "Peter" ) );
  assert ( l -> m_Next == NULL );
  freeResult ( l );
  assert ( addPerson ( &a, 13, "Quido", 12, 11 ) == 1 );
  l = ancestors ( &a, 13 );
  assert ( l );
  assert ( l -> m_ID == 1 );
  assert ( ! strcmp ( l -> m_Name, "John" ) );
  assert ( l -> m_Next );
  assert ( l -> m_Next -> m_ID == 2 );
  assert ( ! strcmp ( l -> m_Next -> m_Name, "Jane" ) );
  assert ( l -> m_Next -> m_Next );
  assert ( l -> m_Next -> m_Next -> m_ID == 3 );
  assert ( ! strcmp ( l -> m_Next -> m_Next -> m_Name, "Caroline" ) );
  assert ( l -> m_Next -> m_Next -> m_Next );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_ID == 4 );
  assert ( ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_ID == 5 );
  assert ( ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "George" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_ID == 6 );
  assert ( ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Martin" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_ID == 8 );
  assert ( ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Sandra" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_ID == 11 );
  assert ( ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Phillipe" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_ID == 12 );
  assert ( ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Maria" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  freeResult ( l );
  l = commonAncestors ( &a, 9, 12 );
  assert ( l );
  assert ( l -> m_ID == 1 );
  assert ( ! strcmp ( l -> m_Name, "John" ) );
  assert ( l -> m_Next );
  assert ( l -> m_Next -> m_ID == 2 );
  assert ( ! strcmp ( l -> m_Next -> m_Name, "Jane" ) );
  assert ( l -> m_Next -> m_Next == NULL );
  freeResult ( l );
  assert ( addPerson ( &a, 1, "Francois", 0, 0 ) == 0 );
  initAll ( &b );
  assert ( addPerson ( &b, 10000, "John", 0, 0 ) == 1 );
  assert ( addPerson ( &b, 10000, "Peter", 0, 0 ) == 0 );
  assert ( addPerson ( &b, 20000, "Jane", 10000, 0 ) == 1 );
  assert ( addPerson ( &b, 30000, "Maria", 10000, 10000 ) == 0 );
  assert ( addPerson ( &b, 40000, "Joe", 10000, 30000 ) == 0 );
  assert ( addPerson ( &b, 50000, "Carol", 50000, 20000 ) == 0 );
  assert ( addPerson ( &b, 12, "Maria", 20000, 10000 ) == 1 );
  l = ancestors ( &a, 12 );
  assert ( l );
  assert ( l -> m_ID == 1 );
  assert ( ! strcmp ( l -> m_Name, "John" ) );
  assert ( l -> m_Next );
  assert ( l -> m_Next -> m_ID == 2 );
  assert ( ! strcmp ( l -> m_Next -> m_Name, "Jane" ) );
  assert ( l -> m_Next -> m_Next );
  assert ( l -> m_Next -> m_Next -> m_ID == 3 );
  assert ( ! strcmp ( l -> m_Next -> m_Next -> m_Name, "Caroline" ) );
  assert ( l -> m_Next -> m_Next -> m_Next );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_ID == 4 );
  assert ( ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_ID == 5 );
  assert ( ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "George" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_ID == 8 );
  assert ( ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Sandra" ) );
  assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  freeResult ( l );
  l = ancestors ( &b, 12 );
  assert ( l );
  assert ( l -> m_ID == 10000 );
  assert ( ! strcmp ( l -> m_Name, "John" ) );
  assert ( l -> m_Next );
  assert ( l -> m_Next -> m_ID == 20000 );
  assert ( ! strcmp ( l -> m_Next -> m_Name, "Jane" ) );
  assert ( l -> m_Next -> m_Next == NULL );
  freeResult ( l );
  assert ( ancestors ( &a, 20000 ) == NULL );
  assert ( commonAncestors ( &b, 7, 10 ) == NULL );
  doneAll ( &b );

  doneAll ( &a );

  return 0;
}
#endif /* __PROGTEST__ */