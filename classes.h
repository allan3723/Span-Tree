//ache; Cheng, Allan

class roads
{
  public:
    roads() {}

    int cityA, cityB, length;
};

class region
{
  public:
    region() {}

    int root, size;
};

template <class T>
class node
{
  public:
    node() {}
    T data;
    node<T> *next;
};


class sets
{
  public:
    sets(int numberOfElements)
    {
      n = numberOfElements;
      parent = new int[n];

      for (int i = 0; i < n; i++) //fill
        parent[i] = -1; 
    }

    void SUnion(int root, int combined)
    {
      parent[combined] = root;
    }
  
    int SFind(int i)
    {
      while(parent[i]>=0)
        i = parent[i];
      return i;    
    }

    void WUnion(int i, int j)
    {
      int temp = parent[i] + parent[j];
      if (parent[i] > parent[j])
      {
        parent[i] = j;
        parent[j] = temp;
      }

      else
      {
        parent[j] = i;
        parent[i] = temp;
      }
    }

    int CFind(int i)
    {
      int r, s;
      for (r = i; parent[r] >= 0; r = parent[r])
        while (i != r)
        {
          s = parent[i];
          parent[i] = r;
          i = s;
        }
      return r;
    }

  private:
    int *parent;
    int n;
};


template<class T>
class linkedlist // + graph
{
  public:
  
  linkedlist()
  {
    size = 0;
    flag = false;
  }

  void insert(T data)
  {
    if (size == 0)
    {
      head = new node<T>;
      head->data = data;
      head->next = NULL;
      current = head;
      size = 1;
    }
    else
    {
      temp = new node<T>;
      temp->data = data;
      temp->next = NULL;
      current->next = temp;
      current = temp;
      size++;
    }
  }

  void insertRSize(int size, int pos)
  {
    temp = new node<T>;
    temp = head + (pos * (head->next - head));
    (temp->data).size = size;
  }

  void printRSize()
  {
    temp = new node<T>;
    temp = head;
    while (temp != NULL)
    {
      cout << temp->data.root << " " << temp->data.size << endl;
      temp = temp->next;
    }
  }

  int listsize() {return size;}

  bool find(int data)
  {
    if (size == 0)
      return false;

    temp = new node<T>;
    temp = head;

    while (temp != NULL)
    {
      if ((temp->data).root == data)
      {
//        delete temp; ///
        return true;
      }

      temp = temp->next;
    }
    delete temp; ////
    return false;
  }

  T get(int pos)
  {
    temp = new node<T>;
    temp = head + (pos * (head->next - head));
    return temp->data;
  }

  int getRSize(int pos)
  {
    temp = new node<T>;
    temp = head+(pos * (head->next - head));
    return temp->data.size;
  }

  int getRRoot(int pos)
  {
    temp = new node<T>;
    temp = head+(pos*(head->next - head));
    return temp->data.root;
  }

  void swapR(int i, int j) //specifically for region
  {
    node<region>* node2 = new node<T>;
    node<region>* node1 = new node<T>;
    temp = new node<T>;
    node1 = head+(i*(head->next - head));
    node2 = head+(j*(head->next - head));

    temp->data.root = node1->data.root; temp->data.size = node1->data.size;
    node1->data.root = node2->data.root; node1->data.size = node2->data.size;
    node2->data.root = temp->data.root; node2->data.size = temp->data.size;

    delete temp;
  }

  void qSort(const int left, const int right) //quick sort for region
  {
    if (left < right)
    {
      int i = left,
          j = right + 1,
          pivot = getRSize(left);

      do
      {
        do 
        {
          i++; 
          if (getRSize(i) == getRSize(left) && i != left)
          {
            setFlag(true);
          }
        } while(getRSize(i) < pivot && i < right+1);
        do 
        {
          j--; 
          if (getRSize(j) == getRSize(left) && j != left)
            setFlag(true);
        } while(getRSize(j) > pivot && j >= i);

        if (i < j) swapR(i, j);
      } while(i < j);
      swapR(left, j);

      qSort(left, j-1);
      qSort(j+1, right);
    } //if
  }

  void qSort2(const int left, const int right) //quick sort for region
  {
    if (left < right)
    {
      int i = left,
          j = right + 1,
          pivot = getRRoot(left);

      do
      {
        do i++; while(getRRoot(i) < pivot && i < right+1);
        do j--; while(getRRoot(j) > pivot && j >= i);
        if (i < j) swapR(i, j);
      } while(i < j);
      swapR(left, j);

      qSort2(left, j-1);
      qSort2(j+1, right);
    } //if
  }

  void print()
  {
    if (size == 0)
      return;
    temp = new node<T>;
    temp = head;
    while (temp != NULL)
    {
      cout << temp->data << endl;;
      temp = temp->next;
    } 
    delete temp; 
  }

  void printRoad()
  {
    temp = new node<roads>;
    temp = head;
    while (temp != NULL)
    {
      cout << "<road>" << temp->data.cityA << " " 
           << temp->data.cityB << " " << temp->data.length  
           << "</road>\n";

      temp = temp->next;
    }
  }
  
  void setFlag(bool something) {flag = something;}

  bool getFlag() {return flag;} 
 
  private:
    node<T> *head, *temp, *current;
    int size;
    bool flag;
};

