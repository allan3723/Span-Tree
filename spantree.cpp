//ache; Cheng, Allan

#include <algorithm>
#include <iostream>
using namespace std;
#include "classes.h"

void readInput();
void kruskal(roads *a, int numofroads, int numofcities);
void qSort(roads *a, const int left, const int right);
void qSort2(roads *a, const int left, const int right);
void qSort3(roads *a, const int left, const int right);
void swap(roads& a, roads& b);
bool minimum = false, maximum = false;

int main()
{
  cout << "<?xml version=\"1.0\"?>\n<country>\n";
  readInput();
  cout << "</country>\n";

  return 0;
} //main()

void readInput()
{
  int numCity, numRoad, i, j, k, l, cityA, cityB;

  cin >> numCity >> numRoad;

  roads oRoad[numRoad];
  for (i = 0; i < numRoad; i++)
  {
    cin >> cityA >> cityB >> oRoad[i].length;    
    oRoad[i].cityA = min(cityA, cityB);
    oRoad[i].cityB = max(cityA, cityB);
  }

  qSort(oRoad, 0, numRoad-1);

  if (minimum)
    for (i = 0; i < numRoad-1; i++)
    {
      if (oRoad[i].length == oRoad[i+1].length)
      {
        j = i;
        while(i < numRoad-1 && oRoad[i].length == oRoad[i+1].length) i++;

        qSort2(oRoad, j, i);
        minimum = false;

        if (maximum)
          for (k = j; k < i; k++)
          {
            if (oRoad[k].cityA == oRoad[k+1].cityA)
            {
              l = k;
              while (k < i && oRoad[k].cityA == oRoad[k+1].cityA) k++;

              qSort3(oRoad, l, k);
              maximum = false;
            }
          }
      }
    }

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
      roads* temp = new roads;
      *temp = MST.get(i);
      root1 = link.CFind(temp->cityA);
      regions[root1].insert(*temp);

      if (!roots.find(root1))
      {
        region temp4;
        temp4.root = root1;
        roots.insert(temp4);
      }
    }

    for (i = 0; i < roots.listsize(); i++)
    {
      region temp2 = roots.get(i);
      roots.insertRSize(regions[temp2.root].listsize(), i);
//cout << regions[temp2.root].listsize() << endl;
    }

    roots.qSort(0, roots.listsize()-1);

    if (roots.getFlag())
      for (i = 0; i < roots.listsize()-1; i++)
      {
        if (roots.getRSize(i) == roots.getRSize(i+1))
        {
          int j = i;
          while (i < roots.listsize()-1 && roots.getRSize(i) == roots.getRSize(i+1)) i++;
          
          roots.qSort2(j, i);
          roots.setFlag(false);
        }
      }

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
        if (a[i].length == pivot)
          minimum = true;
      } while (a[i].length < pivot);
      do
      { 
        j--;
        if (a[j].length == pivot)
          minimum = true;
      } while (a[j].length > pivot);
      if (i<j) swap(a[i], a[j]);
    } while (i < j);

    swap(a[left], a[j]);

    qSort(a, left, j-1);
    qSort(a, j+1, right);
  }
}


void qSort2(roads *a, const int left, const int right) //quicksort from book
{ 
  if(left<right)
  {
    int i = left,
        j = right + 1,
        pivot = a[left].cityA;

    do
    {
      do 
      {
        i++;
        if (a[i].cityA == pivot)
          maximum = true;
      } while (a[i].cityA < pivot);
      do
      { 
        j--;
        if (a[j].cityA == pivot)
          maximum = true;
      } while (a[j].cityA > pivot);
      if (i<j) swap(a[i], a[j]);
    } while (i < j);

    swap(a[left], a[j]);

    qSort2(a, left, j-1);
    qSort2(a, j+1, right);
  }
}


void qSort3(roads *a, const int left, const int right) //quicksort from book
{ 
  if(left<right)
  {
    int i = left,
        j = right + 1,
        pivot = a[left].cityB;

    do
    {
      do i++; while (a[i].cityB < pivot);
      do j--; while (a[j].cityB > pivot);
      if (i<j) swap(a[i], a[j]);
    } while (i < j);

    swap(a[left], a[j]);

    qSort3(a, left, j-1);
    qSort3(a, j+1, right);
  }
}

void swap(roads& a, roads& b)
{
  roads temp; 
  temp = a; a = b; b = temp;
}
