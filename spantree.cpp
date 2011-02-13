//ache; Cheng, Allan

#include <algorithm>
#include <iostream>
using namespace std;
#include "classes.h"

void readInput();
void kruskal(roads *a, int numofroads, int numofcities);
void qSort(roads *a, const int left, const int right);
void swap(roads& a, roads& b);

int main()
{
  cout << "<?xml version=\"1.0\"?>\n<country>\n";
  readInput();
  cout << "</country>\n";

  return 0;
} //main()

void readInput()
{
  int numCity, numRoad, i, cityA, cityB;

  cin >> numCity >> numRoad;

  roads oRoad[numRoad];
  for (i = 0; i < numRoad; i++)
  {
    cin >> cityA >> cityB >> oRoad[i].length;    
    oRoad[i].cityA = min(cityA, cityB);
    oRoad[i].cityB = max(cityA, cityB);
  }
  qSort(oRoad, 0, numRoad-1);

  kruskal(oRoad, numRoad, numCity);

//  for (i = 0; i < numRoad; i++)
//    cout<<oRoad[i].cityA<<" "<<oRoad[i].cityB<< " "<<oRoad[i].length
//    << " " << /*oRoad[i].priority <<*/ endl;
}

void kruskal(roads *a, int numofroads, int numofcity)
{
  int i, root1, root2;
  linkedlist<roads> MST;
  linkedlist<region> roots;
  linkedlist<roads> regions[numofcity];
  sets link(numofcity);

  for (i = 0;/* i <= numofcity &&*/ i < numofroads; i++) //eliminate cycles
  {
    root1 = link.CFind(a[i].cityA);
    root2 = link.CFind(a[i].cityB);

    if (root1 != root2)
    {
      MST.insert(a[i]);
      link.SUnion(root1, root2);
    }
  }


    for (i = 0; i < MST.listsize(); i++)
    {
      roads temp = MST.get(i);
      root1 = link.CFind(temp.cityA);
      regions[root1].insert(temp);

      if (!roots.find(root1))
      {
        region* temp3 = new region;
        temp3->root = root1;
        roots.insert(*temp3);
      }
    }

    for (i = 0; i < roots.listsize(); i++)
    {
      region temp2 = roots.get(i);
      roots.insertRSize(regions[temp2.root].listsize(), i);
//      cout << regions[temp2.root].listsize() << endl;
    }


    roots.qSort(0, roots.listsize()-1);
/*  for (i = 0; i < numofcity; i++)
    cout << a[i].cityA << "'s root = " << link.CFind(a[i].cityA)
         << " and " << a[i].cityB << "'s root = " << link.CFind(a[i].cityB)
         << endl;
  cout << "size = " << MST.listsize() << endl; */
  for (i = roots.listsize()+MST.listsize(); i < numofcity; i++)
    cout << "<region>\n</region>\n";

  for (i = 0; i < roots.listsize(); i++)
  {
    cout << "<region>\n";
    regions[roots.getRRoot(i)].printRoad();
    cout << "</region>\n";
  }
}

void qSort(roads *a, const int left, const int right) //quicksort from book
{ //sorts the input by length
  if(left<right)
  {
    int i = left,
        j = right + 1,
        pivot = a[left].length;

    do
    {
      do 
      {
        i++;
        if (a[i].length == pivot && i != left)
        {
//          cout << a[i].length << endl;
//          cout << "a[i].cityA = " << a[i].cityA << " b = " << a[i].cityB 
//               << " pivotA = " << a[left].cityA << " pB = " << a[left].cityB
//               << endl;
          if (min(a[i].cityA, a[i].cityB) > min(a[left].cityA, a[left].cityB))
            swap(a[i], a[left]);

          else
            if (max(a[i].cityA, a[i].cityB) > max(a[left].cityA, a[left].cityB))
              swap(a[i], a[left]);
        }
      } while (a[i].length < pivot);
      do
      { 
        j--;
        if (a[j].length == pivot && j != left)
        {
//          cout << "a[j].cityA = " << a[j].cityA << " b = " << a[j].cityB 
//               << " pivotA = " << a[left].cityA << " pB = " << a[left].cityB
//               << endl;
//          cout << a[j].length << endl;
          if (min(a[j].cityA, a[j].cityB) > min(a[left].cityA, a[left].cityB))
            swap(a[j], a[left]);
          else
            if (max(a[j].cityA, a[i].cityB) > max(a[left].cityA, a[left].cityB))
              swap(a[j], a[left]);
        } 
      } while (a[j].length > pivot);
      if (i<j) swap(a[i], a[j]);
    } while (i < j);

    swap(a[left], a[j]);

    qSort(a, left, j-1);
    qSort(a, j+1, right);
  }
}

void swap(roads& a, roads& b)
{
  roads temp; 
  temp = a; a = b; b = temp;
}
