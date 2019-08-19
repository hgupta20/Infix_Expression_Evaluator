class ArrayList
  {
  private:
    int *arr;
    int size;
    int current;

  public:
    void init()
      {
          size = 2;
          current = 0;
          arr = new int[size];
      }
    bool isEmpty()
      {
        if(current == 0)
          {
            return true;
          }
        return false;
      }
    void push(int data)
      {
        if (current == size)
          {
            //Grow the array
            int *temp = new int[size+2];
            size = size +2;
            for(int i = 0;i<size-2;i++)
            {
              temp[i] = arr[i];
            }
            delete arr;
            arr = temp;
          }
        arr[current]=data;
        current++;
      }
    int top()
    {
      return arr[current-1];
    }
    void pop()
    {
      current--;
      arr[current]=0;
    }
    void reset()
    {
      size = 2;
      current =0;
      int *temp = new int[2];
      delete arr;
      arr = temp;
    }
  };
